#ifndef PX_MEMORY_BYTE_ORDER_H
#define PX_MEMORY_BYTE_ORDER_H

#include "import.h"

typedef enum PxByteOrder
{
    PX_BYTE_ORDER_NONE,
    PX_BYTE_ORDER_NETWORK,
    PX_BYTE_ORDER_REVERSE,
    PX_BYET_ORDER_COUNT,
}
PxByteOrder;

PxByteOrder
pxByteOrder();

void*
pxMemoryNetFromLocal(void* memory, pxiword amount, pxiword stride);

void*
pxMemoryNetCopyLocal(void* memory, void* value, pxiword amount, pxiword stride);

pxu16
pxU16NetFromLocal(pxu16 value);

pxu32
pxU32NetFromLocal(pxu32 value);

pxu64
pxU64NetFromLocal(pxu64 value);

pxuword
pxUWordNetFromLocal(pxuword value);

pxu16
pxI16NetFromLocal(pxi16 value);

pxu32
pxI32NetFromLocal(pxi32 value);

pxu64
pxI64NetFromLocal(pxi64 value);

pxuword
pxIWordNetFromLocal(pxiword value);

pxu32
pxF32NetFromLocal(pxf32 value);

pxu64
pxF64NetFromLocal(pxf64 value);

pxuword
pxFWordNetFromLocal(pxfword value);

void*
pxMemoryLocalFromNet(void* memory, pxiword amount, pxiword stride);

void*
pxMemoryLocalCopyNet(void* memory, void* value, pxiword amount, pxiword stride);

pxu16
pxU16LocalFromNet(pxu16 value);

pxu32
pxU32LocalFromNet(pxu32 value);

pxu64
pxU64LocalFromNet(pxu64 value);

pxuword
pxUWordLocalFromNet(pxuword value);

pxi16
pxI16LocalFromNet(pxu16 value);

pxi32
pxI32LocalFromNet(pxu32 value);

pxi64
pxI64LocalFromNet(pxu64 value);

pxiword
pxIWordLocalFromNet(pxuword value);

pxf32
pxF32LocalFromNet(pxu32 value);

pxf64
pxF64LocalFromNet(pxu64 value);

pxfword
pxFWordLocalFromNet(pxuword value);

#endif // PX_MEMORY_BYTE_ORDER_H
