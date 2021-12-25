#include "pch.h"

#include "MngdIdentifyPersonCommand.h"
#include "MngdIdentifyPersonCommandExecutorInputData.h"


// C++ includes
#include <memory>
#include <IdentifyPersonCommandExecutor.h>
#include <CommandManager.h>
//#include <CommandReturnsNoOutputData.h>

#include <opencv2/opencv.hpp>


namespace ManagedCommandsWrapper {
	class IdentifyPersonCommandExecutor_Impl
	{
	private:
		IdentifyPersonCommandExecutor* m_executor;
	public:
		IdentifyPersonCommandExecutor_Impl(UIUpdateCallbackFuncPtr fptr, bool useOpenCVHighGUI = true)
		{
			m_executor = new IdentifyPersonCommandExecutor(fptr, useOpenCVHighGUI);
		}
		~IdentifyPersonCommandExecutor_Impl()
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

		bool Execute(IdentifyPersonCommandExecutorInputData& inputData)
		{
			std::unique_ptr<NullData> otNullData =
				AdaptiveHumanTracker::SkillsManager<IdentifyPersonCommandExecutorInputData, NullData>::GetInstance()->Execute< IdentifyPersonCommandExecutor>(inputData, *m_executor);
			if (otNullData)
				return true;
			return false;
		}

		void Terminate()
		{
			AdaptiveHumanTracker::SkillsManager<IdentifyPersonCommandExecutorInputData, NullData>::GetInstance()->Terminate();
		}
	};
}


void ManagedCommandsWrapper::MngdIdentifyPersonCommand::Terminate()
{
	m_executorPImpl->Terminate();
}

bool ManagedCommandsWrapper::MngdIdentifyPersonCommand::Execute()
{
	IdentifyPersonCommandExecutorInputData humanDetectCmdInputData;
	
	
	MarshalString(m_inputData->ModelDirectoryPath, humanDetectCmdInputData.modelDirectoryPath);
	MarshalString(m_inputData->DataDirectoryPath, humanDetectCmdInputData.dataDirectoryPath);


	

	if (m_executorPImpl->Execute(humanDetectCmdInputData))
	{
		return true;
	}
	return false;
}


void ManagedCommandsWrapper::MngdIdentifyPersonCommand::UpdateCVMatImageInForm(cv::Mat* openCVImage)
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

UIUpdateCallbackFuncPtr ManagedCommandsWrapper::MngdIdentifyPersonCommand::GetUIUpdateCallbackFuncPtr()
{
	m_BitmapFromCVMatDelegate = gcnew BitmapFromCVMatDelegate(this, &MngdIdentifyPersonCommand::UpdateCVMatImageInForm);
	gch = GCHandle::Alloc(m_BitmapFromCVMatDelegate);

	IntPtr intPointer2Func = Marshal::GetFunctionPointerForDelegate(m_BitmapFromCVMatDelegate);
	UIUpdateCallbackFuncPtr unManagedCallbackcb = static_cast<UIUpdateCallbackFuncPtr>(intPointer2Func.ToPointer());
	return unManagedCallbackcb;
}

void ManagedCommandsWrapper::MngdIdentifyPersonCommand::SetAdaptiveHumanTrackingFormUpdateDelegate(UpdateAdaptiveHumanTrackingFormDelegate^ callback)
{
	m_UpdateAdaptiveHumanTrackingFormDelegate = callback;
}

void ManagedCommandsWrapper::MngdIdentifyPersonCommand::Initializer(System::String^ modelDirPath, System::String^ dataDirPath)
{
	m_inputData = gcnew MngdIdentifyPersonCommandExecutorInputData(modelDirPath, dataDirPath);

	m_UpdateAdaptiveHumanTrackingFormDelegate =
		gcnew UpdateAdaptiveHumanTrackingFormDelegate(this, &ManagedCommandsWrapper::MngdIdentifyPersonCommand::UpdateImageStub);
	UIUpdateCallbackFuncPtr fptr = GetUIUpdateCallbackFuncPtr();
	if (m_executorPImpl)
	{
		delete m_executorPImpl;
		m_executorPImpl = nullptr;
	}
	m_executorPImpl = new IdentifyPersonCommandExecutor_Impl(fptr, false);
}
void ManagedCommandsWrapper::MngdIdentifyPersonCommand::UpdateImageStub(Bitmap^ bitmpImage)
{
	// Stub
	// Do nothing
}
ManagedCommandsWrapper::MngdIdentifyPersonCommand::MngdIdentifyPersonCommand()
{
	m_inputData = gcnew MngdIdentifyPersonCommandExecutorInputData();

	m_UpdateAdaptiveHumanTrackingFormDelegate =
		gcnew UpdateAdaptiveHumanTrackingFormDelegate(this,
			&ManagedCommandsWrapper::MngdIdentifyPersonCommand::UpdateImageStub);
	UIUpdateCallbackFuncPtr fptr = GetUIUpdateCallbackFuncPtr();
	//m_executor = new RegisterPersonCommandExecutor(fptr, false);
	m_executorPImpl = new IdentifyPersonCommandExecutor_Impl(fptr, false);
}
ManagedCommandsWrapper::MngdIdentifyPersonCommand::MngdIdentifyPersonCommand(
	System::String^ modelDirPath, System::String^ dataDirPath)
{
	Initializer(modelDirPath, dataDirPath);
}

ManagedCommandsWrapper::MngdIdentifyPersonCommand::~MngdIdentifyPersonCommand()
{
	if (m_executorPImpl)
	{
		delete m_executorPImpl;
		m_executorPImpl = nullptr;
	}
}
