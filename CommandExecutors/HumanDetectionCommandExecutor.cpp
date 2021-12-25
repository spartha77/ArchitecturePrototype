#include "HumanDetectionCommandExecutor.h"
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
#include <human_detection.h>
#include "image_draw.h"


// Event handlers

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
class HumanDetectionCommandExecutor_impl
{
private:
    std::unique_ptr<HumanDetectionCommandExecutorInputData> m_inputData;
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
    int m_playInterval = 33;
    bool m_OpenCVHIGHGUIDisplay = true;


    // flags for synchronous dependencies
    bool stopDetection_ = false;
    bool humanDetectionRunStatus_ = false;

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
    HumanDetectionCommandExecutor_impl(bool openCVHIGHGUIDisplay = true)
    {
        m_OpenCVHIGHGUIDisplay = openCVHIGHGUIDisplay;
    };
    //HumanDetectionCommandExecutor_impl() {};

    HumanDetectionCommandExecutor_impl(const HumanDetectionCommandExecutor_impl& other)
    {
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
        m_playInterval = other.m_playInterval;
        m_OpenCVHIGHGUIDisplay = other.m_OpenCVHIGHGUIDisplay;
    }

    HumanDetectionCommandExecutor_impl& operator=(const HumanDetectionCommandExecutor_impl& rhs)
    {
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
        m_playInterval = rhs.m_playInterval;
        m_OpenCVHIGHGUIDisplay = rhs.m_OpenCVHIGHGUIDisplay;
        return *this;
    }
    HumanDetectionCommandExecutor_impl(const std::string& modelDirectoryPath,
        const std::string& dataDirectoryPath, bool openCVHIGHGUIDisplay = true)
    {
        //m_inputData = std::make_unique< HumanDetectionCommandExecutorInputData>();
        m_inputData = std::unique_ptr<HumanDetectionCommandExecutorInputData>(new HumanDetectionCommandExecutorInputData());
        m_inputData->modelDirectoryPath = modelDirectoryPath;
        m_inputData->dataDirectoryPath = dataDirectoryPath;
        m_OpenCVHIGHGUIDisplay = openCVHIGHGUIDisplay;

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
    ~HumanDetectionCommandExecutor_impl() {}

    void Terminate()
    {
        if (stopDetection_ == true)
            return; // Already stopped execution

        std::mutex this_mutex;
        this_mutex.lock();
        {
            stopDetection_ = true;
        }
        this_mutex.unlock();

        {
            std::unique_lock<std::mutex> wait_for_variable_lock(runExecuteCompleteMutex_);
            runExecuteCompleteCV_.wait_for(wait_for_variable_lock, chrono::seconds(5), [this] {return humanDetectionRunStatus_; });
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
                    this->humanDetectionRunStatus_ = false;
                    this->runExecuteCompleteCV_.notify_one();
                }
                
            });


        humanDetectionRunStatus_ = true;
        stopDetection_ = false;

        cv::VideoCapture capture;
        cv::Mat image;
        size_t frame_count = 0;

        //capture.open(atoi(m_inputData->imageDirectoryPath.c_str()));		// live-video - cameraID (0)
        capture.open(0); //live-video - cameraID (0)
        if (!capture.isOpened()) {
            cout << "Error opening video stream or file" << endl;
            return -1;
        }

        HumanDetection human_det(ssd_model, ssd_device);
        if (!human_det.initialize()) {
            return false;
        }

        while (!stopDetection_) {
            capture.read(image);
            //std::vector< bbox > result;
            cv::Mat image_for_drawn;
            PersonIdMsg human_msg = human_det.detect(image, 5);
            image.copyTo(image_for_drawn);
            for (size_t j = 0; j < human_msg.persons_size(); j++)
            {
                Person* result = human_msg.mutable_persons(j);
                cv::Rect face_rect(result->x(), result->y(), result->w(), result->h());
                drawBBox(image_for_drawn, "  ", face_rect, cv::Scalar(0, 255, 0));
                if (m_OpenCVHIGHGUIDisplay)
                {
                    cv::namedWindow("Human Detection", cv::WINDOW_NORMAL);
                    cv::imshow("Human Detection", image_for_drawn);
                }
                else
                {
                    // Trigger event handler for new found image
                    AdaptiveHumanTracker::Event eventForSubscription =
                        AdaptiveHumanTracker::Event::HUMAN_DETECTION;

                    AdaptiveHumanTracker::EventHandler<AdaptiveHumanTracker::Event, cv::Mat>::Notify(eventForSubscription, image_for_drawn);
                    /*auto* eventHandler =
                        AdaptiveHumanTracker::EventHandler<AdaptiveHumanTracker::Event, cv::Mat>::GetInstance(eventForSubscription);
                    eventHandler->Notify(updatedImage);*/
                }
            }
            this_thread::sleep_for(chrono::milliseconds(m_playInterval));
            cv::waitKey(1);
        }
        capture.release();
        cv::destroyAllWindows();

        return true;
    }
};

HumanDetectionCommandExecutor::HumanDetectionCommandExecutor(UIUpdateCallbackFuncPtr uiUpdateHandler, 
    bool openCVHighGUIDsplay):
    m_UIUpdateHandler(uiUpdateHandler),
    m_UIUpdateHandlerSTDFunction(::__dummyUIUpdateStubFunc),
    m_OpenCVHighGUIDisplay(openCVHighGUIDsplay)
{
    //m_implementor = std::make_unique< HumanDetectionCommandExecutor_impl>();
   /* m_implementor = std::unique_ptr<HumanDetectionCommandExecutor_impl>(new
        HumanDetectionCommandExecutor_impl(openCVHighGUIDsplay));*/
    //m_OpenCVHighGUIDisplay = openCVHighGUIDsplay;
    //m_UIUpdateHandler = uiUpdateHandler;
    RegisterHostUIUpdateEventHandler();
}

HumanDetectionCommandExecutor::HumanDetectionCommandExecutor(std::function<void(cv::Mat*)> uiUpdateHandlerSTDFunction, 
    bool openCVHighGUIDsplay):
    m_UIUpdateHandler(nullptr),
    m_UIUpdateHandlerSTDFunction(uiUpdateHandlerSTDFunction),
    m_OpenCVHighGUIDisplay(openCVHighGUIDsplay)
{
    //m_implementor = std::make_unique< HumanDetectionCommandExecutor_impl>();
    /*m_implementor = std::unique_ptr<HumanDetectionCommandExecutor_impl>(new
        HumanDetectionCommandExecutor_impl(openCVHighGUIDsplay));*/
    //m_OpenCVHighGUIDisplay = openCVHighGUIDsplay;
    //m_UIUpdateHandler = uiUpdateHandler;
    RegisterHostUIUpdateEventHandler();
}

HumanDetectionCommandExecutor::HumanDetectionCommandExecutor(const HumanDetectionCommandExecutor& other):
    m_UIUpdateHandler(other.m_UIUpdateHandler),
    m_UIUpdateHandlerSTDFunction(other.m_UIUpdateHandlerSTDFunction),
    m_OpenCVHighGUIDisplay(other.m_OpenCVHighGUIDisplay),
    m_inputData(other.m_inputData)
{
    //m_inputData = other.m_inputData;
    /*m_implementor.reset(new HumanDetectionCommandExecutor_impl(m_inputData.modelDirectoryPath,
        m_inputData.dataDirectoryPath, other.m_implementor ?
        other.m_implementor->GetOpenCVHighGUIDisplay() : other.m_OpenCVHighGUIDisplay));*/
    //m_OpenCVHighGUIDisplay = other.m_OpenCVHighGUIDisplay;
    //m_UIUpdateHandler = other.m_UIUpdateHandler;
    RegisterHostUIUpdateEventHandler();
}
//HumanDetectionCommandExecutor& HumanDetectionCommandExecutor::operator=(const HumanDetectionCommandExecutor& rhs)
//{
//    m_inputData = rhs.m_inputData;
//    if (rhs.m_implementor)
//        m_implementor.reset(new HumanDetectionCommandExecutor_impl(*rhs.m_implementor));
//    m_OpenCVHighGUIDisplay = rhs.m_OpenCVHighGUIDisplay;
//    m_UIUpdateHandler = rhs.m_UIUpdateHandler;
//    RegisterHostUIUpdateEventHandler();
//    return *this;
//}
HumanDetectionCommandExecutor::HumanDetectionCommandExecutor(
    const std::string& modelDirectoryPath,
    const std::string& dataDirectoryPath, 
    UIUpdateCallbackFuncPtr uiUpdateHandler, 
    bool openCVHighGUIDsplay):
    m_UIUpdateHandler(uiUpdateHandler),
    m_UIUpdateHandlerSTDFunction(::__dummyUIUpdateStubFunc),
    m_OpenCVHighGUIDisplay(openCVHighGUIDsplay)
{
    m_inputData = { modelDirectoryPath , dataDirectoryPath};
    //Private implementor
   /* m_implementor = std::make_unique< HumanDetectionCommandExecutor_impl>(modelDirectoryPath,
        dataDirectoryPath);*/

    /*m_implementor = std::unique_ptr<HumanDetectionCommandExecutor_impl>(
        new HumanDetectionCommandExecutor_impl(modelDirectoryPath,
            dataDirectoryPath, openCVHighGUIDsplay));*/

    //m_OpenCVHighGUIDisplay = openCVHighGUIDsplay;

    //m_UIUpdateHandler = uiUpdateHandler;
    RegisterHostUIUpdateEventHandler();
}

HumanDetectionCommandExecutor::HumanDetectionCommandExecutor(
    const std::string& modelDirectoryPath,
    const std::string& dataDirectoryPath, 
    std::function<void(cv::Mat*)> uiUpdateHandlerSTDFunction, 
    bool openCVHighGUIDsplay):
    m_UIUpdateHandler(nullptr),
    m_UIUpdateHandlerSTDFunction(uiUpdateHandlerSTDFunction),
    m_OpenCVHighGUIDisplay(openCVHighGUIDsplay)
{
    m_inputData = { modelDirectoryPath , dataDirectoryPath };
    //Private implementor
   /* m_implementor = std::make_unique< HumanDetectionCommandExecutor_impl>(modelDirectoryPath,
        dataDirectoryPath);*/

    /*m_implementor = std::unique_ptr<HumanDetectionCommandExecutor_impl>(
        new HumanDetectionCommandExecutor_impl(modelDirectoryPath,
            dataDirectoryPath, openCVHighGUIDsplay));*/

    //m_OpenCVHighGUIDisplay = openCVHighGUIDsplay;

    //m_UIUpdateHandler = uiUpdateHandler;
    RegisterHostUIUpdateEventHandler();
}
HumanDetectionCommandExecutor::~HumanDetectionCommandExecutor()
{
    UnRegisterHostUIUpdateEventHandler();
}

void HumanDetectionCommandExecutor::UnRegisterHostUIUpdateEventHandler()
{
    // Initialize all the objects for event handlers
    AdaptiveHumanTracker::Event eventForSubscription =
        AdaptiveHumanTracker::Event::HUMAN_DETECTION;

    AdaptiveHumanTracker::EventHandler<AdaptiveHumanTracker::Event, cv::Mat>::UnRegister<HumanDetectionCommandExecutor>(
        eventForSubscription, *this);
}
void HumanDetectionCommandExecutor::Terminate()
{
    if (m_implementor)
        m_implementor->Terminate();
}
std::unique_ptr<NullData> HumanDetectionCommandExecutor::RunExecute(const HumanDetectionCommandExecutorInputData& inputData)
{
    /* m_implementor = std::make_unique< HumanDetectionCommandExecutor_impl>(inputData.modelDirectoryPath,
         inputData.dataDirectoryPath);*/

    m_implementor = std::unique_ptr<HumanDetectionCommandExecutor_impl>(
        new HumanDetectionCommandExecutor_impl(inputData.modelDirectoryPath,
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
std::function<std::unique_ptr<NullData>(HumanDetectionCommandExecutorInputData&)>
HumanDetectionCommandExecutor::GetSkillExecutionMethod()
{
    return [this](HumanDetectionCommandExecutorInputData& data) {return this->RunExecute(data); };
}
// For event handler
void HumanDetectionCommandExecutor::OnEventNotified(cv::Mat& openCVImage)
{
    //if (m_BitmapFromCVMatFunctionPtr )
       // m_BitmapFromCVMatFunctionPtr(&openCVImage);
    if (m_UIUpdateHandler)
        m_UIUpdateHandler(&openCVImage);
    else
        m_UIUpdateHandlerSTDFunction(&openCVImage);
}
std::function <void(cv::Mat & mat)> HumanDetectionCommandExecutor::GetEventNotifyMethodCbMethod()
{
    return [this](cv::Mat& openCVImage) {return this->OnEventNotified(openCVImage); };
}

void HumanDetectionCommandExecutor::SetBitmapFromCVMatFunctionPtr(UIUpdateCallbackFuncPtr callback)
{
    //m_BitmapFromCVMatFunctionPtr = callback;

}
void HumanDetectionCommandExecutor::RegisterHostUIUpdateEventHandler()
{
    // Initialize all the objects for event handlers
    AdaptiveHumanTracker::Event eventForSubscription =
        AdaptiveHumanTracker::Event::HUMAN_DETECTION;
   

    AdaptiveHumanTracker::EventHandler<AdaptiveHumanTracker::Event, cv::Mat>::Register<HumanDetectionCommandExecutor>(eventForSubscription, *this);
    
}
