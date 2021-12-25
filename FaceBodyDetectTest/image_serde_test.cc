#include <image_serde.h>

#include <string>
#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <person_id.pb.h>

using namespace std;

int main(int argc, char** argv) {

  if (argc < 2) {
    cout << "Usage: image_serde_test <image_path>" << endl;
    return -1;
  }

  string image_path(argv[1]);
  cv::Mat image = cv::imread(image_path, cv::IMREAD_COLOR);
  if (image.empty()) {
    cout << "fail to read image: " << image_path << endl;
    return -1;
  }

  cout << image.cols << "x" << image.rows << endl;
  cout << image.elemSize() << endl;
  cout << image.total() << ", " << image.rows*image.cols*image.elemSize() << endl;

  cv::imshow("ori", image);

  Image image_pb = image_to_pb(image);

  cv::Mat image_der = image_from_pb(image_pb);

  cv::imshow("reload", image_der);
  cv::waitKey(5000);

  return 0;
}
