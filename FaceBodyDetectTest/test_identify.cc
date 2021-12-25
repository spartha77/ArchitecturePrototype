/**
 * Test adaptive person identification by feeding all images under given directory
 */

#include "adaptive_person_id.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>

#include <sys/types.h>
#include <dirent.h>

using namespace std;

vector<string> get_file_list(const string& path) {
  vector<string> result;

  DIR *dp = opendir(path.c_str());
  if (dp == nullptr) {
    printf("fail to opendir '%s'. error: %s\n", path.c_str(), strerror(errno));
    return result;
  }

  struct dirent *ep;
  while ((ep = readdir(dp)) != nullptr) {
    // skip directory "." and ".."
    if ((strcmp(ep->d_name, ".")!=0) && (strcmp(ep->d_name, "..")!=0)) {
      result.push_back(path+"/"+ep->d_name);
    }
  }
  closedir(dp);

  sort(result.begin(), result.end());

  return result;
}

bool parse_args(int argc, char** argv, string& model_dir, string& data_dir, string& image_dir,
  int& play_interval, int& loop_cnt, bool& step) {

  //////////
  // Arguments:
  // 1. mandatory argumenets:
  //    model_dir: top directory to all trained models
  //    data_dir:  top direcotry to save face and body data
  //    image_dir: directory to test images
  // 2. optional arguments:
  //    -i: interval (in milliseconds) to play next image, defaults to 33 ms
  //    -l: the number to loop over all input images
  //    -s: play each image in "single step" mode
  /////////
  if (argc < 4) {
    cout << "Usage: test_identify <model_dir> <data_dir> <image_dir> [-i ii] [-l ll] [-s]" << endl;
    return false;
  }

  model_dir = argv[1];
  data_dir = argv[2];
  image_dir = argv[3];

  play_interval = 33;   // 30 fps
  loop_cnt = 0;
  step = false;
  if (argc > 4) {
    int i = 4;
    while (i < argc) {
      if (strcmp(argv[4], "-i") == 0) {
        i++;
        if (i >= argc) {
          cout << "missing value for option '-i'" << endl;
          return false;
        }
        play_interval = atoi(argv[i]);
      } else if (strcmp(argv[4], "-l") == 0) {
        i++;
        if (i >= argc) {
          cout << "missing value for option '-l'" << endl;
          return false;
        }
        loop_cnt = atoi(argv[i]);
      } else if (strcmp(argv[4], "-s") == 0) {
        step = true;
      }
      ++i;
    }
  }

  return true;
}

int main(int argc, char** argv) {

  string model_dir, data_dir, image_dir;
  int interval_ms, loop_cnt;
  bool step;
  if (!parse_args(argc, argv, model_dir, data_dir, image_dir, interval_ms, loop_cnt, step))
    return false;

  cout << "model dir: " << model_dir << endl;
  cout << "data dir: " << data_dir << endl;
  cout << "image dir: " << image_dir << endl;
  cout << "play interval: " << interval_ms << " ms" << endl;
  cout << "play count: " << loop_cnt << endl;
  cout << "step: " << step << endl;

  vector<string> image_files = get_file_list(image_dir);

  string ssd_model = model_dir + "/ssd/openvino_fp32.xml";
  string ssd_device("CPU");
  string body_id_model = model_dir + "/body/aligned_reid_openvino_fp32.xml";
  string body_id_device("CPU");
  string body_feature_path = data_dir + "/body/kdtree";
  int body_feature_dim = 2048;
  string face_det_model = model_dir + "/face/retinaface/faceDetector_fp32.xml";
  string face_det_device("CPU");
  string face_feature_model = model_dir + "/face/arcface50/openvino_fp32.xml";
  string face_feature_device("CPU");
  int face_feature_dim = 512;
  string face_feature_path = data_dir + "/face";

  AdaptivePersonId person_id;
  bool succ = person_id.initialize(ssd_model, ssd_device,
    body_id_model, body_id_device, body_feature_dim, body_feature_path,
    face_det_model, face_det_device, face_feature_model, face_feature_device, face_feature_dim,
    face_feature_path, AdaptivePersonId::Mode::Identify);
  if (!succ) return -1;

  while (true) {
    for (auto& file : image_files) {
      cv::Mat image = cv::imread(file, cv::IMREAD_COLOR);
      if (image.empty()) {
        cout << "fail to read image file: " << file << endl;
        break;
      }

      PersonIdMsg result = person_id.identify(image);
      person_id.draw_images();
      // for (auto& p : result.persons()) {
      //   printf("image: %s\nPerson: name(%s), fused(%d), source(%d), face(%d)\n", file.c_str(), p.name().c_str(), p.fused(), p.source(), p.face_from_detection());
      // }

      if (step) {
        char s;
        cin >> s;
      } else {
        this_thread::sleep_for(chrono::milliseconds(interval_ms));
      }
    }

    loop_cnt--;
    if (loop_cnt <= 0) break;
  }

  return 0;
}
