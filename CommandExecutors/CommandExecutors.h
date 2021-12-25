#pragma once
// Generic helper definitions for shared library support
#if defined _WINDOWS || defined __CYGWIN__
  #define DLL_IMPORT __declspec(dllimport)
  #define DLL_EXPORT __declspec(dllexport)
  #define DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define DLL_IMPORT __attribute__ ((visibility ("default")))
    #define DLL_EXPORT __attribute__ ((visibility ("default")))
    #define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define DLL_IMPORT
    #define DLL_EXPORT
    #define DLL_LOCAL
  #endif
#endif

// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the COMMANDEXECUTORS_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// COMMANDEXECUTORS_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef COMMANDEXECUTORS_EXPORTS
#define COMMANDEXECUTORS_API DLL_EXPORT
#else
#define COMMANDEXECUTORS_API DLL_IMPORT
#endif

#include <functional>
// This class is exported from the dll
class COMMANDEXECUTORS_API CCommandExecutors {
public:
	CCommandExecutors(void);
	// TODO: add your methods here.
};

extern COMMANDEXECUTORS_API int nCommandExecutors;

COMMANDEXECUTORS_API int fnCommandExecutors(void);

namespace AdaptiveHumanTracker {

    class COMMANDEXECUTORS_API PostActionRAIIObject {
    private:
        std::function<void()> m_finalAction;
    public:
        PostActionRAIIObject() = delete;
        PostActionRAIIObject(std::function<void()> func);
        ~PostActionRAIIObject();
    };
}

namespace cv
{
    class Mat;
}


namespace {
    void OnUIUpdateStub(cv::Mat* mat)
    {

    }

    std::function<void(cv::Mat*)> __dummyUIUpdateStubFunc(OnUIUpdateStub);
}
//
//// Stubbed functions
//
//COMMANDEXECUTORS_API void __dummyUIUpdateStub(cv::Mat*);
