#ifndef PAX_STRING_UTF16_CPP
#define PAX_STRING_UTF16_CPP

#include "utf16.hpp"

namespace pax {

b32
utf16_encode(UTF16* self, u32 value)
{
    uptr units = utf16_units_to_write(value);

    self->a    = 0;
    self->b    = 0;
    self->size = 0;

    switch (units) {
        case 1: { self->a = pax_cast(u16, value); } break;

        case 2: {
            u32 temp = value - 0x10000;

            self->a = pax_cast(u16, ((temp >> 10) & 0xffff) | 0xd800);
            self->b = pax_cast(u16, ( temp        & 0x03ff) | 0xdc00);
        } break;

        default: return 0;
    }

    self->size = units;

    return 1;
}

uptr
utf16_encode_forw(u16* memory, uptr length, uptr index, u32 value)
{
    UTF16 utf16 = {};

    if (utf16_encode(&utf16, value) == 0) return 0;

    if (index < 0 || index + utf16.size > length)
        return 0;

    for (uptr i = 0; i < utf16.size; i += 1)
        memory[index + i] = utf16.memory[i];

    return utf16.size;
}

uptr
utf16_encode_forw_circ(u16* memory, uptr length, uptr index, u32 value)
{
    UTF16 utf16 = {};

    if (utf16_encode(&utf16, value) == 0) return 0;

    if (index < 0 || index > length | utf16.size > length)
        return 0;

    for (uptr i = 0; i < utf16.size; i += 1)
        memory[(index + i) % length] = utf16.memory[i];

    return utf16.size;
}

b32
utf16_decode(UTF16* self, u32* value)
{
    uptr units = utf16_units_to_read(self->a);
    u32  temp  = 0;

    if (self->size != units) return 0;

    switch (units) {
        case 1: { temp = self->a; } break;

        case 2: {
            if (unicode_is_surrogate_high(self->a) == 0)
                return 0;

            temp  = 0x10000;
            temp += (self->a - 0xd800) << 10;
            temp += (self->b - 0xdc00);
        } break;

        default: return 0;
    }

    if (unicode_is_codepoint(temp) == 0) return 0;
    if (unicode_is_surrogate(temp) != 0) return 0;

    if (value != 0) *value = temp;

    return 1;
}

uptr
utf16_decode_forw(u16* memory, uptr length, uptr index, u32* value)
{
    UTF16 utf16 = {};

    if (index >= 0 && index < length)
        utf16.size = utf16_units_to_read(memory[index]);

    if (utf16.size <= 0 || index + utf16.size > length)
        return 0;

    for (uptr i = 0; i < utf16.size; i += 1)
        utf16.memory[i] = memory[index + i];

    if (utf16_decode(&utf16, value) == 0) return 0;

    return utf16.size;
}

uptr
utf16_decode_forw_circ(u16* memory, uptr length, uptr index, u32* value)
{
    UTF16 utf16 = {};

    if (index >= 0 && index < length)
        utf16.size = utf16_units_to_read(memory[index]);

    if (utf16.size <= 0 || utf16.size > length) return 0;

    for (uptr i = 0; i < utf16.size; i += 1)
        utf16.memory[i] = memory[(index + i) % length];

    if (utf16_decode(&utf16, value) == 0) return 0;

    return utf16.size;
}

uptr
utf16_decode_back(u16* memory, uptr length, uptr index, u32* value)
{
    UTF16 utf16 = {};
    uptr  start = index;

    if (index < 0 || index >= length) return 0;

    while (unicode_is_surrogate_low(memory[index]) != 0) {
        index -= 1;

        if (index < 0 || index >= length)
            return 0;
    }

    utf16.size = start - index + 1;

    if (utf16.size != utf16_units_to_read(memory[index]))
        return 0;

    for (uptr i = 0; i < utf16.size; i += 1)
        utf16.memory[i] = memory[index + i];

    if (utf16_decode(&utf16, value) == 0) return 0;

    return utf16.size;
}

uptr
utf16_decode_back_circ(u16* memory, uptr length, uptr index, u32* value)
{
    UTF16 utf16 = {};
    uptr  count = 0;

    if (index < 0 || index >= length) return 0;

    while (count < 2) {
        if (unicode_is_surrogate_low(memory[index % length]) == 0)
            break;

        index  = (index + length - 1) % length;
        count += 1;
    }

    utf16.size = count + 1;

    if (utf16.size != utf16_units_to_read(memory[index % length]))
        return 0;

    for (uptr i = 0; i < utf16.size; i += 1)
        utf16.memory[i] = memory[(index + i) % length];

    if (utf16_decode(&utf16, value) == 0) return 0;

    return utf16.size;
}

uptr
utf16_units_to_write(u32 value)
{
    uptr units = 0;

    if (value >= 0x0     && value <= 0xd7ff)   units = 1;
    if (value >= 0xe000  && value <= 0xffff)   units = 1;
    if (value >= 0x10000 && value <= 0x10ffff) units = 2;

    return units;
}

uptr
utf16_units_to_read(u16 value)
{
    uptr units = 0;

    if (value >= 0x0    && value <= 0xd7ff) units = 1;
    if (value >= 0xd800 && value <= 0xdbff) units = 2;
    if (value >= 0xe000 && value <= 0xffff) units = 1;

    return units;
}

} // namespace pax

#endif // PAX_STRING_UTF16_CPP
