#ifndef PX_MEMORY_BYTE_ORDER_C
#define PX_MEMORY_BYTE_ORDER_C

#include "order.h"

PxByteOrder
pxByteOrder()
{
    pxu16 word = 0x0001;

    switch (pxCast(pxu8*, &word)[0]) {
        case 0:
            return PX_BYTE_ORDER_NETWORK;

        case 1:
            return PX_BYTE_ORDER_REVERSE;

        default: break;
    }

    return PX_BYTE_ORDER_NONE;
}

void*
pxMemoryNetFromLocal(void* memory, pxiword amount, pxiword stride)
{
    if (pxByteOrder() == PX_BYTE_ORDER_REVERSE)
        return pxMemoryFlip(memory, amount * stride, 1);

    return memory;
}

void*
pxMemoryNetCopyLocal(void* memory, void* value, pxiword amount, pxiword stride)
{
    if (pxByteOrder() == PX_BYTE_ORDER_REVERSE)
        return pxMemoryCopyFlipped(memory, value, amount * stride, 1);

    return pxMemoryCopy(memory, value, amount * stride, 1);
}

pxu16
pxU16NetFromLocal(pxu16 value)
{
    pxu16 result = 0;

    pxMemoryNetCopyLocal(&result,
        &value, 1, PX_U16_SIZE);

    return result;
}

pxu32
pxU32NetFromLocal(pxu32 value)
{
    pxu32 result = 0;

    pxMemoryNetCopyLocal(&result,
        &value, 1, PX_U32_SIZE);

    return result;
}

pxu64
pxU64NetFromLocal(pxu64 value)
{
    pxu64 result = 0;

    pxMemoryNetCopyLocal(&result,
        &value, 1, PX_U64_SIZE);

    return result;
}

pxuword
pxUWordNetFromLocal(pxuword value)
{
    pxuword result = 0;

    pxMemoryNetCopyLocal(&result,
        &value, 1, PX_UWORD_SIZE);

    return result;
}

pxu16
pxI16NetFromLocal(pxi16 value)
{
    pxu16 result = 0;

    pxMemoryNetCopyLocal(&result,
        &value, 1, PX_I16_SIZE);

    return result;
}

pxu32
pxI32NetFromLocal(pxi32 value)
{
    pxu32 result = 0;

    pxMemoryNetCopyLocal(&result,
        &value, 1, PX_I32_SIZE);

    return result;
}

pxu64
pxI64NetFromLocal(pxi64 value)
{
    pxu64 result = 0;

    pxMemoryNetCopyLocal(&result,
        &value, 1, PX_I64_SIZE);

    return result;
}

pxuword
pxIWordNetFromLocal(pxiword value)
{
    pxuword result = 0;

    pxMemoryNetCopyLocal(&result,
        &value, 1, PX_IWORD_SIZE);

    return result;
}

pxu32
pxF32NetFromLocal(pxf32 value)
{
    pxu32 result = 0;

    pxMemoryNetCopyLocal(&result,
        &value, 1, PX_F32_SIZE);

    return result;
}

pxu64
pxF64NetFromLocal(pxf64 value)
{
    pxu64 result = 0;

    pxMemoryNetCopyLocal(&result,
        &value, 1, PX_F64_SIZE);

    return result;
}

pxuword
pxFWordNetFromLocal(pxfword value)
{
    pxuword result = 0;

    pxMemoryNetCopyLocal(&result,
        &value, 1, PX_FWORD_SIZE);

    return result;
}

void*
pxMemoryLocalFromNet(void* memory, pxiword amount, pxiword stride)
{
    if (pxByteOrder() == PX_BYTE_ORDER_REVERSE)
        return pxMemoryFlip(memory, amount * stride, 1);

    return memory;
}

void*
pxMemoryLocalCopyNet(void* memory, void* value, pxiword amount, pxiword stride)
{
    if (pxByteOrder() == PX_BYTE_ORDER_REVERSE)
        return pxMemoryCopyFlipped(memory, value, amount * stride, 1);

    return pxMemoryCopy(memory, value, amount * stride, 1);
}

pxu16
pxU16LocalFromNet(pxu16 value)
{
    pxu16 result = 0;

    pxMemoryLocalCopyNet(&result,
        &value, 1, PX_U16_SIZE);

    return result;
}

pxu32
pxU32LocalFromNet(pxu32 value)
{
    pxu32 result = 0;

    pxMemoryLocalCopyNet(&result,
        &value, 1, PX_U32_SIZE);

    return result;
}

pxu64
pxU64LocalFromNet(pxu64 value)
{
    pxu64 result = 0;

    pxMemoryLocalCopyNet(&result,
        &value, 1, PX_U64_SIZE);

    return result;
}

pxuword
pxUWordLocalFromNet(pxuword value)
{
    pxuword result = 0;

    pxMemoryLocalCopyNet(&result,
        &value, 1, PX_UWORD_SIZE);

    return result;
}

pxi16
pxI16LocalFromNet(pxu16 value)
{
    pxi16 result = 0;

    pxMemoryLocalCopyNet(&result,
        &value, 1, PX_I64_SIZE);

    return result;
}

pxi32
pxI32LocalFromNet(pxu32 value)
{
    pxi32 result = 0;

    pxMemoryLocalCopyNet(&result,
        &value, 1, PX_I32_SIZE);

    return result;
}

pxi64
pxI64LocalFromNet(pxu64 value)
{
    pxi64 result = 0;

    pxMemoryLocalCopyNet(&result,
        &value, 1, PX_I64_SIZE);

    return result;
}

pxiword
pxIWordLocalFromNet(pxuword value)
{
    pxiword result = 0;

    pxMemoryLocalCopyNet(&result,
        &value, 1, PX_IWORD_SIZE);

    return result;
}

pxf32
pxF32LocalFromNet(pxu32 value)
{
    pxf32 result = 0;

    pxMemoryLocalCopyNet(&result,
        &value, 1, PX_F32_SIZE);

    return result;
}

pxf64
pxF64LocalFromNet(pxu64 value)
{
    pxf64 result = 0;

    pxMemoryLocalCopyNet(&result,
        &value, 1, PX_F64_SIZE);

    return result;
}

pxfword
pxFWordLocalFromNet(pxuword value)
{
    pxfword result = 0;

    pxMemoryLocalCopyNet(&result,
        &value, 1, PX_FWORD_SIZE);

    return result;
}

#endif // PX_MEMORY_BYTE_ORDER_C
