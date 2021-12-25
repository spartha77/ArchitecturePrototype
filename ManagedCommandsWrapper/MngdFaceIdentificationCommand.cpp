#include "pch.h"

#include "MngdFaceIdentificationCommand.h"
#include "MngdFaceIdentificationCommandExecutorInputData.h"


// C++ includes
#include <memory>
#include <FaceIdentificationCommandExecutor.h>
#include <CommandManager.h>
//#include <CommandReturnsNoOutputData.h>

#include <opencv2/opencv.hpp>


namespace ManagedCommandsWrapper {
	class FaceIdentificationCommandExecutor_Impl
	{
	private:
		FaceIdentificationCommandExecutor* m_executor;
	public:
		FaceIdentificationCommandExecutor_Impl(UIUpdateCallbackFuncPtr fptr, bool useOpenCVHighGUI = true)
		{
			m_executor = new FaceIdentificationCommandExecutor(fptr, useOpenCVHighGUI);
		}
		~FaceIdentificationCommandExecutor_Impl()
		{
			if (m_executor)
			{
				delete m_executor;
				m_executor = nullptr;
			}
		}

		
		bool Execute(FaceIdentificationCommandExecutorInputData& inputData)
		{
			std::unique_ptr<NullData> otNullData =
				AdaptiveHumanTracker::SkillsManager<FaceIdentificationCommandExecutorInputData, NullData>::GetInstance()->Execute< FaceIdentificationCommandExecutor>(inputData, *m_executor);
			if (otNullData)
				return true;
			return false;
		}

		void Terminate()
		{
			AdaptiveHumanTracker::SkillsManager<FaceIdentificationCommandExecutorInputData, NullData>::GetInstance()->Terminate();
		}
	};
}
void ManagedCommandsWrapper::MngdFaceIdentificationCommand::Terminate()
{
	m_executorPImpl->Terminate();
}
bool ManagedCommandsWrapper::MngdFaceIdentificationCommand::Execute()
{
	FaceIdentificationCommandExecutorInputData humanDetectCmdInputData;
	// registerCmdInputData.modelDirectoryPath = std::string("C:\\partha\\Source_OpenVINO\\FaceBodyDetectionOpenVINO\\FaceBodyDetectionOpenVINO\\Input\\Models");
	// registerCmdInputData.dataDirectoryPath = std::string("C:\\partha\\Source_OpenVINO\\FaceBodyDetectionOpenVINO\\FaceBodyDetectionOpenVINO\\Input\\Models");
	// registerCmdInputData.imageDirectoryPathf = std::string("C:\\partha\\Source_OpenVINO\\FaceBodyDetectionOpenVINO\\FaceBodyDetectionOpenVINO\\Input\\Images");
	// registerCmdInputData.registeredName = std::string("Vishnu");

	MarshalString(m_inputData->ModelDirectoryPath, humanDetectCmdInputData.modelDirectoryPath);
	MarshalString(m_inputData->DataDirectoryPath, humanDetectCmdInputData.dataDirectoryPath);


	// Final test 
	//std::unique_ptr<NullData> otNullData = CommandManager::GetInstance()->Execute< CommandReturnsNoOutputData, FaceIdentificationCommandExecutor, FaceIdentificationCommandExecutorInputData, NullData>(HumanDetectCmdInputData, executor);
	//if (otNullData)
		//return true;

	/*auto execMethod = m_executorPImpl->GetSkillExecutionMethod();
	using execType = decltype(execMethod);
	std::unique_ptr<NullData> otNullData = AdaptiveHumanTracker::SkillsManager<FaceIdentificationCommandExecutorInputData, NullData>::GetInstance()->Execute<execType>(HumanDetectCmdInputData, execMethod);
	if (otNullData)
		return true;

	return false;*/

	if (m_executorPImpl->Execute(humanDetectCmdInputData))
	{
		return true;
	}
	return false;
}


void ManagedCommandsWrapper::MngdFaceIdentificationCommand::UpdateCVMatImageInForm(cv::Mat* openCVImage)
{
	if (openCVImage == nullptr)
		return;
	Bitmap^ newBitmap = nullptr;
	try
	{
		newBitmap  = gcnew Bitmap((*openCVImage).cols,
			(*openCVImage).rows,
			(*openCVImage).step1(),
			System::Drawing::Imaging::PixelFormat::Format24bppRgb,
			IntPtr((*openCVImage).data));
	}
	catch(System::Exception^)
	{
		; // DO nothing
	}
	m_UpdateAdaptiveHumanTrackingFormDelegate(newBitmap);
}

UIUpdateCallbackFuncPtr ManagedCommandsWrapper::MngdFaceIdentificationCommand::GetUIUpdateCallbackFuncPtr()
{
	m_BitmapFromCVMatDelegate = gcnew BitmapFromCVMatDelegate(this, &MngdFaceIdentificationCommand::UpdateCVMatImageInForm);
	gch = GCHandle::Alloc(m_BitmapFromCVMatDelegate);

	IntPtr intPointer2Func = Marshal::GetFunctionPointerForDelegate(m_BitmapFromCVMatDelegate);
	UIUpdateCallbackFuncPtr unManagedCallbackcb = static_cast<UIUpdateCallbackFuncPtr>(intPointer2Func.ToPointer());
	return unManagedCallbackcb;
}

void ManagedCommandsWrapper::MngdFaceIdentificationCommand::SetAdaptiveHumanTrackingFormUpdateDelegate(UpdateAdaptiveHumanTrackingFormDelegate^ callback)
{
	m_UpdateAdaptiveHumanTrackingFormDelegate = callback;
}

void ManagedCommandsWrapper::MngdFaceIdentificationCommand::Initializer(System::String^ modelDirPath, System::String^ dataDirPath)
{
	m_inputData = gcnew MngdFaceIdentificationCommandExecutorInputData(modelDirPath, dataDirPath);

	m_UpdateAdaptiveHumanTrackingFormDelegate =
		gcnew UpdateAdaptiveHumanTrackingFormDelegate(this, &ManagedCommandsWrapper::MngdFaceIdentificationCommand::UpdateImageStub);
	UIUpdateCallbackFuncPtr fptr = GetUIUpdateCallbackFuncPtr();
	if (m_executorPImpl)
	{
		delete m_executorPImpl;
		m_executorPImpl = nullptr;
	}
	m_executorPImpl = new FaceIdentificationCommandExecutor_Impl(fptr, false);
}
void ManagedCommandsWrapper::MngdFaceIdentificationCommand::UpdateImageStub(Bitmap^ bitmpImage)
{
	// Stub
	// Do nothing
}
ManagedCommandsWrapper::MngdFaceIdentificationCommand::MngdFaceIdentificationCommand()
{
	m_inputData = gcnew MngdFaceIdentificationCommandExecutorInputData();

	m_UpdateAdaptiveHumanTrackingFormDelegate =
		gcnew UpdateAdaptiveHumanTrackingFormDelegate(this,
			&ManagedCommandsWrapper::MngdFaceIdentificationCommand::UpdateImageStub);
	UIUpdateCallbackFuncPtr fptr = GetUIUpdateCallbackFuncPtr();
	//m_executor = new RegisterPersonCommandExecutor(fptr, false);
	m_executorPImpl = new FaceIdentificationCommandExecutor_Impl(fptr, false);
}
ManagedCommandsWrapper::MngdFaceIdentificationCommand::MngdFaceIdentificationCommand(
	System::String^ modelDirPath, System::String^ dataDirPath)
{
	Initializer(modelDirPath, dataDirPath);
}

ManagedCommandsWrapper::MngdFaceIdentificationCommand::~MngdFaceIdentificationCommand()
{
	if (m_executorPImpl)
	{
		delete m_executorPImpl;
		m_executorPImpl = nullptr;
	}
}
