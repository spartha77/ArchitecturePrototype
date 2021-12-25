#include "face_confidence.h"
#include "opencv2/imgproc/imgproc.hpp"
#include <logging.h>
#include "face_pose_estimation.h"

using namespace std;

// model file include:
//  int m_nPersonNum;
//  int m_nTemplateNum;    // template number
//  int *m_PersonIDArray;  // template person ID
//  struct FaceCMFeature *m_FaceCMFeature; // FaceCMFeature for each template
bool CFaceConfidence::Init(char* sModelFilename) {
    FaceEstimator = std::make_unique< CFacePoseEstimation>();
    return false;
}
CFaceConfidence::~CFaceConfidence()
{

}
CFaceConfidence::CFaceConfidence() {
    //log_enabled_ = getenv("LOG_FACE_CONF") != nullptr;
#if defined _WINDOWS  
    char* pValue = nullptr;
    size_t length = 0;
    errno_t errorVal = _dupenv_s(&pValue, &length, "LOG_FACE_CONF");
#else
  error_t errorVal = getenv("LOG_FACE_CONF") != nullptr;
#endif
    log_enabled_ = (errorVal == 0);
    if (log_enabled_) {
        std::cout << "[" << log_prefix_ << "] log enabled" << std::endl;
    }
    FaceEstimator = std::make_unique< CFacePoseEstimation>();
}

//------------------------------------------------------------------------------------------
// register FCM feature for a template
// FCM feature: nFaceID, appearance feature, pose feature
bool CFaceConfidence::RegisterFCMFeature(cv::Mat& lpColorImage, cv::Mat& lpDepthImage, cv::Mat& lpFaceImage, vector<cv::Point2d> Landmarks, const char* lpFilename, int nFaceID) {
    FaceCMFeature FaceCMFeatureTemplate;
    FaceCMFeatureTemplate.nFaceID = nFaceID;
    FaceCMFeatureTemplate.dSimilarity = 0.0f;
    FaceCMFeatureTemplate.FaceIntensity_Similarity = 0.0f;
    FaceCMFeatureTemplate.FaceFeature2 = NULL;
    bool bOK = RegisterFCMFeature_Appearance(lpFaceImage, FaceCMFeatureTemplate);
    if (!bOK) return false;

    bOK = RegisterFCMFeature_Pose(lpColorImage, lpDepthImage, Landmarks, FaceCMFeatureTemplate);

    SaveFCMFeature((char*)lpFilename, FaceCMFeatureTemplate);
    return true;
}

bool CFaceConfidence::ExtractFCMFeature(const cv::Mat& lpColorImage, cv::Mat& lpDepthImage,
    cv::Mat& lpFaceImage, vector<cv::Point2d> Landmarks, FaceCMFeature& FaceCMFeatureTemplate) {

    FaceCMFeatureTemplate.dSimilarity = 0.0f;
    FaceCMFeatureTemplate.FaceIntensity_Similarity = 0.0f;
    FaceCMFeatureTemplate.FaceFeature2 = NULL;

    bool bOK = EstimateFCMFeature_Intensity(lpFaceImage, FaceCMFeatureTemplate);
    bOK &= EstimateFCMFeature_Pose(lpDepthImage, Landmarks, FaceCMFeatureTemplate);

    return bOK;
}

// estimate FCM pose feature
bool CFaceConfidence::RegisterFCMFeature_Pose(cv::Mat& lpColorImage, cv::Mat& lpDepthImage,
    vector<cv::Point2d> Landmarks, FaceCMFeature& FaceCMFeatureTemplate) {
    bool bOK = EstimateFCMFeature_Pose(lpDepthImage, Landmarks, FaceCMFeatureTemplate);
    return bOK;
}

// estimate FCM appearance feature
bool CFaceConfidence::RegisterFCMFeature_Appearance(cv::Mat& FaceImage,
    FaceCMFeature& FaceCMFeatureTemplate) {

    return EstimateFCMFeature_Intensity(FaceImage, FaceCMFeatureTemplate);
}

// load registered FCM features
bool CFaceConfidence::LoadFCMFeature(char* lpFileName, FaceCMFeature& FaceCMFeatureTemplate) {
    FILE* InputFileStream;
#if defined _WINDOWS
    errno_t fileOPenError = fopen_s(&InputFileStream, lpFileName, "rb");
    if (fileOPenError != 0)
        return false;
#else
  InputFileStream = fopen(lpFileName, "rb");
  if (InputFileStream == NULL)
    return false;
#endif

    int nRead = fread(&FaceCMFeatureTemplate, sizeof(FaceCMFeature), 1, InputFileStream);
    fclose(InputFileStream);

    if (nRead != sizeof(FaceCMFeature))
        return false;
    return true;
}

// save registered FCM features
bool CFaceConfidence::SaveFCMFeature(char* lpFileName, FaceCMFeature FaceCMFeatureTemplate) {
    /*FILE *OutputFile;
    OutputFile = fopen(lpFileName, "wb");
    if (OutputFile == NULL)
      return false;*/

    FILE* OutputFileStream;
#if defined _WINDOWS 
    errno_t fileOPenError = fopen_s(&OutputFileStream, lpFileName, "wb");
    if (fileOPenError != 0)
        return false;
#else
  OutputFileStream = fopen(lpFileName, "wb");
  if (OutputFileStream == NULL)
    return false;
#endif

    fwrite(&FaceCMFeatureTemplate, sizeof(FaceCMFeature), 1, OutputFileStream);
    fclose(OutputFileStream);
    return true;
}
//------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------
//  Intensity Distribution
//  Estimate the intensity distribution features for the face image
bool CFaceConfidence::EstimateFCMFeature_Intensity(const cv::Mat& FaceImage,
    FaceCMFeature& FaceCMFeatureTemplate) {
    int i, j;
    cv::Size t = FaceImage.size();
    int nChannle = FaceImage.channels();

    cv::Mat gray(FaceImage.rows, FaceImage.cols, FaceImage.depth());
    if (nChannle != 1)
        cvtColor(FaceImage, gray, cv::COLOR_BGRA2GRAY);
    else gray = FaceImage;

    int nModuleWidth = t.width / FCM_INTENSITY_COL_NUM;
    int nModuleHeight = t.height / FCM_INTENSITY_ROW_NUM;
    int nStart_x = (t.width - nModuleWidth * FCM_INTENSITY_COL_NUM) / 2;
    int nStart_y = (t.height - nModuleHeight * FCM_INTENSITY_ROW_NUM) / 2;

    int nModuleWidth_No, nModuleHeight_No;
    int nModuleWidth_Offset, nModuleHeight_Offset;
    int nModule_Index = 0;
    unsigned char BTemp;
    for (i = 0; i < FCM_INTENSITY_COL_NUM; i++)
        for (j = 0; j < FCM_INTENSITY_COL_NUM; j++) {
            FaceCMFeatureTemplate.FaceIntensityFeature[nModule_Index] = 0.0f;
            nModuleHeight_Offset = nStart_y + j * nModuleHeight;
            nModuleWidth_Offset = nStart_x + i * nModuleWidth;
            for (nModuleHeight_No = 0; nModuleHeight_No < nModuleHeight; nModuleHeight_No++)
                for (nModuleWidth_No = 0; nModuleWidth_No < nModuleWidth; nModuleWidth_No++) {
                    BTemp = gray.at<unsigned char>(nModuleHeight_Offset + nModuleHeight_No, nModuleWidth_Offset + nModuleWidth_No);
                    FaceCMFeatureTemplate.FaceIntensityFeature[nModule_Index] += BTemp;
                }
            nModule_Index++;
        }

    double dSum = 0.0f;
    nModule_Index = 0;
    for (i = 0; i < FCM_INTENSITY_COL_NUM; i++)
        for (j = 0; j < FCM_INTENSITY_COL_NUM; j++) {
            dSum += FaceCMFeatureTemplate.FaceIntensityFeature[nModule_Index];
            nModule_Index++;
        }

    nModule_Index = 0;
    for (i = 0; i < FCM_INTENSITY_COL_NUM; i++)
        for (j = 0; j < FCM_INTENSITY_COL_NUM; j++) {
            FaceCMFeatureTemplate.FaceIntensityFeature[nModule_Index] /= dSum;
            nModule_Index++;
        }
    return true;
}

//Calculate the difference between the intensity distribution features of two face images
double CFaceConfidence::MatchFCMFeature_Intensity(vector<FaceCMFeature>& All_Result,
    FaceCMFeature& FaceCMFeatureTemplate) {

    if (All_Result.size() <= 0)
        return 0.0f;
    int i, j;
    double dDiff = 0;

    double dMin_Diff = 1000.0f;
    double dMax_Diff = -1000.0f;
    for (size_t m = 0; m < All_Result.size(); m++) {
        int nModule_Index = 0;
        for (i = 0; i < FCM_INTENSITY_COL_NUM; i++)
            for (j = 0; j < FCM_INTENSITY_COL_NUM; j++) {
                dDiff += fabs(All_Result[m].FaceIntensityFeature[nModule_Index] - FaceCMFeatureTemplate.FaceIntensityFeature[nModule_Index]);
                nModule_Index++;
            }

        All_Result[m].FaceIntensity_Similarity = dDiff;

        if (dMin_Diff > dDiff) dMin_Diff = dDiff;
        if (dMax_Diff < dDiff) dMax_Diff = dDiff;
    }

    // Differece --> Similarity
    double dTemp;

    double dScale = 1.0;
    if (fabs(dMax_Diff - dMin_Diff) > 0.01)
        dScale = 1.0 / (dMax_Diff - dMin_Diff);
    for (size_t m = 0; m < All_Result.size(); m++) {
        dTemp = All_Result[m].FaceIntensity_Similarity;
        All_Result[m].FaceIntensity_Similarity = 1.0 - (dTemp - dMin_Diff) * dScale;
        //All_Result[m].FaceIntensity_Similarity = (1.0 - dTemp);
        if (All_Result[m].FaceIntensity_Similarity < 0) All_Result[m].FaceIntensity_Similarity = 0.0f;
    }

    double dFinalScore = 0.0f;
    if ((m_nResultFaceIndex >= 0) && (m_nResultFaceIndex < (int)All_Result.size()))
        dFinalScore = All_Result[m_nResultFaceIndex].FaceIntensity_Similarity;
    return dFinalScore;
}

// predict the face confidencemeasure based on intensity features
double CFaceConfidence::FaceCMPredict_Intensity(cv::Mat FaceImage, vector<cv::Point2d> pts,
    vector<FaceCMFeature>& All_Result) {
    //double dScore_Heuritic = FaceCMPredict_Heuritic(FaceImage, pts);
    //return dScore_Heuritic;


    FaceCMFeature CurrentFaceCMFeature;
    EstimateFCMFeature_Intensity(FaceImage, CurrentFaceCMFeature);
    double dScore = MatchFCMFeature_Intensity(All_Result, CurrentFaceCMFeature);
    return dScore;
}
//------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------
//   Score list
// normalize the scores from different templates
bool CFaceConfidence::OriginalScoreEstimation(vector<FaceCMFeature>& All_Result) {
    m_nResultFaceIndex = -1;
    m_dCM_OriginalScore = 1.0f;
    m_dCM_OffsetScore = 1.0f;
    if (All_Result.size() <= 0)
        return false;

    double dMax_Score = -100.0;
    double dOutliear_Max_Score = -100;
    for (size_t i = 0; i < All_Result.size(); i++) {
        if (All_Result[i].nFaceID == m_nResultFaceID) {
            if (dMax_Score < All_Result[i].dSimilarity) {
                dMax_Score = All_Result[i].dSimilarity;
                m_nResultFaceIndex = i;
            }
        }
        else {
            dOutliear_Max_Score = std::max(dOutliear_Max_Score, All_Result[i].dSimilarity);
        }
    }
    _LOG("RESULT ID:%d\n", m_nResultFaceID);
    m_dCM_OriginalScore = dMax_Score;
    if (dOutliear_Max_Score < 0) {
        m_dCM_OffsetScore = 1.0f;
        _LOG("dOutliear_Max_Score < 0, m_dCM_OffsetScore = 1.0\n");
        return true;
    }
    m_dCM_OffsetScore = 3.0 * (dMax_Score - dOutliear_Max_Score);
    _LOG("dMax_Score %f, dOutliear_Max_Score %f\n", dMax_Score, dOutliear_Max_Score);
    return true;
}

// normalize the scores from different templates
bool CFaceConfidence::SimilarityNormalization(vector<FaceCMFeature>& All_Result) {
    double dMin_Score = 100.0;
    double dMax_Score = -100.0;
    for (size_t i = 0; i < All_Result.size(); i++) {
        dMin_Score = std::min(dMin_Score, All_Result[i].dSimilarity);
        dMax_Score = std::max(dMax_Score, All_Result[i].dSimilarity);
    }

    double dScale = 1.0 / (dMax_Score - dMin_Score);
    for (size_t i = 0; i < All_Result.size(); i++)
        All_Result[i].dSimilarity = (All_Result[i].dSimilarity - dMin_Score) * dScale;
    return true;
}

bool CFaceConfidence::OffsetScoreEstimation(vector<FaceCMFeature>& All_Result) {
    return true;
}
//------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------
// predict the heuritic clues
double CFaceConfidence::FaceCMPredict_Heuritic(cv::Mat FaceImage, vector<cv::Point2d> pts) {
    // face size clue
    double dScore = 1.0;

    double dDistance_x = pts[0].x - pts[1].x;
    double dDistance_y = pts[0].y - pts[1].y;

    double dDistance = sqrt(dDistance_x * dDistance_x + dDistance_y * dDistance_y);
    dScore = dDistance / 128;
    if (dScore > 1.0) dScore = 1.0;
    return dScore;
}
//------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------
// Estimate the face pose features
bool CFaceConfidence::EstimateFCMFeature_Pose(cv::Mat DepthImage, vector<cv::Point2d> pts,
    FaceCMFeature& FaceCMFeatureTemplate) {

    if (DepthImage.rows == 0 || DepthImage.cols == 0) {
        FaceCMFeatureTemplate.dFacePan = -1.0f;
        FaceCMFeatureTemplate.dFaceTilt = -1.0f;
        return false;
    }

    int nLandmarkNum = pts.size();
    cv::Point2f Landmark[MAX_LANDMARK_NUM];
    for (int i = 0; i < nLandmarkNum; i++) {
        Landmark[i].x = pts[i].x;
        Landmark[i].y = pts[i].y;
    }
    unsigned short* lpDepthData = DepthImage.ptr<unsigned short>(0);//
    FaceEstimator->PoseEstimationWithLandmarks(DepthImage.cols, DepthImage.rows, Landmark, lpDepthData, 5);

    FaceCMFeatureTemplate.dFacePan = FaceEstimator->m_dPan_Angle;
    FaceCMFeatureTemplate.dFaceTilt = FaceEstimator->m_dTilt_Angle;
    return true;
}

// predict the face confidencemeasure
double CFaceConfidence::FaceCMPredict_Pose(cv::Mat DepthImage, vector<cv::Point2d> pts,
    vector<FaceCMFeature>& All_Result) {

    if (DepthImage.rows == 0 || DepthImage.cols == 0) {
        return 1.0f;
    }
    FaceCMFeature FaceCMFeatureTemplate;
    EstimateFCMFeature_Pose(DepthImage, pts, FaceCMFeatureTemplate);

    if (All_Result[m_nResultFaceIndex].dFacePan < 0.0f) return 1.0f;
    if (All_Result[m_nResultFaceIndex].dFaceTilt < 0.0f) return 1.0f;

    // double dPan_Diff = FaceCMFeatureTemplate.dFacePan - All_Result[m_nResultFaceIndex].dFacePan;
    // double dTilt_Diff = FaceCMFeatureTemplate.dFaceTilt - All_Result[m_nResultFaceIndex].dFaceTilt;

    // double dDiff = fabs(dPan_Diff) + fabs(dTilt_Diff);
    return 1.0f;
}
//------------------------------------------------------------------------------------------

// predict the face confidencemeasure
double CFaceConfidence::FaceCMPredict(cv::Mat ColorImage, cv::Mat DepthImage, cv::Mat FaceImage,
    vector<cv::Point2d> pts, vector<FaceCMFeature>& All_Result) {

    m_nResultFaceIndex = -1;
    //SimilarityNormalization(All_Result);
    OriginalScoreEstimation(All_Result);

    double dScore_ScoreList = m_dCM_OriginalScore * m_dCM_OffsetScore;
    double dScore_Heuritic = FaceCMPredict_Heuritic(FaceImage, pts);
    double dScore_Intensity = FaceCMPredict_Intensity(FaceImage, pts, All_Result);
    double dScore_Pose = FaceCMPredict_Pose(DepthImage, pts, All_Result);

    double dFinal_Score = dScore_ScoreList + dScore_Heuritic * 0.4 + dScore_Intensity * 0.15 + dScore_Pose * 0.3;

    _LOG("DCM: %f, %f\n", m_dCM_OriginalScore, m_dCM_OffsetScore);
    _LOG("FaceCMPredict: %f, %f, %f, %f, %f\n", dScore_ScoreList, dScore_Heuritic, dScore_Intensity, dScore_Pose, dFinal_Score);

    //  dFinal_Score = dScore_Pose;
    return dFinal_Score;
}
