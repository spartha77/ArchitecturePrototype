#include "body_identification.h"

#include <unordered_map>
#if defined _WINDOWS
#include <io.h>
#else
#include <unistd.h>
#endif

#include <image_serde.h>
#include <image_draw.h>
#include <logging.h>
#include <fs.h>

using namespace std;

#define ALIGN_REID_INPUT_WIDTH 125
#define ALIGN_REID_INPUT_HEIGHT 253

#define THRESHOLD_UNKNOWN_FEATURES_SIMILARITY_BODYID 0.5
#define THRESHOLD_ADD_FEATURES_MIN 0.001
#define THRESHOLD_ADD_FEATURES_MAX 8.0

BodyIdentification::BodyIdentification(const string& model_path, const string& device,
  int feature_dim, const string& PRIDsaveFolder) {
    numFeatures_ = 0;
  nchannel = 3;
  nHeight = ALIGN_REID_INPUT_HEIGHT;
  nWidth = ALIGN_REID_INPUT_WIDTH;
  nFeatureDim=feature_dim;
  path_PRIDsaveFolder = PRIDsaveFolder;
#ifdef _WINDOWS
  feature_path=path_PRIDsaveFolder+"\\allFeatures.txt";
  nameList_path = path_PRIDsaveFolder+"\\personIndex.txt";
  treeIdx_path= path_PRIDsaveFolder+"\\kdTreeIndex.txt";
#else
  feature_path = path_PRIDsaveFolder + "/allFeatures.txt";
  nameList_path = path_PRIDsaveFolder + "/personIndex.txt";
  treeIdx_path = path_PRIDsaveFolder + "/kdTreeIndex.txt";
#endif

  model_path_ = model_path;
  device_ = device;

  char* pValue = nullptr;
  size_t length = 0;
   #if defined _WINDOWS
  errno_t errorVal = _dupenv_s(&pValue, &length, "LOG_BODY_ID");
  #else
  error_t errorVal = getenv("LOG_BODY_ID") != nullptr;
  #endif
  log_enabled_ = (errorVal == 0);

  if (log_enabled_) {
    cout << "[" << log_prefix_ << "] log enabled" << endl;
  }
}

BodyIdentification::~BodyIdentification() {
  stopped_ = true;

  saveBodyReidFeatures();

  if (identify_thread_.joinable()) {
    new_input_mtx_.lock();
    new_input_ = true;
    new_input_cv_.notify_one();
    new_input_mtx_.unlock();

    identify_thread_.join();
  }

  if (cotrain_thread_.joinable()) {
    new_cotrain_mtx_.lock();
    new_cotrain_ = true;
    new_cotrain_cv_.notify_one();
    new_cotrain_mtx_.unlock();

    cotrain_thread_.join();
  }
}

bool BodyIdentification::initialize() {
  openvino_.initialize(model_path_, "body_id", device_);

  if (!is_dir(path_PRIDsaveFolder)) {
    if (!make_dirs(path_PRIDsaveFolder, 0755)) {
      cout << "[Error]: fail to create data directory for BodyIdentification" << endl;
      return false;
    }
    cout << "[Info]: create BodyIdentification data directory (" << path_PRIDsaveFolder << ")"
         << endl;
  }

  cotrain_thread_ = thread([&] () {
    while (!stopped_) {
      unique_lock<mutex> lck(new_cotrain_mtx_);
      while (true) {
        if (new_cotrain_cv_.wait_for(lck, chrono::seconds(1), [this] {return new_cotrain_;})) {
          break;
        }
      }
      if (stopped_) return;

      do_cotrain(new_cotrain_msg_);
      new_cotrain_ = false;
    }
  });

  initBodyReidFeatures();

  cout << "BodyIdentification initialization done!" << endl;

  return true;
}

void BodyIdentification::set_fusion_callback(void(Fusion::*cb)(const PersonIdMsg&), Fusion* fusion) {
  notify_fusion_ = bind(cb, fusion, std::placeholders::_1);

  identify_thread_ = thread([&] () {
    while (!stopped_) {
      unique_lock<mutex> lck(new_input_mtx_);
      while (true) {
        if (new_input_cv_.wait_for(lck, chrono::seconds(1), [this] {return new_input_;})) {
          break;
        }
      }
      if (stopped_) return;

      do_identify(new_input_msg_);
      notify_fusion_(new_input_msg_);
      new_input_ = false;
    }
  });

  fusion_callback_set = true;
}

PersonIdMsg BodyIdentification::identify(const PersonIdMsg& msg) {
  PersonIdMsg result = msg;
  do_identify(result);
  return result;
}

void BodyIdentification::identify_async(const PersonIdMsg& msg) {

  if (!fusion_callback_set) {
    cout << "[Error]: fusion callback in BodyIdentification is NOT set!" << endl;
    return;
  }

  lock_guard<mutex> lck(new_input_mtx_);
  if (new_input_) {
    cout << "[Warn-BI] still processing previous body_id" << endl;
    return;
  }
  new_input_msg_ = msg;
  new_input_ = true;
  new_input_cv_.notify_one();
}

void BodyIdentification::do_identify(PersonIdMsg& msg) {
  cv::Mat image = image_from_pb(msg.image());

  _LOG_MSG("do_identify", "entry", "input_msg", msg);

  lock_guard<mutex> lk(global_mtx_);
  unordered_map<string, int> name_counts;
  for(int i = 0; i < msg.persons_size(); i++) {
    Person* person = msg.mutable_persons(i);

    if((person->name()!="") || (person->source()!=NEED_RECOG)) {
      _LOG("Skip recognition\n");
      continue;
    }

    // adjust person bbox to fit into image
    if(person->x() < 0) person->set_x(0);
    if(person->y() < 0) person->set_y(0);
    if(person->x() + person->w() > image.cols) person->set_w(image.cols - person->x());
    if(person->y() + person->h() > image.rows) person->set_h(image.rows - person->y());

    cv::Mat imageOnePerson = image(cv::Rect(person->x(), person->y(), person->w(), person->h()));
    float similarity=0;
    string name = this->identityOnePersonImg(imageOnePerson,similarity);
    person->set_name(name);
    person->set_similarity(similarity);
    person->set_confidence(similarity);
    person->set_source(BODY);
    auto iter = name_counts.find(name);
    if(iter != name_counts.end()){
        iter->second++;
    } else {
        name_counts[name] = 1;
    }
  }
  for(auto iter=name_counts.begin(); iter!=name_counts.end(); ++iter) {
    if(iter->second >1){
      string temp_name = iter->first;
      float max_similarity = -1;
      int max_similarity_id = -1;
      for(int i = 0; i < msg.persons_size(); i++) {
        Person* person = msg.mutable_persons(i);
        if(person->name() == temp_name){
          if(person->similarity() > max_similarity){
            max_similarity_id = i;
            max_similarity = person->similarity();
          }
     //       _LOG("!!!!!!Clear all names!!!!\n");
          person->set_name(""); //clean first, and will assigned only one later
        }
      }
   //   _LOG("!!!!!!Assign back names: %i, %s!!!!\n", max_similarity_id, temp_name);
     msg.mutable_persons(max_similarity_id)->set_name(temp_name);
    }
  }

  cv::Scalar color;
  string txt;
  bool register_mode = false;
  if (register_mode) {
    color = cv::Scalar(0, 255, 255);
    txt = "registering";
  } else {
    color = cv::Scalar(0, 0, 0);
    txt = "identifying";
  }
  cv::Mat image_copy;
  image.copyTo(image_copy);
  drawImageResult(msg, image_copy, txt, color);
  set_drawn_image(image_copy);
}

void BodyIdentification::cotrain(const PersonIdMsg& msg) {

  lock_guard<mutex> lck(new_cotrain_mtx_);
  if (new_cotrain_) {
    cout << "[Warn-BI] still processing previous body_id" << endl;
    return;
  }
  new_cotrain_msg_ = msg;
  new_cotrain_ = true;
  new_cotrain_cv_.notify_one();
}

// modified based on `subRegisterOnceCallback` in person_id.cpp
void BodyIdentification::do_cotrain(PersonIdMsg msg) {

  lock_guard<mutex> lck(global_mtx_);

  registerNew(msg);
  postRegisterNew();
}

void BodyIdentification::postRegisterNew() {
  saveBodyReidFeatures();
  updatePIDmodel();
}

bool BodyIdentification::registerNew(PersonIdMsg& msg) {
  _LOG("register new person in body_id\n");

  cv::Mat image = image_from_pb(msg.image());

  cv::Mat image_for_drawn;
  image.copyTo(image_for_drawn);

  for(int i = 0; i < msg.persons_size(); i++) {
    Person* person = msg.mutable_persons(i);
    string name = person->name();
    if (name == "") {
      _LOG("Failed to register! The register person name is illegal\n");
      continue;
    }
    if(person->x() < 0) person->set_x(0);
    if(person->y() < 0) person->set_y(0);
    if(person->x() + person->w() > image.cols) person->set_w(image.cols - person->x());
    if(person->y() + person->h() > image.rows) person->set_h(image.rows - person->y());

    cv::Rect person_rect(person->x(), person->y(), person->w(), person->h());
    cv::Mat imageOnePerson = image(person_rect);
    bool added = registerOnePersonImg(imageOnePerson, name);
    if (added) {
      drawBBox(image_for_drawn, name, person_rect, cv::Scalar(0, 0, 0));
    }
  }

  cv::putText(image_for_drawn, "register", cv::Point(5, 25), cv::FONT_HERSHEY_SIMPLEX, 1.0,
  cv::Scalar(255, 255, 255), 2);
  set_drawn_image(image_for_drawn);

  return true;
}

void BodyIdentification::initBodyReidFeatures() {
  //step 2: load registered person features and the kdtree index
  allFeatures=NULL;
  nameList.clear();
  numFeatures_=0;

  _LOG("Initilizing Body RID model\n");
#ifdef _WINDOWS
  if ((_access(feature_path.c_str(), 0) != -1) && (_access(nameList_path.c_str(), 0) != -1) && (_access(treeIdx_path.c_str(), 0) != -1)) {
#else
  if ((access(feature_path.c_str(), 0 ) !=-1) && (access(nameList_path.c_str(), 0 ) !=-1) && (access(treeIdx_path.c_str(), 0 ) !=-1)) {
#endif
    loadAllFeatures();
    loadNameList();

    flann::Matrix<float> dataset = flann::Matrix<float>(allFeatures, numFeatures_, nFeatureDim);
    index=new flann::Index<flann::L2<float> >(dataset, flann::SavedIndexParams(treeIdx_path));
    unordered_set<string> registeredNames=collectNames();
    _LOG("Inilized: Registered Persons are: %lu\n",nameList.size());
    for(auto& name : registeredNames)
        _LOG("%s\n", name.c_str());
  } else {
    index=new flann::Index<flann::L2<float> >(flann::KDTreeIndexParams(4));
    _LOG("No Persons have been registered, please register person first\n");
  }
}

void BodyIdentification::saveBodyReidFeatures() {
  if(numFeatures_>0) {
    saveAllFeatures();
    saveNameList();
    index->save(treeIdx_path.c_str());
    _LOG("postRegister: current registered feature numbers: %d\n",numFeatures_);
    unordered_set<string> registeredNames=collectNames();
    _LOG("Registered Persons are: \n");
    for(auto& name : registeredNames)
      _LOG("%s\n",name.c_str());
  } else {
    _LOG("No Persons are Registered! \n");
  }
}

bool BodyIdentification::saveNameList() {
  ofstream outfile(nameList_path.c_str(), ios::out|ios::trunc);
  if (outfile.is_open()) {
    outfile << nameList.size() << endl;
    for(size_t n=0;n<nameList.size();n++)
        outfile <<  nameList[n] << endl;
    outfile.close();
    return true;
  } else {
    _LOG("error in saveNameList, Cannot open output file: %s\n", nameList_path.c_str());
    return false;
  }
}

bool BodyIdentification::loadNameList(){
  ifstream infile(nameList_path, ios::in);
  if(infile.is_open()) {
    nameList.clear();
    int numfeatures;
    infile>>numfeatures;
    for(int n=0;n<numfeatures;n++) {
      string name;
      infile>>name;
      nameList.push_back(name);
    }
    return true;
  } else {
    _LOG("error in loadNameList, Cannot open output file: %s\n", nameList_path.c_str());
    return false;
  }
}

bool BodyIdentification::saveAllFeatures() {
  _LOG("save body features to %s\n",feature_path.c_str());

  FILE *fp;
  if ((fp = fopen(feature_path.c_str(), "wb")) == NULL) {
    _LOG("error in saveAllFeatures, Cannot open output file: %s\n", feature_path.c_str());
    return false;
  }

  fwrite(&numFeatures_,sizeof(int),1,fp);
  fwrite(&nFeatureDim,sizeof(int),1,fp);
  fwrite(allFeatures,sizeof(float),numFeatures_*nFeatureDim,fp);
  fclose(fp);

  return true;
}


bool BodyIdentification::loadAllFeatures() {
  FILE *fp;
  if ((fp = fopen(feature_path.c_str(), "rb")) == NULL) {
    _LOG("error in loadAllFeatures, Cannot open output file: %s\n", feature_path.c_str());
    return false;
  }

  fread(&numFeatures_,sizeof(int),1,fp);
  fread(&nFeatureDim,sizeof(int),1,fp);
  allFeatures=(float*)malloc(sizeof(float)*numFeatures_*nFeatureDim);
  fread(allFeatures,sizeof(float),numFeatures_*nFeatureDim,fp);
  fclose(fp);

  return true;
}


unordered_set<string> BodyIdentification::collectNames() {
  unordered_set<string> result;
  for(size_t n=0;n<nameList.size();n++) {
    result.insert(nameList[n]);
  }
  return result;
}



bool BodyIdentification::registerOnePersonImg(const cv::Mat& image, const string& personName)
{
  //check the input personName in old name list, automatically changed to the latest name
  string latestName(personName);
  for(size_t i=0; i<nameMapList.size(); i++) {
    string oldname = nameMapList[i].first;
    if (latestName == nameMapList[i].first) {
      latestName = nameMapList[i].second;
    }
  }

  float* onefeature = extractFeatureWithOpenVino(image);

  flann::Matrix<float> datatoadd = flann::Matrix<float>(onefeature, 1, nFeatureDim);
  bool bAdd=true;
  if (index->size()<1) {
    _LOG("index=0\n");
    index->buildIndex(datatoadd);
  } else {
    flann::Matrix<float> query = flann::Matrix<float>(onefeature, 1, nFeatureDim);
    flann::Matrix<int> indices(new int[query.rows*1], query.rows, 1);
    flann::Matrix<float> dists(new float[query.rows*1], query.rows, 1);
    index->knnSearch(query, indices, dists, 1, flann::SearchParams(128));
    float dist = dists[0][0];
    int indice_dist=indices[0][0];
    _LOG("dist %f\n", dist);

    if (isnan(dist) || isinf(dist)
        || dist < numeric_limits<float>::min() || dist >numeric_limits<float>::max()
        || (dist > THRESHOLD_ADD_FEATURES_MAX)) {
      bAdd = false;
      _LOG("dist is illegal\n");
    } else {
      if((dist < THRESHOLD_ADD_FEATURES_MIN) && (latestName==nameList[indice_dist])) {
          bAdd=false;
        _LOG("skipped\n");
      }
    }

    delete[] indices.ptr();
    delete[] dists.ptr();
  }
  if(bAdd)  {
    _LOG("add new feature for %s in body id\n",latestName.c_str());
    numFeatures_++;
    if(numFeatures_>1) {
      float* allFeaturesBackup = allFeatures;
      float* m_allFeatures = (float*)realloc(allFeatures,sizeof(float)*numFeatures_*nFeatureDim);
      if (m_allFeatures == NULL) {
        
        allFeatures = allFeaturesBackup;
        allFeaturesBackup = NULL;
        numFeatures_--;
        if (onefeature != nullptr) {
          delete [] onefeature;
          onefeature = nullptr;
        }
        return false;
      } else {
        
        allFeatures = m_allFeatures;
        m_allFeatures = NULL;
        allFeaturesBackup = NULL;
      }
    }
    else
      allFeatures=(float*)malloc(sizeof(float)*nFeatureDim);

    memcpy(allFeatures+(numFeatures_-1)*nFeatureDim, onefeature, sizeof(float)*nFeatureDim);

    _LOG("add point,so rebuild tree\n");
    if (index) {
      delete(index);
      index=NULL;
    }
    flann::Matrix<float> dataset = flann::Matrix<float>(allFeatures, numFeatures_, nFeatureDim);
    this->index=new flann::Index<flann::L2<float> > (dataset, flann::KDTreeIndexParams(4));
    index->buildIndex();

    nameList.push_back(latestName);
    if (onefeature != nullptr) {
      delete [] onefeature;
      onefeature = nullptr;
    }
    return true;
  } else {
    if (onefeature != nullptr) {
      delete [] onefeature;
      onefeature = nullptr;
    }
    return false;
  }
}

string BodyIdentification::identityOnePersonImg(const cv::Mat& image, float similarity) {
  if(numFeatures_<1) {
    _LOG("No person has been registered, please register first\n");
    return "";
  } else {
    float* onefeature = extractFeatureWithOpenVino(image);
    flann::Matrix<float> query = flann::Matrix<float>(onefeature, 1, nFeatureDim);
    int nn=2;
    flann::Matrix<int> indices(new int[query.rows*nn], query.rows, nn);
    flann::Matrix<float> dists(new float[query.rows*nn], query.rows, nn);
    index->knnSearch(query, indices, dists, nn, flann::SearchParams(128));

    float dist=dists[0][0];
    int indice_dist=indices[0][0];
    similarity = exp(-dist*dist/6.0f);

    delete[] indices.ptr();
    delete[] dists.ptr();
    if (onefeature != nullptr) {
        delete [] onefeature;
        onefeature = nullptr;
    }
    _LOG("matching_name=%s, matching similarity=%f, matching index=%d\n",nameList[indice_dist].c_str(), similarity, indice_dist);
    if((similarity < THRESHOLD_UNKNOWN_FEATURES_SIMILARITY_BODYID) \
        || isnan(similarity) || isinf(similarity) \
        || similarity < numeric_limits<float>::min() || similarity >numeric_limits<float>::max()) {
      _LOG("Unknown User\n");
      return "";
    }
    return nameList[indice_dist];
  }
}

void BodyIdentification::updatePIDmodel() {
  if(allFeatures) {
    free(allFeatures);
    allFeatures=NULL;
  }

  nameList.clear();
  numFeatures_=0;
  if(index) {
    delete(index);
    index=NULL;
  }

  _LOG("reloading Body RID model\n");
#ifdef _WINDOWS
  if ((_access(feature_path.c_str(), 0) != -1) && (_access(nameList_path.c_str(), 0) != -1) && (_access(treeIdx_path.c_str(), 0) != -1)) {
#else
  if ((access(feature_path.c_str(), 0) != -1) && (access(nameList_path.c_str(), 0) != -1) && (access(treeIdx_path.c_str(), 0) != -1)) {
#endif
  
    loadAllFeatures();
    loadNameList();

    flann::Matrix<float> dataset = flann::Matrix<float>(allFeatures, numFeatures_, nFeatureDim);
    index=new flann::Index<flann::L2<float> >(dataset, flann::SavedIndexParams(treeIdx_path));
    unordered_set<string> registeredNames=collectNames();
    _LOG("Registered Persons are: \n");
    for(auto& name : registeredNames)
        _LOG("%s\n", name.c_str());
  } else {
    index=new flann::Index<flann::L2<float> >(flann::KDTreeIndexParams(4));
    _LOG("No Persons have been registered, please register person first\n");
  }
}


float* BodyIdentification::extractFeatureWithOpenVino(const cv::Mat& img) {
  cv::Mat img_copy =img.clone();

  //do preprocessing for aligned reid algorithm
  cv::Size input_sz(ALIGN_REID_INPUT_WIDTH, ALIGN_REID_INPUT_HEIGHT);
  cv::resize(img_copy, img_copy, input_sz, cv::InterpolationFlags::INTER_LINEAR);
  cv::cvtColor(img_copy, img_copy, cv::COLOR_RGB2BGR);
  img_copy.convertTo(img_copy, CV_32FC3, 1.0f/255);
  cv::Mat mean = cv::Mat(img_copy.size().height, img_copy.size().width, CV_32FC3, cv::Scalar(0.486, 0.459, 0.408));
  cv::Mat std = cv::Mat(img_copy.size().height, img_copy.size().width, CV_32FC3, cv::Scalar(0.229, 0.224, 0.225));
  cv::subtract(img_copy, mean, img_copy);
  cv::divide(img_copy, std, img_copy);

  const float *feature = openvino_.getFeatures(img_copy);
  float* res_feature= new float[nFeatureDim];
  memcpy(res_feature,feature,sizeof(float)*nFeatureDim);

  return res_feature;
}



cv::Mat BodyIdentification::get_drawn_image() {
  cv::Mat result;

  drawn_image_mtx_.lock();
  drawn_image_.copyTo(result);
  drawn_image_mtx_.unlock();

  return result;
}

void BodyIdentification::set_drawn_image(const cv::Mat& image) {
  lock_guard<mutex> lck(drawn_image_mtx_);
  image.copyTo(drawn_image_);
}
