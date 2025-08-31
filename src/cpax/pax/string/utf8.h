#ifndef PX_STRING_UTF8_H
#define PX_STRING_UTF8_H

#include "unicode.h"

#define PX_UTF8_MIN_UNITS pxCast(pxiword, 1)
#define PX_UTF8_MAX_UNITS pxCast(pxiword, 4)

typedef struct PxUtf8
{
    union
    {
        struct {
            pxu8 a, b, c, d;
        };

        pxu8 memory[PX_UTF8_MAX_UNITS];
    };

    pxiword size;
}
PxUtf8;

pxb8
pxUtf8Encode(PxUtf8* self, pxi32 value);

pxiword
pxUtf8WriteMemory8Forw(pxu8* memory, pxiword length, pxiword index, pxi32 value);

pxiword
pxUtf8WriteMemory8Back(pxu8* memory, pxiword length, pxiword index, pxi32 value);

pxb8
pxUtf8Decode(PxUtf8* self, pxi32* value);

pxiword
pxUtf8ReadMemory8Forw(pxu8* memory, pxiword length, pxiword index, pxi32* value);

pxiword
pxUtf8ReadMemory8Back(pxu8* memory, pxiword length, pxiword index, pxi32* value);

pxiword
pxUtf8UnitsToWrite(pxi32 value);

pxiword
pxUtf8UnitsToRead(pxu8 value);

pxb8
pxUtf8IsTrailing(pxu8 value);

pxb8
pxUtf8IsOverlong(pxi32 value, pxiword units);

#endif // PX_STRING_UTF8_H
