#ifndef PX_LINUX_MEMORY_SYSTEM_C
#define PX_LINUX_MEMORY_SYSTEM_C

#include "system.h"

#include <unistd.h>
#include <sys/mman.h>

pxiword
pxLinuxMemoryPageSize()
{
    return pxCast(pxiword, sysconf(_SC_PAGESIZE));
}

PxArena
pxLinuxMemoryReserve(pxiword amount)
{
    pxiword stride = pxLinuxMemoryPageSize();

    if (amount <= 0 || stride > PX_U32_MAX / amount)
        return (PxArena) {0};

    void* result = mmap(0, amount * stride, PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (result == MAP_FAILED)
        return (PxArena) {0};

    return (PxArena) {
        .memory = result,
        .length = amount * stride,
    };
}

void
pxLinuxMemoryRelease(PxArena* arena)
{
    if (arena->memory != 0)
        munmap(arena->memory, arena->length);

    arena->memory = 0;
    arena->length = 0;
    arena->offset = 0;
}

#endif // PX_LINUX_MEMORY_SYSTEM_C
