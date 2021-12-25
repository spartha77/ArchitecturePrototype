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
struct FaceDetectionCommandExecutorInputData
{
    std::string modelDirectoryPath;
    std::string dataDirectoryPath;
};

class FaceDetectionCommandExecutor_impl;
class COMMANDEXECUTORS_API FaceDetectionCommandExecutor
{
private:
    FaceDetectionCommandExecutorInputData m_inputData;
    std::unique_ptr< FaceDetectionCommandExecutor_impl> m_implementor;
    bool m_OpenCVHighGUIDisplay = true;
    std::function<void(cv::Mat*)> m_UIUpdateHandlerSTDFunction;
    UIUpdateCallbackFuncPtr m_UIUpdateHandler = nullptr;
public:
    FaceDetectionCommandExecutor(/*std::function<void(cv::Mat*)>*/UIUpdateCallbackFuncPtr uiUpdateHandler = nullptr, bool openCVHighGUIDsplay = true);
    FaceDetectionCommandExecutor(std::function<void(cv::Mat*)> uiUpdateHandlerSTDFunction, bool openCVHighGUIDsplay = true);
    ~FaceDetectionCommandExecutor();
    FaceDetectionCommandExecutor(const FaceDetectionCommandExecutor& other);
    FaceDetectionCommandExecutor(const std::string& modelDirectoryPath,
        const std::string& dataDirectoryPath, /*std::function<void(cv::Mat*)>*/UIUpdateCallbackFuncPtr uiUpdateHandler,
        bool openCVHighGUIDsplay = true);
    FaceDetectionCommandExecutor(const std::string& modelDirectoryPath,
        const std::string& dataDirectoryPath, std::function<void(cv::Mat*)> uiUpdateHandlerSTDFunction,
        bool openCVHighGUIDsplay = true);
    //FaceDetectionCommandExecutor& operator=(const FaceDetectionCommandExecutor& rhs);
    void Terminate();
    std::unique_ptr<NullData> RunExecute(const FaceDetectionCommandExecutorInputData& inputData);
    void RegisterHostUIUpdateEventHandler();
    void UnRegisterHostUIUpdateEventHandler();

    std::function<std::unique_ptr<NullData>(FaceDetectionCommandExecutorInputData&)>
        GetSkillExecutionMethod();
    
    // For event handler
    void OnEventNotified(cv::Mat& openCVImage);
    std::function <void(cv::Mat & mat)> GetEventNotifyMethodCbMethod();

    void SetBitmapFromCVMatFunctionPtr(UIUpdateCallbackFuncPtr callback);
};