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
struct HumanDetectionCommandExecutorInputData
{
    std::string modelDirectoryPath;
    std::string dataDirectoryPath;
};

class HumanDetectionCommandExecutor_impl;
class COMMANDEXECUTORS_API HumanDetectionCommandExecutor
{
private:
    HumanDetectionCommandExecutorInputData m_inputData;
    std::unique_ptr< HumanDetectionCommandExecutor_impl> m_implementor;
    bool m_OpenCVHighGUIDisplay;
    std::function<void(cv::Mat*)> m_UIUpdateHandlerSTDFunction;
    UIUpdateCallbackFuncPtr m_UIUpdateHandler = nullptr;
public:
    HumanDetectionCommandExecutor(UIUpdateCallbackFuncPtr uiUpdateHandler, bool openCVHighGUIDsplay = true);
    HumanDetectionCommandExecutor(std::function<void(cv::Mat*)> uiUpdateHandlerSTDFunction, bool openCVHighGUIDsplay = true);
    ~HumanDetectionCommandExecutor();
    HumanDetectionCommandExecutor(const HumanDetectionCommandExecutor& other);
    HumanDetectionCommandExecutor(const std::string& modelDirectoryPath,
        const std::string& dataDirectoryPath, /*std::function<void(cv::Mat*)>*/UIUpdateCallbackFuncPtr uiUpdateHandler,
        bool openCVHighGUIDsplay = true);
    HumanDetectionCommandExecutor(const std::string& modelDirectoryPath,
        const std::string& dataDirectoryPath, std::function<void(cv::Mat*)>  uiUpdateHandlerSTDFunction,
        bool openCVHighGUIDsplay = true);
    //HumanDetectionCommandExecutor& operator=(const HumanDetectionCommandExecutor& rhs);
    void Terminate();
    std::unique_ptr<NullData> RunExecute(const HumanDetectionCommandExecutorInputData& inputData);
    void RegisterHostUIUpdateEventHandler();
    void UnRegisterHostUIUpdateEventHandler();

    std::function<std::unique_ptr<NullData>(HumanDetectionCommandExecutorInputData&)>
        GetSkillExecutionMethod();

    // For event handler
    void OnEventNotified(cv::Mat& openCVImage);
    std::function <void(cv::Mat & mat)> GetEventNotifyMethodCbMethod();

    void SetBitmapFromCVMatFunctionPtr(UIUpdateCallbackFuncPtr callback);
};
