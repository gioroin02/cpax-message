#ifndef PX_LINUX_MEMORY_SYSTEM_H
#define PX_LINUX_MEMORY_SYSTEM_H

#include "import.h"

pxiword
pxLinuxMemoryPageSize();

PxArena
pxLinuxMemoryReserve(pxiword amount);

void
pxLinuxMemoryRelease(PxArena* arena);

#endif // PX_LINUX_MEMORY_SYSTEM_H
