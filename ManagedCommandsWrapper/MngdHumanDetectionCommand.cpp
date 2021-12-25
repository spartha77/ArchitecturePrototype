#include "pch.h"

#include "MngdHumanDetectionCommand.h"
#include "MngdHumanDetectionCommandExecutorInputData.h"


// C++ includes
#include <memory>
#include <HumanDetectionCommandExecutor.h>
#include <CommandManager.h>
//#include <CommandReturnsNoOutputData.h>

#include <opencv2/opencv.hpp>


namespace ManagedCommandsWrapper {
	class HumanDetectionCommandExecutor_Impl
	{
	private:
		HumanDetectionCommandExecutor* m_executor;
	public:
		HumanDetectionCommandExecutor_Impl(UIUpdateCallbackFuncPtr fptr, bool useOpenCVHighGUI = true)
		{
			m_executor = new HumanDetectionCommandExecutor(fptr, useOpenCVHighGUI);
		}
		~HumanDetectionCommandExecutor_Impl()
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

		bool Execute(HumanDetectionCommandExecutorInputData& inputData)
		{
			std::unique_ptr<NullData> otNullData =
				AdaptiveHumanTracker::SkillsManager<HumanDetectionCommandExecutorInputData, NullData>::GetInstance()->Execute< HumanDetectionCommandExecutor>(inputData, *m_executor);
			if (otNullData)
				return true;
			return false;
		}

		void Terminate()
		{
			AdaptiveHumanTracker::SkillsManager<HumanDetectionCommandExecutorInputData, NullData>::GetInstance()->Terminate();
		}
	};
}

void ManagedCommandsWrapper::MngdHumanDetectionCommand::Terminate()
{
	m_executorPImpl->Terminate();
}

bool ManagedCommandsWrapper::MngdHumanDetectionCommand::Execute()
{
	HumanDetectionCommandExecutorInputData humanDetectCmdInputData;
	
	MarshalString(m_inputData->ModelDirectoryPath, humanDetectCmdInputData.modelDirectoryPath);
	MarshalString(m_inputData->DataDirectoryPath, humanDetectCmdInputData.dataDirectoryPath);


	

	if (m_executorPImpl->Execute(humanDetectCmdInputData))
	{
		return true;
	}
	return false;
}


void ManagedCommandsWrapper::MngdHumanDetectionCommand::UpdateCVMatImageInForm(cv::Mat* openCVImage)
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

UIUpdateCallbackFuncPtr ManagedCommandsWrapper::MngdHumanDetectionCommand::GetUIUpdateCallbackFuncPtr()
{
	m_BitmapFromCVMatDelegate = gcnew BitmapFromCVMatDelegate(this, &MngdHumanDetectionCommand::UpdateCVMatImageInForm);
	gch = GCHandle::Alloc(m_BitmapFromCVMatDelegate);

	IntPtr intPointer2Func = Marshal::GetFunctionPointerForDelegate(m_BitmapFromCVMatDelegate);
	UIUpdateCallbackFuncPtr unManagedCallbackcb = static_cast<UIUpdateCallbackFuncPtr>(intPointer2Func.ToPointer());
	return unManagedCallbackcb;
}

void ManagedCommandsWrapper::MngdHumanDetectionCommand::SetAdaptiveHumanTrackingFormUpdateDelegate(UpdateAdaptiveHumanTrackingFormDelegate^ callback)
{
	m_UpdateAdaptiveHumanTrackingFormDelegate = callback;
}

void ManagedCommandsWrapper::MngdHumanDetectionCommand::Initializer(System::String^ modelDirPath, System::String^ dataDirPath)
{
	m_inputData = gcnew MngdHumanDetectionCommandExecutorInputData(modelDirPath, dataDirPath);

	m_UpdateAdaptiveHumanTrackingFormDelegate =
		gcnew UpdateAdaptiveHumanTrackingFormDelegate(this, &ManagedCommandsWrapper::MngdHumanDetectionCommand::UpdateImageStub);
	UIUpdateCallbackFuncPtr fptr = GetUIUpdateCallbackFuncPtr();
	if (m_executorPImpl)
	{
		delete m_executorPImpl;
		m_executorPImpl = nullptr;
	}
	m_executorPImpl = new HumanDetectionCommandExecutor_Impl(fptr, false);
}
void ManagedCommandsWrapper::MngdHumanDetectionCommand::UpdateImageStub(Bitmap^ bitmpImage)
{
	// Stub
	// Do nothing
}
ManagedCommandsWrapper::MngdHumanDetectionCommand::MngdHumanDetectionCommand()
{
	m_inputData = gcnew MngdHumanDetectionCommandExecutorInputData();

	m_UpdateAdaptiveHumanTrackingFormDelegate =
		gcnew UpdateAdaptiveHumanTrackingFormDelegate(this,
			&ManagedCommandsWrapper::MngdHumanDetectionCommand::UpdateImageStub);
	UIUpdateCallbackFuncPtr fptr = GetUIUpdateCallbackFuncPtr();
	//m_executor = new RegisterPersonCommandExecutor(fptr, false);
	m_executorPImpl = new HumanDetectionCommandExecutor_Impl(fptr, false);
}
ManagedCommandsWrapper::MngdHumanDetectionCommand::MngdHumanDetectionCommand(
	System::String^ modelDirPath, System::String^ dataDirPath)
{
	Initializer(modelDirPath, dataDirPath);
}

ManagedCommandsWrapper::MngdHumanDetectionCommand::~MngdHumanDetectionCommand()
{
	if (m_executorPImpl)
	{
		delete m_executorPImpl;
		m_executorPImpl = nullptr;
	}
}
