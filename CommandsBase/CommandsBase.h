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
// from a DLL simpler. All files within this DLL are compiled with the COMMANDS_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// COMMANDS_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#pragma once
#ifdef COMMANDSBASE_EXPORTS
#define COMMANDSBASE_API DLL_EXPORT
#else
#define COMMANDSBASE_API DLL_IMPORT
#endif

// This class is exported from the dll
class COMMANDSBASE_API CCommandsBase {
public:
	CCommandsBase(void);
	// TODO: add your methods here.
};

extern COMMANDSBASE_API int nCommandsBase;

COMMANDSBASE_API int fnCommandsBase(void);
