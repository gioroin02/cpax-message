#ifndef PX_JSON_READER_H
#define PX_JSON_READER_H

#include "token.h"
#include "event.h"

typedef struct PxJsonReader
{
    PxReader reader;
    PxQueue  stack;

    PxString8 name;

    pxb8 colon;
    pxb8 comma;
}
PxJsonReader;

PxJsonReader
pxJsonReaderMake(PxArena* arena, pxiword length, PxReader reader);

PxJsonEvent
pxJsonReaderNext(PxJsonReader* self, PxArena* arena);

#endif // PX_JSON_READER_H
