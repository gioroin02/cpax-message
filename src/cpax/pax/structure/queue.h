#ifndef PX_STRUCTURE_QUEUE_H
#define PX_STRUCTURE_QUEUE_H

#include "import.h"

#define pxQueueReserve(arena, t, length) \
    pxQueueReserveMemory(arena, length, pxSize(t))

#define pxQueueInsertHead(self, t, x) \
    pxQueueInsertHeadMemory(self, x, pxSize(t))

#define pxQueueInsertTail(self, t, x) \
    pxQueueInsertTailMemory(self, x, pxSize(t))

#define pxQueueRemoveHead(self, t, x) \
    pxQueueRemoveHeadMemory(self, x, pxSize(t))

#define pxQueueRemoveTail(self, t, x) \
    pxQueueRemoveTailMemory(self, x, pxSize(t))

#define pxQueueUpdate(self, index, t, x) \
    pxQueueUpdateMemory(self, index, x, pxSize(t))

#define pxQueueUpdateHead(self, t, x) \
    pxQueueUpdateHeadMemory(self, x, pxSize(t))

#define pxQueueUpdateTail(self, t, x) \
    pxQueueUpdateTailMemory(self, x, pxSize(t))

#define pxQueueRead(self, index, t, x) \
    pxQueueReadMemory(self, index, x, pxSize(t))

#define pxQueueReadHead(self, t, x) \
    pxQueueReadHeadMemory(self, x, pxSize(t))

#define pxQueueReadTail(self, t, x) \
    pxQueueReadTailMemory(self, x, pxSize(t))

typedef struct
{
    pxu8*   memory;
    pxiword length;
    pxiword stride;
    pxiword size;
    pxiword head;
    pxiword tail;
}
PxQueue;

PxQueue
pxQueueReserveMemory(PxArena* arena, pxiword length, pxiword stride);

PxQueue
pxQueueCopy(PxArena* arena, PxQueue* value);

PxQueue
pxQueueCopyAmount(PxArena* arena, PxQueue* value, pxiword amount);

void
pxQueueClear(PxQueue* self);

void
pxQueueFill(PxQueue* self);

pxb8
pxQueueInsertHeadMemory(PxQueue* self, void* memory, pxiword stride);

pxb8
pxQueueInsertTailMemory(PxQueue* self, void* memory, pxiword stride);

pxb8
pxQueueCreateHead(PxQueue* self);

pxb8
pxQueueCreateTail(PxQueue* self);

pxb8
pxQueueRemoveHeadMemory(PxQueue* self, void* memory, pxiword stride);

pxb8
pxQueueRemoveTailMemory(PxQueue* self, void* memory, pxiword stride);

pxb8
pxQueueDropHead(PxQueue* self);

pxb8
pxQueueDropTail(PxQueue* self);

pxb8
pxQueueUpdateMemory(PxQueue* self, pxiword index, void* memory, pxiword stride);

pxb8
pxQueueUpdateHeadMemory(PxQueue* self, void* memory, pxiword stride);

pxb8
pxQueueUpdateTailMemory(PxQueue* self, void* memory, pxiword stride);

pxb8
pxQueueReadMemory(PxQueue* self, pxiword index, void* memory, pxiword stride);

pxb8
pxQueueReadHeadMemory(PxQueue* self, void* memory, pxiword stride);

pxb8
pxQueueReadTailMemory(PxQueue* self, void* memory, pxiword stride);

#endif // PX_STRUCTURE_QUEUE_H
