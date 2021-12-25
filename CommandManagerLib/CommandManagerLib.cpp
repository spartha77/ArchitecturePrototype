// CommandManagerLib.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "CommandManagerLib.h"


// This is an example of an exported variable
COMMANDMANAGERLIB_API int nCommandManagerLib=0;

// This is an example of an exported function.
COMMANDMANAGERLIB_API int fnCommandManagerLib(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CCommandManagerLib::CCommandManagerLib()
{
    return;
}
