#ifndef PX_STREAM_READER_C
#define PX_STREAM_READER_C

#include "reader.h"

PxReader
pxBufferReader(PxBuffer8* self, PxBuffer8* buffer)
{
    if (self == 0 || buffer == 0)
        return (PxReader) {0};

    return (PxReader) {
        .buffer = buffer,
        .ctxt   = self,
        .proc   = &pxBuffer8ReadHead,
    };
}

PxBuffer8*
pxReaderSetBuffer(PxReader* self, PxBuffer8* buffer)
{
    PxBuffer8* result = self->buffer;

    if (buffer != 0)
        self->buffer = buffer;
    else
        return 0;

    return result;
}

pxiword
pxReaderFill(PxReader* self)
{
    PxReaderProc* proc = pxCast(PxReaderProc*, self->proc);

    if (proc != 0)
        return proc(self->ctxt, self->buffer);

    return 0;
}

pxu8
pxReaderSkip(PxReader* self, pxiword offset)
{
    if (offset < 0) return 0;

    for (pxiword i = 0; i < offset;) {
        i += pxBuffer8DropHead(self->buffer, offset - i);

        if (i < offset) {
            if (pxReaderFill(self) == 0)
                return 0;
        } else
            break;
    }

    return pxBuffer8GetForwOr(self->buffer, 0, 0);
}

pxu8
pxReaderPeek(PxReader* self, pxiword offset)
{
    if (offset < 0 || offset >= self->buffer->length)
        return 0;

    if (offset >= self->buffer->size) {
        pxiword length = offset - self->buffer->size + 1;
        pxiword amount = 0;

        for (pxiword i = 0; i < length;) {
            amount = pxReaderFill(self);

            if (amount != 0)
                i += amount;
            else
                return 0;
        }
    }

    return pxBuffer8GetForwOr(self->buffer, offset, 0);
}

PxString8
pxReaderPeekString(PxReader* self, PxArena* arena, pxiword length)
{
    if (length <= 0) return (PxString8) {0};

    pxiword offset = pxArenaOffset(arena);
    pxu8*   result = pxArenaReserve(arena, pxu8, length + 1);
    pxiword diff   = 0;
    pxu8    byte   = pxReaderPeek(self, 0);

    while (byte != 0 && diff < length) {
        result[diff] = byte;

        diff += 1;
        byte  = pxReaderPeek(self, diff);
    }

    if (diff < length)
        pxArenaRewind(arena, offset + diff + 1);

    return (PxString8) {
        .memory = result, .length = diff,
    };
}

PxString8
pxReaderPeekLine(PxReader* self, PxArena* arena, pxiword length)
{
    if (length <= 0) return (PxString8) {0};

    pxiword offset = pxArenaOffset(arena);
    pxu8*   result = pxArenaReserve(arena, pxu8, length + 1);
    pxiword diff   = 0;
    pxu8    byte   = pxReaderPeek(self, 0);

    while (byte != 0 && byte != 10 && diff < length) {
        result[diff] = byte;

        diff += 1;
        byte  = pxReaderPeek(self, diff);
    }

    if (diff < length)
        pxArenaRewind(arena, offset + diff + 1);

    return (PxString8) {
        .memory = result, .length = diff,
    };
}

PxString8
pxReaderString(PxReader* self, PxArena* arena, pxiword length)
{
    if (length <= 0) return (PxString8) {0};

    pxiword offset = pxArenaOffset(arena);
    pxu8*   result = pxArenaReserve(arena, pxu8, length + 1);
    pxiword diff   = 0;
    pxu8    byte   = pxReaderPeek(self, 0);

    while (byte != 0 && diff < length) {
        result[diff] = byte;

        diff += 1;
        byte  = pxReaderSkip(self, 1);
    }

    if (diff < length)
        pxArenaRewind(arena, offset + diff + 1);

    return (PxString8) {
        .memory = result, .length = diff,
    };
}

PxString8
pxReaderLine(PxReader* self, PxArena* arena, pxiword length)
{
    if (length <= 0) return (PxString8) {0};

    pxiword offset = pxArenaOffset(arena);
    pxu8*   result = pxArenaReserve(arena, pxu8, length + 1);
    pxiword diff   = 0;
    pxu8    byte   = pxReaderPeek(self, 0);

    while (byte != 0 && byte != 10 && diff < length) {
        result[diff] = byte;

        diff += 1;
        byte  = pxReaderSkip(self, 1);
    }

    byte = pxReaderSkip(self, 1);

    if (diff < length)
        pxArenaRewind(arena, offset + diff + 1);

    return (PxString8) {
        .memory = result, .length = diff,
    };
}

#endif // PX_STREAM_READER_C
