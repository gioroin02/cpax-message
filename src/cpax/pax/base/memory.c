#ifndef PX_BASE_MEMORY_C
#define PX_BASE_MEMORY_C

#include "memory.h"

void*
pxMemoryZero(void* memory, pxiword amount, pxiword stride)
{
    if (amount <= 0 || stride <= 0) return memory;

    for (pxiword i = 0; i < amount * stride; i += 1)
        pxCast(pxu8*, memory)[i] = 0;

    return memory;
}

void*
pxMemoryFlip(void* memory, pxiword amount, pxiword stride)
{
    if (amount <= 0 || stride <= 0) return memory;

    pxiword l = 0;
    pxiword r = stride * (amount - 1);

    for (; l < r; l += stride, r -= stride) {
        for (pxiword i = 0; i < stride; i += 1) {
            pxu8 left  = pxCast(pxu8*, memory)[l + i];
            pxu8 right = pxCast(pxu8*, memory)[r + i];

            pxCast(pxu8*, memory)[l + i] = right;
            pxCast(pxu8*, memory)[r + i] = left;
        }
    }

    return memory;
}

void*
pxMemoryCopy(void* memory, void* value, pxiword amount, pxiword stride)
{
    if (amount <= 0 || stride <= 0) return memory;

    for (pxiword i = 0; i < amount * stride; i += 1)
        pxCast(pxu8*, memory)[i] = pxCast(pxu8*, value)[i];

    return memory;
}

void*
pxMemoryCopyFlipped(void* memory, void* value, pxiword amount, pxiword stride)
{
    if (amount <= 0 || stride <= 0) return memory;

    for (pxiword i = 0; i < amount; i += 1) {
        pxiword k = (amount - i - 1);

        for (pxiword j = 0; j < stride; j += 1) {
            pxCast(pxu8*, memory)[i * stride + j] =
                pxCast(pxu8*, value)[k * stride + j];
        }
    }

    return memory;
}

void*
pxMemoryCopyBack(void* memory, pxiword amount, pxiword offset, pxiword stride)
{
    if (amount <= 0 || stride <= 0 || offset <= 0)
        return memory;

    pxu8* result = pxCast(pxu8*, memory) - offset * stride;

    for (pxiword i = 0; i < amount * stride; i += 1)
        result[i] = pxCast(pxu8*, memory)[i];

    return result;
}

void*
pxMemoryCopyForw(void* memory, pxiword amount, pxiword offset, pxiword stride)
{
    if (amount <= 0 || stride <= 0 || offset <= 0)
        return memory;

    pxu8* result = pxCast(pxu8*, memory) + offset * stride;

    for (pxiword i = amount * stride; i > 0; i -= 1)
        result[i - 1] = pxCast(pxu8*, memory)[i - 1];

    return result;
}

pxb8
pxMemoryIsEqual(void* memory, void* value, pxiword amount, pxiword stride)
{
    if (amount <= 0 || stride <= 0) return 0;

    for (pxiword i = 0; i < amount * stride; i += 1) {
        if (pxCast(pxu8*, memory)[i] != pxCast(pxu8*, value)[i])
            return 0;
    }

    return 1;
}

#endif // PX_BASE_MEMORY_C
