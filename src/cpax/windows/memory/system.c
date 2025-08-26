#ifndef PX_WINDOWS_MEMORY_SYSTEM_C
#define PX_WINDOWS_MEMORY_SYSTEM_C

#include "system.h"

#define NOMINMAX
#define NOGDI
#define WIN32_LEAN_AND_MEAN

#include  <windows.h>

pxiword
pxWindowsMemoryPageSize()
{
    SYSTEM_INFO info = {0};

    GetSystemInfo(&info);

    return pxCast(pxiword, info.dwPageSize);
}

PxArena
pxWindowsMemoryReserve(pxiword amount)
{
    pxiword stride = pxWindowsMemoryPageSize();

    if (amount <= 0 || stride > PX_U32_MAX / amount)
        return (PxArena) {0};

    void* result = VirtualAlloc(0, pxCast(DWORD, amount * stride),
        MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    return (PxArena) {
        .memory = result,
        .length = amount * stride,
    };
}

void
pxWindowsMemoryRelease(PxArena* arena)
{
    if (arena->memory != 0)
        VirtualFree(arena->memory, 0, MEM_RELEASE);

    arena->memory = 0;
    arena->length = 0;
    arena->offset = 0;
}

#endif // PX_WINDOWS_MEMORY_SYSTEM_C
