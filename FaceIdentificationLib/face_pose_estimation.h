/*
 * License: 3-clause BSD. See LICENSE file in root directory.
 * Copyright(c) 2015-2016 Intel Corporation. All Rights Reserved.
 * */

#include "opencv2/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#define MAX_LANDMARK_NUM   10
class CFacePoseEstimation {
public:
  cv::Mat m_FaceNorm;
  double m_dPan_Angle;
  double m_dTilt_Angle;

  // landmark method
  int m_nLandMarkNum;
  double *m_LandMarkArray;
  cv::Mat m_LandMarkMatrix;
  

  bool PoseEstimationWithLandmarks(int nWidth, int nHeight, cv::Point2f*Landmark, unsigned short *lpDepthMap, int nLandmark_Num);
  bool Get3DLandMark(int nWidth, int nHeight, cv::Point2f*Landmark, unsigned short *lpDepthMap, int nLandmark_Num);
  void NormEstimationWithLandmark();
  void LandmarkResidue(double* ResidueArray);

  void FaceNorm_Normalization();
public:
  CFacePoseEstimation();
  ~CFacePoseEstimation();
};

