#ifndef PX_BASE_ARENA_H
#define PX_BASE_ARENA_H

#include "memory.h"

#define pxArenaReserve(arena, type, amount) \
    pxCast(type*, pxArenaReserveMemory(arena, amount, pxSize(type)))

typedef struct PxArena
{
    pxu8*   memory;
    pxiword length;
    pxiword offset;
}
PxArena;

PxArena
pxArenaMake(pxu8* memory, pxiword length);

void*
pxArenaReserveMemory(PxArena* self, pxiword amount, pxiword stride);

pxb8
pxArenaReleaseMemory(PxArena* self, void* memory);

void*
pxArenaCopyMemory(PxArena* self, void* memory, pxiword amount, pxiword stride);

void
pxArenaClear(PxArena* self);

pxiword
pxArenaOffset(PxArena* self);

pxb8
pxArenaRewind(PxArena* self, pxiword offset);

pxiword
pxArenaAlignForw(PxArena* self, pxiword align);

#endif // PX_BASE_ARENA_H
