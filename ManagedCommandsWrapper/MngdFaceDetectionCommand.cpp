#include "pch.h"

#include "MngdFaceDetectionCommand.h"
#include "MngdFaceDetectionCommandExecutorInputData.h"


// C++ includes
#include <memory>
#include <FaceDetectionCommandExecutor.h>
#include <CommandManager.h>
//#include <CommandReturnsNoOutputData.h>

#include <opencv2/opencv.hpp>


namespace ManagedCommandsWrapper {
	class FaceDetectionCommandExecutor_Impl
	{
	private:
		FaceDetectionCommandExecutor* m_executor;
	public:
		FaceDetectionCommandExecutor_Impl(UIUpdateCallbackFuncPtr fptr, bool useOpenCVHighGUI = true)
		{
			m_executor = new FaceDetectionCommandExecutor(fptr, useOpenCVHighGUI);
		}
		~FaceDetectionCommandExecutor_Impl()
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

		bool Execute(FaceDetectionCommandExecutorInputData& inputData)
		{
			std::unique_ptr<NullData> otNullData =
				AdaptiveHumanTracker::SkillsManager<FaceDetectionCommandExecutorInputData, NullData>::GetInstance()->Execute< FaceDetectionCommandExecutor>(inputData, *m_executor);
			if (otNullData)
				return true;
			return false;
		}

		void Terminate()
		{
			AdaptiveHumanTracker::SkillsManager<FaceDetectionCommandExecutorInputData, NullData>::GetInstance()->Terminate();
		}
	};
}
void ManagedCommandsWrapper::MngdFaceDetectionCommand::Terminate()
{
	m_executorPImpl->Terminate();
}
bool ManagedCommandsWrapper::MngdFaceDetectionCommand::Execute()
{
	FaceDetectionCommandExecutorInputData humanDetectCmdInputData;
	
	MarshalString(m_inputData->ModelDirectoryPath, humanDetectCmdInputData.modelDirectoryPath);
	MarshalString(m_inputData->DataDirectoryPath, humanDetectCmdInputData.dataDirectoryPath);

	
	

	if (m_executorPImpl->Execute(humanDetectCmdInputData))
	{
		return true;
	}
	return false;
}


void ManagedCommandsWrapper::MngdFaceDetectionCommand::UpdateCVMatImageInForm(cv::Mat* openCVImage)
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

UIUpdateCallbackFuncPtr ManagedCommandsWrapper::MngdFaceDetectionCommand::GetUIUpdateCallbackFuncPtr()
{
	m_BitmapFromCVMatDelegate = gcnew BitmapFromCVMatDelegate(this, &MngdFaceDetectionCommand::UpdateCVMatImageInForm);
	gch = GCHandle::Alloc(m_BitmapFromCVMatDelegate);

	IntPtr intPointer2Func = Marshal::GetFunctionPointerForDelegate(m_BitmapFromCVMatDelegate);
	UIUpdateCallbackFuncPtr unManagedCallbackcb = static_cast<UIUpdateCallbackFuncPtr>(intPointer2Func.ToPointer());
	return unManagedCallbackcb;
}

void ManagedCommandsWrapper::MngdFaceDetectionCommand::SetAdaptiveHumanTrackingFormUpdateDelegate(UpdateAdaptiveHumanTrackingFormDelegate^ callback)
{
	m_UpdateAdaptiveHumanTrackingFormDelegate = callback;
}

void ManagedCommandsWrapper::MngdFaceDetectionCommand::Initializer(System::String^ modelDirPath, System::String^ dataDirPath)
{
	m_inputData = gcnew MngdFaceDetectionCommandExecutorInputData(modelDirPath, dataDirPath);

	m_UpdateAdaptiveHumanTrackingFormDelegate =
		gcnew UpdateAdaptiveHumanTrackingFormDelegate(this, &ManagedCommandsWrapper::MngdFaceDetectionCommand::UpdateImageStub);
	UIUpdateCallbackFuncPtr fptr = GetUIUpdateCallbackFuncPtr();
	if (m_executorPImpl)
	{
		delete m_executorPImpl;
		m_executorPImpl = nullptr;
	}
	m_executorPImpl = new FaceDetectionCommandExecutor_Impl(fptr, false);
}
void ManagedCommandsWrapper::MngdFaceDetectionCommand::UpdateImageStub(Bitmap^ bitmpImage)
{
	// Stub
	// Do nothing
}
ManagedCommandsWrapper::MngdFaceDetectionCommand::MngdFaceDetectionCommand()
{
	m_inputData = gcnew MngdFaceDetectionCommandExecutorInputData();

	m_UpdateAdaptiveHumanTrackingFormDelegate =
		gcnew UpdateAdaptiveHumanTrackingFormDelegate(this, 
			&ManagedCommandsWrapper::MngdFaceDetectionCommand::UpdateImageStub);
	UIUpdateCallbackFuncPtr fptr = GetUIUpdateCallbackFuncPtr();
	//m_executor = new RegisterPersonCommandExecutor(fptr, false);
	m_executorPImpl = new FaceDetectionCommandExecutor_Impl(fptr, false);
}
ManagedCommandsWrapper::MngdFaceDetectionCommand::MngdFaceDetectionCommand(
	System::String^ modelDirPath, System::String^ dataDirPath)
{
	Initializer(modelDirPath, dataDirPath);
}

ManagedCommandsWrapper::MngdFaceDetectionCommand::~MngdFaceDetectionCommand()
{
	if (m_executorPImpl)
	{
		delete m_executorPImpl;
		m_executorPImpl = nullptr;
	}
}