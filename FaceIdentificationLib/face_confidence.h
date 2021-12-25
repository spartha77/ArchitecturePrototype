#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <opencv2/opencv.hpp>
#include "FaceIdentificationLib.h"

//#include "face_pose_estimation.h"


#define FCM_INTENSITY_ROW_NUM 6
#define FCM_INTENSITY_COL_NUM 6

typedef struct _FaceCMFeature {
    int nFaceID;
    double dSimilarity;
    double FaceIntensity_Similarity;
    double dFacePan;
    double dFaceTilt;
    double FaceIntensityFeature[FCM_INTENSITY_ROW_NUM * FCM_INTENSITY_COL_NUM];
    double* FaceFeature2;
} FaceCMFeature;

class  CFacePoseEstimation;
class FACEIDENTIFICATIONLIB_API CFaceConfidence {
private:
    int m_nPersonNum;
    int m_nTemplateNum;    // template number
    //int *m_PersonIDArray;  // template person ID   // not used // Prajwal
    FaceCMFeature m_FaceCMFeature; // FaceCMFeature for each template

    double m_dCM_OriginalScore;
    double m_dCM_OffsetScore;
    int m_nResultFaceID;
    int m_nResultFaceIndex;
    // Feature of

    bool log_enabled_ = false;
    const char* log_prefix_ = "CFaceConfidence";

    std::unique_ptr<CFacePoseEstimation> FaceEstimator;
public:
    CFaceConfidence();
    ~CFaceConfidence();
public:
    void SetFaceID(int nFaceID) { m_nResultFaceID = nFaceID; };
    bool Init(char* sModelFilename);

    bool SaveFCMFeature(char* lpFileName, FaceCMFeature FaceCMFeatureTemplate);// Input:filename, FaceCMFeature
    bool LoadFCMFeature(char* lpFileName, FaceCMFeature& FaceCMFeatureTemplate);

    bool RegisterFCMFeature(cv::Mat& lpColorImage, cv::Mat& lpDepthImage, cv::Mat& lpFaceImage,
        std::vector<cv::Point2d> Landmarks, const char* lpFilename, int nFaceID);
    bool RegisterFCMFeature_Appearance(cv::Mat& FaceImage, FaceCMFeature& FaceCMFeatureTemplate);
    bool RegisterFCMFeature_Pose(cv::Mat& lpColorImage, cv::Mat& lpDepthImage,
        std::vector<cv::Point2d> Landmarks, FaceCMFeature& FaceCMFeatureTemplate);

    bool ExtractFCMFeature(const cv::Mat& lpColorImage, cv::Mat& lpDepthImage, cv::Mat& lpFaceImage,
        std::vector<cv::Point2d> Landmarks, FaceCMFeature& FaceCMFeatureTemplate);

    bool EstimateFCMFeature_Intensity(const cv::Mat& FaceImage, FaceCMFeature& FaceCMFeatureTemplate);
    double MatchFCMFeature_Intensity(std::vector<FaceCMFeature>& All_Result,
        FaceCMFeature& FaceCMFeatureTemplate);
    double FaceCMPredict_Intensity(cv::Mat FaceImage, std::vector<cv::Point2d> pts,
        std::vector<FaceCMFeature>& All_Result);

    bool SimilarityNormalization(std::vector<FaceCMFeature>& All_Result);
    bool OffsetScoreEstimation(std::vector<FaceCMFeature>& All_Result);
    bool OriginalScoreEstimation(std::vector<FaceCMFeature>& All_Result);

    bool EstimateFCMFeature_Pose(cv::Mat DepthImage, std::vector<cv::Point2d> pts,
        FaceCMFeature& FaceCMFeatureTemplate);
    double FaceCMPredict_Pose(cv::Mat DepthImage, std::vector<cv::Point2d> pts,
        std::vector<FaceCMFeature>& All_Result);

    double FaceCMPredict_Heuritic(cv::Mat FaceImage, std::vector<cv::Point2d> pts);
    double FaceCMPredict(cv::Mat ColorImage, cv::Mat DepthImage, cv::Mat FaceImage,
        std::vector<cv::Point2d> pts, std::vector<FaceCMFeature>& All_Result);
};
