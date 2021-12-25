#include "pch.h"

#include "MngdRegisterPersonCommand.h"
#include "MngdRegisterPersonCommandExecutorInputData.h"


#include <RegisterPersonCommandExecutor.h>
#include <CommandManager.h>
//#include <CommandReturnsNoOutputData.h>


#include <EventsObserversNotifiers.h>
#include <EventData.h>
#include <IObserver.h>
#include <EventHandler.h>
#include <Events.h>
#include <ObserverImpl.h>
#include <ObserverFactory.h>


namespace ManagedCommandsWrapper {
	class RegisterPersonCommandExecutor_Impl
	{
	private:
		RegisterPersonCommandExecutor* m_executor;
	public:
		RegisterPersonCommandExecutor_Impl(UIUpdateCallbackFuncPtr fptr, bool useOpenCVHighGUI = true)
		{
			m_executor = new RegisterPersonCommandExecutor(fptr, useOpenCVHighGUI);
		}
		~RegisterPersonCommandExecutor_Impl()
		{
			if (m_executor)
			{
				delete m_executor;
				m_executor = nullptr;
			}
		}

		/*auto GetSkillExecutionMethod()
		{
			return m_executor->GetSkillExecutionMethod();
		}*/

		bool Execute( AdaptiveHumanTracker::RegisterPersonCommandExecutorInputData& inputData)
		{
			std::unique_ptr<NullData> otNullData = 
				AdaptiveHumanTracker::SkillsManager<AdaptiveHumanTracker::RegisterPersonCommandExecutorInputData, NullData>::GetInstance()->Execute< RegisterPersonCommandExecutor>(inputData, *m_executor);
			if (otNullData)
				return true;
			return false;
		}
	};
}
bool ManagedCommandsWrapper::MngdRegisterPersonCommand::Execute()
{
	AdaptiveHumanTracker::RegisterPersonCommandExecutorInputData registerCmdInputData;
	/*registerCmdInputData.modelDirectoryPath = std::string("C:\\Users\\partha3x\\Desktop\\Input\\Models");
	registerCmdInputData.dataDirectoryPath = std::string("C:\\Users\\partha3x\\Desktop\\Input\\Models");
	registerCmdInputData.imageDirectoryPath = std::string("C:\\Users\\partha3x\\Desktop\\Input\\Images");
	registerCmdInputData.registeredName = std::string("Vishnu");*/
	//registerCmdInputData.registrationMode = AdaptiveHumanTracker::FaceRegistrationMode::BY_PERSON_NAME_ONLINE;
	
	//registerCmdInputData.registrationMode = FaceRegistrationMode::BY_PERSON_NAME_ONLINE;

	MarshalString(m_inputData->ModelDirectoryPath, registerCmdInputData.modelDirectoryPath);
	MarshalString(m_inputData->DataDirectoryPath, registerCmdInputData.dataDirectoryPath);
	MarshalString(m_inputData->ImageDirectoryPath, registerCmdInputData.imageDirectoryPath);
	MarshalString(m_inputData->RegisteredName, registerCmdInputData.registeredName);

	if (m_inputData->RegistrationMode == ManagedCommandsWrapper::FaceRegistrationMode::ONLINE)
	{
		registerCmdInputData.registrationMode = AdaptiveHumanTracker::FaceRegistrationMode::ONLINE;
	}
	else if (m_inputData->RegistrationMode == ManagedCommandsWrapper::FaceRegistrationMode::OFFLINE)
	{
		registerCmdInputData.registrationMode = AdaptiveHumanTracker::FaceRegistrationMode::OFFLINE;
	}
	//registerCmdInputData.registrationMode = 

	//RegisterPersonCommandExecutor executor;
	// Final test 
	//std::unique_ptr<NullData> otNullData = CommandManager::GetInstance()->Execute< CommandReturnsNoOutputData, RegisterPersonCommandExecutor, AdaptiveHumanTracker::RegisterPersonCommandExecutorInputData, NullData>(registerCmdInputData, *m_executor);
	//if (otNullData)
		//return true;

	//auto execMethod = m_executorPImpl->GetSkillExecutionMethod();
	//using execType = decltype(execMethod);
	//std::unique_ptr<NullData> otNullData = AdaptiveHumanTracker::SkillsManager<AdaptiveHumanTracker::RegisterPersonCommandExecutorInputData, NullData>::GetInstance()->Execute<execType>(registerCmdInputData, execMethod);
	//if (otNullData)
	//	return true;
	//
	//
	//return false;

	if (m_executorPImpl->Execute(registerCmdInputData))
	{
		return true;
	}
	return false;
}
ManagedCommandsWrapper::MngdRegisterPersonCommand::MngdRegisterPersonCommand()
{
	m_inputData = gcnew MngdRegisterPersonCommandExecutorInputData();
	
	m_UpdateAdaptiveHumanTrackingFormDelegate =
		gcnew UpdateAdaptiveHumanTrackingFormDelegate(this, &ManagedCommandsWrapper::MngdRegisterPersonCommand::UpdateImageStub);
	UIUpdateCallbackFuncPtr fptr = GetUIUpdateCallbackFuncPtr();
	//m_executor = new RegisterPersonCommandExecutor(fptr, false);
	m_executorPImpl = new RegisterPersonCommandExecutor_Impl(fptr, false);
	//m_executor->RegisterHostUIUpdateEventHandler();
	//SetBitmapFromCVMatDelegate();
	//InitializeEventHandler();


	//m_executor->RegisterHostUIUpdateEventHandler();
}
ManagedCommandsWrapper::MngdRegisterPersonCommand::~MngdRegisterPersonCommand()
{
	//m_EventHandler->Unsubscribe(m_registerPersonObserver);
	if (m_executorPImpl)
	{
		delete m_executorPImpl;
		m_executorPImpl = nullptr;
	}
}

ManagedCommandsWrapper::MngdRegisterPersonCommand::MngdRegisterPersonCommand(System::String^ modelDirPath, System::String^ dataDirPath,
	System::String^ imageDirPath, System::String^ regName)
{
	Initializer(modelDirPath, dataDirPath, imageDirPath, regName);
}
void ManagedCommandsWrapper::MngdRegisterPersonCommand::Initializer(System::String^ modelDirPath, System::String^ dataDirPath,
	System::String^ imageDirPath, System::String^ regName)
{
	m_inputData = gcnew MngdRegisterPersonCommandExecutorInputData(modelDirPath, dataDirPath, imageDirPath, regName);

	m_UpdateAdaptiveHumanTrackingFormDelegate =
		gcnew UpdateAdaptiveHumanTrackingFormDelegate(this, &ManagedCommandsWrapper::MngdRegisterPersonCommand::UpdateImageStub);
	UIUpdateCallbackFuncPtr fptr = GetUIUpdateCallbackFuncPtr();
	if (m_executorPImpl)
	{
		delete m_executorPImpl;
		m_executorPImpl = nullptr;
	}
	m_executorPImpl = new RegisterPersonCommandExecutor_Impl(fptr, false);
	//SetBitmapFromCVMatDelegate();
}

void ManagedCommandsWrapper::MngdRegisterPersonCommand::UpdateImageStub(Bitmap^ bitmpImage)
{
	// Stub
	// Do nothing
}
void ManagedCommandsWrapper::MngdRegisterPersonCommand::UpdateCVMatImageInForm(cv::Mat* openCVImage)
{
	if (openCVImage == nullptr)
		return;
	Bitmap^ newBitmap = nullptr;
	try
	{
		newBitmap = gcnew Bitmap((*openCVImage).cols,
			(*openCVImage).rows,
			(*openCVImage).step1(),
			System::Drawing::Imaging::PixelFormat::Format24bppRgb,
			IntPtr((*openCVImage).data));
	}
	catch (System::Exception^)
	{
		;//Do nothing
	}

	m_UpdateAdaptiveHumanTrackingFormDelegate(newBitmap);
}
UIUpdateCallbackFuncPtr ManagedCommandsWrapper::MngdRegisterPersonCommand::GetUIUpdateCallbackFuncPtr()
{
	m_BitmapFromCVMatDelegate = gcnew BitmapFromCVMatDelegate(this, &MngdRegisterPersonCommand::UpdateCVMatImageInForm);
	gch = GCHandle::Alloc(m_BitmapFromCVMatDelegate);

	IntPtr intPointer2Func = Marshal::GetFunctionPointerForDelegate(m_BitmapFromCVMatDelegate);
	UIUpdateCallbackFuncPtr unManagedCallbackcb = static_cast<UIUpdateCallbackFuncPtr>(intPointer2Func.ToPointer());
	return unManagedCallbackcb;
	//m_executor->SetBitmapFromCVMatFunctionPtr(unManagedCallbackcb);
}
void ManagedCommandsWrapper::MngdRegisterPersonCommand::SetAdaptiveHumanTrackingFormUpdateDelegate(UpdateAdaptiveHumanTrackingFormDelegate^ callback)
{
	m_UpdateAdaptiveHumanTrackingFormDelegate = callback;
	//gcnew UpdateAdaptiveHumanTrackingFormDelegate(this, &MngdOpenCVWrapper::UpdateImage);
}

System::String^ ManagedCommandsWrapper::MngdRegisterPersonCommand::ModelDirectoryPath::get()
{	
	return m_inputData->ModelDirectoryPath;
}

void ManagedCommandsWrapper::MngdRegisterPersonCommand::ModelDirectoryPath::set(System::String^ value)
{
	m_inputData->ModelDirectoryPath = value;
}

System::String^ ManagedCommandsWrapper::MngdRegisterPersonCommand::DataDirectoryPath::get()
{
	return m_inputData->DataDirectoryPath;
}

void ManagedCommandsWrapper::MngdRegisterPersonCommand::DataDirectoryPath::set(System::String^ value)
{
	m_inputData->DataDirectoryPath = value;
}

System::String^ ManagedCommandsWrapper::MngdRegisterPersonCommand::ImageDirectoryPath::get()
{
	return m_inputData->ImageDirectoryPath;
}
void ManagedCommandsWrapper::MngdRegisterPersonCommand::ImageDirectoryPath::set(System::String^ value)
{
	m_inputData->ImageDirectoryPath = value;
}

System::String^ ManagedCommandsWrapper::MngdRegisterPersonCommand::RegisteredName::get()
{
	return m_inputData->RegisteredName;
}

void ManagedCommandsWrapper::MngdRegisterPersonCommand::RegisteredName::set(System::String^ value)
{
	m_inputData->RegisteredName = value;
}


ManagedCommandsWrapper::FaceRegistrationMode ManagedCommandsWrapper::MngdRegisterPersonCommand::RegistrationMode::get()
{
	return m_inputData->RegistrationMode;
}

void ManagedCommandsWrapper::MngdRegisterPersonCommand::RegistrationMode::set(ManagedCommandsWrapper::FaceRegistrationMode value)
{
	m_inputData->RegistrationMode = value;
}
