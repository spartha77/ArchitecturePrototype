#pragma once

#include <memory>
#include <opencv2/core/mat.hpp>
#include <gcroot.h>
#using <system.drawing.dll>
#using <System.Windows.Forms.dll>
using namespace System;
using namespace System::Windows;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Runtime::InteropServices;
using namespace System::Security::Permissions;

class UnmanagedOpenCVWrapper;
typedef void (__stdcall* TestBitmapFromCVMatFunctionPtr)(UnmanagedOpenCVWrapper*);
//static TestBitmapFromCVMatFunctionPtr testBitmapFromCVMatFunctionPtr;

public delegate void TestUpdateAdaptiveHumanTrackingFormDelegate(Bitmap^ bitmapImage);
public delegate void TestBitmapFromCVMatDelegate(UnmanagedOpenCVWrapper*);

extern "C" {
	__declspec(dllexport)  class  UnmanagedOpenCVWrapper
	{
	private:
		cv::Mat m_OpenCvImage;
		TestBitmapFromCVMatFunctionPtr m_BitmapFromCVMatFunctionPtr;

	public:
		UnmanagedOpenCVWrapper();
		~UnmanagedOpenCVWrapper();
		UnmanagedOpenCVWrapper(const UnmanagedOpenCVWrapper& UnmanagedOpenCVWrapper);
		UnmanagedOpenCVWrapper& operator=(UnmanagedOpenCVWrapper& rhs);
		cv::Mat GetOpenCVImage();
		void ShowImage(const std::string& m_WindowTitle);
		void OnEventNotified(cv::Mat& image)
		{
			m_BitmapFromCVMatFunctionPtr(this);
		}
		void SetBitmapFromCVMatFunctionPtr(TestBitmapFromCVMatFunctionPtr callback)
		{
			m_BitmapFromCVMatFunctionPtr = callback;
		}
	};
}





namespace ManagedCommandsWrapper {
	
	public ref class MngdOpenCVWrapper
	{
	private:
		UnmanagedOpenCVWrapper* m_cppOpenCVWrapper;
		TestUpdateAdaptiveHumanTrackingFormDelegate^ m_UpdateAdaptiveHumanTrackingFormDelegate;
		TestBitmapFromCVMatDelegate^ m_BitmapFromCVMatDelegate;
		static GCHandle gch;
		
	public:
		
		MngdOpenCVWrapper();
		//MngdOpenCVWrapper(UnmanagedOpenCVWrapper* image);
		~MngdOpenCVWrapper();
		//property UnmanagedOpenCVWrapper Image;
		void UpdateCVMatImageInForm(UnmanagedOpenCVWrapper* cppWrapper)
		{
			if (cppWrapper == nullptr)
				return;
			//std::string cppWindowTitle;
			//ManagedCommandsWrapper::MarshalString(windowTitle, cppWindowTitle);

			//HBITMAP hBit = CreateBitmap(m_cppOpenCVWrapper->GetOpenCVImage().cols, 
			//	m_cppOpenCVWrapper->GetOpenCVImage().rows, 1, 32, m_cppOpenCVWrapper->GetOpenCVImage().data);

			////m_cppOpenCVWrapper->ShowImage(cppWindowTitle);
			////Bitmap^ bitmapOfOpenCVImage = gcnew Bitmap(m_cppOpenCVWrapper->GetOpenCVImage().rows, 
			////	m_cppOpenCVWrapper->GetOpenCVImage().cols, 
			////	/*4 * m_cppOpenCVWrapper->GetOpenCVImage().rows, */
			////	m_cppOpenCVWrapper->GetOpenCVImage().step1(),
			////	System::Drawing::Imaging::PixelFormat::Format4bppIndexed, 
			////	IntPtr(m_cppOpenCVWrapper->GetOpenCVImage().data));
			//Bitmap^ bitmapOfOpenCVImage = Bitmap::FromHbitmap((IntPtr)hBit);
			//return bitmapOfOpenCVImage;


			/*return gcnew Bitmap(m_cppOpenCVWrapper->GetOpenCVImage().cols,
				m_cppOpenCVWrapper->GetOpenCVImage().rows,
				4 * m_cppOpenCVWrapper->GetOpenCVImage().rows,
				System::Drawing::Imaging::PixelFormat::Format24bppRgb,
				IntPtr(m_cppOpenCVWrapper->GetOpenCVImage().data));*/

			Bitmap^ newBitmap = gcnew Bitmap(cppWrapper->GetOpenCVImage().cols,
				cppWrapper->GetOpenCVImage().rows,
				cppWrapper->GetOpenCVImage().step1(),
				System::Drawing::Imaging::PixelFormat::Format24bppRgb,
				IntPtr(cppWrapper->GetOpenCVImage().data));

			m_UpdateAdaptiveHumanTrackingFormDelegate(newBitmap);

		}
		
		void SetBitmapFromCVMatDelegate()
		{
			m_BitmapFromCVMatDelegate = gcnew TestBitmapFromCVMatDelegate(this, &MngdOpenCVWrapper::UpdateCVMatImageInForm);
			gch = GCHandle::Alloc(m_BitmapFromCVMatDelegate);

			IntPtr intPointer2Func = Marshal::GetFunctionPointerForDelegate(m_BitmapFromCVMatDelegate);
			TestBitmapFromCVMatFunctionPtr unManagedCallbackcb = static_cast<TestBitmapFromCVMatFunctionPtr>(intPointer2Func.ToPointer());
			m_cppOpenCVWrapper->SetBitmapFromCVMatFunctionPtr(unManagedCallbackcb);
		}
		void SetAdaptiveHumanTrackingFormUpdateDelegate(TestUpdateAdaptiveHumanTrackingFormDelegate^ callback)
		{
			m_UpdateAdaptiveHumanTrackingFormDelegate = callback;
				//gcnew TestUpdateAdaptiveHumanTrackingFormDelegate(this, &MngdOpenCVWrapper::UpdateImage);
			
		}
		void UpdateImageStub(Bitmap^ bitmpImage)
		{
			//m_cppOpenCVWrapper->SetAdaptiveHumanTrackingFormFunctionPtr();
			// Stub
			// Do nothing
		}
		property UnmanagedOpenCVWrapper* OpenCVImageWrapper {
			UnmanagedOpenCVWrapper* get() {
				return m_cppOpenCVWrapper;
			}

			void set(UnmanagedOpenCVWrapper* value) {
				*m_cppOpenCVWrapper = *value;
			}
		}

		void TriggerUpdate()
		{
			m_cppOpenCVWrapper->OnEventNotified(m_cppOpenCVWrapper->GetOpenCVImage());
		}
	};
}


