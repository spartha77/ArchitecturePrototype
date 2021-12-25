// ConcreteCommandsLib.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "ConcreteCommandsLib.h"


// This is an example of an exported variable
CONCRETECOMMANDSLIB_API int nConcreteCommandsLib=0;

// This is an example of an exported function.
CONCRETECOMMANDSLIB_API int fnConcreteCommandsLib(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CConcreteCommandsLib::CConcreteCommandsLib()
{
    return;
}
