// FaceIdentificationLib.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "FaceIdentificationLib.h"


// This is an example of an exported variable
FACEIDENTIFICATIONLIB_API int nFaceIdentificationLib=0;

// This is an example of an exported function.
FACEIDENTIFICATIONLIB_API int fnFaceIdentificationLib(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CFaceIdentificationLib::CFaceIdentificationLib()
{
    return;
}
