#include "IdentifyPersonCommandExecutor.h"
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <NullData.h>
#include <adaptive_person_id.h>
#include <person_id.pb.h>
#include <opencv2/core/mat.hpp>

// Event handlers
#include <EventsObserversNotifiers.h>
#include <EventData.h>
#include <IObserver.h>
#include <EventHandler.h>
#include <Events.h>
#include <ObserverImpl.h>
#include <ObserverFactory.h>

using namespace std;
//void OnUIUpdateStub(cv::Mat* mat)
//{
//    // Do nothing
//}
//std::function<void(cv::Mat*)> __dummyUIUpdateStubFunc(OnUIUpdateStub);
class IdentifyPersonCommandExecutor_impl
{
private:
    std::unique_ptr<IdentifyPersonCommandExecutorInputData> m_inputData;
    std::vector<std::string> image_files;
    std::string ssd_model;
    std::string ssd_device;
    std::string body_id_model;
    std::string body_id_device;
    std::string body_feature_path;
    int body_feature_dim = 2048;
    std::string face_det_model;
    std::string face_det_device;
    std::string face_feature_model;
    std::string face_feature_device;
    int face_feature_dim = 512;
    std::string face_feature_path;
    std::unique_ptr<AdaptivePersonId> person_id;
    int m_playInterval = 33;
    bool m_OpenCVHIGHGUIDisplay;


    // flags for synchronous dependencies
    bool stopIdentification_ = false;
    bool identifyPersonRunStatus_ = false;

    std::mutex runExecuteCompleteMutex_;
    std::condition_variable runExecuteCompleteCV_;

public:
    void SetOpenCVHighGUIDisplay(bool flag = true)
    {
        m_OpenCVHIGHGUIDisplay = flag;
    }
    bool GetOpenCVHighGUIDisplay()
    {
        return m_OpenCVHIGHGUIDisplay;
    }
    std::vector<std::string> get_file_list(const std::string& path) {
        std::vector<std::string> result;

        DIR* dp = opendir(path.c_str());
        if (dp == nullptr) {
            //printf("fail to opendir '%s'. error: %s\n", path.c_str(), strerror(errno));
            std::cout << "Failed to opendir" << "\t" << "path.c_str()" << std::endl;
            return result;
        }
        std::string directorySeperator;
#ifdef _WINDOWS
        directorySeperator = "\\";
#else
        directorySeperator = "/";
#endif
            struct dirent* ep;
        while ((ep = readdir(dp)) != nullptr) {
            // skip directory "." and ".."
            if ((strcmp(ep->d_name, ".") != 0) && (strcmp(ep->d_name, "..") != 0)) {
                result.push_back(path + directorySeperator + ep->d_name);
            }
        }
        closedir(dp);

        std::sort(result.begin(), result.end());

        return result;
    }
    IdentifyPersonCommandExecutor_impl(bool openCVHIGHGUIDisplay = true)
    {
        m_OpenCVHIGHGUIDisplay = openCVHIGHGUIDisplay;
    };

    IdentifyPersonCommandExecutor_impl(const IdentifyPersonCommandExecutor_impl& other)
    {
        // m_inputData.reset(new IdentifyPersonCommandExecutorInputData(*other.m_inputData));

        image_files = other.image_files;
        ssd_model = other.ssd_model;
        ssd_device = other.ssd_device;
        body_id_model = other.body_id_model;
        body_id_device = other.body_id_device;
        body_feature_path = other.body_feature_path;
        body_feature_dim = other.body_feature_dim;
        face_det_model = other.face_det_model;
        face_det_device = other.face_det_device;
        face_feature_model = other.face_feature_model;
        face_feature_device = other.face_feature_device;
        face_feature_dim = other.face_feature_dim;
        face_feature_path = other.face_feature_path;
        // person_id.reset(new AdaptivePersonId(*other.person_id));
        m_playInterval = other.m_playInterval;
        m_OpenCVHIGHGUIDisplay = other.m_OpenCVHIGHGUIDisplay;
    }
    void SetInputData(const std::string& modelDirectoryPath,
        const std::string& dataDirectoryPath,
        bool openCVHIGHGUIDisplay = true)
    {
        //person_id = std::make_unique< AdaptivePersonId>();
        person_id = std::unique_ptr< AdaptivePersonId>(new AdaptivePersonId());
        //m_inputData = std::make_unique< IdentifyPersonCommandExecutorInputData>();
        m_inputData = std::unique_ptr< IdentifyPersonCommandExecutorInputData>(new IdentifyPersonCommandExecutorInputData());
        m_inputData->modelDirectoryPath = modelDirectoryPath;
        m_inputData->dataDirectoryPath = dataDirectoryPath;

        // Variables setting
        // image_files = get_file_list(m_inputData->imageDirectoryPath);
        m_OpenCVHIGHGUIDisplay = openCVHIGHGUIDisplay;
        //std::cout << image_files.size() << " input images" << endl;

#ifdef _WINDOWS
        ssd_model = m_inputData->modelDirectoryPath + "\\ssd\\openvino_fp32.xml";
        body_id_model = m_inputData->modelDirectoryPath + "\\body\\aligned_reid_openvino_fp32.xml";
        body_feature_path = m_inputData->dataDirectoryPath + "\\body\\kdtree";
        face_det_model = m_inputData->modelDirectoryPath + "\\face\\retinaface\\faceDetector_fp32.xml";
        face_feature_model = m_inputData->modelDirectoryPath + "\\face\\arcface50\\openvino_fp32.xml";
        face_feature_path = m_inputData->dataDirectoryPath + "\\face";
#else
        ssd_model = m_inputData->modelDirectoryPath + "/ssd/openvino_fp32.xml";
        body_id_model = m_inputData->modelDirectoryPath + "/body/aligned_reid_openvino_fp32.xml";
        body_feature_path = m_inputData->dataDirectoryPath + "/body/kdtree";
        face_det_model = m_inputData->modelDirectoryPath + "/face/retinaface/faceDetector_fp32.xml";
        face_feature_model = m_inputData->modelDirectoryPath + "/face/arcface50/openvino_fp32.xml";
        face_feature_path = m_inputData->dataDirectoryPath + "/face";
#endif
        ssd_device = "CPU";
        body_id_device = "CPU";
        body_feature_dim = 2048;
        face_det_device = "CPU";
        face_feature_device = "CPU";
        face_feature_dim = 512;
    }
    IdentifyPersonCommandExecutor_impl& operator=(const IdentifyPersonCommandExecutor_impl& rhs)
    {
        // m_inputData.reset(new IdentifyPersonCommandExecutorInputData(*rhs.m_inputData));

        image_files = rhs.image_files;
        ssd_model = rhs.ssd_model;
        ssd_device = rhs.ssd_device;
        body_id_model = rhs.body_id_model;
        body_id_device = rhs.body_id_device;
        body_feature_path = rhs.body_feature_path;
        body_feature_dim = rhs.body_feature_dim;
        face_det_model = rhs.face_det_model;
        face_det_device = rhs.face_det_device;
        face_feature_model = rhs.face_feature_model;
        face_feature_device = rhs.face_feature_device;
        face_feature_dim = rhs.face_feature_dim;
        face_feature_path = rhs.face_feature_path;
        // person_id.reset(new AdaptivePersonId(*rhs.person_id));
        m_playInterval = rhs.m_playInterval;
        m_OpenCVHIGHGUIDisplay = rhs.m_OpenCVHIGHGUIDisplay;
    }
    IdentifyPersonCommandExecutor_impl(const std::string& modelDirectoryPath,
        const std::string& dataDirectoryPath,
        bool openCVHIGHGUIDisplay = true)

    {
        SetInputData(modelDirectoryPath, dataDirectoryPath, openCVHIGHGUIDisplay);
    }
    ~IdentifyPersonCommandExecutor_impl() {}

    void Terminate()
    {
        if (stopIdentification_ == true)
            return; // Already stopped execution

        std::mutex this_mutex;
        this_mutex.lock();
        {
            stopIdentification_ = true;
        }
        this_mutex.unlock();

        {
            std::unique_lock<std::mutex> wait_for_variable_lock(runExecuteCompleteMutex_);
            runExecuteCompleteCV_.wait_for(wait_for_variable_lock, chrono::seconds(5), [this] {return identifyPersonRunStatus_; });
        }

        // Wait for thread running RunExecute to stop
        //this_thread::sleep_for(chrono::milliseconds(500));
    }
    bool RunExecute()
    {
        AdaptiveHumanTracker::PostActionRAIIObject raiiObject([this]()
            {
                {
                    std::unique_lock<std::mutex> wait_for_variable_lock(this->runExecuteCompleteMutex_);
                    this->identifyPersonRunStatus_ = false;
                    this->runExecuteCompleteCV_.notify_one();
                }
                
            });


        identifyPersonRunStatus_ = true;
        stopIdentification_ = false;

        // vector<string> image_files;
        cv::VideoCapture capture;
        cv::Mat image;
        size_t frame_count = 0;
        //AdaptivePersonId person_id;
        //if (inputType) {
        //    if (image_dir.length() >= 3)
        //        capture.open(image_dir.c_str());			// offline - filepath
        //    else
            //    capture.open(atoi(m_inputData->imageDirectoryPath.c_str()));		// live-video - cameraID (0)
        capture.open(0);		// live-video - cameraID (0)
        if (!capture.isOpened()) {
             cout << "Error opening video stream or file" << endl;
            return -1;
        }
        //}
        //else {
        //    image_files = get_file_list(image_dir);
        //}
        bool succ = person_id->initialize(ssd_model, ssd_device,
            body_id_model, body_id_device, body_feature_dim, body_feature_path,
            face_det_model, face_det_device, face_feature_model, face_feature_device, face_feature_dim,
            face_feature_path, AdaptivePersonId::Mode::Identify);
        if (!succ) return -1;

        while (!stopIdentification_) {
            capture.read(image);
            auto result = person_id->identify(image);
            //person_id->identify(image);
            //person_id->draw_images();
            // m_OpenCVHIGHGUIDisplay = true;
            cv::Mat updatedImage = person_id->draw_images(m_OpenCVHIGHGUIDisplay);
            //cv::Mat updatedImage = person_id->draw_images();

            if (!m_OpenCVHIGHGUIDisplay)
            {
                // Trigger event handler for new found image
                AdaptiveHumanTracker::Event eventForSubscription =
                    AdaptiveHumanTracker::Event::ADAPTIVE_PERSON_IDENTIFICATION;

                AdaptiveHumanTracker::EventHandler<AdaptiveHumanTracker::Event, cv::Mat>::Notify(eventForSubscription, updatedImage);
                //AdaptiveHumanTracker::EventHandler<AdaptiveHumanTracker::Event, cv::Mat>::Notify(eventForSubscription, image);
                /*auto* eventHandler =
                    AdaptiveHumanTracker::EventHandler<AdaptiveHumanTracker::Event, cv::Mat>::GetInstance(eventForSubscription);
                eventHandler->Notify(updatedImage);*/
            }
            this_thread::sleep_for(chrono::milliseconds(m_playInterval));
            cv::waitKey(1);
        }
        capture.release();
        cv::destroyAllWindows();

        return true;
    }
};

void IdentifyPersonCommandExecutor::RegisterHostUIUpdateEventHandler()
{
    // Initialize all the objects for event handlers
    AdaptiveHumanTracker::Event eventForSubscription =
        AdaptiveHumanTracker::Event::ADAPTIVE_PERSON_IDENTIFICATION;
    
    AdaptiveHumanTracker::EventHandler<AdaptiveHumanTracker::Event, cv::Mat>::Register<IdentifyPersonCommandExecutor>(eventForSubscription, *this);

    
}
void IdentifyPersonCommandExecutor::UnRegisterHostUIUpdateEventHandler()
{
    // Initialize all the objects for event handlers
    AdaptiveHumanTracker::Event eventForSubscription =
        AdaptiveHumanTracker::Event::ADAPTIVE_PERSON_IDENTIFICATION;
   
    AdaptiveHumanTracker::EventHandler<AdaptiveHumanTracker::Event, cv::Mat>::UnRegister<IdentifyPersonCommandExecutor>(eventForSubscription, *this);

}

IdentifyPersonCommandExecutor::IdentifyPersonCommandExecutor(
    std::function<void(cv::Mat*)>& uiUpdateHandlerSTDFunction, 
    bool openCVHighGUIDisplay) :
    m_UIUpdateHandlerSTDFunction(uiUpdateHandlerSTDFunction),
    m_UIUpdateHandler(nullptr),
    m_OpenCVHighGUIDisplay(openCVHighGUIDisplay)
{
    //m_implementor = std::make_unique< RegisterPersonCommandExecutor_impl>(nullptr);
    //m_implementor = std::unique_ptr< RegisterPersonCommandExecutor_impl>(nullptr);
    //m_OpenCVHighGUIDisplay = openCVHighGUIDisplay;
    //m_BitmapFromCVMatFunctionPtr = nullptr;
    RegisterHostUIUpdateEventHandler();
}
IdentifyPersonCommandExecutor::IdentifyPersonCommandExecutor(
    UIUpdateCallbackFuncPtr uiUpdateHandler, 
    bool openCVHighGUIDisplay):
    m_UIUpdateHandler(uiUpdateHandler),
    m_UIUpdateHandlerSTDFunction(::__dummyUIUpdateStubFunc),
    m_implementor(nullptr),
    m_OpenCVHighGUIDisplay(openCVHighGUIDisplay)
{
    //m_implementor = std::make_unique< IdentifyPersonCommandExecutor_impl>(nullptr);
    //m_implementor = std::unique_ptr< IdentifyPersonCommandExecutor_impl>(nullptr);
    
    //m_BitmapFromCVMatFunctionPtr = nullptr;
    //m_UIUpdateHandler = uiUpdateHandler;
    RegisterHostUIUpdateEventHandler();
}

IdentifyPersonCommandExecutor::IdentifyPersonCommandExecutor(
    bool openCVHighGUIDisplay):
    m_UIUpdateHandler(nullptr),
    m_UIUpdateHandlerSTDFunction(::__dummyUIUpdateStubFunc),
    m_OpenCVHighGUIDisplay(openCVHighGUIDisplay),
    m_implementor(nullptr)
{
    //m_implementor = std::make_unique< IdentifyPersonCommandExecutor_impl>(nullptr);
    //m_implementor = std::unique_ptr< IdentifyPersonCommandExecutor_impl>(nullptr);
    //m_OpenCVHighGUIDisplay = openCVHighGUIDisplay;
    //m_BitmapFromCVMatFunctionPtr = nullptr;
    //m_UIUpdateHandler = uiUpdateHandler;
    RegisterHostUIUpdateEventHandler();
}

IdentifyPersonCommandExecutor::IdentifyPersonCommandExecutor(
    const IdentifyPersonCommandExecutor& other):
    m_UIUpdateHandler(other.m_UIUpdateHandler),
    m_UIUpdateHandlerSTDFunction(other.m_UIUpdateHandlerSTDFunction),
    m_OpenCVHighGUIDisplay(other.m_OpenCVHighGUIDisplay),
    m_inputData(other.m_inputData)
{
    //m_inputData = other.m_inputData;
    /*m_implementor.reset(new IdentifyPersonCommandExecutor_impl(m_inputData.modelDirectoryPath,
        m_inputData.dataDirectoryPath, other.m_implementor ? other.m_implementor->GetOpenCVHighGUIDisplay() : other.m_OpenCVHighGUIDisplay));
    */
    //m_OpenCVHighGUIDisplay = other.m_OpenCVHighGUIDisplay;
    //m_BitmapFromCVMatFunctionPtr = other.m_BitmapFromCVMatFunctionPtr;
    //m_UIUpdateHandler = other.m_UIUpdateHandler;
    RegisterHostUIUpdateEventHandler();
}


//IdentifyPersonCommandExecutor& IdentifyPersonCommandExecutor::operator=(const IdentifyPersonCommandExecutor& rhs)
//{
//    m_inputData = rhs.m_inputData;
//
//    m_implementor.reset(new IdentifyPersonCommandExecutor_impl(m_inputData.modelDirectoryPath,
//        m_inputData.dataDirectoryPath, m_OpenCVHighGUIDisplay));
//
//    //m_BitmapFromCVMatFunctionPtr = rhs.m_BitmapFromCVMatFunctionPtr;
//    m_UIUpdateHandler = rhs.m_UIUpdateHandler;
//    m_OpenCVHighGUIDisplay = rhs.m_OpenCVHighGUIDisplay;
//    RegisterHostUIUpdateEventHandler();
//    return *this;
//}
IdentifyPersonCommandExecutor::IdentifyPersonCommandExecutor(
    const std::string& modelDirectoryPath,
    const std::string& dataDirectoryPath,
    UIUpdateCallbackFuncPtr uiUpdateHandler,
    bool openCVHighGUIDisplay):
    m_UIUpdateHandler(uiUpdateHandler),
    m_UIUpdateHandlerSTDFunction(::__dummyUIUpdateStubFunc),
    m_OpenCVHighGUIDisplay(openCVHighGUIDisplay)
{
    m_inputData = { modelDirectoryPath , dataDirectoryPath };
    //Private implementor
    //m_implementor = std::make_unique< IdentifyPersonCommandExecutor_impl>(modelDirectoryPath,
      //  dataDirectoryPath, openCVHighGUIDisplay);

    /*m_implementor = std::unique_ptr< IdentifyPersonCommandExecutor_impl>(
        new IdentifyPersonCommandExecutor_impl(modelDirectoryPath,
            dataDirectoryPath, openCVHighGUIDisplay));*/

    //m_OpenCVHighGUIDisplay = openCVHighGUIDisplay;
    //m_UIUpdateHandler = uiUpdateHandler;
    RegisterHostUIUpdateEventHandler();
}

IdentifyPersonCommandExecutor::IdentifyPersonCommandExecutor(
    const std::string& modelDirectoryPath,
    const std::string& dataDirectoryPath,
    std::function<void(cv::Mat*)> uiUpdateHandlerSTDFunction,
    bool openCVHighGUIDisplay) :
    m_UIUpdateHandler(nullptr),
    m_UIUpdateHandlerSTDFunction(uiUpdateHandlerSTDFunction),
    m_OpenCVHighGUIDisplay(openCVHighGUIDisplay)
{
    m_inputData = { modelDirectoryPath , dataDirectoryPath };
    RegisterHostUIUpdateEventHandler();
}
IdentifyPersonCommandExecutor::~IdentifyPersonCommandExecutor()
{
    //m_BitmapFromCVMatFunctionPtr = nullptr;
    UnRegisterHostUIUpdateEventHandler();
}
void IdentifyPersonCommandExecutor::Terminate()
{
    if (m_implementor)
        m_implementor->Terminate();
}
std::unique_ptr<NullData> IdentifyPersonCommandExecutor::RunExecute(IdentifyPersonCommandExecutorInputData& inputData)
{
    //m_implementor = std::make_unique< IdentifyPersonCommandExecutor_impl>(inputData.modelDirectoryPath,
      //  inputData.dataDirectoryPath, inputData.imageDirectoryPath, inputData.registeredName, m_OpenCVHighGUIDisplay);

    m_implementor = std::unique_ptr< IdentifyPersonCommandExecutor_impl>(
        new IdentifyPersonCommandExecutor_impl(inputData.modelDirectoryPath,
            inputData.dataDirectoryPath, m_OpenCVHighGUIDisplay));

    if (m_implementor->RunExecute())
    {
        //return std::make_unique<NullData>();
        m_implementor.reset();
        return std::unique_ptr<NullData>(new NullData());
    }
    m_implementor.reset();
    return std::unique_ptr<NullData>(nullptr);
}

void IdentifyPersonCommandExecutor::SetOutputDisplayModeToOPenCV(bool openCvDisplayMode)
{
    m_OpenCVHighGUIDisplay = openCvDisplayMode;
}

bool IdentifyPersonCommandExecutor::IsOutputDisplayModeOpenCV()
{
    return m_OpenCVHighGUIDisplay;
}

void IdentifyPersonCommandExecutor::OnEventNotified(cv::Mat& openCVImage)
{
    //if (m_BitmapFromCVMatFunctionPtr )
       // m_BitmapFromCVMatFunctionPtr(&openCVImage);
    if (m_UIUpdateHandler)
        m_UIUpdateHandler(&openCVImage);
    else
        m_UIUpdateHandlerSTDFunction(&openCVImage);
}