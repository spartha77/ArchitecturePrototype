// FaceDetectionLib.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "FaceDetectionLib.h"


// This is an example of an exported variable
FACEDETECTIONLIB_API int nFaceDetectionLib=0;

// This is an example of an exported function.
FACEDETECTIONLIB_API int fnFaceDetectionLib(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CFaceDetectionLib::CFaceDetectionLib()
{
    return;
}
