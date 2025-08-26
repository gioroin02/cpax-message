#ifndef PX_JSON_READER_C
#define PX_JSON_READER_C

#include "reader.h"

PxJsonReader
pxJsonReaderMake(PxArena* arena, pxiword length, PxReader reader)
{
    PxQueue stack =
        pxQueueReserve(arena, PxJsonLayerType, length);

    if (stack.length <= 0) return (PxJsonReader) {0};

    return (PxJsonReader) {
        .reader = reader,
        .stack  = stack,
    };
}

PxJsonEvent
pxJsonReaderNext(PxJsonReader* self, PxArena* arena)
{
    PxJsonEvent     result = pxJsonEventCount();
    PxJsonLayerType parent = PX_JSON_LAYER_NONE;

    while (result.type == PX_JSON_EVENT_COUNT) {
        if (pxQueueReadTail(&self->stack, PxJsonLayerType, &parent) == 0)
            parent = PX_JSON_LAYER_NONE;

        PxJsonToken token = pxJsonNext(&self->reader, arena);

        if (token.type == PX_JSON_TOKEN_COUNT) break;

        switch (token.type) {
            case PX_JSON_TOKEN_ERROR: {
                result = pxJsonEventError(token.error.subject,
                    token.error.message);
            } break;

            case PX_JSON_TOKEN_OBJECT_OPEN: {
                result = pxJsonEventObjectOpen();

                PxJsonLayerType layer = PX_JSON_LAYER_OBJECT;

                pxQueueInsertTail(&self->stack, PxJsonLayerType,
                    &layer);

                self->name  = (PxString8) {0};
                self->colon = 0;
                self->comma = 0;
            } break;

            case PX_JSON_TOKEN_OBJECT_CLOSE: {
                result = pxJsonEventObjectClose();

                pxQueueDropTail(&self->stack);

                self->name  = (PxString8) {0};
                self->colon = 0;
                self->comma = 0;
            } break;

            case PX_JSON_TOKEN_ARRAY_OPEN: {
                result = pxJsonEventArrayOpen();

                PxJsonLayerType layer = PX_JSON_LAYER_ARRAY;

                pxQueueInsertTail(&self->stack, PxJsonLayerType,
                    &layer);

                self->name  = (PxString8) {0};
                self->colon = 0;
                self->comma = 0;
            } break;

            case PX_JSON_TOKEN_ARRAY_CLOSE: {
                result = pxJsonEventArrayClose();

                pxQueueDropTail(&self->stack);

                self->name  = (PxString8) {0};
                self->colon = 0;
                self->comma = 0;
            } break;

            case PX_JSON_TOKEN_COLON: {
                if (parent == PX_JSON_LAYER_OBJECT) {
                    token = pxJsonPeek(&self->reader, arena);

                    switch (token.type) {
                        case PX_JSON_TOKEN_OBJECT_OPEN:
                        case PX_JSON_TOKEN_ARRAY_OPEN:
                            result = pxJsonEventName(self->name);
                        break;

                        default: break;
                    }
                }

                self->colon = 1;
                self->comma = 0;
            } break;

            case PX_JSON_TOKEN_COMMA: {
                self->name  = (PxString8) {0};
                self->colon = 0;
                self->comma = 1;
            } break;

            case PX_JSON_TOKEN_STRING: {
                if (parent != PX_JSON_LAYER_OBJECT || self->colon != 0)
                    result = pxJsonEventString(token.svalue, self->name);
                else
                    self->name = token.svalue;

                self->colon = 0;
                self->comma = 0;
            } break;

            case PX_JSON_TOKEN_UNSIGNED: {
                result =
                    pxJsonEventUnsigned(token.uvalue, self->name);

                self->colon = 0;
                self->comma = 0;
            } break;

            case PX_JSON_TOKEN_INTEGER: {
                result =
                    pxJsonEventInteger(token.ivalue, self->name);

                self->colon = 0;
                self->comma = 0;
            } break;

            case PX_JSON_TOKEN_FLOATING: {
                result =
                    pxJsonEventFloating(token.fvalue, self->name);

                self->colon = 0;
                self->comma = 0;
            } break;

            case PX_JSON_TOKEN_BOOLEAN: {
                result =
                    pxJsonEventBoolean(token.bvalue, self->name);

                self->colon = 0;
                self->comma = 0;
            } break;

            case PX_JSON_TOKEN_NULL: {
                result = pxJsonEventNull(self->name);

                self->colon = 0;
                self->comma = 0;
            } break;

            default: break;
        }
    }

    return result;
}

#endif // PX_JSON_READER_C
