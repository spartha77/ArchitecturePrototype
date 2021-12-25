#pragma once
#ifndef __FACEDETECTION_HPP__
#define __FACEDETECTION_HPP__

#include <vector>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <inference_engine.hpp>
#include "FaceDetectionLib.h"

#define DETECTION_THRESHOLD 0.6
#define DETECTION_NMS 0.4
#define OPENVINO_DET_INPUT_WIDTH 320
#define OPENVINO_DET_INPUT_HEIGHT 240

struct Point
{
    float _x;
    float _y;
};
struct bbox
{
    float x1;
    float y1;
    float x2;
    float y2;
    float s;
    Point point[5];
};

struct box
{
    float cx;
    float cy;
    float sx;
    float sy;
};
inline bool cmp(bbox a, bbox b)
{
    if (a.s > b.s)
        return true;
    return false;
};

class FACEDETECTIONLIB_API FaceDetection
{
  public:
    FaceDetection(std::string model_path, std::string device);
    ~FaceDetection() { ; };
    bool initialize();
    void detect(cv::Mat img, std::vector<bbox> &total_box);

  private:
    void create_anchor(std::vector<box> &anchor, int w, int h);
    void nms(std::vector<bbox> &input_boxes, float NMS_THRESH);

  private:
    std::string model_path_;
    std::string device_;

    std::string imageInputName;
    std::vector<std::string> outputNames;
    std::string ldmk_name, cls_name, loc_name;
    std::string xml_file, bin_file;

    InferenceEngine::ExecutableNetwork executable_network;
    InferenceEngine::InferRequest infer_request;
    InferenceEngine::InferencePlugin plugin;
};
#endif