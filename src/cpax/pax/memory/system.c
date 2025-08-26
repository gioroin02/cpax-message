#ifndef PX_MEMORY_SYSTEM_C
#define PX_MEMORY_SYSTEM_C

#include "system.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../../windows/memory/system.c"

    #define __pxMemoryPageSize__ pxWindowsMemoryPageSize
    #define __pxMemoryReserve__  pxWindowsMemoryReserve
    #define __pxMemoryRelease__  pxWindowsMemoryRelease

#else

    #error "Unknown platform

#endif

pxiword
pxMemoryPageSize()
{
    return __pxMemoryPageSize__();
}

PxArena
pxMemoryReserve(pxiword amount)
{
    return __pxMemoryReserve__(amount);
}

void
pxMemoryRelease(PxArena* arena)
{
    __pxMemoryRelease__(arena);
}

#endif // PX_MEMORY_SYSTEM_C
