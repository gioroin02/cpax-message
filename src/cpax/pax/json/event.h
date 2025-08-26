#ifndef PX_JSON_EVENT_H
#define PX_JSON_EVENT_H

#include "import.h"

typedef enum PxJsonLayerType
{
    PX_JSON_LAYER_NONE,
    PX_JSON_LAYER_OBJECT,
    PX_JSON_LAYER_ARRAY,
}
PxJsonLayerType;

typedef enum PxJsonEventType
{
    PX_JSON_EVENT_NONE,

    PX_JSON_EVENT_ERROR,

    PX_JSON_EVENT_OBJECT_OPEN,
    PX_JSON_EVENT_OBJECT_CLOSE,
    PX_JSON_EVENT_ARRAY_OPEN,
    PX_JSON_EVENT_ARRAY_CLOSE,

    PX_JSON_EVENT_NAME,

    PX_JSON_EVENT_STRING,
    PX_JSON_EVENT_UNSIGNED,
    PX_JSON_EVENT_INTEGER,
    PX_JSON_EVENT_FLOATING,
    PX_JSON_EVENT_BOOLEAN,
    PX_JSON_EVENT_NULL,

    PX_JSON_EVENT_COUNT,
}
PxJsonEventType;

typedef struct PxJsonEventError
{
    PxString8 message;
    PxString8 subject;
}
PxJsonEventError;

typedef struct PxJsonEvent
{
    PxJsonEventType type;
    PxString8       name;

    union
    {
        PxJsonEventError error;

        PxString8 svalue;
        pxuword   uvalue;
        pxiword   ivalue;
        pxfword   fvalue;
        pxbword   bvalue;
    };
}
PxJsonEvent;

PxJsonEvent
pxJsonEventNone();

PxJsonEvent
pxJsonEventError(PxString8 subject, PxString8 message);

PxJsonEvent
pxJsonEventObjectOpen();

PxJsonEvent
pxJsonEventObjectClose();

PxJsonEvent
pxJsonEventArrayOpen();

PxJsonEvent
pxJsonEventArrayClose();

PxJsonEvent
pxJsonEventName(PxString8 name);

PxJsonEvent
pxJsonEventString(PxString8 value, PxString8 name);

PxJsonEvent
pxJsonEventUnsigned(pxuword value, PxString8 name);

PxJsonEvent
pxJsonEventInteger(pxiword value, PxString8 name);

PxJsonEvent
pxJsonEventFloating(pxfword value, PxString8 name);

PxJsonEvent
pxJsonEventBoolean(pxbword value, PxString8 name);

PxJsonEvent
pxJsonEventNull(PxString8 name);

PxJsonEvent
pxJsonEventCount();

#endif // PX_JSON_EVENT_H
