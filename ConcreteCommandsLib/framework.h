#pragma once

// Windows Header Files
#if defined _WINDOWS
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <Windows.h>
#else
#include <unistd.h>
#endif

