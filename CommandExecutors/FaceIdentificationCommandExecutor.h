#pragma once
#include "CommandExecutors.h"
#include <string>
#include <memory>
#include <functional>

namespace cv {
    class Mat;
}

#ifdef _WINDOWS
typedef void(__stdcall* UIUpdateCallbackFuncPtr)(cv::Mat*);
#else
typedef void(*UIUpdateCallbackFuncPtr)(cv::Mat*);
#endif


class NullData;
struct FaceIdentificationCommandExecutorInputData
{
    std::string modelDirectoryPath;
    std::string dataDirectoryPath;
};

class FaceIdentificationCommandExecutor_impl;
class COMMANDEXECUTORS_API FaceIdentificationCommandExecutor
{
private:
    FaceIdentificationCommandExecutorInputData m_inputData;
    std::unique_ptr< FaceIdentificationCommandExecutor_impl> m_PrivateImplementor;
    bool m_OpenCVHighGUIDisplay;
    std::function<void(cv::Mat*)> m_UIUpdateHandlerSTDFunction;
    UIUpdateCallbackFuncPtr m_UIUpdateHandler = nullptr;
public:
    FaceIdentificationCommandExecutor(UIUpdateCallbackFuncPtr uiUpdateHandler, bool openCVHighGUIDsplay = true);
    FaceIdentificationCommandExecutor(std::function<void(cv::Mat*)> uiUpdateHandlerSTDFunction, bool openCVHighGUIDsplay = true);
    ~FaceIdentificationCommandExecutor();
    FaceIdentificationCommandExecutor(const FaceIdentificationCommandExecutor& other);
    FaceIdentificationCommandExecutor(const std::string& modelDirectoryPath,
        const std::string& dataDirectoryPath, /*std::function<void(cv::Mat*)>*/UIUpdateCallbackFuncPtr uiUpdateHandler,
        bool openCVHighGUIDsplay = true);
    FaceIdentificationCommandExecutor(const std::string& modelDirectoryPath,
        const std::string& dataDirectoryPath, std::function<void(cv::Mat*)> uiUpdateHandlerSTDFunction,
        bool openCVHighGUIDsplay = true);
    /*FaceIdentificationCommandExecutor& operator=(const FaceIdentificationCommandExecutor& rhs);*/
    void Terminate();
    std::unique_ptr<NullData> RunExecute(const FaceIdentificationCommandExecutorInputData& inputData);
    void RegisterHostUIUpdateEventHandler();
    void UnRegisterHostUIUpdateEventHandler();

   
    // For event handler
    void OnEventNotified(cv::Mat& openCVImage);
    

    void SetBitmapFromCVMatFunctionPtr(UIUpdateCallbackFuncPtr callback);
};