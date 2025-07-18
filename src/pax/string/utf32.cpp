#ifndef PAX_STRING_UTF32_CPP
#define PAX_STRING_UTF32_CPP

#include "utf32.hpp"

namespace pax {

b32
utf32_encode(UTF32* self, u32 value)
{
    uptr units = utf32_units_to_write(value);

    self->a    = 0;
    self->size = 0;

    switch (units) {
        case 1: { self->a = value; } break;

        default: return 0;
    }

    self->size = units;

    return 1;
}

uptr
utf32_encode_forw(u32* memory, uptr length, uptr index, u32 value)
{
    UTF32 utf32 = {};

    if (utf32_encode(&utf32, value) == 0) return 0;

    if (index < 0 || index + utf32.size > length)
        return 0;

    if (utf32.size != 0) memory[index] = utf32.memory[0];

    return utf32.size;
}

b32
utf32_decode(UTF32* self, u32* value)
{
    uptr units = utf32_units_to_read(self->a);
    u32  temp  = 0;

    if (self->size != units) return 0;

    switch (units) {
        case 1: { temp = self->a; } break;

        default: return 0;
    }

    if (unicode_is_codepoint(temp) == 0) return 0;
    if (unicode_is_surrogate(temp) != 0) return 0;

    if (value != 0) *value = temp;

    return 1;
}

uptr
utf32_decode_forw(u32* memory, uptr length, uptr index, u32* value)
{
    UTF32 utf32 = {};

    if (index >= 0 && index < length)
        utf32.size = utf32_units_to_read(memory[index]);

    if (utf32.size <= 0 || index + utf32.size > length)
        return 0;

    utf32.memory[0] = memory[index];

    if (utf32_decode(&utf32, value) == 0) return 0;

    return utf32.size;
}

uptr
utf32_decode_back(u32* memory, uptr length, uptr index, u32* value)
{
    UTF32 utf32 = {};

    if (index < 0 || index >= length) return 0;

    utf32.size = 1;

    if (utf32.size != utf32_units_to_read(memory[index]))
        return 0;

    utf32.memory[0] = memory[index];

    if (utf32_decode(&utf32, value) == 0) return 0;

    return utf32.size;
}

uptr
utf32_units_to_write(u32 value)
{
    uptr units = 0;

    if (value >= 0x0    && value <= 0xd7ff)   units = 1;
    if (value >= 0xe000 && value <= 0x10ffff) units = 1;

    return units;
}

uptr
utf32_units_to_read(u32 value)
{
    uptr units = 0;

    if (value >= 0x0    && value <= 0xd7ff)   units = 1;
    if (value >= 0xe000 && value <= 0x10ffff) units = 1;

    return units;
}

} // namespace pax

#endif // PAX_STRING_UTF32_CPP
