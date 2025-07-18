#ifndef PAX_STRING_CONVERT_CPP
#define PAX_STRING_CONVERT_CPP

#include "convert.hpp"

namespace pax {

uptr
utf8_units_from_utf16(u16* memory, uptr length)
{
    uptr index = 0;
    uptr other = 0;

    while (other < length) {
        u32 unicode = 0;

        uptr read = utf16_decode_forw(memory, length,
            index, &unicode);

        uptr write = utf8_units_to_write(unicode);

        if (read <= 0 || write <= 0) return 0;

        index += read;
        other += write;
    }

    return other;
}

uptr
utf8_units_from_utf32(u32* memory, uptr length)
{
    uptr index = 0;
    uptr other = 0;

    while (other < length) {
        u32 unicode = 0;

        uptr read = utf32_decode_forw(memory, length,
            index, &unicode);

        uptr write = utf8_units_to_write(unicode);

        if (read <= 0 || write <= 0) return 0;

        index += read;
        other += write;
    }

    return other;
}

uptr
utf16_units_from_utf8(u8* memory, uptr length)
{
    uptr index = 0;
    uptr other = 0;

    while (other < length) {
        u32 unicode = 0;

        uptr read = utf8_decode_forw(memory, length,
            index, &unicode);

        uptr write = utf16_units_to_write(unicode);

        if (read <= 0 || write <= 0) return 0;

        index += read;
        other += write;
    }

    return other;
}

uptr
utf16_units_from_utf32(u32* memory, uptr length)
{
    uptr index = 0;
    uptr other = 0;

    while (other < length) {
        u32 unicode = 0;

        uptr read = utf32_decode_forw(memory, length,
            index, &unicode);

        uptr write = utf16_units_to_write(unicode);

        if (read <= 0 || write <= 0) return 0;

        index += read;
        other += write;
    }

    return other;
}

uptr
utf32_units_from_utf8(u8* memory, uptr length)
{
    uptr index = 0;
    uptr other = 0;

    while (other < length) {
        u32 unicode = 0;

        uptr read = utf8_decode_forw(memory, length,
            index, &unicode);

        uptr write = utf32_units_to_write(unicode);

        if (read <= 0 || write <= 0) return 0;

        index += read;
        other += write;
    }

    return other;
}

uptr
utf32_units_from_utf16(u16* memory, uptr length)
{
    uptr index = 0;
    uptr other = 0;

    while (other < length) {
        u32 unicode = 0;

        uptr read = utf16_decode_forw(memory, length,
            index, &unicode);

        uptr write = utf32_units_to_write(unicode);

        if (read <= 0 || write <= 0) return 0;

        index += read;
        other += write;
    }

    return other;
}

uptr
utf8_units_from_str16(str16 value)
{
    return utf8_units_from_utf16(value.memory, value.length);
}

uptr
utf8_units_from_str32(str32 value)
{
    return utf8_units_from_utf32(value.memory, value.length);
}

uptr
utf16_units_from_str8(str8 value)
{
    return utf16_units_from_utf8(value.memory, value.length);
}

uptr
utf16_units_from_str32(str32 value)
{
    return utf16_units_from_utf32(value.memory, value.length);
}

uptr
utf32_units_from_str8(str8 value)
{
    return utf32_units_from_utf8(value.memory, value.length);
}

uptr
utf32_units_from_str16(str16 value)
{
    return utf32_units_from_utf16(value.memory, value.length);
}

str8
str8_from_str16(Arena* arena, str16 value)
{
    uptr length = utf8_units_from_str16(value);
    str8 result = str8_reserve(arena, length);

    if (result.length == 0) return result;

    for (uptr i = 0, j = 0; j < length;) {
        u32 unicode = 0;

        i += utf16_decode_forw(value.memory,
            value.length, i, &unicode);

        j += utf8_encode_forw(result.memory,
            result.length, j, unicode);
    }

    return result;
}

str8
str8_from_str32(Arena* arena, str32 value)
{
    uptr length = utf8_units_from_str32(value);
    str8 result = str8_reserve(arena, length);

    if (result.length == 0) return result;

    for (uptr i = 0, j = 0; j < length;) {
        u32 unicode = 0;

        i += utf32_decode_forw(value.memory,
            value.length, i, &unicode);

        j += utf8_encode_forw(result.memory,
            result.length, j, unicode);
    }

    return result;
}

str16
str16_from_str8(Arena* arena, str8 value)
{
    uptr  length = utf16_units_from_str8(value);
    str16 result = str16_reserve(arena, length);

    if (result.length == 0) return result;

    for (uptr i = 0, j = 0; j < length;) {
        u32 unicode = 0;

        i += utf8_decode_forw(value.memory,
            value.length, i, &unicode);

        j += utf16_encode_forw(result.memory,
            result.length, j, unicode);
    }

    return result;
}

str16
str16_from_str32(Arena* arena, str32 value)
{
    uptr  length = utf16_units_from_str32(value);
    str16 result = str16_reserve(arena, length);

    if (result.length == 0) return result;

    for (uptr i = 0, j = 0; j < length;) {
        u32 unicode = 0;

        i += utf32_decode_forw(value.memory,
            value.length, i, &unicode);

        j += utf16_encode_forw(result.memory,
            result.length, j, unicode);
    }

    return result;
}

str32
str32_from_str8(Arena* arena, str8 value)
{
    uptr  length = utf32_units_from_str8(value);
    str32 result = str32_reserve(arena, length);

    if (result.length == 0) return result;

    for (uptr i = 0, j = 0; j < length;) {
        u32 unicode = 0;

        i += utf8_decode_forw(value.memory,
            value.length, i, &unicode);

        j += utf32_encode_forw(result.memory,
            result.length, j, unicode);
    }

    return result;
}

str32
str32_from_str16(Arena* arena, str16 value)
{
    uptr  length = utf32_units_from_str16(value);
    str32 result = str32_reserve(arena, length);

    if (result.length == 0) return result;

    for (uptr i = 0, j = 0; j < length;) {
        u32 unicode = 0;

        i += utf16_decode_forw(value.memory,
            value.length, i, &unicode);

        j += utf32_encode_forw(result.memory,
            result.length, j, unicode);
    }

    return result;
}

} // namespace pax

#endif // PAX_STRING_CONVERT_CPP
