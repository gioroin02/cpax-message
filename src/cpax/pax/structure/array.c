#ifndef PX_STRUCTURE_ARRAY_C
#define PX_STRUCTURE_ARRAY_C

#include "array.h"

PxArray
pxArrayReserveMemory(PxArena* arena, pxiword length, pxiword stride)
{
    if (length <= 0 || stride <= 0) return (PxArray) {0};

    pxu8* memory = pxArenaReserveMemory(arena, length, stride);

    if (memory == 0) return (PxArray) {0};

    return (PxArray) {
        .memory = memory,
        .length = length,
        .stride = stride,
    };
}

PxArray
pxArrayCopy(PxArena* arena, PxArray* value)
{
    return pxArrayCopyAmount(arena, value, value->size);
}

PxArray
pxArrayCopyAmount(PxArena* arena, PxArray* value, pxiword amount)
{
    if (value == 0 || amount <= 0) return (PxArray) {0};

    pxiword stride = value->stride;
    PxArray result = pxArrayReserveMemory(arena, amount, stride);

    if (result.length <= 0) return result;

    result.size = pxMin(result.length, value->size);

    for (pxiword i = 0; i < result.size; i += 1) {
        pxMemoryCopy(result.memory + i * stride,
            value->memory + i * stride, 1, stride);
    }

    return result;
}

void
pxArrayClear(PxArray* self)
{
    self->size = 0;
}

void
pxArrayFill(PxArray* self)
{
    pxiword diff = self->length - self->size;

    self->size = self->length;

    for (pxiword i = 0; i < diff; i += 1) {
        pxMemoryZero(self->memory + i * self->stride,
            1, self->stride);
    }
}

pxb8
pxArrayInsertMemory(PxArray* self, pxiword index, void* memory, pxiword stride)
{
    if (self->size < 0 || self->size >= self->length)
        return 0;

    if (index < 0 || index > self->size) return 0;

    if (self->stride != stride || memory == 0) return 0;

    if (index > 0) {
        pxiword length = self->size - index;

        pxMemoryCopyForw(self->memory + index * stride,
            length, 1, stride);
    }

    pxMemoryCopy(self->memory + index * stride,
        memory, 1, stride);

    self->size += 1;

    return 1;
}

pxb8
pxArrayInsertHeadMemory(PxArray* self, void* memory, pxiword stride)
{
    return pxArrayInsertMemory(self, 0, memory, stride);
}

pxb8
pxArrayInsertTailMemory(PxArray* self, void* memory, pxiword stride)
{
    return pxArrayInsertMemory(self, self->size, memory, stride);
}

pxb8
pxArrayCreate(PxArray* self, pxiword index)
{
    pxiword stride = self->stride;

    if (self->size < 0 || self->size >= self->length)
        return 0;

    if (index < 0 || index > self->size) return 0;

    if (index > 0) {
        pxiword length = self->size - index;

        pxMemoryCopyForw(self->memory + index * stride,
            length, 1, stride);
    }

    pxMemoryZero(self->memory + index * stride, 1, stride);

    self->size += 1;

    return 1;
}

pxb8
pxArrayCreateHead(PxArray* self)
{
    return pxArrayCreate(self, 0);
}

pxb8
pxArrayCreateTail(PxArray* self)
{
    return pxArrayCreate(self, self->size);
}

pxb8
pxArrayRemoveMemory(PxArray* self, pxiword index, void* memory, pxiword stride)
{
    if (index < 0 || index >= self->size)
        return 0;

    if (self->stride != stride) return 0;

    if (memory != 0) {
        pxMemoryCopy(memory, self->memory + index * stride,
            1, stride);
    }

    if (index > 0) {
        pxiword length = self->size - index;

        pxMemoryCopyBack(self->memory + index * stride,
            length, 1, stride);
    }

    self->size -= 1;

    return 1;
}

pxb8
pxArrayRemoveHeadMemory(PxArray* self, void* memory, pxiword stride)
{
    return pxArrayRemoveMemory(self, 0, memory, stride);
}

pxb8
pxArrayRemoveTailMemory(PxArray* self, void* memory, pxiword stride)
{
    return pxArrayRemoveMemory(self, self->size - 1, memory, stride);
}

pxb8
pxArrayDrop(PxArray* self, pxiword index)
{
    if (index < 0 || index >= self->size)
        return 0;

    pxiword length = self->size - index;
    pxiword stride = self->stride;

    pxMemoryCopyBack(self->memory + index * stride,
        length, 1, stride);

    self->size -= 1;

    return 1;
}

pxb8
pxArrayDropHead(PxArray* self)
{
    return pxArrayDrop(self, 0);
}

pxb8
pxArrayDropTail(PxArray* self)
{
    return pxArrayDrop(self, self->size - 1);
}

pxb8
pxArrayUpdateMemory(PxArray* self, pxiword index, void* memory, pxiword stride)
{
    if (index < 0 || index >= self->size)
        return 0;

    if (stride != self->stride || memory == 0) return 0;

    pxiword i = index;

    pxMemoryCopy(self->memory + i * stride,
        memory, 1, stride);

    return 1;
}

pxb8
pxArrayUpdateHeadMemory(PxArray* self, void* memory, pxiword stride)
{
    return pxArrayUpdateMemory(self, 0, memory, stride);
}

pxb8
pxArrayUpdateTailMemory(PxArray* self, void* memory, pxiword stride)
{
    return pxArrayUpdateMemory(self, self->size - 1, memory, stride);
}

pxb8
pxArrayReadMemory(PxArray* self, pxiword index, void* memory, pxiword stride)
{
    if (index < 0 || index >= self->size)
        return 0;

    if (stride != self->stride) return 0;

    if (memory != 0) {
        pxiword i = index;

        pxMemoryCopy(memory, self->memory + i * stride,
            1, stride);
    }

    return 1;
}

pxb8
pxArrayReadHeadMemory(PxArray* self, void* memory, pxiword stride)
{
    return pxArrayReadMemory(self, 0, memory, stride);
}

pxb8
pxArrayReadTailMemory(PxArray* self, void* memory, pxiword stride)
{
    return pxArrayReadMemory(self, self->size - 1, memory, stride);
}

#endif // PX_STRUCTURE_ARRAY_C
