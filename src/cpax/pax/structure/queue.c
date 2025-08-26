#ifndef PX_STRUCTURE_QUEUE_C
#define PX_STRUCTURE_QUEUE_C

#include "queue.h"

PxQueue
pxQueueReserveMemory(PxArena* arena, pxiword length, pxiword stride)
{
    if (length <= 0 || stride <= 0) return (PxQueue) {0};

    pxu8* memory = pxArenaReserveMemory(arena, length, stride);

    if (memory == 0) return (PxQueue) {0};

    return (PxQueue) {
        .memory = memory,
        .length = length,
        .stride = stride,
    };
}

PxQueue
pxQueueCopy(PxArena* arena, PxQueue* value)
{
    return pxQueueCopyAmount(arena, value, value->size);
}

PxQueue
pxQueueCopyAmount(PxArena* arena, PxQueue* value, pxiword amount)
{
    if (value == 0 || amount <= 0) return (PxQueue) {0};

    pxiword stride = value->stride;
    PxQueue result = pxQueueReserveMemory(arena, amount, stride);

    if (result.length <= 0) return result;

    result.size = pxMin(result.length, value->size);
    result.tail = result.size;

    for (pxiword i = 0; i < result.size; i += 1) {
        pxiword j = (value->head + i) % value->length;

        pxMemoryCopy(result.memory + i * stride,
            value->memory + j * stride, 1, stride);
    }

    return result;
}

void
pxQueueClear(PxQueue* self)
{
    self->size = 0;
    self->head = 0;
    self->tail = 0;
}

void
pxQueueFill(PxQueue* self)
{
    pxiword diff = self->length - self->size;

    self->size = self->length;
    self->tail = self->head;

    for (pxiword i = 0; i < diff; i += 1) {
        pxiword j = (self->head + i) % self->length;

        pxMemoryZero(self->memory + i * self->stride,
            1, self->stride);
    }
}

pxb8
pxQueueInsertHeadMemory(PxQueue* self, void* memory, pxiword stride)
{
    if (self->size < 0 || self->size >= self->length)
        return 0;

    if (self->stride != stride || memory == 0) return 0;

    pxiword prev = self->head + self->length - 1;

    self->size += 1;
    self->head  = prev % self->length;

    pxiword i = self->head;

    pxMemoryCopy(self->memory + i * stride,
        memory, 1, stride);

    return 1;
}

pxb8
pxQueueInsertTailMemory(PxQueue* self, void* memory, pxiword stride)
{
    if (self->size < 0 || self->size >= self->length)
        return 0;

    if (self->stride != stride || memory == 0) return 0;

    pxiword next = self->tail + 1;
    pxiword i    = self->tail;

    pxMemoryCopy(self->memory + i * stride,
        memory, 1, stride);

    self->size += 1;
    self->tail  = next % self->length;

    return 1;
}

pxb8
pxQueueCreateHead(PxQueue* self)
{
    pxiword stride = self->stride;

    if (self->size < 0 || self->size >= self->length)
        return 0;

    pxiword prev = self->head + self->length - 1;

    self->size += 1;
    self->head  = prev % self->length;

    pxiword i = self->head;

    pxMemoryZero(self->memory + i * stride,
        1, stride);

    return 1;
}

pxb8
pxQueueCreateTail(PxQueue* self)
{
    pxiword stride = self->stride;

    if (self->size < 0 || self->size >= self->length)
        return 0;

    pxiword next = self->tail + 1;
    pxiword i    = self->tail;

    pxMemoryZero(self->memory + i * stride,
        1, stride);

    self->size += 1;
    self->tail  = next % self->length;

    return 1;
}

pxb8
pxQueueRemoveHeadMemory(PxQueue* self, void* memory, pxiword stride)
{
    if (self->size <= 0 || self->size > self->length)
        return 0;

    pxiword next = self->head + 1;

    if (memory != 0) {
        pxiword i = self->head;

        pxMemoryCopy(memory, self->memory + i * stride,
            1, stride);
    }

    self->size -= 1;
    self->head  = next % self->length;

    return 1;
}

pxb8
pxQueueRemoveTailMemory(PxQueue* self, void* memory, pxiword stride)
{
    if (self->size <= 0 || self->size > self->length)
        return 0;

    pxiword prev = self->tail + self->length - 1;

    self->size -= 1;
    self->tail  = prev % self->length;

    if (memory != 0) {
        pxiword i = self->tail;

        pxMemoryCopy(memory, self->memory + i * stride,
            1, stride);
    }

    return 1;
}

pxb8
pxQueueDropHead(PxQueue* self)
{
    if (self->size <= 0 || self->size > self->length)
        return 0;

    pxiword next = self->head + 1;

    self->size -= 1;
    self->head  = next % self->length;

    return 1;
}

pxb8
pxQueueDropTail(PxQueue* self)
{
    if (self->size <= 0 || self->size > self->length)
        return 0;

    pxiword prev = self->tail + self->length - 1;

    self->size -= 1;
    self->tail  = prev % self->length;

    return 1;
}

pxb8
pxQueueUpdateMemory(PxQueue* self, pxiword index, void* memory, pxiword stride)
{
    if (index < 0 || index >= self->size)
        return 0;

    if (stride != self->stride || memory == 0) return 0;

    pxiword i = (self->head + index) % self->length;

    pxMemoryCopy(self->memory + i * stride,
        memory, 1, stride);

    return 1;
}

pxb8
pxQueueUpdateHeadMemory(PxQueue* self, void* memory, pxiword stride)
{
    return pxQueueUpdateMemory(self, 0, memory, stride);
}

pxb8
pxQueueUpdateTailMemory(PxQueue* self, void* memory, pxiword stride)
{
    return pxQueueUpdateMemory(self, self->size - 1, memory, stride);
}

pxb8
pxQueueReadMemory(PxQueue* self, pxiword index, void* memory, pxiword stride)
{
    if (index < 0 || index >= self->size)
        return 0;

    if (stride != self->stride) return 0;

    if (memory != 0) {
        pxiword i = (self->head + index) % self->length;

        pxMemoryCopy(memory, self->memory + i * stride,
            1, stride);
    }

    return 1;
}

pxb8
pxQueueReadHeadMemory(PxQueue* self, void* memory, pxiword stride)
{
    return pxQueueReadMemory(self, 0, memory, stride);
}

pxb8
pxQueueReadTailMemory(PxQueue* self, void* memory, pxiword stride)
{
    return pxQueueReadMemory(self, self->size - 1, memory, stride);
}

#endif // PX_STRUCTURE_QUEUE_C
