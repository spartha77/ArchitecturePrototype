// CommandExecutors.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "CommandExecutors.h"
#include <opencv2/core/mat.hpp>

// This is an example of an exported variable
COMMANDEXECUTORS_API int nCommandExecutors=0;

// This is an example of an exported function.
COMMANDEXECUTORS_API int fnCommandExecutors(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CCommandExecutors::CCommandExecutors()
{
    return;
}

AdaptiveHumanTracker::PostActionRAIIObject::PostActionRAIIObject(std::function<void()> func) :m_finalAction(func)
{
}

AdaptiveHumanTracker::PostActionRAIIObject::~PostActionRAIIObject()
{
    m_finalAction();
}
//
//COMMANDEXECUTORS_API void OnUIUpdateStub(cv::Mat* mat)
//{
//    // Do nothing
//}
//
//COMMANDEXECUTORS_API void __dummyUIUpdateStub(cv::Mat*)
//{
//    // Do nothing
//}
