#ifndef _FACE_IDENTIFICATION_H_
#define _FACE_IDENTIFICATION_H_

#include <opencv2/opencv.hpp>
#include <openvino_lib.h>
#include <FaceIdentificationLib.h>

class FACEIDENTIFICATIONLIB_API FaceFeatureExtraction{
public:
    FaceFeatureExtraction(const std::string &path,  const std::string& dev, int feature_dim);
    ~FaceFeatureExtraction() = default;
    bool initialize();
public:
    float* extractFeature(cv::Mat input_img, std::vector<cv::Point2f> &ldmks);

private:
    cv::Mat affine(cv::Mat &src, std::vector<cv::Point2f> &ldmks);

private:
    std::string model_path_;
    std::string device_;
    openvino_lib openvino_;

    const std::vector<cv::Point2f> mTarget = {{38.2946, 51.6963}, {73.5318, 51.5014},
                                        {56.0252, 71.7366}, {41.5493, 92.3655}, {70.7299, 92.2041}};
    int mChannels;
    int mWidth;
    int mHeight;
    int mFeatureDim;

    bool log_enabled_ = false;
    const char* log_prefix_ = "FaceFeatureExtraction";
};
#endif
