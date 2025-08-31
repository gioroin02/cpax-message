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
pxMemoryNetFromHost(void* memory, pxiword amount, pxiword stride);

void*
pxMemoryCopyNetFromHost(void* memory, void* value, pxiword amount, pxiword stride);

pxu16
pxU16NetFromHost(pxu16 value);

pxu32
pxU32NetFromHost(pxu32 value);

pxu64
pxU64NetFromHost(pxu64 value);

pxuword
pxUWordNetFromHost(pxuword value);

pxu16
pxI16NetFromHost(pxi16 value);

pxu32
pxI32NetFromHost(pxi32 value);

pxu64
pxI64NetFromHost(pxi64 value);

pxuword
pxIWordNetFromHost(pxiword value);

pxu32
pxF32NetFromHost(pxf32 value);

pxu64
pxF64NetFromHost(pxf64 value);

pxuword
pxFWordNetFromHost(pxfword value);

void*
pxMemoryHostFromNet(void* memory, pxiword amount, pxiword stride);

void*
pxMemoryCopyHostFromNet(void* memory, void* value, pxiword amount, pxiword stride);

pxu16
pxU16HostFromNet(pxu16 value);

pxu32
pxU32HostFromNet(pxu32 value);

pxu64
pxU64HostFromNet(pxu64 value);

pxuword
pxUWordHostFromNet(pxuword value);

pxi16
pxI16HostFromNet(pxu16 value);

pxi32
pxI32HostFromNet(pxu32 value);

pxi64
pxI64HostFromNet(pxu64 value);

pxiword
pxIWordHostFromNet(pxuword value);

pxf32
pxF32HostFromNet(pxu32 value);

pxf64
pxF64HostFromNet(pxu64 value);

pxfword
pxFWordHostFromNet(pxuword value);

#endif // PX_MEMORY_BYTE_ORDER_H
