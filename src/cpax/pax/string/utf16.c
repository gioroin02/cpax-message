#ifndef PX_STRING_UTF16_C
#define PX_STRING_UTF16_C

#include "utf16.h"

pxb8
pxUtf16Encode(PxUtf16* self, pxi32 value)
{
    pxiword units = pxUtf16UnitsToWrite(value);

    pxMemoryZero(self->memory, PX_UTF16_MAX_UNITS, 2);

    self->size = 0;

    switch (units) {
        case 1: self->a = pxCast(pxu16, value); break;

        case 2:
            self->a = pxCast(pxu16, (((value - 0x10000) >> 10) & 0xffff) | 0xd800);
            self->b = pxCast(pxu16, (((value - 0x10000) >>  0) & 0x03ff) | 0xdc00);
        break;

        default: return 0;
    }

    self->size = units;

    return 1;
}

pxiword
pxUtf16WriteMemoryForw(pxu16* memory, pxiword length, pxiword index, pxi32 value)
{
    PxUtf16 utf16 = {0};

    if (pxUtf16Encode(&utf16, value) == 0) return 0;

    if (index < 0 || index + utf16.size > length)
        return 0;

    for (pxiword i = 0; i < utf16.size; i += 1)
        memory[index + i] = utf16.memory[i];

    return utf16.size;
}

pxiword
pxUtf16WriteMemoryBack(pxu16* memory, pxiword length, pxiword index, pxi32 value)
{
    PxUtf16 utf16 = {0};

    if (pxUtf16Encode(&utf16, value) == 0) return 0;

    if (index - utf16.size < 0 || index >= length)
        return 0;

    for (pxiword i = 0; i < utf16.size; i += 1)
        memory[index - utf16.size + i] = utf16.memory[i];

    return utf16.size;
}

pxb8
pxUtf16Decode(PxUtf16* self, pxi32* value)
{
    pxiword units = pxUtf16UnitsToRead(self->memory[0]);
    pxi32   temp  = 0;

    if (self->size != units) return 0;

    switch (units) {
        case 1: temp = self->a; break;

        case 2:
            if (pxUnicodeIsSurrogateHigh(self->b) == 0)
                return 0;

            temp += (self->a - 0xd800) << 10;
            temp += (self->b - 0xdc00) <<  0;
            temp += 0x10000;
        break;

        default: return 0;
    }

    if (pxUnicodeIsValid(temp) == 0) return 0;

    if (value != 0) *value = temp;

    return 1;
}

pxiword
pxUtf16ReadMemoryForw(pxu16* memory, pxiword length, pxiword index, pxi32* value)
{
    PxUtf16 utf16 = {0};

    if (index >= 0 && index < length)
        utf16.size = pxUtf16UnitsToRead(memory[index]);

    if (utf16.size <= 0 || index + utf16.size > length)
        return 0;

    for (pxiword i = 0; i < utf16.size; i += 1)
        utf16.memory[i] = memory[index + i];

    if (pxUtf16Decode(&utf16, value) == 0) return 0;

    return utf16.size;
}

pxiword
pxUtf16ReadMemoryBack(pxu16* memory, pxiword length, pxiword index, pxi32* value)
{
    PxUtf16 utf16 = {0};
    pxiword start = index;

    if (index < 0 || index >= length) return 0;

    while (pxUnicodeIsSurrogateLow(memory[index]) != 0) {
        index -= 1;

        if (index < 0 || index >= length)
            return 0;
    }

    utf16.size = start - index + 1;

    if (utf16.size != pxUtf16UnitsToRead(memory[index]))
        return 0;

    for (pxiword i = 0; i < utf16.size; i += 1)
        utf16.memory[i] = memory[index + i];

    if (pxUtf16Decode(&utf16, value) == 0) return 0;

    return utf16.size;
}

pxiword
pxUtf16UnitsToWrite(pxi32 value)
{
    if (value >=     0x0 && value <=   0xd7ff) return 1;
    if (value >=  0xe000 && value <=   0xffff) return 1;
    if (value >= 0x10000 && value <= 0x10ffff) return 2;

    return 0;
}

pxiword
pxUtf16UnitsToRead(pxu16 value)
{
    if (value >=    0x0 && value <= 0xd7ff) return 1;
    if (value >= 0xd800 && value <= 0xdbff) return 2;
    if (value >= 0xe000 && value <= 0xffff) return 1;

    return 0;
}

#endif // PX_STRING_UTF16_C
