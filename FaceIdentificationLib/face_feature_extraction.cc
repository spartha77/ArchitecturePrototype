#include "face_feature_extraction.h"

FaceFeatureExtraction::FaceFeatureExtraction(const std::string &path, const std::string& dev, int feature_dim)
{
    device_ = dev;
    model_path_ = path;
    mChannels = 3;
    mWidth = 112;
    mHeight = 112;
    mFeatureDim = feature_dim;
}
bool FaceFeatureExtraction::initialize()
{
    openvino_.initialize(model_path_, "face_id", device_);
    return true;
}

float *FaceFeatureExtraction::extractFeature(cv::Mat input_img, std::vector<cv::Point2f> &ldmks)
{
    cv::Mat affined_img = affine(input_img, ldmks);
    cv::Mat rgb;
    cv::cvtColor(affined_img, rgb, cv::COLOR_BGR2RGB);
    cv::Size input_geometry(mWidth, mHeight);
    if (rgb.size() != input_geometry)
        cv::resize(rgb, rgb, input_geometry);
    rgb.convertTo(rgb, CV_32FC3);
    rgb = rgb / 255.0;

    const float *feature = openvino_.getFeatures(rgb);
    float *res_feature = new float[mFeatureDim];
    memcpy(res_feature, feature, sizeof(float) * mFeatureDim);
    return res_feature;
}

cv::Mat FaceFeatureExtraction::affine(cv::Mat &src, std::vector<cv::Point2f> &ldmks)
{
    cv::Mat dst = cv::Mat::zeros(mHeight, mWidth, src.type());

    /*cv::Mat warpMat = cv::estimateRigidTransform(ldmks, mTarget, true);*/
    cv::Mat warpMat = cv::estimateAffine2D(ldmks, mTarget); // PARTHA
    cv::warpAffine(src, dst, warpMat, dst.size(), cv::INTER_LINEAR, cv::BORDER_TRANSPARENT);
    return dst;
}
