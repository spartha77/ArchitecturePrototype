// EventsObserversNotifiers.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "EventsObserversNotifiers.h"
#include <iostream>

// This is an example of an exported variable
EVENTSOBSERVERSNOTIFIERS_API int nEventsObserversNotifiers=0;

// This is an example of an exported function.
EVENTSOBSERVERSNOTIFIERS_API int fnEventsObserversNotifiers(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CEventsObserversNotifiers::CEventsObserversNotifiers()
{
    std::cout << "From the constructor CEventsObserversNotifiers::CEventsObserversNotifiers()" << std::endl;
    return;
}
