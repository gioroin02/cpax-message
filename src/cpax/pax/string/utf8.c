#ifndef PX_STRING_UTF8_C
#define PX_STRING_UTF8_C

#include "utf8.h"

pxb8
pxUtf8Encode(PxUtf8* self, pxi32 value)
{
    pxiword units = pxUtf8UnitsToWrite(value);

    pxMemoryZero(self->memory, PX_UTF8_MAX_UNITS, 1);

    self->size = 0;

    switch (units) {
        case 1: self->a = pxCast(pxu8, value); break;

        case 2:
            self->a = pxCast(pxu8, ((value >> 6) & 0xff) | 0xc0);
            self->b = pxCast(pxu8, ((value >> 0) & 0x3f) | 0x80);
        break;

        case 3:
            self->a = pxCast(pxu8, ((value >> 12) & 0xff) | 0xe0);
            self->b = pxCast(pxu8, ((value >>  6) & 0x3f) | 0x80);
            self->c = pxCast(pxu8, ((value >>  0) & 0x3f) | 0x80);
        break;

        case 4:
            self->a = pxCast(pxu8, ((value >> 18) & 0xff) | 0xf0);
            self->b = pxCast(pxu8, ((value >> 12) & 0x3f) | 0x80);
            self->c = pxCast(pxu8, ((value >>  6) & 0x3f) | 0x80);
            self->d = pxCast(pxu8, ((value >>  0) & 0x3f) | 0x80);
        break;

        default: return 0;
    }

    self->size = units;

    return 1;
}

pxiword
pxUtf8WriteMemoryForw(pxu8* memory, pxiword length, pxiword index, pxi32 value)
{
    PxUtf8 utf8 = {0};

    if (pxUtf8Encode(&utf8, value) == 0) return 0;

    if (index < 0 || index + utf8.size > length)
        return 0;

    for (pxiword i = 0; i < utf8.size; i += 1)
        memory[index + i] = utf8.memory[i];

    return utf8.size;
}

pxiword
pxUtf8WriteMemoryBack(pxu8* memory, pxiword length, pxiword index, pxi32 value)
{
    PxUtf8 utf8 = {0};

    if (pxUtf8Encode(&utf8, value) == 0) return 0;

    if (index - utf8.size < 0 || index >= length)
        return 0;

    for (pxiword i = 0; i < utf8.size; i += 1)
        memory[index - utf8.size + i] = utf8.memory[i];

    return utf8.size;
}

pxb8
pxUtf8Decode(PxUtf8* self, pxi32* value)
{
    pxiword units = pxUtf8UnitsToRead(self->memory[0]);
    pxi32   temp  = 0;

    if (self->size != units) return 0;

    switch (units) {
        case 1: temp = self->a; break;

        case 2:
            if (pxUtf8IsTrailing(self->b) == 0) return 0;

            temp  = (self->a & 0x1f) << 6;
            temp += (self->b & 0x3f) << 0;
        break;

        case 3:
            if (pxUtf8IsTrailing(self->b) == 0) return 0;
            if (pxUtf8IsTrailing(self->c) == 0) return 0;

            temp  = (self->a & 0x0f) << 12;
            temp += (self->b & 0x3f) << 6;
            temp += (self->c & 0x3f) << 0;
        break;

        case 4:
            if (pxUtf8IsTrailing(self->b) == 0) return 0;
            if (pxUtf8IsTrailing(self->c) == 0) return 0;
            if (pxUtf8IsTrailing(self->d) == 0) return 0;

            temp  = (self->a & 0x07) << 18;
            temp += (self->b & 0x3f) << 12;
            temp += (self->c & 0x3f) << 6;
            temp += (self->d & 0x3f) << 0;
        break;

        default: return 0;
    }

    if (pxUtf8IsOverlong(temp, units) != 0)
        return 0;

    if (pxUnicodeIsValid(temp) == 0) return 0;

    if (value != 0) *value = temp;

    return 1;
}

pxiword
pxUtf8ReadMemoryForw(pxu8* memory, pxiword length, pxiword index, pxi32* value)
{
    PxUtf8 utf8 = {0};

    if (index >= 0 && index < length)
        utf8.size = pxUtf8UnitsToRead(memory[index]);

    if (utf8.size <= 0 || index + utf8.size > length)
        return 0;

    for (pxiword i = 0; i < utf8.size; i += 1)
        utf8.memory[i] = memory[index + i];

    if (pxUtf8Decode(&utf8, value) == 0) return 0;

    return utf8.size;
}

pxiword
pxUtf8ReadMemoryBack(pxu8* memory, pxiword length, pxiword index, pxi32* value)
{
    PxUtf8  utf8  = {0};
    pxiword start = index;

    if (index < 0 || index >= length) return 0;

    while (pxUtf8IsTrailing(memory[index]) != 0) {
        index -= 1;

        if (index < 0 || index >= length)
            return 0;
    }

    utf8.size = start - index + 1;

    if (utf8.size != pxUtf8UnitsToRead(memory[index]))
        return 0;

    for (pxiword i = 0; i < utf8.size; i += 1)
        utf8.memory[i] = memory[index + i];

    if (pxUtf8Decode(&utf8, value) == 0) return 0;

    return utf8.size;
}

pxiword
pxUtf8UnitsToWrite(pxi32 value)
{
    if (value >=     0x0 && value <=     0x7f) return 1;
    if (value >=    0x80 && value <=    0x7ff) return 2;
    if (value >=   0x800 && value <=   0xd7ff) return 3;
    if (value >=  0xe000 && value <=   0xffff) return 3;
    if (value >= 0x10000 && value <= 0x10ffff) return 4;

    return 0;
}

pxiword
pxUtf8UnitsToRead(pxu8 value)
{
    if (value >=  0x0 && value <= 0x7f) return 1;
    if (value >= 0xc0 && value <= 0xdf) return 2;
    if (value >= 0xe0 && value <= 0xef) return 3;
    if (value >= 0xf0 && value <= 0xf7) return 4;

    return 0;
}

pxb8
pxUtf8IsTrailing(pxu8 value)
{
    return (value & 0xc0) == 0x80 ? 1 : 0;
}

pxb8
pxUtf8IsOverlong(pxi32 value, pxiword units)
{
    if (value >=     0xc080 && value <=     0xc1ff && units == 2) return 1;
    if (value >=   0xe08080 && value <=   0xe09fff && units == 3) return 1;
    if (value >= 0xf0808080 && value <= 0xf0bfffff && units == 4) return 1;

    return 0;
}

#endif // PX_STRING_UTF8_C
