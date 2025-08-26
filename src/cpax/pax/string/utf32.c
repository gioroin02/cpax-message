#ifndef PX_STRING_UTF32_C
#define PX_STRING_UTF32_C

#include "utf32.h"

pxb8
pxUtf32Encode(PxUtf32* self, pxi32 value)
{
    pxiword units = pxUtf32UnitsToWrite(value);

    pxMemoryZero(self->memory, PX_UTF32_MAX_UNITS, 4);

    self->size = 0;

    switch (units) {
        case 1:
            self->a = pxCast(pxu32, value);
        break;

        default: return 0;
    }

    self->size = units;

    return 1;
}

pxiword
pxUtf32WriteMemoryForw(pxu32* memory, pxiword length, pxiword index, pxi32 value)
{
    PxUtf32 utf32 = {0};

    if (pxUtf32Encode(&utf32, value) == 0) return 0;

    if (index < 0 || index + utf32.size > length)
        return 0;

    for (pxiword i = 0; i < utf32.size; i += 1)
        memory[index + i] = utf32.memory[i];

    return utf32.size;
}

pxiword
pxUtf32WriteMemoryBack(pxu32* memory, pxiword length, pxiword index, pxi32 value)
{
    PxUtf32 utf32 = {0};

    if (pxUtf32Encode(&utf32, value) == 0) return 0;

    if (index - utf32.size < 0 || index >= length)
        return 0;

    for (pxiword i = 0; i < utf32.size; i += 1)
        memory[index - utf32.size + i] = utf32.memory[i];

    return utf32.size;
}

pxb8
pxUtf32Decode(PxUtf32* self, pxi32* value)
{
    pxiword units = pxUtf32UnitsToRead(self->memory[0]);
    pxi32   temp  = 0;

    if (self->size != units) return 0;

    switch (units) {
        case 1: temp = self->a; break;

        default: return 0;
    }

    if (pxUnicodeIsValid(temp) == 0) return 0;

    if (value != 0) *value = temp;

    return 1;
}

pxiword
pxUtf32ReadMemoryForw(pxu32* memory, pxiword length, pxiword index, pxi32* value)
{
    PxUtf32 utf32 = {0};

    if (index >= 0 && index < length)
        utf32.size = pxUtf32UnitsToRead(memory[index]);

    if (utf32.size <= 0 || index + utf32.size > length)
        return 0;

    for (pxiword i = 0; i < utf32.size; i += 1)
        utf32.memory[i] = memory[index + i];

    if (pxUtf32Decode(&utf32, value) == 0) return 0;

    return utf32.size;
}

pxiword
pxUtf32ReadMemoryBack(pxu32* memory, pxiword length, pxiword index, pxi32* value)
{
    PxUtf32 utf32 = {.size = 1};

    if (index < 0 || index >= length) return 0;

    if (utf32.size != pxUtf32UnitsToRead(memory[index]))
        return 0;

    for (pxiword i = 0; i < utf32.size; i += 1)
        utf32.memory[i] = memory[index + i];

    if (pxUtf32Decode(&utf32, value) == 0) return 0;

    return utf32.size;
}

pxiword
pxUtf32UnitsToWrite(pxi32 value)
{
    if (value >=    0x0 && value <=   0xd7ff) return 1;
    if (value >= 0xe000 && value <= 0x10ffff) return 1;

    return 0;
}

pxiword
pxUtf32UnitsToRead(pxu32 value)
{
    if (value >=    0x0 && value <=   0xd7ff) return 1;
    if (value >= 0xe000 && value <= 0x10ffff) return 1;

    return 0;
}

#endif // PX_STRING_UTF32_C
