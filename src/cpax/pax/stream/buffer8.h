#ifndef PX_STREAM_BUFFER8_H
#define PX_STREAM_BUFFER8_H

#include "import.h"

typedef struct PxBuffer8
{
    pxu8*   memory;
    pxiword length;
    pxiword size;
    pxiword head;
    pxiword tail;
}
PxBuffer8;

/* PxBuffer8 */

PxBuffer8
pxBuffer8Make(pxu8* memory, pxiword length);

PxBuffer8
pxBuffer8MakeFull(pxu8* memory, pxiword length);

PxBuffer8
pxBuffer8Reserve(PxArena* arena, pxiword length);

PxBuffer8
pxBuffer8ReserveFull(PxArena* arena, pxiword length);

PxBuffer8
pxBuffer8Copy(PxArena* arena, PxBuffer8 value);

PxBuffer8
pxBuffer8CopyAmount(PxArena* arena, PxBuffer8 value, pxiword amount);

PxBuffer8
pxBuffer8CopyMemory(PxArena* arena, pxu8* memory, pxiword length);

void
pxBuffer8Clear(PxBuffer8* self);

void
pxBuffer8Fill(PxBuffer8* self);

void
pxBuffer8Normalize(PxBuffer8* self);

/* PxBuffer8 getting */

pxb8
pxBuffer8GetForw(PxBuffer8* self, pxiword index, pxu8* value);

pxu8
pxBuffer8GetForwOr(PxBuffer8* self, pxiword index, pxu8 value);

pxb8
pxBuffer8GetBack(PxBuffer8* self, pxiword index, pxu8* value);

pxu8
pxBuffer8GetBackOr(PxBuffer8* self, pxiword index, pxu8 value);

/* PxBuffer8 dropping */

pxiword
pxBuffer8DropHead(PxBuffer8* self, pxiword amount);

pxiword
pxBuffer8DropTail(PxBuffer8* self, pxiword amount);

/* PxBuffer8 writing */

pxiword
pxBuffer8WriteHead(PxBuffer8* self, PxBuffer8* buffer);

pxiword
pxBuffer8WriteMemoryHead(PxBuffer8* self, pxu8* memory, pxiword length);

pxiword
pxBuffer8WriteStringHead(PxBuffer8* self, PxString8 string);

pxiword
pxBuffer8WriteTail(PxBuffer8* self, PxBuffer8* buffer);

pxiword
pxBuffer8WriteMemoryTail(PxBuffer8* self, pxu8* memory, pxiword length);

pxiword
pxBuffer8WriteStringTail(PxBuffer8* self, PxString8 string);

/* PxBuffer8 reading */

pxiword
pxBuffer8ReadHead(PxBuffer8* self, PxBuffer8* buffer);

pxiword
pxBuffer8ReadMemoryHead(PxBuffer8* self, pxu8* memory, pxiword length);

PxString8
pxBuffer8ReadStringHead(PxBuffer8* self, PxArena* arena, pxiword length);

pxiword
pxBuffer8ReadTail(PxBuffer8* self, PxBuffer8* buffer);

pxiword
pxBuffer8ReadMemoryTail(PxBuffer8* self, pxu8* memory, pxiword length);

PxString8
pxBuffer8ReadStringTail(PxBuffer8* self, PxArena* arena, pxiword length);

/* PxBuffer8 peeking */

pxiword
pxBuffer8PeekHead(PxBuffer8* self, PxBuffer8* buffer);

pxiword
pxBuffer8PeekMemoryHead(PxBuffer8* self, pxu8* memory, pxiword length);

PxString8
pxBuffer8PeekStringHead(PxBuffer8* self, PxArena* arena, pxiword length);

pxiword
pxBuffer8PeekTail(PxBuffer8* self, PxBuffer8* buffer);

pxiword
pxBuffer8PeekMemoryTail(PxBuffer8* self, pxu8* memory, pxiword length);

PxString8
pxBuffer8PeekStringTail(PxBuffer8* self, PxArena* arena, pxiword length);

#endif // PX_STREAM_BUFFER8_H
