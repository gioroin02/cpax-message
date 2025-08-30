#ifndef PX_MEMORY_SYSTEM_C
#define PX_MEMORY_SYSTEM_C

#include "system.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../../windows/memory/system.c"

    #define __pxMemoryPageSize__ pxWindowsMemoryPageSize
    #define __pxMemoryReserve__  pxWindowsMemoryReserve
    #define __pxMemoryRelease__  pxWindowsMemoryRelease

#elif PX_SYSTEM == PX_SYSTEM_LINUX

    #include "../../linux/memory/system.c"

    #define __pxMemoryPageSize__ pxLinuxMemoryPageSize
    #define __pxMemoryReserve__  pxLinuxMemoryReserve
    #define __pxMemoryRelease__  pxLinuxMemoryRelease

#else

    #error "Unknown platform"

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
