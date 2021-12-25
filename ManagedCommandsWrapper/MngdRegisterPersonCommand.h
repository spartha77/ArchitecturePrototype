#pragma once

#include <opencv2/opencv.hpp>


// C++-CLI includes
#include "MngdRegisterPersonCommandExecutorInputData.h"
#include "ManagedCommandsWrapperUtils.h"

//
#using <system.drawing.dll>
using namespace System;
using namespace System::Drawing;
using namespace System::Runtime::InteropServices;
using namespace System::Security::Permissions;



#ifdef _WINDOWS
typedef void(__stdcall* UIUpdateCallbackFuncPtr)(cv::Mat*);
#else
typedef void(*UIUpdateCallbackFuncPtr)(cv::Mat*);
#endif

public delegate void UpdateAdaptiveHumanTrackingFormDelegate(Bitmap^ bitmapImage);
public delegate void BitmapFromCVMatDelegate(cv::Mat*);
//

namespace ManagedCommandsWrapper
{
	class RegisterPersonCommandExecutor_Impl;
	// The abve PIMPL implements the RegisterPersonCommandExecutor in Private Implementation mode.
	// This is necessitated by the fact that CLR option on C++ code does not include std libraries
	// but they are needed to keep the sanity of the logic, which uses c++ 11 and above. 
	// This is achieved by including the std containers in the run time by providing the logic in
	// the CPP file (MngdRegisterPersonCommand.cpp). Also, this header file may be included in other
	// locations while the includes of the underlying implementer is shielded from those who include
	// this header
}


namespace ManagedCommandsWrapper {



	public ref class MngdRegisterPersonCommand
	{
	protected:
		ManagedCommandsWrapper::MngdRegisterPersonCommandExecutorInputData^ m_inputData;
		RegisterPersonCommandExecutor_Impl* m_executorPImpl;

		//AdaptiveHumanTracker::IObserver* m_registerPersonObserver;
		//AdaptiveHumanTracker::EventHandler<AdaptiveHumanTracker::Event, cv::Mat>* m_EventHandler; // Singleton

		// Event handling
		UpdateAdaptiveHumanTrackingFormDelegate^ m_UpdateAdaptiveHumanTrackingFormDelegate;
		BitmapFromCVMatDelegate^ m_BitmapFromCVMatDelegate;
		static GCHandle gch;
	public:
		~MngdRegisterPersonCommand();
		MngdRegisterPersonCommand();
		
		void Initializer(System::String^ modelDirPath, System::String^ dataDirPath,
			System::String^ imageDirPath, System::String^ regName);

		MngdRegisterPersonCommand(System::String^ modelDirPath, System::String^ dataDirPath,
			System::String^ imageDirPath, System::String^ regName);
		
		void UpdateImageStub(Bitmap^ bitmpImage);

		void UpdateCVMatImageInForm(cv::Mat* openCVImage);

		UIUpdateCallbackFuncPtr GetUIUpdateCallbackFuncPtr();

		void SetAdaptiveHumanTrackingFormUpdateDelegate(UpdateAdaptiveHumanTrackingFormDelegate^ callback);

		property System::String^ ModelDirectoryPath
		{
			System::String^ get();
			void set(System::String^ value);
		}

		property System::String^ DataDirectoryPath
		{
			System::String^ get();
			void set(System::String^ value);
		}

		property System::String^ ImageDirectoryPath
		{
			System::String^ get();
			void set(System::String^ value);
		}

		property System::String^ RegisteredName
		{
			System::String^ get();
			void set(System::String^ value);
		}

		property FaceRegistrationMode RegistrationMode
		{
			FaceRegistrationMode get();
			void set(FaceRegistrationMode value);
		}

		bool Execute();
	};

}
