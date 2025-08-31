#ifndef PX_STREAM_READER_H
#define PX_STREAM_READER_H

#include "buffer8.h"

typedef pxiword (PxReaderProc) (void*, PxBuffer8*);

typedef struct PxReader
{
    PxBuffer8* buffer;

    void* ctxt;
    void* proc;
}
PxReader;

PxReader
pxBufferReader(PxBuffer8* self, PxBuffer8* buffer);

PxBuffer8*
pxReaderSetBuffer(PxReader* self, PxBuffer8* buffer);

pxiword
pxReaderFill(PxReader* self);

pxu8
pxReaderSkip(PxReader* self, pxiword offset);

pxu8
pxReaderPeek(PxReader* self, pxiword offset);

PxString8
pxReaderPeekString8(PxReader* self, PxArena* arena, pxiword length);

PxString8
pxReaderPeekLine(PxReader* self, PxArena* arena, pxiword length);

PxString8
pxReaderString8(PxReader* self, PxArena* arena, pxiword length);

PxString8
pxReaderLine(PxReader* self, PxArena* arena, pxiword length);

#endif // PX_STREAM_READER_H
