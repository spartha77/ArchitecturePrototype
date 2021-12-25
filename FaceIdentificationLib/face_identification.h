#ifndef __FACE_RECOGNITION_H__
#define __FACE_RECOGNITION_H__

/*
 * Face recognition module
 */

#include <string>
#include <memory>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>

#include <FaceIdentificationLib.h>
#include <face_detection.h>
#include "face_feature_extraction.h"
#include "face_confidence.h"
#include <person_id.pb.h>
#include <fusion.h>

class FACEIDENTIFICATIONLIB_API FaceIdentification {
public:
  FaceIdentification(const std::string& feature_data_dir, std::shared_ptr<FaceDetection> face_det, std::shared_ptr<FaceFeatureExtraction> feature_extract);
  ~FaceIdentification();

  bool initialize();
  void set_fusion_callback(void(Fusion::*cb)(const PersonIdMsg&), Fusion* fusion);

  PersonIdMsg identify(const PersonIdMsg& msg);
  void identify_async(const PersonIdMsg& msg);

  bool registerNew(const PersonIdMsg& msg);
  bool deletePerson(const std::string& name);
  void preRegisterNew(){};
  void postRegisterNew(){saveFeatures();};
  void queryPersonList(std::vector<std::string> &all);

  cv::Mat get_drawn_image();

private:

  struct FaceFeature{
    char name[512];
    int id; // id starting from 0, connect to fcm
    int nfeatures;
    int ndim;
    std::vector <float *> vec_feats;
  };

  std::thread identify_thread_;
  PersonIdMsg new_input_msg_;
  bool new_input_ = false;
  std::mutex new_input_mtx_;
  std::condition_variable new_input_cv_;
  void do_identify(PersonIdMsg& msg);

  bool stopped_ = false;

  cv::Mat drawn_image_;
  std::mutex drawn_image_mtx_;
  void set_drawn_image(const cv::Mat& image);

  bool checkLastSave(Person* person);
  float *identifyOne(const cv::Mat &src_img, cv::Rect body_rect, std::vector<cv::Point2d> &ldmks, cv::Rect &face_rect);
  bool loadFeatures();
  bool saveFeatures();
  bool inRect(bbox b1, cv::Rect b2);

  std::pair<int, float>  computeMaxSimilarity(float* fc1);
  std::vector<std::pair<int, float>> computeTopNSimilarity(float *fc1, int n); 

  int   findPerson(const char *name);
  bool  addPerson(const std::string& name, float **pfeat, FaceCMFeature &FaceCMFeature);
  bool  addFeatureToPerson(int id, float **pfeat, FaceCMFeature &FaceCMFeature);
  float simd_dot(const float*, const float*, const long len);
  bool  normBox(cv::Rect &rect, cv::Size sz);

  std::shared_ptr<FaceDetection> face_detection_;
  std::shared_ptr<FaceFeatureExtraction> feature_extract_;

  CFaceConfidence m_face_confidence_estimator;
  PersonIdMsg saveLast;
  std::string mFeatureDir;
  std::string mFeaturePath;
  std::string mFeatureASCII;
  
  

  //for feature saving
  int m_register_num;
  std::vector<FaceFeature> m_face_feats;
  //add FCM support
  std::vector<FaceCMFeature>  m_fcm_feats; //all fcm feats

  unsigned int max_unknown_id; 
  std::vector<unsigned int> m_last_unknowns;
  // send face recognition result to fusion module
  std::function<void(const PersonIdMsg&)> notify_fusion_;
  bool fusion_callback_set = false;

  std::mutex global_mtx_;

  bool force_identify_face = false;


  bool log_enabled_ = false;
  const char* log_prefix_ = "FaceIdentification";
};

#endif  // __FACE_RECOGNITION_H__
