#include "face_identification.h"

#include <image_serde.h>
#include <image_draw.h>
#include <logging.h>
#include <fs.h>

#define INSIGHT_FEATURE_SIZE 512 //check = c*h*w
#define FACE_IDENTITY_THRESH 0.1
#define TRACKING_AREA 0.9
#define THRESHOLD_UNKNOWN_FEATURES_SIMILARITY_FACEID 0.6 //4

using namespace std;

FaceIdentification::FaceIdentification(const string &feature_data_dir,
                                 shared_ptr<FaceDetection> face_det,
                                 shared_ptr<FaceFeatureExtraction> feature_extract)
{
  face_detection_ = face_det;
  feature_extract_ = feature_extract;
  mFeatureDir = feature_data_dir;
#ifdef _WINDOWS
  mFeaturePath = feature_data_dir + "\\face_feature.bin";
#else
  mFeaturePath = feature_data_dir + "/face_feature.bin";
#endif
  m_register_num = 0;

  log_enabled_ = getenv("LOG_FACE_ID") != nullptr;
  if (log_enabled_)
  {
    cout << "[" << log_prefix_ << "] log enabled" << endl;
  }
}

FaceIdentification::~FaceIdentification()
{

  saveFeatures();
  for (int i = 0; i < m_register_num; i++)
  {
    for (auto it = m_face_feats[i].vec_feats.begin(); it != m_face_feats[i].vec_feats.end(); ++it)
    {
      delete[] * it;
      *it = NULL;
    }
  }

  stopped_ = true;
  if (identify_thread_.joinable())
  {
    new_input_mtx_.lock();
    new_input_ = true;
    new_input_cv_.notify_one();
    new_input_mtx_.unlock();

    identify_thread_.join();
  }
}

bool FaceIdentification::initialize()
{

  if (!is_dir(mFeatureDir)) {
    if (!make_dirs(mFeatureDir, 0755)) {
      cout << "[Error]: fail to create data directory for FaceIdentification" << endl;
      return false;
    }
    cout << "[Info]: create FaceIdentification data directory (" << mFeatureDir << ")" << endl;
  }

  if (!face_detection_->initialize())
    return false;
  if(!feature_extract_->initialize())
    return false;

  loadFeatures();

  cout << "FaceIdentification initialization done!" << endl;

  return true;
}

void FaceIdentification::set_fusion_callback(void(Fusion::*cb)(const PersonIdMsg&), Fusion* fusion) {
  notify_fusion_ = bind(cb, fusion, placeholders::_1);

  identify_thread_ = thread([&]() {
    while (!stopped_)
    {
      unique_lock<mutex> lck(new_input_mtx_);
      while (true)
      {
        if (new_input_cv_.wait_for(lck, chrono::seconds(1), [this] { return new_input_; }))
        {
          break;
        }
      }
      if (stopped_)
        return;

      do_identify(new_input_msg_);
      notify_fusion_(new_input_msg_);
      new_input_ = false;
    }
  });

  fusion_callback_set = true;
}

PersonIdMsg FaceIdentification::identify(const PersonIdMsg &msg) {
  PersonIdMsg result = msg;
  do_identify(result);
  return result;
}

void FaceIdentification::identify_async(const PersonIdMsg &msg)
{

  if (!fusion_callback_set) {
    cout << "[Error]: fusion callback in FaceIdentification is NOT set!" << endl;
    return;
  }

  lock_guard<mutex> lck(new_input_mtx_);
  if (new_input_)
  {
    cout << "[Warn-FI] still processing previous face_id" << endl;
    return;
  }
  new_input_msg_ = msg;
  new_input_ = true;
  new_input_cv_.notify_one();
}

void FaceIdentification::do_identify(PersonIdMsg &msg)
{
  cv::Mat image = image_from_pb(msg.image());
  cv::Mat depth; //not used now

  _LOG_MSG("do_identify", "entry", "input_msg", msg);

  PersonIdMsg result = msg;

  result.clear_persons();

  int width = image.cols;
  int height = image.rows;

  lock_guard<mutex> lk(global_mtx_);
  for (int i = 0; i < msg.persons_size(); i++)
  {
    Person *person = msg.mutable_persons(i);

    // Ingore the person already has a name
    if (person->name() != "")
      continue;

    //_LOG("person size: %d * %d = %d\n", person->w, person->h, person->w * person->h);
    if (person->x() < 0)
      person->set_x(0);
    if (person->y() < 0)
      person->set_y(0);
    if (person->x() + person->w() > image.cols)
      person->set_w(image.cols - person->x());
    if (person->y() + person->h() > image.rows)
      person->set_h(image.rows - person->y());

    if (checkLastSave(person) && (force_identify_face == false))
    {
      Person *p = result.add_persons();
      *p = *person;
      continue;
    }

    cv::Rect body_crop_rect = cv::Rect(person->x(), person->y(), person->w(), person->h());
    if (!normBox(body_crop_rect, cv::Size(width, height)))
    {
      _LOG("Invalid detection box: (%d,%d,%d,%d)", body_crop_rect.x, body_crop_rect.y, body_crop_rect.width, body_crop_rect.height);
      continue;
    }

    //Detect face rect, landmarks  and the feature
    cv::Mat crop = image(body_crop_rect);
    vector<cv::Point2d> ldmks;
    cv::Rect face_rect;
    auto p_curr_feats = identifyOne(image, body_crop_rect, ldmks, face_rect);

    if (p_curr_feats == nullptr)
      continue;

    auto max_similarity = computeMaxSimilarity(p_curr_feats);

    cv::Mat face = crop(face_rect);

    m_face_confidence_estimator.SetFaceID(max_similarity.first);
    //confidence estimation part
    float conf = m_face_confidence_estimator.FaceCMPredict(crop, depth, face, ldmks, this->m_fcm_feats);
    _LOG("%s: conf %f\n", (max_similarity.first >= 0 ? m_face_feats[max_similarity.first].name : "N/A"), conf);
    if (conf >= FACE_IDENTITY_THRESH)
    {
      if (max_similarity.second < THRESHOLD_UNKNOWN_FEATURES_SIMILARITY_FACEID)
      {
        person->set_name("");
      }
      else
      {
        person->set_name(m_face_feats[max_similarity.first].name);
      }

      person->set_face_from_detection(true);
      person->mutable_face()->set_x(face_rect.x + person->x());
      person->mutable_face()->set_y(face_rect.y + person->y());
      person->mutable_face()->set_w(face_rect.width);
      person->mutable_face()->set_h(face_rect.height);
      person->set_similarity(max_similarity.second);
      person->set_confidence(conf);

      person->set_source(FACE);
      Person *p = result.add_persons();
      *p = *person;
    }

    if (p_curr_feats != nullptr)
    {
      delete[] p_curr_feats;
      p_curr_feats = nullptr;
    }
  }
  force_identify_face = false;
  saveLast = result;

  cv::Mat image_copy;
  image.copyTo(image_copy);
  drawImageResult(result, image_copy, "identifying", cv::Scalar(0, 0, 0));
  set_drawn_image(image_copy);

}



bool FaceIdentification::normBox(cv::Rect &rect, cv::Size sz)
{
  int width = sz.width;
  int height = sz.height;
  int x1 = max(0, int(rect.x));
  int y1 = max(0, int(rect.y));
  int x2 = min(width - 1, int(rect.x + rect.width - 1));
  int y2 = min(height - 1, int(rect.y + rect.height - 1));
  if ((x1 >= x2) || (y1 >= y2))
  {
    return false;
  }
  rect.x = x1;
  rect.y = y1;
  rect.width = x2 - x1;
  rect.height = y2 - y1;
  return true;
}

void FaceIdentification::queryPersonList(vector<string> &all)
{
  for (size_t i = 0; i < m_face_feats.size(); i++)
  {
    all.push_back(string(m_face_feats[i].name));
  }
}

bool FaceIdentification::registerNew(const PersonIdMsg &msg)
{
  cv::Mat image = image_from_pb(msg.image());
  cv::Mat depth; //not used

  int width = image.cols;
  int height = image.rows;

  cv::Mat image_for_drawn;
  image.copyTo(image_for_drawn);

  lock_guard<mutex> lk(global_mtx_);
  for (int i = 0; i < msg.persons_size(); i++)
  {
    const Person &person = msg.persons(i);

    if (person.name() == "")
    {
      _LOG("  skipped null person\n");
      continue;
    }

    _LOG("Need to register person name is %s\n", person.name().c_str());
    cv::Rect body_crop_rect = cv::Rect(person.x(), person.y(), person.w(), person.h());
    if (!normBox(body_crop_rect, cv::Size(width, height)))
    {
      _LOG("Invalid detection box: (%d,%d,%d,%d)", body_crop_rect.x, body_crop_rect.y, body_crop_rect.width, body_crop_rect.height);
      continue;
    }

    //Detect face rect, landmarks  and the feature
    cv::Mat crop = image(body_crop_rect);
    vector<cv::Point2d> ldmks;
    cv::Rect face_rect;
    auto p_curr_feats = identifyOne(image, body_crop_rect, ldmks, face_rect);

    if (p_curr_feats == nullptr)
      continue;

    // draw landmark on image
    for (int i = 0; i < 5; i++)
    {
      cv::Point cvPt(ldmks[i].x + person.x(), ldmks[i].y + person.y());
      cv::circle(image_for_drawn, cvPt, 3, cv::Scalar(0, 0, 255), -1);
    }

    // dray face bbox and person name
    cv::Rect face_rect_ori(body_crop_rect.x+face_rect.x, body_crop_rect.y+face_rect.y,
                           face_rect.width, face_rect.height);
    cv::rectangle(image_for_drawn, face_rect_ori, cv::Scalar(0, 255, 0), 1);
    cv::putText(image_for_drawn, person.name(),
      cv::Point(face_rect_ori.tl().x, face_rect_ori.tl().y-5),
      cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 255, 0), 1);

    //extract FCM feature for confidence
    cv::Mat face = crop(face_rect);

    FaceCMFeature FaceCMFeatureTemplate;
    m_face_confidence_estimator.ExtractFCMFeature(crop, depth, face, ldmks, FaceCMFeatureTemplate);

    int id = findPerson(person.name().c_str());

    auto max_similarity = computeMaxSimilarity(p_curr_feats);
    if (id < 0)
    {
      //rename the person which was auto registered
      while (max_similarity.second > 0.5)
      {
        id = max_similarity.first;
        deletePerson(m_face_feats[id].name);
        max_similarity = computeMaxSimilarity(p_curr_feats);
      }
      _LOG("create new person\n");
      addPerson(person.name(), &p_curr_feats, FaceCMFeatureTemplate);
    }
    else
    { //direct add to feature array
      _LOG("add to exsiting\n");
      addFeatureToPerson(id, &p_curr_feats, FaceCMFeatureTemplate);
    }

    if (p_curr_feats != nullptr)
    {
      delete[] p_curr_feats;
      p_curr_feats = nullptr;
    }
  }
  cv::putText(image_for_drawn, "register", cv::Point(5, 25), cv::FONT_HERSHEY_SIMPLEX, 1.0,
              cv::Scalar(255, 255, 255), 2);
  set_drawn_image(image_for_drawn);

  return true;
}

bool FaceIdentification::checkLastSave(Person *person)
{
  char *forceFace = getenv("force_face");
  if (forceFace)
  {
    int enable = strtoul(forceFace, nullptr, 0);
    if (enable)
      return false;
  }

  cv::Rect rect(person->x(), person->y(), person->w(), person->h());

  for (int i = 0; i < saveLast.persons_size(); i++)
  {
    const Person &knownPerson = saveLast.persons(i);

    cv::Rect knownRect(knownPerson.x(), knownPerson.y(), knownPerson.w(), knownPerson.h());

    cv::Rect intersect = knownRect & rect;
    float coverage = ((float)intersect.area()) / ((float)knownRect.area());

    if (coverage > TRACKING_AREA)
    {
      person->set_name(knownPerson.name());
      person->set_confidence(knownPerson.confidence());
      person->set_face_from_detection(false);
      *(person->mutable_face()) = knownPerson.face();
      _LOG("found known person \"%s\" in lastSave, coverage: %f\n", person->name().c_str(), coverage);
      return true;
    }
  }

  return false;
}
bool FaceIdentification::inRect(bbox b1, cv::Rect b2)
{
    float b2_x2 = b2.x + b2.width - 1;
    float b2_y2 = b2.y + b2.height - 1;
    if((b1.x1 >=b2.x) &&(b1.y1 >=b2.y) && (b1.x2 <=b2_x2)&&(b1.y2 <=b2_y2))
        return true;
    else
        return false;
}

float *FaceIdentification::identifyOne(const cv::Mat &src_img, cv::Rect body_rect,
                                    vector<cv::Point2d> &ldmks, cv::Rect &face_rect)
{
  std::vector<bbox> det_faces, valid_det_faces;
  face_detection_->detect(src_img, det_faces);

  for (size_t i = 0; i<det_faces.size(); i++)
  {
    if (inRect(det_faces[i], body_rect))
      valid_det_faces.push_back(det_faces[i]);
  }
  int n_faces = valid_det_faces.size();
  if (n_faces != 1)
  { //disable multiple faces in one body box
    return nullptr;
  }
  cv::Mat bodyImage = src_img(body_rect);
  face_rect = cv::Rect(cv::Point(valid_det_faces[0].x1 - body_rect.x, valid_det_faces[0].y1 - body_rect.y),
                      cv::Point(valid_det_faces[0].x2 - body_rect.x, valid_det_faces[0].y2 - body_rect.y));
  normBox(face_rect, cv::Size(body_rect.width, body_rect.height));
  vector<cv::Point2f> fldmks;
  ldmks.clear();
  for (int p = 0; p < 5; p++)
  {
    float x = std::max(.0f, std::min((float)body_rect.width, valid_det_faces[0].point[p]._x - body_rect.x));
    float y = std::max(.0f, std::min((float)body_rect.height, valid_det_faces[0].point[p]._y - body_rect.y));
    fldmks.push_back(cv::Point2f(x,y));
    ldmks.push_back(cv::Point2d(x,y));
  }
  //align and extract featues with 5 points
  return feature_extract_->extractFeature(bodyImage, fldmks);
}

//Bigger similarity means same person
pair<int, float> FaceIdentification::computeMaxSimilarity(float *fc1)
{
  map<int, float> res;
  int dim = INSIGHT_FEATURE_SIZE;
  int counter = 0;
  int pcount = 0;
  vector<FaceFeature>::iterator it = this->m_face_feats.begin();
  while (it != this->m_face_feats.end())
  {
    int n_feat = it->nfeatures;
    vector<float> similarity(n_feat, 0.0);
    //#pragma omp parallel for
    for (int i = 0; i < n_feat; ++i)
    {
      float *fc2 = (float *)it->vec_feats[i];
      similarity[i] = this->simd_dot(fc1, fc2, dim) / (sqrt(this->simd_dot(fc1, fc1, dim)) * sqrt(this->simd_dot(fc2, fc2, dim)));
    }
    for (int i = 0; i < n_feat; ++i)
    {
      m_fcm_feats[counter].dSimilarity = similarity[i];
      m_fcm_feats[counter].nFaceID = it->id;
      counter++;
      _LOG("ID: %d, no.:%d, similarity:%f\n", it->id, i, similarity[i]);
    }

    float max_similarity = -1.0;
    for (int i = 0; i < n_feat; ++i)
      max_similarity = max(max_similarity, similarity[i]);

    res[pcount] = max_similarity;
    it++;
    pcount++;
  }

  float max_similarity = -1.0;
  int max_id = -1;
  map<int, float>::const_iterator iter = res.begin();
  while (iter != res.end())
  {
    if (iter->second > max_similarity)
    {
      max_similarity = iter->second;
      max_id = iter->first;
    }
    iter++;
  }
  _LOG("MAX_ID: %d, max similarity:%f\n", max_id, max_similarity);

  return make_pair(max_id, max_similarity);
}

bool FaceIdentification::loadFeatures()
{
  FILE *fp = fopen(mFeaturePath.c_str(), "rb");
  if (fp == NULL)
    return false;
  int id, nfeatures, ndim;
  char name[50];

  fread(&this->m_register_num, sizeof(int), 1, fp);
  if (m_register_num == 0)
  {
    fclose(fp);
    return true;
  }
  m_face_feats = vector<FaceFeature>(0);
  for (int i = 0; i < m_register_num; i++)
  {
    FaceFeature tempFeat;
    fread(&name, 50, sizeof(char), fp);
    strcpy(tempFeat.name, name);
    fread(&id, 1, sizeof(int), fp);
    tempFeat.id = id;
    fread(&nfeatures, 1, sizeof(int), fp);
    tempFeat.nfeatures = nfeatures;
    fread(&ndim, 1, sizeof(int), fp);
    tempFeat.ndim = ndim;

    tempFeat.vec_feats.clear();
    for (int j = 0; j < nfeatures; j++)
    {
      float *pTemp = new float[tempFeat.ndim];
      fread(pTemp, tempFeat.ndim, sizeof(float), fp);
      tempFeat.vec_feats.push_back(pTemp);
    }
    m_face_feats.push_back(tempFeat);
  }
  int n_fcm_feats;
  fread(&n_fcm_feats, 1, sizeof(int), fp);
  for (int i = 0; i < n_fcm_feats; i++)
  {
    FaceCMFeature fcm;
    fread(&fcm, sizeof(FaceCMFeature), 1, fp);
    m_fcm_feats.push_back(fcm);
  }
  fclose(fp);

  return true;
}

bool FaceIdentification::saveFeatures()
{
  FILE *fp = fopen(mFeaturePath.c_str(), "wb+");
  if (fp == NULL)
  {
    _LOG("Failed to write features in %s\n", mFeaturePath.c_str());
    return false;
  }
  fwrite(&m_register_num, 1, sizeof(int), fp);
  if (m_register_num <= 0)
  {
    fclose(fp);
    return true;
  }
  for (int i = 0; i < m_register_num; i++)
  {
    fwrite(&m_face_feats[i].name, 50, sizeof(char), fp);
    fwrite(&m_face_feats[i].id, 1, sizeof(int), fp);
    fwrite(&m_face_feats[i].nfeatures, 1, sizeof(int), fp);
    fwrite(&m_face_feats[i].ndim, 1, sizeof(int), fp);

    for (auto it = m_face_feats[i].vec_feats.begin(); it != m_face_feats[i].vec_feats.end(); ++it)
    {
      float *pTemp = *it;
      fwrite(pTemp, m_face_feats[i].ndim, sizeof(float), fp);
    }
  }

  int n_fcm_feats = m_fcm_feats.size();
  fwrite(&n_fcm_feats, 1, sizeof(int), fp);
  for (int i = 0; i < n_fcm_feats; i++)
  {
    fwrite(&m_fcm_feats[i], sizeof(FaceCMFeature), 1, fp);
  }

  fclose(fp);
  return true;
}

int FaceIdentification::findPerson(const char *name)
{
  int id = -1;
  for (int i = 0; i < m_register_num; i++)
  {
    if (strcmp(m_face_feats[i].name, name) == 0)
    {
      id = i;
    }
  }

  return id;
}

bool FaceIdentification::deletePerson(const string &name)
{

  lock_guard<mutex> lk(global_mtx_);

  int delete_id = findPerson(name.c_str());
  if (delete_id < 0)
  {
    _LOG("Failed in finding delete person: %s", name.c_str());
    return false;
  }
  else
    _LOG("start to delete face features\n");

  //delete face feature
  vector<FaceFeature>::iterator it = m_face_feats.begin();
  advance(it, delete_id);
  float *pTemp = NULL;
  for (int i = 0; i < it->nfeatures; i++)
  {
    pTemp = it->vec_feats[i];
    if (pTemp != NULL)
    {
      delete[] pTemp;
      pTemp = NULL;
    }
  }
  it = m_face_feats.erase(it);
  for (; it != m_face_feats.end(); ++it)
  {
    it->id = it->id - 1;
  }
  _LOG("delete face features\n");

  //search and delete in fcm features
  for (auto it = m_fcm_feats.begin(); it != m_fcm_feats.end();)
  {
    int old_id = it->nFaceID;
    if (old_id == delete_id)
    {
      it = m_fcm_feats.erase(it);
    }
    else
    {
      if (old_id > delete_id)
      {
        it->nFaceID--;
        it++;
      }
      else
      {
        it++;
      }
    }
  }
  m_register_num--;
  _LOG("delete fcm features\n");
  return true;
}

bool FaceIdentification::addPerson(const string &name, float **pfeat, FaceCMFeature &FaceCMFeat)
{

  int id = m_register_num;

  FaceFeature pTempFeat;
  strncpy(pTempFeat.name, name.c_str(), name.length());
  pTempFeat.id = id;
  pTempFeat.nfeatures = 1;
  pTempFeat.ndim = INSIGHT_FEATURE_SIZE;
  pTempFeat.vec_feats.push_back(*pfeat);
  m_face_feats.push_back(pTempFeat);
  *pfeat = NULL;

  //add FCM feature
  FaceCMFeat.nFaceID = id;
  m_fcm_feats.push_back(FaceCMFeat);

  m_register_num++;

  return true;
}

bool FaceIdentification::addFeatureToPerson(int id, float **pfeat, FaceCMFeature &FaceCMFeat)
{

  auto max_similarity = computeMaxSimilarity(*pfeat);
  if (max_similarity.second > 0.7)
  {
    _LOG("Same person found and ignoring\n");
    return false;
  }
  m_face_feats[id].vec_feats.push_back(*pfeat);
  m_face_feats[id].nfeatures++;

  FaceCMFeat.nFaceID = id;
  //find the position to insert, last occurance of id
  vector<FaceCMFeature>::reverse_iterator rit = m_fcm_feats.rbegin();
  if (rit->nFaceID == id)
  { //append at the end of vector{
    m_fcm_feats.push_back(FaceCMFeat);
  }
  else
  {
    for (; rit != m_fcm_feats.rend(); ++rit)
    {
      if (rit->nFaceID == id)
        break;
    }
    rit--;
    m_fcm_feats.insert(rit.base(), FaceCMFeat);
  }
  *pfeat = NULL;

  return true;
}

float FaceIdentification::simd_dot(const float *x, const float *y, const long len)
{
  float inner_prod = 0.0f;
  __m128 X, Y;                   // 128-bit values
  __m128 acc = _mm_setzero_ps(); // set to (0, 0, 0, 0)
  float temp[4];

  long i;
  for (i = 0; i + 4 < len; i += 4)
  {
    X = _mm_loadu_ps(x + i); // load chunk of 4 floats
    Y = _mm_loadu_ps(y + i);
    acc = _mm_add_ps(acc, _mm_mul_ps(X, Y));
  }
  _mm_storeu_ps(&temp[0], acc); // store acc into an array
  inner_prod = temp[0] + temp[1] + temp[2] + temp[3];

  // add the remaining values
  for (; i < len; ++i)
  {
    inner_prod += x[i] * y[i];
  }
  return inner_prod;
}

cv::Mat FaceIdentification::get_drawn_image()
{
  cv::Mat result;

  drawn_image_mtx_.lock();
  drawn_image_.copyTo(result);
  drawn_image_mtx_.unlock();

  return result;
}

void FaceIdentification::set_drawn_image(const cv::Mat &image)
{
  lock_guard<mutex> lck(drawn_image_mtx_);
  image.copyTo(drawn_image_);
}
