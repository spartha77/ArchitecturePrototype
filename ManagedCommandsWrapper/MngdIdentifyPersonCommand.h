#pragma once

#ifndef __MNGDIDENTIFYPERSONCMD_H__
#define __MNGDIDENTIFYPERSONCMD_H__


// C++-CLI includes
#include "MngdIdentifyPersonCommandExecutorInputData.h"
#include "ManagedCommandsWrapperUtils.h"
#include "MngdAbstractSkill.h"
//
#using <system.drawing.dll>
using namespace System;
using namespace System::Drawing;
using namespace System::Runtime::InteropServices;
using namespace System::Security::Permissions;




//// Forward declarations
//namespace cv
//{
//	class Mat;
//}

//
//#ifdef _WINDOWS
//typedef void(__stdcall* UIUpdateCallbackFuncPtr)(cv::Mat*);
//#else
//typedef void(*UIUpdateCallbackFuncPtr)(cv::Mat*);
//#endif

//public delegate void UpdateAdaptiveHumanTrackingFormDelegate(Bitmap^ bitmapImage);
//public delegate void BitmapFromCVMatDelegate(cv::Mat*);
//
namespace ManagedCommandsWrapper
{
	class IdentifyPersonCommandExecutor_Impl;
	// The abve PIMPL implements the RegisterPersonCommandExecutor in Private Implementation mode.
	// This is necessitated by the fact that CLR option on C++ code does not include std libraries
	// but they are needed to keep the sanity of the logic, which uses c++ 11 and above. 
	// This is achieved by including the std containers in the run time by providing the logic in
	// the CPP file (MngdRegisterPersonCommand.cpp). Also, this header file may be included in other
	// locations while the includes of the underlying implementer is shielded from those who include
	// this header
}


namespace ManagedCommandsWrapper {

	public ref class MngdIdentifyPersonCommand : IAbstractSkill
	{
	protected:
		ManagedCommandsWrapper::MngdIdentifyPersonCommandExecutorInputData^ m_inputData;
		IdentifyPersonCommandExecutor_Impl* m_executorPImpl;

		// Event handling
		UpdateAdaptiveHumanTrackingFormDelegate^ m_UpdateAdaptiveHumanTrackingFormDelegate;
		BitmapFromCVMatDelegate^ m_BitmapFromCVMatDelegate;
		static GCHandle gch;
	public:
		MngdIdentifyPersonCommand();
		MngdIdentifyPersonCommand(System::String^ modelDirPath, System::String^ dataDirPath);
		void Initializer(System::String^ modelDirPath, System::String^ dataDirPath) override;
		virtual ~MngdIdentifyPersonCommand();

		void UpdateImageStub(Bitmap^ bitmpImage) override;
		void UpdateCVMatImageInForm(cv::Mat* openCVImage) override;
		UIUpdateCallbackFuncPtr GetUIUpdateCallbackFuncPtr() override;
		void SetAdaptiveHumanTrackingFormUpdateDelegate(UpdateAdaptiveHumanTrackingFormDelegate^ callback) override;

		property System::String^ ModelDirectoryPath
		{
			System::String^ get() override
			{
				return m_inputData->ModelDirectoryPath;
			}
			void set(System::String^ value) override
			{
				m_inputData->ModelDirectoryPath = value;
			}
		}

		property System::String^ DataDirectoryPath
		{
			System::String^ get() override
			{
				return m_inputData->DataDirectoryPath;
			}
			void set(System::String^ value) override
			{
				m_inputData->DataDirectoryPath = value;
			}
		}

		bool Execute() override;
		void Terminate() override;
	};

}

#endif
