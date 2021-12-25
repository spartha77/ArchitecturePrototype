#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "MngdOpenCVWrapper.h"
#include "ManagedCommandsWrapperUtils.h"

// Event handlers
#include <EventsObserversNotifiers.h>
#include <EventData.h>
#include <IObserver.h>
#include <EventHandler.h>
#include <Events.h>
#include <ObserverImpl.h>
#include <ObserverFactory.h>

//#include <Windows.h>

ManagedCommandsWrapper::MngdOpenCVWrapper::MngdOpenCVWrapper()
{
	 m_UpdateAdaptiveHumanTrackingFormDelegate =
		gcnew TestUpdateAdaptiveHumanTrackingFormDelegate(this, &ManagedCommandsWrapper::MngdOpenCVWrapper::UpdateImageStub);
	m_cppOpenCVWrapper = new UnmanagedOpenCVWrapper();
	SetBitmapFromCVMatDelegate();
}

ManagedCommandsWrapper::MngdOpenCVWrapper::~MngdOpenCVWrapper()
{
	delete m_cppOpenCVWrapper;
	m_cppOpenCVWrapper = nullptr;
	gch.Free();
}

	

UnmanagedOpenCVWrapper::UnmanagedOpenCVWrapper()
{
	m_OpenCvImage = cv::imread("C:\\input\\mermaid.jpg", 1);
	
}
UnmanagedOpenCVWrapper::~UnmanagedOpenCVWrapper()
{
	m_OpenCvImage.release();
}
UnmanagedOpenCVWrapper::UnmanagedOpenCVWrapper(const UnmanagedOpenCVWrapper& UnmanagedOpenCVWrapper):
	m_OpenCvImage(UnmanagedOpenCVWrapper.m_OpenCvImage)
{
	
}
UnmanagedOpenCVWrapper& UnmanagedOpenCVWrapper::operator=(UnmanagedOpenCVWrapper& rhs)
{
	
	rhs.m_OpenCvImage.copyTo(this->m_OpenCvImage);
	return *this;
}

cv::Mat UnmanagedOpenCVWrapper::GetOpenCVImage()
{
	return m_OpenCvImage;
}

void UnmanagedOpenCVWrapper::ShowImage(const std::string& m_WindowTitle)
{
	cv::imshow(m_WindowTitle.c_str(), m_OpenCvImage);
}


