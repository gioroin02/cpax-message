#ifndef PX_STRING_UTF32_H
#define PX_STRING_UTF32_H

#include "unicode.h"

#define PX_UTF32_MIN_UNITS pxCast(pxiword, 1)
#define PX_UTF32_MAX_UNITS pxCast(pxiword, 1)

typedef struct PxUtf32
{
    union
    {
        struct {
            pxu32 a;
        };

        pxu32 memory[PX_UTF32_MAX_UNITS];
    };

    pxiword size;
}
PxUtf32;

pxb8
pxUtf32Encode(PxUtf32* self, pxi32 value);

pxiword
pxUtf32WriteMemoryForw(pxu32* memory, pxiword length, pxiword index, pxi32 value);

pxiword
pxUtf32WriteMemoryBack(pxu32* memory, pxiword length, pxiword index, pxi32 value);

pxb8
pxUtf32Decode(PxUtf32* self, pxi32* value);

pxiword
pxUtf32ReadMemoryForw(pxu32* memory, pxiword length, pxiword index, pxi32* value);

pxiword
pxUtf32ReadMemoryBack(pxu32* memory, pxiword length, pxiword index, pxi32* value);

pxiword
pxUtf32UnitsToWrite(pxi32 value);

pxiword
pxUtf32UnitsToRead(pxu32 value);

#endif // PX_STRING_UTF32_H
