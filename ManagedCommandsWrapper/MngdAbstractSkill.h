#pragma once

#ifndef __MNGDABSTRACTSKILL_H__
#define __MNGDABSTRACTSKILL_H__

#using <System.dll>
#using <system.drawing.dll>
#using <System.Windows.Forms.dll>

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;


// Forward declarations
namespace cv
{
	class Mat;
}


#ifdef _WINDOWS
#ifndef __UIUPDATECALLBACKFUNCPTR__
#define __UIUPDATECALLBACKFUNCPTR__
typedef void(__stdcall* UIUpdateCallbackFuncPtr)(cv::Mat*);
#else
typedef void(*UIUpdateCallbackFuncPtr)(cv::Mat*);
#endif
#endif



public delegate void UpdateAdaptiveHumanTrackingFormDelegate(Bitmap^ bitmapImage);
public delegate void BitmapFromCVMatDelegate(cv::Mat*);

namespace ManagedCommandsWrapper {

	public interface class IAbstractSkill
	{
	public:
		//virtual ~IAbstractSkill() {}
		property System::String^ DataDirectoryPath;
		property System::String^ ModelDirectoryPath;
		void Initializer(System::String^ modelDirPath, System::String^ dataDirPath);
		bool Execute();
		void Terminate();
		void UpdateCVMatImageInForm(cv::Mat* openCVImage);
		void UpdateImageStub(Bitmap^ bitmpImage);
		void SetAdaptiveHumanTrackingFormUpdateDelegate(UpdateAdaptiveHumanTrackingFormDelegate^ callback);
		UIUpdateCallbackFuncPtr GetUIUpdateCallbackFuncPtr();
	};
}

#endif
