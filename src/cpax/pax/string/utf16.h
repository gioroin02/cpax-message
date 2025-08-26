#ifndef PX_STRING_UTF16_H
#define PX_STRING_UTF16_H

#include "unicode.h"

#define PX_UTF16_MIN_UNITS pxCast(pxiword, 1)
#define PX_UTF16_MAX_UNITS pxCast(pxiword, 2)

typedef struct PxUtf16
{
    union
    {
        struct {
            pxu16 a, b;
        };

        pxu16 memory[PX_UTF16_MAX_UNITS];
    };

    pxiword size;
}
PxUtf16;

pxb8
pxUtf16Encode(PxUtf16* self, pxi32 value);

pxiword
pxUtf16WriteMemoryForw(pxu16* memory, pxiword length, pxiword index, pxi32 value);

pxiword
pxUtf16WriteMemoryBack(pxu16* memory, pxiword length, pxiword index, pxi32 value);

pxb8
pxUtf16Decode(PxUtf16* self, pxi32* value);

pxiword
pxUtf16ReadMemoryForw(pxu16* memory, pxiword length, pxiword index, pxi32* value);

pxiword
pxUtf16ReadMemoryBack(pxu16* memory, pxiword length, pxiword index, pxi32* value);

pxiword
pxUtf16UnitsToWrite(pxi32 value);

pxiword
pxUtf16UnitsToRead(pxu16 value);

#endif // PX_STRING_UTF16_H
