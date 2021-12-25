// CommandsBase.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "CommandsBase.h"


// This is an example of an exported variable
COMMANDSBASE_API int nCommandsBase=0;

// This is an example of an exported function.
COMMANDSBASE_API int fnCommandsBase(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CCommandsBase::CCommandsBase()
{
    return;
}
