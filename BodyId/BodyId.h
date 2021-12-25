
// Generic helper definitions for shared library support
#if defined _WINDOWS || defined __CYGWIN__
  #define FOX_HELPER_DLL_IMPORT __declspec(dllimport)
  #define FOX_HELPER_DLL_EXPORT __declspec(dllexport)
  #define FOX_HELPER_DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define FOX_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define FOX_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
    #define FOX_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define FOX_HELPER_DLL_IMPORT
    #define FOX_HELPER_DLL_EXPORT
    #define FOX_HELPER_DLL_LOCAL
  #endif
#endif

// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the BODYID_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// BODYID_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef BODYID_EXPORTS
#define BODYID_API FOX_HELPER_DLL_EXPORT
#else
#define BODYID_API FOX_HELPER_DLL_IMPORT
#endif

// This class is exported from the dll
class BODYID_API CBodyId {
public:
	CBodyId(void);
	// TODO: add your methods here.
};

extern BODYID_API int nBodyId;

BODYID_API int fnBodyId(void);
