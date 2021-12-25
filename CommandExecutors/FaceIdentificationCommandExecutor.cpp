#include "FaceIdentificationCommandExecutor.h"
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
#include <face_detection.h>
#include <face_identification.h>
#include <human_detection.h>
#include <body_identification.h>
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
class FaceIdentificationCommandExecutor_impl
{
private:
    std::unique_ptr<FaceIdentificationCommandExecutorInputData> m_inputData;
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
    bool stopIdentification_ = false;
    bool faceIdentificationRunStatus_ = false;

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
    FaceIdentificationCommandExecutor_impl(bool openCVHIGHGUIDisplay = true)
    {
        m_OpenCVHIGHGUIDisplay = openCVHIGHGUIDisplay;
    };
    //FaceIdentificationCommandExecutor_impl() {};

    FaceIdentificationCommandExecutor_impl(const FaceIdentificationCommandExecutor_impl& other)
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

    FaceIdentificationCommandExecutor_impl& operator=(const FaceIdentificationCommandExecutor_impl& rhs)
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
    FaceIdentificationCommandExecutor_impl(const std::string& modelDirectoryPath,
        const std::string& dataDirectoryPath, bool openCVHIGHGUIDisplay = true)
    {
        //m_inputData = std::make_unique< FaceIdentificationCommandExecutorInputData>();
        m_inputData = std::unique_ptr<FaceIdentificationCommandExecutorInputData>(new FaceIdentificationCommandExecutorInputData());
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
    ~FaceIdentificationCommandExecutor_impl() {}

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
            runExecuteCompleteCV_.wait_for(wait_for_variable_lock, chrono::seconds(5), [this] {return faceIdentificationRunStatus_; });
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
                    this->faceIdentificationRunStatus_ = false;
                    this->runExecuteCompleteCV_.notify_one();
                }
                
            });

        
        faceIdentificationRunStatus_ = true;
        stopIdentification_ = false;


        cv::VideoCapture capture;
        cv::Mat image;
        size_t frame_count = 0;

        //capture.open(atoi(m_inputData->imageDirectoryPath.c_str()));		// live-video - cameraID (0)
        capture.open(0); //live-video - cameraID (0)
        if (!capture.isOpened()) {
            cout << "Error opening video stream or file" << endl;
            
            /*{
                std::unique_lock<std::mutex> wait_for_variable_lock(runExecuteCompleteMutex_);
                faceIdentificationRunStatus_ = false;
                runExecuteCompleteCV_.notify_one();
            }*/
            return -1;
        }

        HumanDetection human_det(ssd_model, ssd_device);
        BodyIdentification body_identify(body_id_model, body_id_device, body_feature_dim, body_feature_path);
        auto face_detect = make_shared<FaceDetection>(face_det_model, face_det_device);
        auto face_fature_extract = make_shared<FaceFeatureExtraction>(face_feature_model, face_feature_device, face_feature_dim);
        auto face_id = make_shared<FaceIdentification>(face_feature_path, face_detect, face_fature_extract);
        if (!face_detect->initialize()) {
            /*{
                std::unique_lock<std::mutex> wait_for_variable_lock(runExecuteCompleteMutex_);
                faceIdentificationRunStatus_ = false;
                runExecuteCompleteCV_.notify_one();
            }*/
            return false;
        }
        if (!human_det.initialize()) {
           /* {
                std::unique_lock<std::mutex> wait_for_variable_lock(runExecuteCompleteMutex_);
                faceIdentificationRunStatus_ = false;
                runExecuteCompleteCV_.notify_one();
            }*/
            return false;
        }

        if (!face_id->initialize())
        {
            /*{
                std::unique_lock<std::mutex> wait_for_variable_lock(runExecuteCompleteMutex_);
                faceIdentificationRunStatus_ = false;
                runExecuteCompleteCV_.notify_one();
            }*/
            return false;
        }

        while (!stopIdentification_) {
            capture.read(image);
            cv::Mat image_for_drawn;

            PersonIdMsg humandetect_msg = human_det.detect(image, 10);
            PersonIdMsg face_msg = face_id->identify(humandetect_msg);
            cv::Mat face_id_image = face_id->get_drawn_image();

            for (size_t j = 0; j < humandetect_msg.persons_size(); j++)
            {
                humandetect_msg.mutable_persons(j)->set_source(NEED_RECOG);
                if (m_OpenCVHIGHGUIDisplay)
                {
                    cv::namedWindow("Face identification", cv::WINDOW_NORMAL);
                    cv::imshow("Face identification", face_id_image);
                }
                else
                {
                    // Trigger event handler for new found image
                    AdaptiveHumanTracker::Event eventForSubscription =
                        AdaptiveHumanTracker::Event::FACE_IDENTIFICATION;

                    AdaptiveHumanTracker::EventHandler<AdaptiveHumanTracker::Event, cv::Mat>::Notify(eventForSubscription, face_id_image);
                    /*auto* eventHandler =
                        AdaptiveHumanTracker::EventHandler<AdaptiveHumanTracker::Event, cv::Mat>::GetInstance(eventForSubscription);
                    eventHandler->Notify(updatedImage);*/
                }
            }
            
            //cv::namedWindow("Face identification", cv::WINDOW_NORMAL);
            //cv::imshow("Face identification", face_id_image);

            this_thread::sleep_for(chrono::milliseconds(m_playInterval));
            cv::waitKey(1);
        }
        capture.release();
        cv::destroyAllWindows();
        /*{
            std::unique_lock<std::mutex> wait_for_variable_lock(runExecuteCompleteMutex_);
            faceIdentificationRunStatus_ = false;
            runExecuteCompleteCV_.notify_one();
        }*/
        return true;
    }
};
FaceIdentificationCommandExecutor::FaceIdentificationCommandExecutor(
    UIUpdateCallbackFuncPtr uiUpdateHandler, 
    bool openCVHighGUIDsplay):
    m_UIUpdateHandler(uiUpdateHandler),
    m_UIUpdateHandlerSTDFunction(::__dummyUIUpdateStubFunc),
    m_OpenCVHighGUIDisplay(openCVHighGUIDsplay)
{
    //m_PrivateImplementor = std::make_unique< FaceIdentificationCommandExecutor_impl>();
    /*m_PrivateImplementor = std::unique_ptr<FaceIdentificationCommandExecutor_impl>(new
        FaceIdentificationCommandExecutor_impl(openCVHighGUIDsplay));*/
    //m_OpenCVHighGUIDisplay = openCVHighGUIDsplay;
    //m_UIUpdateHandler = uiUpdateHandler;
    RegisterHostUIUpdateEventHandler();
}

FaceIdentificationCommandExecutor::FaceIdentificationCommandExecutor(
    std::function<void(cv::Mat*)> uiUpdateHandlerSTDFunction, 
    bool openCVHighGUIDsplay):
    m_UIUpdateHandler(nullptr),
    m_UIUpdateHandlerSTDFunction(uiUpdateHandlerSTDFunction),
    m_OpenCVHighGUIDisplay(openCVHighGUIDsplay)
{
    //m_PrivateImplementor = std::make_unique< FaceIdentificationCommandExecutor_impl>();
    /*m_PrivateImplementor = std::unique_ptr<FaceIdentificationCommandExecutor_impl>(new
        FaceIdentificationCommandExecutor_impl(openCVHighGUIDsplay));*/
    //m_OpenCVHighGUIDisplay = openCVHighGUIDsplay;
    //m_UIUpdateHandler = uiUpdateHandler;
    RegisterHostUIUpdateEventHandler();
}

FaceIdentificationCommandExecutor::FaceIdentificationCommandExecutor(const FaceIdentificationCommandExecutor& other):
    m_UIUpdateHandler(other.m_UIUpdateHandler),
    m_UIUpdateHandlerSTDFunction(other.m_UIUpdateHandlerSTDFunction),
    m_OpenCVHighGUIDisplay(other.m_OpenCVHighGUIDisplay),
    m_inputData(other.m_inputData)
{
    //m_inputData = other.m_inputData;
    /*m_PrivateImplementor.reset(new FaceIdentificationCommandExecutor_impl(m_inputData.modelDirectoryPath,
        m_inputData.dataDirectoryPath, other.m_PrivateImplementor ?
        other.m_PrivateImplementor->GetOpenCVHighGUIDisplay() : other.m_OpenCVHighGUIDisplay));*/
   // m_OpenCVHighGUIDisplay = other.m_OpenCVHighGUIDisplay;
    //m_UIUpdateHandler = other.m_UIUpdateHandler;
    RegisterHostUIUpdateEventHandler();
}
//FaceIdentificationCommandExecutor& FaceIdentificationCommandExecutor::operator=(const FaceIdentificationCommandExecutor& rhs)
//{
//    m_inputData = rhs.m_inputData;
//    /*if (rhs.m_PrivateImplementor)
//        m_PrivateImplementor.reset(new FaceIdentificationCommandExecutor_impl(*rhs.m_PrivateImplementor));*/
//    m_OpenCVHighGUIDisplay = rhs.m_OpenCVHighGUIDisplay;
//    m_UIUpdateHandler = rhs.m_UIUpdateHandler;
//    
//    return *this;
//}
FaceIdentificationCommandExecutor::FaceIdentificationCommandExecutor(
    const std::string& modelDirectoryPath,
    const std::string& dataDirectoryPath, 
    UIUpdateCallbackFuncPtr uiUpdateHandler, 
    bool openCVHighGUIDsplay):
    m_UIUpdateHandler(uiUpdateHandler),
    m_UIUpdateHandlerSTDFunction(::__dummyUIUpdateStubFunc),
    m_OpenCVHighGUIDisplay(openCVHighGUIDsplay)
{
    m_inputData = { modelDirectoryPath , dataDirectoryPath };
    //Private implementor
   /* m_PrivateImplementor = std::make_unique< FaceIdentificationCommandExecutor_impl>(modelDirectoryPath,
        dataDirectoryPath);*/

    /*m_PrivateImplementor = std::unique_ptr<FaceIdentificationCommandExecutor_impl>(
        new FaceIdentificationCommandExecutor_impl(modelDirectoryPath,
            dataDirectoryPath, openCVHighGUIDsplay));*/

    //m_OpenCVHighGUIDisplay = openCVHighGUIDsplay;

    //m_UIUpdateHandler = uiUpdateHandler;
    RegisterHostUIUpdateEventHandler();
}

FaceIdentificationCommandExecutor::FaceIdentificationCommandExecutor(
    const std::string& modelDirectoryPath,
    const std::string& dataDirectoryPath,
    std::function<void(cv::Mat*)> uiUpdateHandlerSTDFunction,
    bool openCVHighGUIDsplay) :
    m_UIUpdateHandler(nullptr),
    m_UIUpdateHandlerSTDFunction(uiUpdateHandlerSTDFunction),
    m_OpenCVHighGUIDisplay(openCVHighGUIDsplay)
{
    m_inputData = { modelDirectoryPath , dataDirectoryPath };
    //Private implementor
   /* m_PrivateImplementor = std::make_unique< FaceIdentificationCommandExecutor_impl>(modelDirectoryPath,
        dataDirectoryPath);*/

        /*m_PrivateImplementor = std::unique_ptr<FaceIdentificationCommandExecutor_impl>(
            new FaceIdentificationCommandExecutor_impl(modelDirectoryPath,
                dataDirectoryPath, openCVHighGUIDsplay));*/

                //m_OpenCVHighGUIDisplay = openCVHighGUIDsplay;

                //m_UIUpdateHandler = uiUpdateHandler;
    RegisterHostUIUpdateEventHandler();
}
FaceIdentificationCommandExecutor::~FaceIdentificationCommandExecutor()
{
    UnRegisterHostUIUpdateEventHandler();
}
std::unique_ptr<NullData> FaceIdentificationCommandExecutor::RunExecute(const FaceIdentificationCommandExecutorInputData& inputData)
{
    /* m_PrivateImplementor = std::make_unique< FaceIdentificationCommandExecutor_impl>(inputData.modelDirectoryPath,
         inputData.dataDirectoryPath);*/

    m_PrivateImplementor = std::unique_ptr<FaceIdentificationCommandExecutor_impl>(
        new FaceIdentificationCommandExecutor_impl(inputData.modelDirectoryPath,
            inputData.dataDirectoryPath, m_OpenCVHighGUIDisplay));

    if (m_PrivateImplementor->RunExecute())
    {
        //return std::make_unique<NullData>();
        m_PrivateImplementor.reset();
        return std::unique_ptr<NullData>(new NullData());
    }
    m_PrivateImplementor.reset();
    return std::unique_ptr<NullData>(nullptr);
}
//std::function<std::unique_ptr<NullData>(FaceIdentificationCommandExecutorInputData&)>
//FaceIdentificationCommandExecutor::GetSkillExecutionMethod()
//{
//    return [this](FaceIdentificationCommandExecutorInputData& data) {return this->RunExecute(data); };
//}
// For event handler
void FaceIdentificationCommandExecutor::OnEventNotified(cv::Mat& openCVImage)
{
    //if (m_BitmapFromCVMatFunctionPtr )
       // m_BitmapFromCVMatFunctionPtr(&openCVImage);
    if (m_UIUpdateHandler)
        m_UIUpdateHandler(&openCVImage);
    else
        m_UIUpdateHandlerSTDFunction(&openCVImage);
}

void FaceIdentificationCommandExecutor::SetBitmapFromCVMatFunctionPtr(UIUpdateCallbackFuncPtr callback)
{
    

}
void FaceIdentificationCommandExecutor::RegisterHostUIUpdateEventHandler()
{
    // Initialize all the objects for event handlers
    AdaptiveHumanTracker::Event eventForSubscription =
        AdaptiveHumanTracker::Event::FACE_IDENTIFICATION;
   
    AdaptiveHumanTracker::EventHandler<AdaptiveHumanTracker::Event, cv::Mat>::Register<FaceIdentificationCommandExecutor>(eventForSubscription, *this);
}

void FaceIdentificationCommandExecutor::UnRegisterHostUIUpdateEventHandler()
{
    // Initialize all the objects for event handlers
    AdaptiveHumanTracker::Event eventForSubscription =
        AdaptiveHumanTracker::Event::FACE_IDENTIFICATION;

    AdaptiveHumanTracker::EventHandler<AdaptiveHumanTracker::Event, cv::Mat>::UnRegister<FaceIdentificationCommandExecutor>(
        eventForSubscription, *this);
}

void FaceIdentificationCommandExecutor::Terminate()
{
    if (m_PrivateImplementor)
    {
        m_PrivateImplementor->Terminate();
    }
}
