#ifndef PX_WINDOWS_MEMORY_SYSTEM_H
#define PX_WINDOWS_MEMORY_SYSTEM_H

#include "import.h"

pxiword
pxWindowsMemoryPageSize();

PxArena
pxWindowsMemoryReserve(pxiword amount);

void
pxWindowsMemoryRelease(PxArena* arena);

#endif // PX_WINDOWS_MEMORY_SYSTEM_H
