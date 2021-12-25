#ifndef __BODY_IDENTIFICATION_H__
#define __BODY_IDENTIFICATION_H__

/*
 * Body identification module
 */

#include <vector>
#include <string>
#include <unordered_set>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>

#include <BodyId.h>
// MUST be included before OpenCV, otherwise will cause mysterious compilation error
#include "flann/flann.hpp"

#include <opencv2/opencv.hpp>

#include <openvino_lib.h>
#include <person_id.pb.h>
#include <fusion.h>

class BODYID_API BodyIdentification {
public:
  BodyIdentification(const std::string& model_path, const std::string& device,
    int feature_dim, const std::string& PRIDsaveFolder);
  ~BodyIdentification();

  bool initialize();
  void set_fusion_callback(void(Fusion::*cb)(const PersonIdMsg&), Fusion* fusion);
  PersonIdMsg identify(const PersonIdMsg& msg);
  void identify_async(const PersonIdMsg& msg);

  void cotrain(const PersonIdMsg& msg);

  bool registerNew(PersonIdMsg& msg);

  cv::Mat get_drawn_image();

private:

  std::string model_path_;
  std::string device_;
  openvino_lib openvino_;

  std::function<void(const PersonIdMsg&)> notify_fusion_;
  bool fusion_callback_set = false;

  typedef std::map<std::string, int> CounterMap;
  std::vector<std::pair<std::string, std::string>> nameMapList;

  std::thread identify_thread_;
  PersonIdMsg new_input_msg_;
  bool new_input_ = false;
  std::mutex new_input_mtx_;
  std::condition_variable new_input_cv_;
  void do_identify(PersonIdMsg& msg);

  std::thread cotrain_thread_;
  PersonIdMsg new_cotrain_msg_;
  bool new_cotrain_ = false;
  std::mutex new_cotrain_mtx_;
  std::condition_variable new_cotrain_cv_;
  void do_cotrain(PersonIdMsg msg);

  bool stopped_ = false;

  cv::Mat drawn_image_;
  std::mutex drawn_image_mtx_;
  void set_drawn_image(const cv::Mat& image);

//caffe model parameters
  int reid_alg_id;
  int nchannel;
  int nHeight;
  int nWidth;
  int nFeatureDim;

//flann parameters
  std::string path_PRIDsaveFolder;
  std::string feature_path;
  std::string treeIdx_path;
  std::string nameList_path;

  flann::Index<flann::L2<float> >* index;

  std::vector<std::string> nameList;
  float* allFeatures;
  int numFeatures_ = 0;

  float* extractFeatureWithOpenVino(const cv::Mat& img);
  std::string identityOnePersonImg(const cv::Mat& img, float dist);
  bool registerOnePersonImg(const cv::Mat& img, const std::string& personName);
  bool removeOnePerson(std::string personName);
  void updatePIDmodel();

  void postRegisterNew();

  void initBodyReidFeatures();
  void saveBodyReidFeatures();
  bool loadAllFeatures();
  bool saveAllFeatures();
  bool loadNameList();
  bool saveNameList();

  std::unordered_set<std::string> collectNames();

  bool log_enabled_ = false;
  const char* log_prefix_ = "BodyIdentification";

  std::mutex global_mtx_; // mutual execution of `identify_person`, `cotrain`, `renamePerson`
};

#endif  // __BODY_IDENTIFICATION_H__
