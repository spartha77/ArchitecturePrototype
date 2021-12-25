#include "RegisterPersonCommandExecutor.h"
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <thread>
#include <NullData.h>
#include <adaptive_person_id.h>

#include <opencv2/core/mat.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <time.h>

#if defined _WINDOWS
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <chrono>
#include <string>
#include <vector>
#include <stack>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <experimental/filesystem>




// Event handlers
#include <EventsObserversNotifiers.h>
#include <EventData.h>
#include <IObserver.h>
#include <EventHandler.h>
#include <Events.h>
#include <ObserverImpl.h>
#include <ObserverFactory.h>


bool isDir(const std::string& dir) {
    std::vector<std::string> fileList;
    DIR* dp;
    dp = opendir(dir.c_str());
    if (dp != NULL)
        return true;
    else
        return false;
}

bool makedirs(const std::string& filePath) {
#if defined _WINDOWS
    std::experimental::filesystem::create_directories(filePath.c_str());
    
    if (!std::experimental::filesystem::exists(filePath))
    {
        printf("fail to mkdir '%s'. error: %s\n", filePath.c_str(), strerror(errno));
        return false;
    }
#else
    //std::string[] s_arr = filePath.split("/");
    std::stack<std::string> folderName;
    //std::string::iterator it;
    std::size_t folderDepth = filePath.length();
    std::size_t space_index;
    std::string path = filePath;
    while (true) {
        space_index = path.find_last_of("/");
        if (space_index == folderDepth - 1) {
            path = path.substr(0, space_index - 0);
            continue;
        }
        else {
            std::string tmpFolder = path.substr(space_index + 1);
            folderName.push(tmpFolder);
            path = path.substr(0, space_index - 0);
            //break;
        }
        if (space_index == 0) {
            break;
        }
    }
    std::string growing_file_path = "/";

    while (!folderName.empty()) {
        growing_file_path += folderName.top();
        folderName.pop();
        if (!isDir(growing_file_path)) {
            int tmpFlag;

            char* file_path = (char*)malloc(sizeof(char) * (growing_file_path.length() + 1));
            //memset(file_path,'\0',sizeof(char)*(growing_file_path.length()+1));
            strncpy(file_path, growing_file_path.c_str(), sizeof(char) * growing_file_path.length());
            file_path[growing_file_path.length()] = '\0';
            tmpFlag = mkdir(file_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
            free(file_path);
            if (tmpFlag != 0) {
                std::cout << "Make dir Failed: " << growing_file_path << std::endl;
                return false;
            }
        }
        growing_file_path += "/";
       }
#endif 
     return true;
}


class RegisterPersonCommandExecutor_impl
{
private:
    std::unique_ptr<RegisterPersonCommandExecutorInputData> m_inputData;
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
    int m_num_imgs_regis = 100;
    bool m_OpenCVHIGHGUIDisplay;    

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
    RegisterPersonCommandExecutor_impl(bool openCVHIGHGUIDisplay = true)
    {
        m_OpenCVHIGHGUIDisplay = openCVHIGHGUIDisplay;
    };

    RegisterPersonCommandExecutor_impl(const RegisterPersonCommandExecutor_impl& other)
    {
        m_inputData.reset(new RegisterPersonCommandExecutorInputData(*other.m_inputData));

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
        person_id.reset(new AdaptivePersonId(*other.person_id));
        m_playInterval = other.m_playInterval;
        m_num_imgs_regis = other.m_num_imgs_regis;
        m_OpenCVHIGHGUIDisplay = other.m_OpenCVHIGHGUIDisplay;
    }
    void SetInputData(const std::string& modelDirectoryPath,
        const std::string& dataDirectoryPath,
        const std::string& imageDirectoryPath,
        const std::string& personName,
        const std::int64_t& registrationMode,
        bool openCVHIGHGUIDisplay = true)
    {
        //person_id = std::make_unique< AdaptivePersonId>();
        person_id = std::unique_ptr< AdaptivePersonId>(new AdaptivePersonId());
        //m_inputData = std::make_unique< RegisterPersonCommandExecutorInputData>();
        m_inputData = std::unique_ptr< RegisterPersonCommandExecutorInputData>(new RegisterPersonCommandExecutorInputData());
        m_inputData->modelDirectoryPath = modelDirectoryPath;
        m_inputData->dataDirectoryPath = dataDirectoryPath;
        m_inputData->imageDirectoryPath = imageDirectoryPath;
        m_inputData->registeredName = personName;
        m_inputData->registrationMode = registrationMode;
        // Variables setting
        //image_files = get_file_list(m_inputData->imageDirectoryPath);
        m_OpenCVHIGHGUIDisplay = openCVHIGHGUIDisplay;
        //std::cout << image_files.size() << " input images" << std::endl;

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
    RegisterPersonCommandExecutor_impl& operator=(const RegisterPersonCommandExecutor_impl& rhs)
    {
        m_inputData.reset(new RegisterPersonCommandExecutorInputData(*rhs.m_inputData));

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
        person_id.reset(new AdaptivePersonId(*rhs.person_id));
        m_playInterval = rhs.m_playInterval;
        m_num_imgs_regis = rhs.m_num_imgs_regis;
        m_OpenCVHIGHGUIDisplay = rhs.m_OpenCVHIGHGUIDisplay;
    }
    RegisterPersonCommandExecutor_impl(const std::string& modelDirectoryPath,
        const std::string& dataDirectoryPath,
        const std::string& imageDirectoryPath,
        const std::string& personName,
        const std::int64_t& registrationMode,
        bool openCVHIGHGUIDisplay = true)

    {
        SetInputData(modelDirectoryPath, dataDirectoryPath, imageDirectoryPath, personName, registrationMode, openCVHIGHGUIDisplay);
    }
    ~RegisterPersonCommandExecutor_impl() {}


    bool RunExecute()
    {

////////////////////////////////////////////// Live Registration modification starts///////////////////////////////////////////////////

        //cout << "registration mode:" << registration_mode << " (0 for offline and 1 for online)" << endl;
        if (m_inputData->registrationMode == 1) {

            m_playInterval = 200;
            if (!isDir(m_inputData->imageDirectoryPath)) {
                makedirs(m_inputData->imageDirectoryPath);
            }
            //cv::VideoCapture cap("/home/pingguo/work/2020/test_det2.mp4");
            cv::VideoCapture cap;
            cap.open(0);
            if (!cap.isOpened()) {
                printf("can not open the camera\n");
                return 0;
            }
            cv::Mat image_online;
            for (int k = 0; k < m_num_imgs_regis; k++) {
                cap >> image_online;

                if (!m_OpenCVHIGHGUIDisplay)
                    {
                        std::cout << "Live Frame : " << k << std::endl;
                        // Trigger event handler for new found image
                        AdaptiveHumanTracker::Event eventForSubscription =
                            AdaptiveHumanTracker::Event::FACE_REGISTRATION;

                        AdaptiveHumanTracker::EventHandler<AdaptiveHumanTracker::Event, cv::Mat>::Notify(eventForSubscription, image_online);
                        cv::waitKey(m_playInterval);
                        /*auto* eventHandler =
                            AdaptiveHumanTracker::EventHandler<AdaptiveHumanTracker::Event, cv::Mat>::GetInstance(eventForSubscription);
                        eventHandler->Notify(updatedImage);*/
                    }
                    else
                    {
                        cv::imshow("registering", image_online);
                        cv::waitKey(m_playInterval);
                    }

                //this_thread::sleep_for(chrono::milliseconds(play_interval));
                time_t currtime = time(NULL);
                tm* p = localtime(&currtime);
                char filename[1000] = { 0 };
                sprintf(filename, "%s/Win_%d%02d%02d%02d%02d%02d.jpg", m_inputData->imageDirectoryPath.c_str(), p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
                std::cout << filename << std::endl;
                cv::imwrite(filename, image_online);
            }
            if (m_OpenCVHIGHGUIDisplay)
            {
                cv::destroyWindow("registering");
            } 
        }

////////////////////////////////////////////// Live Registration modification end///////////////////////////////////////////////////
        bool retVal = person_id->initialize(ssd_model, ssd_device,
            body_id_model, body_id_device, body_feature_dim, body_feature_path,
            face_det_model, face_det_device, face_feature_model, face_feature_device, face_feature_dim,
            face_feature_path, AdaptivePersonId::Mode::Register);
        std::cout << "Registration Initialization status : " << retVal << std::endl;
        if (!retVal) return retVal;


        image_files = get_file_list(m_inputData->imageDirectoryPath);
        std::cout << "Image File count : " << image_files.size() << std::endl;
        for (auto& file : image_files) {
            cv::Mat image = cv::imread(file, cv::IMREAD_COLOR);
            if (image.empty()) {
                std::cout << "fail to read image file: " << file << std::endl;
                break;
            }

            bool retVal2 = person_id->register_person(image, m_inputData->registeredName);

            cv::Mat updatedImage = person_id->draw_images(m_OpenCVHIGHGUIDisplay);

            if (!m_OpenCVHIGHGUIDisplay)
            {
                 std::cout << "Live  output frame : " << file << std::endl;
                // Trigger event handler for new found image
                AdaptiveHumanTracker::Event eventForSubscription =
                    AdaptiveHumanTracker::Event::FACE_REGISTRATION;

                AdaptiveHumanTracker::EventHandler<AdaptiveHumanTracker::Event, cv::Mat>::Notify(eventForSubscription, updatedImage);
                /*auto* eventHandler =
                    AdaptiveHumanTracker::EventHandler<AdaptiveHumanTracker::Event, cv::Mat>::GetInstance(eventForSubscription);
                eventHandler->Notify(updatedImage);*/
            }


            if (!retVal2) {
                std::cout << "fail to register using file: " << file << std::endl;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(m_playInterval));
        }

        return true;
    }
};
void RegisterPersonCommandExecutor::RegisterHostUIUpdateEventHandler()
{
    // Initialize all the objects for event handlers
    AdaptiveHumanTracker::Event eventForSubscription =
        AdaptiveHumanTracker::Event::FACE_REGISTRATION;
    using EventFuncCb = typename std::function<void(cv::Mat&)>;
    auto notifier = GetEventNotifyMethodCbMethod();
    AdaptiveHumanTracker::EventHandler<AdaptiveHumanTracker::Event, cv::Mat>::Register<EventFuncCb>(eventForSubscription, notifier);

    // Create observer for RegisterCommandExecutor
   /* m_RegisterPersonObserver =
        AdaptiveHumanTracker::ObserverFactory<cv::Mat, RegisterPersonCommandExecutor>::CreateObserver(*this);

    eventHandler->Subscribe(m_RegisterPersonObserver.get());*/
}
RegisterPersonCommandExecutor::RegisterPersonCommandExecutor(std::function<void(cv::Mat*)> uiUpdateHandler, bool openCVHighGUIDisplay)
{
    //m_implementor = std::make_unique< RegisterPersonCommandExecutor_impl>(nullptr);
    m_implementor = std::unique_ptr< RegisterPersonCommandExecutor_impl>(nullptr);
    m_OpenCVHighGUIDisplay = openCVHighGUIDisplay;
    //m_BitmapFromCVMatFunctionPtr = nullptr;
    m_UIUpdateHandler = uiUpdateHandler;
    RegisterHostUIUpdateEventHandler();
}

RegisterPersonCommandExecutor::RegisterPersonCommandExecutor(bool openCVHighGUIDisplay)
{
    //m_implementor = std::make_unique< RegisterPersonCommandExecutor_impl>(nullptr);
    m_implementor = std::unique_ptr< RegisterPersonCommandExecutor_impl>(nullptr);
    m_OpenCVHighGUIDisplay = openCVHighGUIDisplay;
    //m_BitmapFromCVMatFunctionPtr = nullptr;
    //m_UIUpdateHandler = uiUpdateHandler;
    RegisterHostUIUpdateEventHandler();
}

RegisterPersonCommandExecutor::RegisterPersonCommandExecutor(const RegisterPersonCommandExecutor& other)
{
    m_inputData = other.m_inputData;
    m_implementor.reset(new RegisterPersonCommandExecutor_impl(m_inputData.modelDirectoryPath,
        m_inputData.dataDirectoryPath, m_inputData.imageDirectoryPath, m_inputData.registeredName,m_inputData.registrationMode,
        other.m_implementor ? other.m_implementor->GetOpenCVHighGUIDisplay() : other.m_OpenCVHighGUIDisplay));
    m_OpenCVHighGUIDisplay = other.m_OpenCVHighGUIDisplay;
    //m_BitmapFromCVMatFunctionPtr = other.m_BitmapFromCVMatFunctionPtr;
    m_UIUpdateHandler = other.m_UIUpdateHandler;
    RegisterHostUIUpdateEventHandler();
}


RegisterPersonCommandExecutor& RegisterPersonCommandExecutor::operator=(const RegisterPersonCommandExecutor& rhs)
{
    m_inputData = rhs.m_inputData;

    m_implementor.reset(new RegisterPersonCommandExecutor_impl(m_inputData.modelDirectoryPath,
        m_inputData.dataDirectoryPath, m_inputData.imageDirectoryPath,
        m_inputData.registeredName,m_inputData.registrationMode,m_OpenCVHighGUIDisplay));

    //m_BitmapFromCVMatFunctionPtr = rhs.m_BitmapFromCVMatFunctionPtr;
    m_UIUpdateHandler = rhs.m_UIUpdateHandler;
    m_OpenCVHighGUIDisplay = rhs.m_OpenCVHighGUIDisplay;
    RegisterHostUIUpdateEventHandler();
    return *this;
}
RegisterPersonCommandExecutor::RegisterPersonCommandExecutor(const std::string& modelDirectoryPath,
    const std::string& dataDirectoryPath,
    const std::string& imageDirectoryPath,
    const std::string& personName,
    const std::int64_t& registrationMode,
    std::function<void(cv::Mat*)> uiUpdateHandler,
    bool openCVHighGUIDisplay)
{

    //Private implementor
    //m_implementor = std::make_unique< RegisterPersonCommandExecutor_impl>(modelDirectoryPath,
      //  dataDirectoryPath, imageDirectoryPath, personName, openCVHighGUIDisplay);

    m_implementor = std::unique_ptr< RegisterPersonCommandExecutor_impl>(
        new RegisterPersonCommandExecutor_impl(modelDirectoryPath,
            dataDirectoryPath, imageDirectoryPath, personName,registrationMode,openCVHighGUIDisplay));

    m_OpenCVHighGUIDisplay = openCVHighGUIDisplay;
    m_UIUpdateHandler = uiUpdateHandler;
    RegisterHostUIUpdateEventHandler();
}
RegisterPersonCommandExecutor::~RegisterPersonCommandExecutor()
{
    //m_BitmapFromCVMatFunctionPtr = nullptr;
}
std::unique_ptr<NullData> RegisterPersonCommandExecutor::RunExecute(RegisterPersonCommandExecutorInputData& inputData)
{
    //m_implementor = std::make_unique< RegisterPersonCommandExecutor_impl>(inputData.modelDirectoryPath,
      //  inputData.dataDirectoryPath, inputData.imageDirectoryPath, inputData.registeredName, m_OpenCVHighGUIDisplay);

    m_implementor = std::unique_ptr< RegisterPersonCommandExecutor_impl>(
        new RegisterPersonCommandExecutor_impl(inputData.modelDirectoryPath,
            inputData.dataDirectoryPath, inputData.imageDirectoryPath, inputData.registeredName,inputData.registrationMode, m_OpenCVHighGUIDisplay));

    if (m_implementor->RunExecute())
    {
        //return std::make_unique<NullData>();
        return std::unique_ptr<NullData>(new NullData());
    }
    return std::unique_ptr<NullData>(nullptr);
}

void RegisterPersonCommandExecutor::SetOutputDisplayModeToOPenCV(bool openCvDisplayMode)
{
    m_OpenCVHighGUIDisplay = openCvDisplayMode;
}

bool RegisterPersonCommandExecutor::IsOutputDisplayModeOpenCV()
{
    return m_OpenCVHighGUIDisplay;
}
