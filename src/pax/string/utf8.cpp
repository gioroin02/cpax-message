#ifndef PAX_STRING_UTF8_CPP
#define PAX_STRING_UTF8_CPP

#include "utf8.hpp"

namespace pax {

b32
utf8_encode(UTF8* self, u32 value)
{
    uptr units = utf8_units_to_write(value);

    self->a    = 0;
    self->b    = 0;
    self->c    = 0;
    self->d    = 0;
    self->size = 0;

    switch (units) {
        case 1: { self->a = pax_cast(u8, value); } break;

        case 2: {
            self->a = pax_cast(u8, ((value >> 6) & 0xff) | 0xc0);
            self->b = pax_cast(u8, ( value       & 0x3f) | 0x80);
        } break;

        case 3: {
            self->a = pax_cast(u8, ((value >> 12) & 0xff) | 0xe0);
            self->b = pax_cast(u8, ((value >> 6)  & 0x3f) | 0x80);
            self->c = pax_cast(u8, ( value        & 0x3f) | 0x80);
        } break;

        case 4: {
            self->a = pax_cast(u8, ((value >> 18) & 0xff) | 0xf0);
            self->b = pax_cast(u8, ((value >> 12) & 0x3f) | 0x80);
            self->c = pax_cast(u8, ((value >> 6)  & 0x3f) | 0x80);
            self->d = pax_cast(u8, ( value        & 0x3f) | 0x80);
        } break;

        default: return 0;
    }

    self->size = units;

    return 1;
}

uptr
utf8_encode_forw(u8* memory, uptr length, uptr index, u32 value)
{
    UTF8 utf8 = {};

    if (utf8_encode(&utf8, value) == 0) return 0;

    if (index < 0 || index + utf8.size > length)
        return 0;

    for (uptr i = 0; i < utf8.size; i += 1)
        memory[index + i] = utf8.memory[i];

    return utf8.size;
}

uptr
utf8_encode_forw_circ(u8* memory, uptr length, uptr index, u32 value)
{
    UTF8 utf8 = {};

    if (utf8_encode(&utf8, value) == 0) return 0;

    if (index < 0 || index > length || utf8.size > length)
        return 0;

    for (uptr i = 0; i < utf8.size; i += 1)
        memory[(index + i) % length] = utf8.memory[i];

    return utf8.size;
}

b32
utf8_decode(UTF8* self, u32* value)
{
    uptr units = utf8_units_to_read(self->a);
    u32  temp  = 0;

    if (self->size != units) return 0;

    switch (units) {
        case 1: { temp = self->a; } break;

        case 2: {
            if (utf8_is_trailing(self->b) == 0)
                return 0;

            temp  = (self->a & 0x1f) << 6;
            temp += (self->b & 0x3f);
        } break;

        case 3: {
            if (utf8_is_trailing(self->b) == 0) return 0;
            if (utf8_is_trailing(self->c) == 0) return 0;

            temp  = (self->a & 0x0f) << 12;
            temp += (self->b & 0x3f) << 6;
            temp += (self->c & 0x3f);
        } break;

        case 4: {
            if (utf8_is_trailing(self->b) == 0) return 0;
            if (utf8_is_trailing(self->c) == 0) return 0;
            if (utf8_is_trailing(self->d) == 0) return 0;

            temp  = (self->a & 0x07) << 18;
            temp += (self->b & 0x3f) << 12;
            temp += (self->c & 0x3f) << 6;
            temp += (self->d & 0x3f);
        } break;

        default: return 0;
    }

    if (utf8_is_overlong(temp, units) != 0)
        return 0;

    if (unicode_is_codepoint(temp) == 0) return 0;
    if (unicode_is_surrogate(temp) != 0) return 0;

    if (value != 0) *value = temp;

    return 1;
}

uptr
utf8_decode_forw(u8* memory, uptr length, uptr index, u32* value)
{
    UTF8 utf8 = {};

    if (index >= 0 && index < length)
        utf8.size = utf8_units_to_read(memory[index]);

    if (utf8.size <= 0 || index + utf8.size > length)
        return 0;

    for (uptr i = 0; i < utf8.size; i += 1)
        utf8.memory[i] = memory[index + i];

    if (utf8_decode(&utf8, value) == 0) return 0;

    return utf8.size;
}

uptr
utf8_decode_forw_circ(u8* memory, uptr length, uptr index, u32* value)
{
    UTF8 utf8 = {};

    if (index >= 0 && index < length)
        utf8.size = utf8_units_to_read(memory[index]);

    if (utf8.size <= 0 || utf8.size > length) return 0;

    for (uptr i = 0; i < utf8.size; i += 1)
        utf8.memory[i] = memory[(index + i) % length];

    if (utf8_decode(&utf8, value) == 0) return 0;

    return utf8.size;
}

uptr
utf8_decode_back(u8* memory, uptr length, uptr index, u32* value)
{
    UTF8 utf8  = {};
    uptr start = index;

    if (index < 0 || index >= length) return 0;

    while (utf8_is_trailing(memory[index]) != 0) {
        index -= 1;

        if (index < 0 || index >= length)
            return 0;
    }

    utf8.size = start - index + 1;

    if (utf8.size != utf8_units_to_read(memory[index]))
        return 0;

    for (uptr i = 0; i < utf8.size; i += 1)
        utf8.memory[i] = memory[index + i];

    if (utf8_decode(&utf8, value) == 0) return 0;

    return utf8.size;
}

uptr
utf8_decode_back_circ(u8* memory, uptr length, uptr index, u32* value)
{
    UTF8 utf8  = {};
    uptr count = 0;

    if (index < 0 || index >= length) return 0;

    while (count < 4) {
        if (utf8_is_trailing(memory[index % length]) == 0)
            break;

        index  = (index + length - 1) % length;
        count += 1;
    }

    utf8.size = count + 1;

    if (utf8.size != utf8_units_to_read(memory[index % length]))
        return 0;

    for (uptr i = 0; i < utf8.size; i += 1)
        utf8.memory[i] = memory[(index + i) % length];

    if (utf8_decode(&utf8, value) == 0) return 0;

    return utf8.size;
}

uptr
utf8_units_to_write(u32 value)
{
    uptr units = 0;

    if (value >= 0x0     && value <= 0x7f)     units = 1;
    if (value >= 0x80    && value <= 0x7ff)    units = 2;
    if (value >= 0x800   && value <= 0xd7ff)   units = 3;
    if (value >= 0xe000  && value <= 0xffff)   units = 3;
    if (value >= 0x10000 && value <= 0x10ffff) units = 4;

    return units;
}

uptr
utf8_units_to_read(u8 value)
{
    uptr units = 0;

    if (value >= 0x00 && value <= 0x7f) units = 1;
    if (value >= 0xc0 && value <= 0xdf) units = 2;
    if (value >= 0xe0 && value <= 0xef) units = 3;
    if (value >= 0xf0 && value <= 0xf7) units = 4;

    return units;
}

b32
utf8_is_trailing(u8 value)
{
    return (value & 0xc0) == 0x80;
}

b32
utf8_is_overlong(u32 value, uptr units)
{
    return (units == 2 && value >= 0xc080     && value <= 0xc1ff) ||
           (units == 3 && value >= 0xe08080   && value <= 0xe09fff) ||
           (units == 4 && value >= 0xf0808080 && value <= 0xf0bfffff);
}

} // namespace pax

#endif // PAX_STRING_UTF8_CPP
