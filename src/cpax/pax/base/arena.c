#ifndef PX_BASE_ARENA_C
#define PX_BASE_ARENA_C

#include "arena.h"

PxArena
pxArenaMake(pxu8* memory, pxiword length)
{
    if (memory == 0 || length <= 0)
        return (PxArena) {0};

    return (PxArena) {
        .memory = memory,
        .length = length,
    };
}

void*
pxArenaReserveMemory(PxArena* self, pxiword amount, pxiword stride)
{
    pxiword length = amount * stride;

    if (amount <= 0 || stride <= 0) return 0;

    pxiword start = pxArenaAlignForw(self, stride);
    pxiword stop  = start + length;

    if (start < self->offset || stop > self->length)
        return 0;

    pxMemoryZero(self->memory + start, length, 1);

    self->offset = stop;

    return self->memory + start;
}

pxb8
pxArenaReleaseMemory(PxArena* self, void* memory)
{
    return 0;
}

void*
pxArenaCopyMemory(PxArena* self, void* memory, pxiword amount, pxiword stride)
{
    if (memory == 0 || amount <= 0 || stride <= 0)
        return 0;

    void* result = pxArenaReserveMemory(self, amount, stride);

    if (result != 0)
        pxMemoryCopy(result, memory, amount, stride);

    return result;
}

void
pxArenaClear(PxArena* self)
{
    self->offset = 0;
}

pxiword
pxArenaOffset(PxArena* self)
{
    return self->offset;
}

pxb8
pxArenaRewind(PxArena* self, pxiword offset)
{
    if (offset < 0 || offset >= self->length)
        return 0;

    self->offset = offset;

    return 1;
}

pxiword
pxArenaAlignForw(PxArena* self, pxiword align)
{
    if (align <= 0) return self->offset;

    pxiword diff = self->offset % align;

    if (diff != 0)
        return self->offset + align - diff;

    return self->offset;
}

#endif // PX_BASE_ARENA_C
