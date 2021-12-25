// BodyId.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "BodyId.h"


// This is an example of an exported variable
BODYID_API int nBodyId=0;

// This is an example of an exported function.
BODYID_API int fnBodyId(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CBodyId::CBodyId()
{
    return;
}
