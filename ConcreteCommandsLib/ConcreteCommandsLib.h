#pragma once
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
// from a DLL simpler. All files within this DLL are compiled with the CONCRETECOMMANDSLIB_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// CONCRETECOMMANDSLIB_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef CONCRETECOMMANDSLIB_EXPORTS
#define CONCRETECOMMANDSLIB_API DLL_EXPORT
#else
#define CONCRETECOMMANDSLIB_API DLL_IMPORT
#endif

// This class is exported from the dll
class CONCRETECOMMANDSLIB_API CConcreteCommandsLib {
public:
	CConcreteCommandsLib(void);
	// TODO: add your methods here.
};

extern CONCRETECOMMANDSLIB_API int nConcreteCommandsLib;

CONCRETECOMMANDSLIB_API int fnConcreteCommandsLib(void);
