#ifndef PX_STREAM_BUFFER16_H
#define PX_STREAM_BUFFER16_H

#include "import.h"

typedef struct PxBuffer16
{
    pxu16*  memory;
    pxiword length;
    pxiword size;
    pxiword head;
    pxiword tail;
}
PxBuffer16;

/* PxBuffer16 */

PxBuffer16
pxBuffer16Make(pxu16* memory, pxiword length);

PxBuffer16
pxBuffer16MakeFull(pxu16* memory, pxiword length);

PxBuffer16
pxBuffer16Reserve(PxArena* arena, pxiword length);

PxBuffer16
pxBuffer16ReserveFull(PxArena* arena, pxiword length);

PxBuffer16
pxBuffer16Copy(PxArena* arena, PxBuffer16 value);

PxBuffer16
pxBuffer16CopyAmount(PxArena* arena, PxBuffer16 value, pxiword amount);

PxBuffer16
pxBuffer16CopyMemory16(PxArena* arena, pxu16* memory, pxiword length);

void
pxBuffer16Clear(PxBuffer16* self);

void
pxBuffer16Fill(PxBuffer16* self);

void
pxBuffer16Normalize(PxBuffer16* self);

/* PxBuffer16 getting */

pxb8
pxBuffer16GetForw(PxBuffer16* self, pxiword index, pxu16* value);

pxu16
pxBuffer16GetForwOr(PxBuffer16* self, pxiword index, pxu16 value);

pxb8
pxBuffer16GetBack(PxBuffer16* self, pxiword index, pxu16* value);

pxu16
pxBuffer16GetBackOr(PxBuffer16* self, pxiword index, pxu16 value);

/* PxBuffer16 dropping */

pxiword
pxBuffer16DropHead(PxBuffer16* self, pxiword amount);

pxiword
pxBuffer16DropTail(PxBuffer16* self, pxiword amount);

/* PxBuffer16 writing */

pxiword
pxBuffer16WriteHead(PxBuffer16* self, PxBuffer16* buffer);

pxiword
pxBuffer16WriteMemory16Head(PxBuffer16* self, pxu16* memory, pxiword length);

pxiword
pxBuffer16WriteString16Head(PxBuffer16* self, PxString16 string);

pxiword
pxBuffer16WriteTail(PxBuffer16* self, PxBuffer16* buffer);

pxiword
pxBuffer16WriteMemory16Tail(PxBuffer16* self, pxu16* memory, pxiword length);

pxiword
pxBuffer16WriteString16Tail(PxBuffer16* self, PxString16 string);

/* PxBuffer16 reading */

pxiword
pxBuffer16ReadHead(PxBuffer16* self, PxBuffer16* buffer);

pxiword
pxBuffer16ReadMemory16Head(PxBuffer16* self, pxu16* memory, pxiword length);

PxString16
pxBuffer16ReadString16Head(PxBuffer16* self, PxArena* arena, pxiword length);

pxiword
pxBuffer16ReadTail(PxBuffer16* self, PxBuffer16* buffer);

pxiword
pxBuffer16ReadMemory16Tail(PxBuffer16* self, pxu16* memory, pxiword length);

PxString16
pxBuffer16ReadString16Tail(PxBuffer16* self, PxArena* arena, pxiword length);

/* PxBuffer16 peeking */

pxiword
pxBuffer16PeekHead(PxBuffer16* self, PxBuffer16* buffer);

pxiword
pxBuffer16PeekMemory16Head(PxBuffer16* self, pxu16* memory, pxiword length);

PxString16
pxBuffer16PeekString16Head(PxBuffer16* self, PxArena* arena, pxiword length);

pxiword
pxBuffer16PeekTail(PxBuffer16* self, PxBuffer16* buffer);

pxiword
pxBuffer16PeekMemory16Tail(PxBuffer16* self, pxu16* memory, pxiword length);

PxString16
pxBuffer16PeekString16Tail(PxBuffer16* self, PxArena* arena, pxiword length);

#endif // PX_STREAM_BUFFER16_H
