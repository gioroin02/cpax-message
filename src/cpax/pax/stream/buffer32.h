#ifndef PX_STREAM_BUFFER32_H
#define PX_STREAM_BUFFER32_H

#include "import.h"

typedef struct PxBuffer32
{
    pxu32*  memory;
    pxiword length;
    pxiword size;
    pxiword head;
    pxiword tail;
}
PxBuffer32;

/* PxBuffer32 */

PxBuffer32
pxBuffer32Make(pxu32* memory, pxiword length);

PxBuffer32
pxBuffer32MakeFull(pxu32* memory, pxiword length);

PxBuffer32
pxBuffer32Reserve(PxArena* arena, pxiword length);

PxBuffer32
pxBuffer32ReserveFull(PxArena* arena, pxiword length);

PxBuffer32
pxBuffer32Copy(PxArena* arena, PxBuffer32 value);

PxBuffer32
pxBuffer32CopyAmount(PxArena* arena, PxBuffer32 value, pxiword amount);

PxBuffer32
pxBuffer32CopyMemory(PxArena* arena, pxu32* memory, pxiword length);

void
pxBuffer32Clear(PxBuffer32* self);

void
pxBuffer32Fill(PxBuffer32* self);

void
pxBuffer32Normalize(PxBuffer32* self);

/* PxBuffer32 getting */

pxb8
pxBuffer32GetForw(PxBuffer32* self, pxiword index, pxu32* value);

pxu32
pxBuffer32GetForwOr(PxBuffer32* self, pxiword index, pxu32 value);

pxb8
pxBuffer32GetBack(PxBuffer32* self, pxiword index, pxu32* value);

pxu32
pxBuffer32GetBackOr(PxBuffer32* self, pxiword index, pxu32 value);

/* PxBuffer32 dropping */

pxiword
pxBuffer32DropHead(PxBuffer32* self, pxiword amount);

pxiword
pxBuffer32DropTail(PxBuffer32* self, pxiword amount);

/* PxBuffer32 writing */

pxiword
pxBuffer32WriteHead(PxBuffer32* self, PxBuffer32* buffer);

pxiword
pxBuffer32WriteMemoryHead(PxBuffer32* self, pxu32* memory, pxiword length);

pxiword
pxBuffer32WriteStringHead(PxBuffer32* self, PxString32 string);

pxiword
pxBuffer32WriteTail(PxBuffer32* self, PxBuffer32* buffer);

pxiword
pxBuffer32WriteMemoryTail(PxBuffer32* self, pxu32* memory, pxiword length);

pxiword
pxBuffer32WriteStringTail(PxBuffer32* self, PxString32 string);

/* PxBuffer32 reading */

pxiword
pxBuffer32ReadHead(PxBuffer32* self, PxBuffer32* buffer);

pxiword
pxBuffer32ReadMemoryHead(PxBuffer32* self, pxu32* memory, pxiword length);

PxString32
pxBuffer32ReadStringHead(PxBuffer32* self, PxArena* arena, pxiword length);

pxiword
pxBuffer32ReadTail(PxBuffer32* self, PxBuffer32* buffer);

pxiword
pxBuffer32ReadMemoryTail(PxBuffer32* self, pxu32* memory, pxiword length);

PxString32
pxBuffer32ReadStringTail(PxBuffer32* self, PxArena* arena, pxiword length);

/* PxBuffer32 peeking */

pxiword
pxBuffer32PeekHead(PxBuffer32* self, PxBuffer32* buffer);

pxiword
pxBuffer32PeekMemoryHead(PxBuffer32* self, pxu32* memory, pxiword length);

PxString32
pxBuffer32PeekStringHead(PxBuffer32* self, PxArena* arena, pxiword length);

pxiword
pxBuffer32PeekTail(PxBuffer32* self, PxBuffer32* buffer);

pxiword
pxBuffer32PeekMemoryTail(PxBuffer32* self, pxu32* memory, pxiword length);

PxString32
pxBuffer32PeekStringTail(PxBuffer32* self, PxArena* arena, pxiword length);

#endif // PX_STREAM_BUFFER32_H
