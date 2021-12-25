/*
 * License: 3-clause BSD. See LICENSE file in root directory.
 * Copyright(c) 2015-2016 Intel Corporation. All Rights Reserved.
 * */

#include "face_pose_estimation.h"
#include "scale_from_depth.h"
#include "math.h"
#define PI 3.1415926
CFacePoseEstimation::CFacePoseEstimation(void) {
  m_nLandMarkNum = 0;
  m_LandMarkArray = (double *)malloc(MAX_LANDMARK_NUM* 3 *sizeof(double));
}

CFacePoseEstimation::~CFacePoseEstimation(void) {
  if(m_LandMarkArray != nullptr) free(m_LandMarkArray);
}

////////////////////////////////////////////////////////////////////////////////////////
/// This routine is a function of CFacePoseEstimation
///  written by Ren Haibing
/// Acknowledge    :
///
/// Function name  : Get3DLandMark
/// Description      : get the 3D world coordinate from the landmarks
///
/// Argument    :  (nWidth, nHeight) -- image size
/// Argument    :  Landmark -- landmark coordinates
/// Argument    :  lpDepthMap -- aligned depth map
///
/// Return type    :
///
/// Create Time    : 2015-3-5  16:50
///
///
/// Side Effect    :
///
///////////////////////////////////////////////////////////////////////////////////////////////
bool CFacePoseEstimation::Get3DLandMark(int nWidth, int nHeight, cv::Point2f *Landmark,
  unsigned short *lpDepthMap, int nLandmark_Num) {

  m_nLandMarkNum = nLandmark_Num;
  if (m_nLandMarkNum > MAX_LANDMARK_NUM)
    m_nLandMarkNum = MAX_LANDMARK_NUM;

  Scale_Depth  DepthTransformer;
  double Image_Coord[3];
  bool bOK = true;
  int x,y;
  for(int i=0;i<m_nLandMarkNum;i++) {
    x = int(Landmark[i].x + 0.5);
    y = int(Landmark[i].y + 0.5);
    Image_Coord[0] = x;
    Image_Coord[1] = y;
    Image_Coord[2] = lpDepthMap[y*nWidth + x];
    if(Image_Coord[2]<10)
      bOK = false;
    DepthTransformer.Coordinate_Image_2_World(nWidth, nHeight, Image_Coord, &(m_LandMarkArray[i*3]));
  }

  return bOK;
}
////////////////////////////////////////////////////////////////////////////////////////
/// This routine is a function of CFacePoseEstimation
///  written by Ren Haibing
/// Acknowledge    :
///
/// Function name  : NormEstimationWithLandmark
/// Description      : estimate the face normal with 6 landmarks
///
/// Argument    :
///
/// Return type    :
///
/// Create Time    : 2015-3-5  17:10
///
///
/// Side Effect    :
///
///////////////////////////////////////////////////////////////////////////////////////////////
void CFacePoseEstimation::NormEstimationWithLandmark() {
  // A * norm = B
  cv::Mat LandMarkMatrix(m_nLandMarkNum, 3, CV_64FC1);//A
  cv::Mat Result(m_nLandMarkNum, 1, CV_64FC1);  // B
  double *lpDouble;
  for(int i=0;i<m_nLandMarkNum;i++)
  {
    lpDouble = LandMarkMatrix.ptr<double>(i);
    lpDouble[0]= m_LandMarkArray[i*3];
    lpDouble[1]= m_LandMarkArray[i*3+1];
    lpDouble[2]= m_LandMarkArray[i*3+2];

    *Result.ptr<double>(i) = 1.0;
  }
  m_LandMarkMatrix = LandMarkMatrix;

  // norm = Inv(A_t * A) * B
  cv::Mat Inv_A = LandMarkMatrix.t();
  cv::Mat Temp = Inv_A * LandMarkMatrix;
  cv::Mat Inv_Temp = Temp.inv();
  cv::Mat Temp2 = Inv_A * Result;
  m_FaceNorm = Inv_Temp * Temp2;
}

////////////////////////////////////////////////////////////////////////////////////////
/// This routine is a function of CFacePoseEstimation
///  written by Ren Haibing
/// Acknowledge    :
///
/// Function name  : PoseEstimationWith6Landmark
/// Description      : pose estimation with 6 landmarks
///
/// Argument    :  (nWidth, nHeight) -- image size
/// Argument    :  Landmark -- landmark coordinates
/// Argument    :  lpDepthMap -- aligned depth map
///
/// Return type    :
///
/// Create Time    : 2015-3-6  11:10
///
///
/// Side Effect    :
///
///////////////////////////////////////////////////////////////////////////////////////////////
bool CFacePoseEstimation::PoseEstimationWithLandmarks(int nWidth, int nHeight,
                    cv::Point2f *Landmark, unsigned short *lpDepthMap, int nLandmarkNum) {
  // get landmarks 3D coordinates
  bool bSuccess = Get3DLandMark(nWidth, nHeight, Landmark, lpDepthMap, nLandmarkNum);
  if(!bSuccess) return false;

  // estimate the face normal
  NormEstimationWithLandmark();
  // double *temp =  m_FaceNorm.ptr<double>(0);
  //cout << "Unnormalized Face Normal:" << temp[0] << "  "<< temp[1] << "   " << temp[2] << endl;

  // calculate the residue
  double dResidue[6];
  LandmarkResidue(dResidue);
  //cout << "Residue: ";
  //for(int j=0;j<6;j++)
  //  cout << dResidue[j] << "  ";
  //cout<<endl;

  // normalize the face normal and get face pose
  FaceNorm_Normalization();

  return true;
}

////////////////////////////////////////////////////////////////////////////////////////
/// This routine is a function of CFacePoseEstimation
///  written by Ren Haibing
/// Acknowledge    :
///
/// Function name  : LandmarkResidue
/// Description      : calculate the landmark residue
///
/// Argument    :  ResidueArray -- output the residue
///
/// Return type    :
///
/// Create Time    : 2015-3-6  9:23
///
///
/// Side Effect    :
///
///////////////////////////////////////////////////////////////////////////////////////////////
void CFacePoseEstimation::LandmarkResidue(double* ResidueArray) {
  // A * norm = B
  cv::Mat Result(m_nLandMarkNum, 1, CV_64FC1);  // B
  for(int i=0;i<m_nLandMarkNum;i++)
    *Result.ptr<double>(i) = 1.0;

  // Residue = A* norm - B
  cv::Mat Temp = m_LandMarkMatrix * m_FaceNorm;
  cv::Mat ResidueMat = Temp - Result;

  double* lpDouble = ResidueMat.ptr<double>(0);
  for(int i=0;i<m_nLandMarkNum;i++)
    ResidueArray[i] = lpDouble[i];
}
////////////////////////////////////////////////////////////////////////////////////////
/// This routine is a function of CFacePoseEstimation
///  written by Ren Haibing
/// Acknowledge    :
///
/// Function name  : FaceNorm_Normalization
/// Description      : calculate the face normal and calculate the face pose
///
/// Argument    :
///
/// Return type    :
///
/// Create Time    : 2015-3-6  9:55
///
///
/// Side Effect    :
///
///////////////////////////////////////////////////////////////////////////////////////////////

void CFacePoseEstimation::FaceNorm_Normalization() {
  double dValue = 0;
  double *dTemp = m_FaceNorm.ptr<double>(0);
  for(int i=0;i<3;i++)
    dValue += dTemp[i] * dTemp[i];
  dValue = sqrt(dValue);

  for(int i=0;i<3;i++)
    dTemp[i] = dTemp[i]/dValue;

  m_dPan_Angle = asin(dTemp[0]) * 180.0/PI;
  m_dTilt_Angle = asin(dTemp[1]) * 180.0/PI;
}
