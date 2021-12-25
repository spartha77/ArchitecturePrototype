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

class NullData;
namespace AdaptiveHumanTracker {
    template<typename ObserverData> 
    class IObserver;
    


    

    enum class FaceRegistrationMode
    {
        OFFLINE,
        ONLINE
    };

    struct RegisterPersonCommandExecutorInputData
    {
        std::string modelDirectoryPath;
        std::string dataDirectoryPath;
        std::string imageDirectoryPath;
        std::string registeredName;
        FaceRegistrationMode registrationMode;
    };
}

class RegisterPersonCommandExecutor;

#ifdef _WINDOWS
typedef void(__stdcall* UIUpdateCallbackFuncPtr)(cv::Mat*);
#else
typedef void(*UIUpdateCallbackFuncPtr)(cv::Mat*);
#endif
//static BitmapFromCVMatFunctionPtr bitmapFromCVMatFunctionPtr;

class RegisterPersonCommandExecutor_impl;
class COMMANDEXECUTORS_API RegisterPersonCommandExecutor
{
private:
    AdaptiveHumanTracker::RegisterPersonCommandExecutorInputData m_inputData;
    std::unique_ptr< RegisterPersonCommandExecutor_impl> m_implementor;
    bool m_OpenCVHighGUIDisplay;

    // event handlers
    //BitmapFromCVMatFunctionPtr m_BitmapFromCVMatFunctionPtr;
    //std::unique_ptr<AdaptiveHumanTracker::IObserver<cv::Mat>> m_RegisterPersonObserver;
    std::function<void(cv::Mat*)> &m_UIUpdateHandlerSTDFunction;
    UIUpdateCallbackFuncPtr m_UIUpdateHandler = nullptr;
public:
    void SetOutputDisplayModeToOPenCV(bool openCvDisplayMode);
    bool IsOutputDisplayModeOpenCV();
    RegisterPersonCommandExecutor(bool openCVHighGUIDisplay = true);
    RegisterPersonCommandExecutor(std::function<void(cv::Mat*)>& uiHandler, bool openCVHighGUIDisplay = true);
    RegisterPersonCommandExecutor(UIUpdateCallbackFuncPtr uiHandler, bool openCVHighGUIDisplay = true);
    ~RegisterPersonCommandExecutor();
    void RegisterHostUIUpdateEventHandler();
    void UnRegisterHostUIUpdateEventHandler();
    RegisterPersonCommandExecutor(const RegisterPersonCommandExecutor& other);
    //RegisterPersonCommandExecutor(RegisterPersonCommandExecutor&& other);
    RegisterPersonCommandExecutor(const std::string& modelDirectoryPath,
        const std::string& dataDirectoryPath,
        const std::string& imageDirectoryPath,
        const std::string& personName,
        const AdaptiveHumanTracker::FaceRegistrationMode& registrationMode,
        UIUpdateCallbackFuncPtr uiUpdateHandler,
        bool openCVHighGUIDisplay = true);
    RegisterPersonCommandExecutor(const std::string& modelDirectoryPath,
        const std::string& dataDirectoryPath,
        const std::string& imageDirectoryPath,
        const std::string& personName,
        const AdaptiveHumanTracker::FaceRegistrationMode& registrationMode,
        std::function<void(cv::Mat*)>& uiUpdateHandlerSTDFunction,
        bool openCVHighGUIDisplay);
   
    std::unique_ptr<NullData> RunExecute(AdaptiveHumanTracker::RegisterPersonCommandExecutorInputData& inputData);
   
    // For event handler
    void OnEventNotified(cv::Mat& openCVImage);
   

   

    void Terminate();

};
