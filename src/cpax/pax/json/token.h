#ifndef PX_JSON_TOKEN_H
#define PX_JSON_TOKEN_H

#include "import.h"

typedef enum PxJsonTokenType
{
    PX_JSON_TOKEN_NONE,

    PX_JSON_TOKEN_ERROR,

    PX_JSON_TOKEN_OBJECT_OPEN,
    PX_JSON_TOKEN_OBJECT_CLOSE,
    PX_JSON_TOKEN_ARRAY_OPEN,
    PX_JSON_TOKEN_ARRAY_CLOSE,
    PX_JSON_TOKEN_COLON,
    PX_JSON_TOKEN_COMMA,

    PX_JSON_TOKEN_STRING,
    PX_JSON_TOKEN_UNSIGNED,
    PX_JSON_TOKEN_INTEGER,
    PX_JSON_TOKEN_FLOATING,
    PX_JSON_TOKEN_BOOLEAN,
    PX_JSON_TOKEN_NULL,

    PX_JSON_TOKEN_COUNT,
}
PxJsonTokenType;

typedef struct PxJsonTokenError
{
    PxString8 message;
    PxString8 subject;
}
PxJsonTokenError;

typedef struct PxJsonToken
{
    PxJsonTokenType type;
    pxiword         length;

    union
    {
        PxJsonTokenError error;

        PxString8 svalue;
        pxuword   uvalue;
        pxiword   ivalue;
        pxfword   fvalue;
        pxbword   bvalue;
    };
}
PxJsonToken;

PxJsonToken
pxJsonTokenNone();

PxJsonToken
pxJsonTokenError(PxString8 subject, PxString8 message);

PxJsonToken
pxJsonTokenObjectOpen();

PxJsonToken
pxJsonTokenObjectClose();

PxJsonToken
pxJsonTokenArrayOpen();

PxJsonToken
pxJsonTokenArrayClose();

PxJsonToken
pxJsonTokenColon();

PxJsonToken
pxJsonTokenComma();

PxJsonToken
pxJsonTokenString(PxString8 string);

PxJsonToken
pxJsonTokenUnsigned(PxString8 string);

PxJsonToken
pxJsonTokenInteger(PxString8 string);

PxJsonToken
pxJsonTokenFloating(PxString8 string);

PxJsonToken
pxJsonTokenBoolean(PxString8 string, pxbword value);

PxJsonToken
pxJsonTokenNull(PxString8 string);

PxJsonToken
pxJsonTokenCount();

PxJsonToken
pxJsonPeek(PxReader* reader, PxArena* arena);

PxJsonToken
pxJsonPeekSymbol(PxReader* reader, PxArena* arena);

PxJsonToken
pxJsonPeekString(PxReader* reader, PxArena* arena);

PxJsonToken
pxJsonPeekNumber(PxReader* reader, PxArena* arena);

PxJsonToken
pxJsonPeekWord(PxReader* reader, PxArena* arena);

PxJsonToken
pxJsonNext(PxReader* reader, PxArena* arena);

pxu8
pxJsonSkipSpaces(PxReader* reader);

#endif // PX_JSON_TOKEN_H
