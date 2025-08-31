#ifndef PX_STREAM_WRITER_C
#define PX_STREAM_WRITER_C

#include "writer.h"

PxWriter
pxBufferWriter(PxBuffer8* self, PxBuffer8* buffer)
{
    if (self == 0 || buffer == 0)
        return (PxWriter) {0};

    return (PxWriter) {
        .buffer = buffer,
        .ctxt   = self,
        .proc   = &pxBuffer8WriteTail,
    };
}

PxBuffer8*
pxWriterSetBuffer(PxWriter* self, PxBuffer8* buffer)
{
    PxBuffer8* result = self->buffer;

    if (buffer != 0)
        self->buffer = buffer;
    else
        return 0;

    return result;
}

pxiword
pxWriterFlush(PxWriter* self)
{
    PxWriterProc* proc = pxCast(PxWriterProc*, self->proc);

    if (proc != 0)
        return proc(self->ctxt, self->buffer);

    return 0;
}

pxiword
pxWriterByte(PxWriter* self, pxu8 value)
{
    if (self->buffer->size + 1 > self->buffer->length)
        pxWriterFlush(self);

    return pxBuffer8WriteMemory8Tail(self->buffer, &value, 1);
}

pxiword
pxWriterString8(PxWriter* self, PxString8 value)
{
    for (pxiword i = 0; i < value.length;) {
        i += pxBuffer8WriteMemory8Tail(self->buffer,
            value.memory + i, value.length - i);

        pxWriterFlush(self);
    }

    return value.length;
}

#endif // PX_STREAM_WRITER_C
