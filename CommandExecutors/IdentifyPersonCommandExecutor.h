#pragma once
#include "CommandExecutors.h"
#include <string>
#include <vector>
#include <memory>
#include <functional>

namespace cv
{
    class Mat;
}

namespace AdaptiveHumanTracker
{
    template<typename ObserverData>
    class IObserver;
}

class NullData;
struct IdentifyPersonCommandExecutorInputData
{
    std::string modelDirectoryPath;
    std::string dataDirectoryPath;
};

class IdentifyPersonCommandExecutor;

#ifdef _WINDOWS
typedef void(__stdcall* UIUpdateCallbackFuncPtr)(cv::Mat*);
#else
typedef void(*UIUpdateCallbackFuncPtr)(cv::Mat*);
#endif
//static BitmapFromCVMatFunctionPtr bitmapFromCVMatFunctionPtr;

class IdentifyPersonCommandExecutor_impl;
class COMMANDEXECUTORS_API IdentifyPersonCommandExecutor
{
private:
    IdentifyPersonCommandExecutorInputData m_inputData;
    std::unique_ptr< IdentifyPersonCommandExecutor_impl> m_implementor;
    bool m_OpenCVHighGUIDisplay;

    // event handlers
    //BitmapFromCVMatFunctionPtr m_BitmapFromCVMatFunctionPtr;
    //std::unique_ptr<AdaptiveHumanTracker::IObserver<cv::Mat>> m_IdentifyPersonObserver;
    std::function<void(cv::Mat*)> m_UIUpdateHandlerSTDFunction;
    UIUpdateCallbackFuncPtr m_UIUpdateHandler = nullptr;
public:
    void SetOutputDisplayModeToOPenCV(bool openCvDisplayMode);
    bool IsOutputDisplayModeOpenCV();
    IdentifyPersonCommandExecutor(bool openCVHighGUIDisplay = true);
    IdentifyPersonCommandExecutor(std::function<void(cv::Mat*)>& uiHandlerSTDFunc, bool openCVHighGUIDisplay = true);
    IdentifyPersonCommandExecutor(UIUpdateCallbackFuncPtr uiHandler, bool openCVHighGUIDisplay = true);
    ~IdentifyPersonCommandExecutor();
    void RegisterHostUIUpdateEventHandler();
    void UnRegisterHostUIUpdateEventHandler();
    IdentifyPersonCommandExecutor(const IdentifyPersonCommandExecutor& other);
    //IdentifyPersonCommandExecutor(IdentifyPersonCommandExecutor&& other);
    IdentifyPersonCommandExecutor(const std::string& modelDirectoryPath,
        const std::string& dataDirectoryPath,
        UIUpdateCallbackFuncPtr uiUpdateHandler,
        bool openCVHighGUIDisplay = true);
    IdentifyPersonCommandExecutor(const std::string& modelDirectoryPath,
        const std::string& dataDirectoryPath,
        std::function<void(cv::Mat*)> uiUpdateHandlerSTDFunction,
        bool openCVHighGUIDisplay = true);
    //IdentifyPersonCommandExecutor& operator=(const IdentifyPersonCommandExecutor& rhs);
    std::unique_ptr<NullData> RunExecute(IdentifyPersonCommandExecutorInputData& inputData);
    std::function<std::unique_ptr<NullData>(IdentifyPersonCommandExecutorInputData&)>
        GetSkillExecutionMethod()
    {
        return [this](IdentifyPersonCommandExecutorInputData& data) {return this->RunExecute(data); };
    }
    // For event handler
    void OnEventNotified(cv::Mat& openCVImage);
    std::function <void(cv::Mat & mat)> GetEventNotifyMethodCbMethod()
    {
        return [this](cv::Mat& openCVImage) {return this->OnEventNotified(openCVImage); };
    }

    void SetBitmapFromCVMatFunctionPtr(UIUpdateCallbackFuncPtr callback)
    {
        //m_BitmapFromCVMatFunctionPtr = callback;

    }
    void Terminate();
};
