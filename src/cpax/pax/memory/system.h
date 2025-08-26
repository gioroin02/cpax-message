#ifndef PX_MEMORY_SYSTEM_H
#define PX_MEMORY_SYSTEM_H

#include "import.h"

pxiword
pxMemoryPageSize();

PxArena
pxMemoryReserve(pxiword amount);

void
pxMemoryRelease(PxArena* arena);

#endif // PX_MEMORY_SYSTEM_H
