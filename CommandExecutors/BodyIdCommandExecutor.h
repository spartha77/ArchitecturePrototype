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
struct BodyIdCommandExecutorInputData
{
    std::string modelDirectoryPath;
    std::string dataDirectoryPath;
};

class BodyIdCommandExecutor_impl;
class COMMANDEXECUTORS_API BodyIdCommandExecutor
{
private:
    BodyIdCommandExecutorInputData m_inputData;
    std::unique_ptr< BodyIdCommandExecutor_impl> m_implementor;
    bool m_OpenCVHighGUIDisplay;
    std::function<void(cv::Mat*)> m_UIUpdateHandlerSTDFunction;
    UIUpdateCallbackFuncPtr m_UIUpdateHandler = nullptr;
public:
    BodyIdCommandExecutor(/*std::function<void(cv::Mat*)>*/UIUpdateCallbackFuncPtr uiUpdateHandler, bool openCVHighGUIDsplay = true);
    BodyIdCommandExecutor(std::function<void(cv::Mat*)> uiUpdateHandlerSTDFunction, bool openCVHighGUIDsplay = true);
    ~BodyIdCommandExecutor();
    BodyIdCommandExecutor(const BodyIdCommandExecutor& other);
    BodyIdCommandExecutor(const std::string& modelDirectoryPath,
        const std::string& dataDirectoryPath, /*std::function<void(cv::Mat*)>*/UIUpdateCallbackFuncPtr uiUpdateHandler,
        bool openCVHighGUIDsplay = true);
    BodyIdCommandExecutor(const std::string& modelDirectoryPath,
        const std::string& dataDirectoryPath, std::function<void(cv::Mat*)> uiUpdateHandlerSTDFunction,
        bool openCVHighGUIDsplay = true);
    //BodyIdCommandExecutor& operator=(const BodyIdCommandExecutor& rhs);
    void Terminate();
    std::unique_ptr<NullData> RunExecute(const BodyIdCommandExecutorInputData& inputData);
    void RegisterHostUIUpdateEventHandler();
    void UnRegisterHostUIUpdateEventHandler();

    std::function<std::unique_ptr<NullData>(BodyIdCommandExecutorInputData&)>
        GetSkillExecutionMethod();

    // For event handler
    void OnEventNotified(cv::Mat& openCVImage);
    std::function <void(cv::Mat & mat)> GetEventNotifyMethodCbMethod();

    void SetBitmapFromCVMatFunctionPtr(UIUpdateCallbackFuncPtr callback);
};
