#ifndef PX_JSON_WRITER_C
#define PX_JSON_WRITER_C

#include "writer.h"

PxJsonWriter
pxJsonWriterMake(PxArena* arena, pxiword length, PxWriter writer)
{
    PxQueue stack =
        pxQueueReserve(arena, PxJsonLayerType, length);

    if (stack.length <= 0) return (PxJsonWriter) {0};

    return (PxJsonWriter) {
        .writer = writer,
        .stack  = stack,
    };
}

pxb8
pxJsonWriterNext(PxJsonWriter* self, PxArena* arena, PxJsonEvent event)
{
    PxJsonLayerType parent = PX_JSON_LAYER_NONE;

    pxQueueReadTail(&self->stack, PxJsonLayerType, &parent);

    switch (event.type) {
        case PX_JSON_EVENT_OBJECT_OPEN: {
            pxWriterByte(&self->writer, PX_ASCII_BRACE_LEFT);

            PxJsonLayerType layer = PX_JSON_LAYER_OBJECT;

            pxQueueInsertTail(&self->stack, PxJsonLayerType,
                &layer);

            self->comma = 0;
        } break;

        case PX_JSON_EVENT_OBJECT_CLOSE: {
            pxWriterByte(&self->writer,
                PX_ASCII_BRACE_RIGHT);

            pxQueueDropTail(&self->stack);

            self->comma = 1;
        } break;

        case PX_JSON_EVENT_ARRAY_OPEN: {
            pxWriterByte(&self->writer, PX_ASCII_SQUARE_LEFT);

            PxJsonLayerType layer = PX_JSON_LAYER_ARRAY;

            pxQueueInsertTail(&self->stack, PxJsonLayerType,
                &layer);

            self->comma = 0;
        } break;

        case PX_JSON_EVENT_ARRAY_CLOSE: {
            pxWriterByte(&self->writer,
                PX_ASCII_SQUARE_RIGHT);

            pxQueueDropTail(&self->stack);

            self->comma = 1;
        } break;

        case PX_JSON_EVENT_NAME: {
            if (parent != PX_JSON_LAYER_OBJECT) return 0;

            if (self->comma != 0)
                pxWriterByte(&self->writer, PX_ASCII_COMMA);

            pxWriterByte(&self->writer, PX_ASCII_QUOTE);
            pxWriterString(&self->writer, event.name);
            pxWriterByte(&self->writer, PX_ASCII_QUOTE);
            pxWriterByte(&self->writer, PX_ASCII_COLON);
        } break;

        case PX_JSON_EVENT_STRING: {
            if (self->comma != 0)
                pxWriterByte(&self->writer, PX_ASCII_COMMA);

            if (parent == PX_JSON_LAYER_OBJECT) {
                if (event.name.length <= 0) return 0;

                pxWriterByte(&self->writer, PX_ASCII_QUOTE);
                pxWriterString(&self->writer, event.name);
                pxWriterByte(&self->writer, PX_ASCII_QUOTE);
                pxWriterByte(&self->writer, PX_ASCII_COLON);
            }

            pxWriterByte(&self->writer, PX_ASCII_QUOTE);
            pxWriterString(&self->writer, event.svalue);
            pxWriterByte(&self->writer, PX_ASCII_QUOTE);

            self->comma = 1;
        } break;

        case PX_JSON_EVENT_UNSIGNED: {
            if (self->comma != 0)
                pxWriterByte(&self->writer, PX_ASCII_COMMA);

            if (parent == PX_JSON_LAYER_OBJECT) {
                if (event.name.length <= 0) return 0;

                pxWriterByte(&self->writer, PX_ASCII_QUOTE);
                pxWriterString(&self->writer, event.name);
                pxWriterByte(&self->writer, PX_ASCII_QUOTE);
                pxWriterByte(&self->writer, PX_ASCII_COLON);
            }

            PxString8 string = pxString8FromUWord(arena,
                pxFormatOptionsRadix(10), event.uvalue);

            pxWriterString(&self->writer, string);

            self->comma = 1;
        } break;

        case PX_JSON_EVENT_INTEGER: {
            if (self->comma != 0)
                pxWriterByte(&self->writer, PX_ASCII_COMMA);

            if (parent == PX_JSON_LAYER_OBJECT) {
                if (event.name.length <= 0) return 0;

                pxWriterByte(&self->writer, PX_ASCII_QUOTE);
                pxWriterString(&self->writer, event.name);
                pxWriterByte(&self->writer, PX_ASCII_QUOTE);
                pxWriterByte(&self->writer, PX_ASCII_COLON);
            }

            PxString8 string = pxString8FromIWord(arena,
                pxFormatOptionsRadix(10), event.ivalue);

            pxWriterString(&self->writer, string);

            self->comma = 1;
        } break;

        case PX_JSON_EVENT_FLOATING: {
            return 0;
        } break;

        case PX_JSON_EVENT_BOOLEAN: {
            if (self->comma != 0)
                pxWriterByte(&self->writer, PX_ASCII_COMMA);

            if (parent == PX_JSON_LAYER_OBJECT) {
                if (event.name.length <= 0) return 0;

                pxWriterByte(&self->writer, PX_ASCII_QUOTE);
                pxWriterString(&self->writer, event.name);
                pxWriterByte(&self->writer, PX_ASCII_QUOTE);
                pxWriterByte(&self->writer, PX_ASCII_COLON);
            }

            if (event.bvalue != 0)
                pxWriterString(&self->writer, pxs8("true"));
            else
                pxWriterString(&self->writer, pxs8("false"));

            self->comma = 1;
        } break;

        case PX_JSON_EVENT_NULL: {
            if (self->comma != 0)
                pxWriterByte(&self->writer, PX_ASCII_COMMA);

            if (parent == PX_JSON_LAYER_OBJECT) {
                if (event.name.length <= 0) return 0;

                pxWriterByte(&self->writer, PX_ASCII_QUOTE);
                pxWriterString(&self->writer, event.name);
                pxWriterByte(&self->writer, PX_ASCII_QUOTE);
                pxWriterByte(&self->writer, PX_ASCII_COLON);
            }

            pxWriterString(&self->writer, pxs8("null"));

            self->comma = 1;
        } break;

        default: return 0;
    }

    pxWriterFlush(&self->writer);

    return 1;
}

#endif // PX_JSON_WRITER_C
