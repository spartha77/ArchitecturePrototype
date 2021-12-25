#include "pch.h"

#include "MngdBodyIdCommand.h"
#include "MngdBodyIdCommandExecutorInputData.h"


// C++ includes
#include <memory>
#include <BodyIdCommandExecutor.h>
#include <CommandManager.h>
//#include <CommandReturnsNoOutputData.h>

#include <opencv2/opencv.hpp>


namespace ManagedCommandsWrapper {
	class BodyIdCommandExecutor_Impl
	{
	private:
		BodyIdCommandExecutor* m_executor;
	public:
		BodyIdCommandExecutor_Impl(UIUpdateCallbackFuncPtr fptr, bool useOpenCVHighGUI = true)
		{
			m_executor = new BodyIdCommandExecutor(fptr, useOpenCVHighGUI);
		}
		~BodyIdCommandExecutor_Impl()
		{
			if (m_executor)
			{
				delete m_executor;
				m_executor = nullptr;
			}
		}

		auto GetSkillExecutionMethod()
		{
			return m_executor->GetSkillExecutionMethod();
		}

		bool Execute(BodyIdCommandExecutorInputData& inputData)
		{
			std::unique_ptr<NullData> otNullData =
				AdaptiveHumanTracker::SkillsManager<BodyIdCommandExecutorInputData, NullData>::GetInstance()->Execute< BodyIdCommandExecutor>(inputData, *m_executor);
			if (otNullData)
				return true;
			return false;
		}

		void Terminate()
		{
			AdaptiveHumanTracker::SkillsManager<BodyIdCommandExecutorInputData, NullData>::GetInstance()->Terminate();
		}
	};
}

void ManagedCommandsWrapper::MngdBodyIdCommand::Terminate()
{
	m_executorPImpl->Terminate();
}
bool ManagedCommandsWrapper::MngdBodyIdCommand::Execute()
{
	BodyIdCommandExecutorInputData bodyIdSkillInputData;
	// registerCmdInputData.modelDirectoryPath = std::string("C:\\partha\\Source_OpenVINO\\FaceBodyDetectionOpenVINO\\FaceBodyDetectionOpenVINO\\Input\\Models");
	// registerCmdInputData.dataDirectoryPath = std::string("C:\\partha\\Source_OpenVINO\\FaceBodyDetectionOpenVINO\\FaceBodyDetectionOpenVINO\\Input\\Models");
	// registerCmdInputData.imageDirectoryPathf = std::string("C:\\partha\\Source_OpenVINO\\FaceBodyDetectionOpenVINO\\FaceBodyDetectionOpenVINO\\Input\\Images");
	// registerCmdInputData.registeredName = std::string("Vishnu");

	MarshalString(m_inputData->ModelDirectoryPath, bodyIdSkillInputData.modelDirectoryPath);
	MarshalString(m_inputData->DataDirectoryPath, bodyIdSkillInputData.dataDirectoryPath);


	// Final test 
	//std::unique_ptr<NullData> otNullData = CommandManager::GetInstance()->Execute< CommandReturnsNoOutputData, BodyIdCommandExecutor, BodyIdCommandExecutorInputData, NullData>(HumanDetectCmdInputData, executor);
	//if (otNullData)
		//return true;

	/*auto execMethod = m_executorPImpl->GetSkillExecutionMethod();
	using execType = decltype(execMethod);
	std::unique_ptr<NullData> otNullData = AdaptiveHumanTracker::SkillsManager<BodyIdCommandExecutorInputData, NullData>::GetInstance()->Execute<execType>(HumanDetectCmdInputData, execMethod);
	if (otNullData)
		return true;

	return false;*/

	if (m_executorPImpl->Execute(bodyIdSkillInputData))
	{
		return true;
	}
	return false;
}


void ManagedCommandsWrapper::MngdBodyIdCommand::UpdateCVMatImageInForm(cv::Mat* openCVImage)
{
	if (openCVImage == nullptr)
		return;
	Bitmap^ newBitmap = gcnew Bitmap((*openCVImage).cols,
		(*openCVImage).rows,
		(*openCVImage).step1(),
		System::Drawing::Imaging::PixelFormat::Format24bppRgb,
		IntPtr((*openCVImage).data));

	m_UpdateAdaptiveHumanTrackingFormDelegate(newBitmap);
}

UIUpdateCallbackFuncPtr ManagedCommandsWrapper::MngdBodyIdCommand::GetUIUpdateCallbackFuncPtr()
{
	m_BitmapFromCVMatDelegate = gcnew BitmapFromCVMatDelegate(this, &MngdBodyIdCommand::UpdateCVMatImageInForm);
	gch = GCHandle::Alloc(m_BitmapFromCVMatDelegate);

	IntPtr intPointer2Func = Marshal::GetFunctionPointerForDelegate(m_BitmapFromCVMatDelegate);
	UIUpdateCallbackFuncPtr unManagedCallbackcb = static_cast<UIUpdateCallbackFuncPtr>(intPointer2Func.ToPointer());
	return unManagedCallbackcb;
}

void ManagedCommandsWrapper::MngdBodyIdCommand::SetAdaptiveHumanTrackingFormUpdateDelegate(UpdateAdaptiveHumanTrackingFormDelegate^ callback)
{
	m_UpdateAdaptiveHumanTrackingFormDelegate = callback;
}

void ManagedCommandsWrapper::MngdBodyIdCommand::Initializer(System::String^ modelDirPath, System::String^ dataDirPath)
{
	m_inputData = gcnew MngdBodyIdCommandExecutorInputData(modelDirPath, dataDirPath);

	m_UpdateAdaptiveHumanTrackingFormDelegate =
		gcnew UpdateAdaptiveHumanTrackingFormDelegate(this, &ManagedCommandsWrapper::MngdBodyIdCommand::UpdateImageStub);
	UIUpdateCallbackFuncPtr fptr = GetUIUpdateCallbackFuncPtr();
	if (m_executorPImpl)
	{
		delete m_executorPImpl;
		m_executorPImpl = nullptr;
	}
	m_executorPImpl = new BodyIdCommandExecutor_Impl(fptr, false);
}
void ManagedCommandsWrapper::MngdBodyIdCommand::UpdateImageStub(Bitmap^ bitmpImage)
{
	// Stub
	// Do nothing
}
ManagedCommandsWrapper::MngdBodyIdCommand::MngdBodyIdCommand()
{
	m_inputData = gcnew MngdBodyIdCommandExecutorInputData();

	m_UpdateAdaptiveHumanTrackingFormDelegate =
		gcnew UpdateAdaptiveHumanTrackingFormDelegate(this,
			&ManagedCommandsWrapper::MngdBodyIdCommand::UpdateImageStub);
	UIUpdateCallbackFuncPtr fptr = GetUIUpdateCallbackFuncPtr();
	//m_executor = new RegisterPersonCommandExecutor(fptr, false);
	m_executorPImpl = new BodyIdCommandExecutor_Impl(fptr, false);
}
ManagedCommandsWrapper::MngdBodyIdCommand::MngdBodyIdCommand(
	System::String^ modelDirPath, System::String^ dataDirPath)
{
	Initializer(modelDirPath, dataDirPath);
}

ManagedCommandsWrapper::MngdBodyIdCommand::~MngdBodyIdCommand()
{
	if (m_executorPImpl)
	{
		delete m_executorPImpl;
		m_executorPImpl = nullptr;
	}
}
