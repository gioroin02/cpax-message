#ifndef PAX_FORMAT_UNSIGNED_CPP
#define PAX_FORMAT_UNSIGNED_CPP

#include "unsigned.hpp"

namespace pax {

b32
uptr_from_str8(str8 self, Format_Options opts, uptr* value)
{
    uptr index = 0;
    uptr base  = opts.base;
    uptr temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        uptr digit = digit_from_ascii(self.memory[index], base);

        if (digit >= 0 && digit < base) {
            if (temp > (UPTR_MAX - digit) / base)
                return 0;

            temp = temp * base + digit;
        } else
            return 0;
    }

    *value = temp;

    return 1;
}

b32
u64_from_str8(str8 self, Format_Options opts, u64* value)
{
    uptr index = 0;
    u64  base  = opts.base;
    u64  temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u64 digit = digit_from_ascii(self.memory[index], base);

        if (digit >= 0 && digit < base) {
            if (temp > (U64_MAX - digit) / base)
                return 0;

            temp = temp * base + digit;
        } else
            return 0;
    }

    *value = temp;

    return 1;
}

b32
u32_from_str8(str8 self, Format_Options opts, u32* value)
{
    uptr index = 0;
    u32  base  = opts.base;
    u32  temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u32 digit = digit_from_ascii(self.memory[index], base);

        if (digit >= 0 && digit < base) {
            if (temp > (U32_MAX - digit) / base)
                return 0;

            temp = temp * base + digit;
        } else
            return 0;
    }

    *value = temp;

    return 1;
}

b32
u16_from_str8(str8 self, Format_Options opts, u16* value)
{
    uptr index = 0;
    u16  base  = opts.base;
    u16  temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u16 digit = digit_from_ascii(self.memory[index], base);

        if (digit >= 0 && digit < base) {
            if (temp > (U16_MAX - digit) / base)
                return 0;

            temp = temp * base + digit;
        } else
            return 0;
    }

    *value = temp;

    return 1;
}

b32
u8_from_str8(str8 self, Format_Options opts, u8* value)
{
    uptr index = 0;
    u8   base  = opts.base;
    u8   temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u8 digit = digit_from_ascii(self.memory[index], base);

        if (digit >= 0 && digit < base) {
            if (temp > (U8_MAX - digit) / base)
                return 0;

            temp = temp * base + digit;
        } else
            return 0;
    }

    *value = temp;

    return 1;
}

b32
uptr_from_str16(str16 self, Format_Options opts, uptr* value)
{
    uptr index = 0;
    uptr base  = opts.base;
    uptr temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        uptr digit = digit_from_ascii(self.memory[index], base);

        if (digit >= 0 && digit < base) {
            if (temp > (UPTR_MAX - digit) / base)
                return 0;

            temp = temp * base + digit;
        } else
            return 0;
    }

    *value = temp;

    return 1;
}

b32
u64_from_str16(str16 self, Format_Options opts, u64* value)
{
    uptr index = 0;
    u64  base  = opts.base;
    u64  temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u64 digit = digit_from_ascii(self.memory[index], base);

        if (digit >= 0 && digit < base) {
            if (temp > (U64_MAX - digit) / base)
                return 0;

            temp = temp * base + digit;
        } else
            return 0;
    }

    *value = temp;

    return 1;
}

b32
u32_from_str16(str16 self, Format_Options opts, u32* value)
{
    uptr index = 0;
    u32  base  = opts.base;
    u32  temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u32 digit = digit_from_ascii(self.memory[index], base);

        if (digit >= 0 && digit < base) {
            if (temp > (U32_MAX - digit) / base)
                return 0;

            temp = temp * base + digit;
        } else
            return 0;
    }

    *value = temp;

    return 1;
}

b32
u16_from_str16(str16 self, Format_Options opts, u16* value)
{
    uptr index = 0;
    u16  base  = opts.base;
    u16  temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u16 digit = digit_from_ascii(self.memory[index], base);

        if (digit >= 0 && digit < base) {
            if (temp > (U16_MAX - digit) / base)
                return 0;

            temp = temp * base + digit;
        } else
            return 0;
    }

    *value = temp;

    return 1;
}

b32
u8_from_str16(str16 self, Format_Options opts, u8* value)
{
    uptr index = 0;
    u8   base  = opts.base;
    u8   temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u8 digit = digit_from_ascii(self.memory[index], base);

        if (digit >= 0 && digit < base) {
            if (temp > (U8_MAX - digit) / base)
                return 0;

            temp = temp * base + digit;
        } else
            return 0;
    }

    *value = temp;

    return 1;
}

b32
uptr_from_str32(str32 self, Format_Options opts, uptr* value)
{
    uptr index = 0;
    uptr base  = opts.base;
    uptr temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        uptr digit = digit_from_ascii(self.memory[index], base);

        if (digit >= 0 && digit < base) {
            if (temp > (UPTR_MAX - digit) / base)
                return 0;

            temp = temp * base + digit;
        } else
            return 0;
    }

    *value = temp;

    return 1;
}

b32
u64_from_str32(str32 self, Format_Options opts, u64* value)
{
    uptr index = 0;
    u64  base  = opts.base;
    u64  temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u64 digit = digit_from_ascii(self.memory[index], base);

        if (digit >= 0 && digit < base) {
            if (temp > (U64_MAX - digit) / base)
                return 0;

            temp = temp * base + digit;
        } else
            return 0;
    }

    *value = temp;

    return 1;
}

b32
u32_from_str32(str32 self, Format_Options opts, u32* value)
{
    uptr index = 0;
    u32  base  = opts.base;
    u32  temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u32 digit = digit_from_ascii(self.memory[index], base);

        if (digit >= 0 && digit < base) {
            if (temp > (U32_MAX - digit) / base)
                return 0;

            temp = temp * base + digit;
        } else
            return 0;
    }

    *value = temp;

    return 1;
}

b32
u16_from_str32(str32 self, Format_Options opts, u16* value)
{
    uptr index = 0;
    u16  base  = opts.base;
    u16  temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u16 digit = digit_from_ascii(self.memory[index], base);

        if (digit >= 0 && digit < base) {
            if (temp > (U16_MAX - digit) / base)
                return 0;

            temp = temp * base + digit;
        } else
            return 0;
    }

    *value = temp;

    return 1;
}

b32
u8_from_str32(str32 self, Format_Options opts, u8* value)
{
    uptr index = 0;
    u8   base  = opts.base;
    u8   temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u8 digit = digit_from_ascii(self.memory[index], base);

        if (digit >= 0 && digit < base) {
            if (temp > (U8_MAX - digit) / base)
                return 0;

            temp = temp * base + digit;
        } else
            return 0;
    }

    *value = temp;

    return 1;
}

/*
b32
uptr_from_buffer(Buffer self, Format_Options opts, uptr* value)
{
    return uptr_from_str8(str8_make(self.memory, self.size), opts, value);
}

b32
u64_from_buffer(Buffer self, Format_Options opts, u64* value)
{
    return u64_from_str8(str8_make(self.memory, self.size), opts, value);
}

b32
u32_from_buffer(Buffer self, Format_Options opts, u32* value)
{
    return u32_from_str8(str8_make(self.memory, self.size), opts, value);
}

b32
u16_from_buffer(Buffer self, Format_Options opts, u16* value)
{
    return u16_from_str8(str8_make(self.memory, self.size), opts, value);
}

b32
u8_from_buffer(Buffer self, Format_Options opts, u8* value)
{
    return u8_from_str8(str8_make(self.memory, self.size), opts, value);
}
*/

str8
str8_from_uptr(Arena* arena, Format_Options opts, uptr value)
{
    uptr size = 0;
    uptr base = opts.base;

    if (value == 0) size = 1;

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    for (uptr temp = value; temp != 0; temp /= base)
        size += 1;

    uptr offset = arena_offset(arena);
    str8 result = str8_reserve(arena, size);

    for (uptr i = size; i > 0; i -= 1) {
        u32 ascii = ascii_from_digit(value, base);

        if (ascii != ASCII_NULL)
            result.memory[i - 1] = pax_cast(u8, ascii);
        else
            break;

        value /= base;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str8
str8_from_u64(Arena* arena, Format_Options opts, u64 value)
{
    uptr size = 0;
    u64  base = opts.base;

    if (value == 0) size = 1;

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    for (u64 temp = value; temp != 0; temp /= base)
        size += 1;

    uptr offset = arena_offset(arena);
    str8 result = str8_reserve(arena, size);

    for (uptr i = size; i > 0; i -= 1) {
        u32 ascii = ascii_from_digit(value, base);

        if (ascii != ASCII_NULL)
            result.memory[i - 1] = pax_cast(u8, ascii);
        else
            break;

        value /= base;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str8
str8_from_u32(Arena* arena, Format_Options opts, u32 value)
{
    uptr size = 0;
    u32  base = opts.base;

    if (value == 0) size = 1;

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    for (u32 temp = value; temp != 0; temp /= base)
        size += 1;

    uptr offset = arena_offset(arena);
    str8 result = str8_reserve(arena, size);

    for (uptr i = size; i > 0; i -= 1) {
        u32 ascii = ascii_from_digit(value, base);

        if (ascii != ASCII_NULL)
            result.memory[i - 1] = pax_cast(u8, ascii);
        else
            break;

        value /= base;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str8
str8_from_u16(Arena* arena, Format_Options opts, u16 value)
{
    uptr size = 0;
    u16  base = opts.base;

    if (value == 0) size = 1;

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    for (u16 temp = value; temp != 0; temp /= base)
        size += 1;

    uptr offset = arena_offset(arena);
    str8 result = str8_reserve(arena, size);

    for (uptr i = size; i > 0; i -= 1) {
        u32 ascii = ascii_from_digit(value, base);

        if (ascii != ASCII_NULL)
            result.memory[i - 1] = pax_cast(u8, ascii);
        else
            break;

        value /= base;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str8
str8_from_u8(Arena* arena, Format_Options opts, u8 value)
{
    uptr size = 0;
    u8   base = opts.base;

    if (value == 0) size = 1;

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    for (u8 temp = value; temp != 0; temp /= base)
        size += 1;

    uptr offset = arena_offset(arena);
    str8 result = str8_reserve(arena, size);

    for (uptr i = size; i > 0; i -= 1) {
        u32 ascii = ascii_from_digit(value, base);

        if (ascii != ASCII_NULL)
            result.memory[i - 1] = pax_cast(u8, ascii);
        else
            break;

        value /= base;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str16
str16_from_uptr(Arena* arena, Format_Options opts, uptr value)
{
    uptr size = 0;
    uptr base = opts.base;

    if (value == 0) size = 1;

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    for (uptr temp = value; temp != 0; temp /= base)
        size += 1;

    uptr  offset = arena_offset(arena);
    str16 result = str16_reserve(arena, size);

    for (uptr i = size; i > 0; i -= 1) {
        u32 ascii = ascii_from_digit(value, base);

        if (ascii != ASCII_NULL)
            result.memory[i - 1] = pax_cast(u16, ascii);
        else
            break;

        value /= base;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str16
str16_from_u64(Arena* arena, Format_Options opts, u64 value)
{
    uptr size = 0;
    u64  base = opts.base;

    if (value == 0) size = 1;

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    for (u64 temp = value; temp != 0; temp /= base)
        size += 1;

    uptr  offset = arena_offset(arena);
    str16 result = str16_reserve(arena, size);

    for (uptr i = size; i > 0; i -= 1) {
        u32 ascii = ascii_from_digit(value, base);

        if (ascii != ASCII_NULL)
            result.memory[i - 1] = pax_cast(u16, ascii);
        else
            break;

        value /= base;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str16
str16_from_u32(Arena* arena, Format_Options opts, u32 value)
{
    uptr size = 0;
    u32  base = opts.base;

    if (value == 0) size = 1;

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    for (u32 temp = value; temp != 0; temp /= base)
        size += 1;

    uptr  offset = arena_offset(arena);
    str16 result = str16_reserve(arena, size);

    for (uptr i = size; i > 0; i -= 1) {
        u32 ascii = ascii_from_digit(value, base);

        if (ascii != ASCII_NULL)
            result.memory[i - 1] = pax_cast(u16, ascii);
        else
            break;

        value /= base;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str16
str16_from_u16(Arena* arena, Format_Options opts, u16 value)
{
    uptr size = 0;
    u16  base = opts.base;

    if (value == 0) size = 1;

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    for (u16 temp = value; temp != 0; temp /= base)
        size += 1;

    uptr  offset = arena_offset(arena);
    str16 result = str16_reserve(arena, size);

    for (uptr i = size; i > 0; i -= 1) {
        u32 ascii = ascii_from_digit(value, base);

        if (ascii != ASCII_NULL)
            result.memory[i - 1] = pax_cast(u16, ascii);
        else
            break;

        value /= base;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str16
str16_from_u8(Arena* arena, Format_Options opts, u8 value)
{
    uptr size = 0;
    u8   base = opts.base;

    if (value == 0) size = 1;

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    for (u8 temp = value; temp != 0; temp /= base)
        size += 1;

    uptr  offset = arena_offset(arena);
    str16 result = str16_reserve(arena, size);

    for (uptr i = size; i > 0; i -= 1) {
        u32 ascii = ascii_from_digit(value, base);

        if (ascii != ASCII_NULL)
            result.memory[i - 1] = pax_cast(u16, ascii);
        else
            break;

        value /= base;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str32
str32_from_uptr(Arena* arena, Format_Options opts, uptr value)
{
    uptr size = 0;
    uptr base = opts.base;

    if (value == 0) size = 1;

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    for (uptr temp = value; temp != 0; temp /= base)
        size += 1;

    uptr  offset = arena_offset(arena);
    str32 result = str32_reserve(arena, size);

    for (uptr i = size; i > 0; i -= 1) {
        u32 ascii = ascii_from_digit(value, base);

        if (ascii != ASCII_NULL)
            result.memory[i - 1] = ascii;
        else
            break;

        value /= base;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str32
str32_from_u64(Arena* arena, Format_Options opts, u64 value)
{
    uptr size = 0;
    u64  base = opts.base;

    if (value == 0) size = 1;

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    for (u64 temp = value; temp != 0; temp /= base)
        size += 1;

    uptr  offset = arena_offset(arena);
    str32 result = str32_reserve(arena, size);

    for (uptr i = size; i > 0; i -= 1) {
        u32 ascii = ascii_from_digit(value, base);

        if (ascii != ASCII_NULL)
            result.memory[i - 1] = ascii;
        else
            break;

        value /= base;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str32
str32_from_u32(Arena* arena, Format_Options opts, u32 value)
{
    uptr size = 0;
    u32  base = opts.base;

    if (value == 0) size = 1;

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    for (u32 temp = value; temp != 0; temp /= base)
        size += 1;

    uptr  offset = arena_offset(arena);
    str32 result = str32_reserve(arena, size);

    for (uptr i = size; i > 0; i -= 1) {
        u32 ascii = ascii_from_digit(value, base);

        if (ascii != ASCII_NULL)
            result.memory[i - 1] = ascii;
        else
            break;

        value /= base;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str32
str32_from_u16(Arena* arena, Format_Options opts, u16 value)
{
    uptr size = 0;
    u16  base = opts.base;

    if (value == 0) size = 1;

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    for (u16 temp = value; temp != 0; temp /= base)
        size += 1;

    uptr  offset = arena_offset(arena);
    str32 result = str32_reserve(arena, size);

    for (uptr i = size; i > 0; i -= 1) {
        u32 ascii = ascii_from_digit(value, base);

        if (ascii != ASCII_NULL)
            result.memory[i - 1] = ascii;
        else
            break;

        value /= base;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str32
str32_from_u8(Arena* arena, Format_Options opts, u8 value)
{
    uptr size = 0;
    u8   base = opts.base;

    if (value == 0) size = 1;

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    for (u8 temp = value; temp != 0; temp /= base)
        size += 1;

    uptr  offset = arena_offset(arena);
    str32 result = str32_reserve(arena, size);

    for (uptr i = size; i > 0; i -= 1) {
        u32 ascii = ascii_from_digit(value, base);

        if (ascii != ASCII_NULL)
            result.memory[i - 1] = ascii;
        else
            break;

        value /= base;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

/*
b32
buffer_write_uptr(Buffer* self, Format_Options opts, uptr value)
{
    uptr start = self->size;
    uptr size  = 0;
    uptr base  = opts.base;

    if (value == 0) size = 1;

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    for (uptr temp = value; temp != 0; temp /= base)
        size += 1;

    if (start < 0 || start + size > self->length)
        return 0;

    for (uptr i = size; i > 0; i -= 1) {
        u32 ascii = ascii_from_digit(value, base);

        if (ascii != ASCII_NULL)
            self->memory[start + i] = pax_cast(u8, ascii);
        else
            return 0;

        value /= base;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        self->memory[start] = ASCII_PLUS;

    self->size += size;

    return 1;
}

b32
buffer_write_u64(Buffer* self, Format_Options opts, u64 value)
{
    uptr start = self->size;
    uptr size  = 0;
    u64  base  = opts.base;

    if (value == 0) size = 1;

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    for (u64 temp = value; temp != 0; temp /= base)
        size += 1;

    if (start < 0 || start + size > self->length)
        return 0;

    for (uptr i = size; i > 0; i -= 1) {
        u32 ascii = ascii_from_digit(value, base);

        if (ascii != ASCII_NULL) {
            self->memory[start + i] = pax_cast(u8, ascii);
        } else
            return 0;

        value /= base;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        self->memory[start] = ASCII_PLUS;

    self->size += size;

    return 1;
}

b32
buffer_write_u32(Buffer* self, Format_Options opts, u32 value)
{
    uptr start = self->size;
    uptr size  = 0;
    u32  base  = opts.base;

    if (value == 0) size = 1;

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    for (u32 temp = value; temp != 0; temp /= base)
        size += 1;

    if (start < 0 || start + size > self->length)
        return 0;

    for (uptr i = size; i > 0; i -= 1) {
        u32 ascii = ascii_from_digit(value, base);

        if (ascii != ASCII_NULL) {
            self->memory[start + i] = pax_cast(u8, ascii);
        } else
            return 0;

        value /= base;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        self->memory[start] = ASCII_PLUS;

    self->size += size;

    return 1;
}

b32
buffer_write_u16(Buffer* self, Format_Options opts, u16 value)
{
    uptr start = self->size;
    uptr size  = 0;
    u16  base  = opts.base;

    if (value == 0) size = 1;

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    for (u16 temp = value; temp != 0; temp /= base)
        size += 1;

    if (start < 0 || start + size > self->length)
        return 0;

    for (uptr i = size; i > 0; i -= 1) {
        u32 ascii = ascii_from_digit(value, base);

        if (ascii != ASCII_NULL) {
            self->memory[start + i] = pax_cast(u8, ascii);
        } else
            return 0;

        value /= base;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        self->memory[start] = ASCII_PLUS;

    self->size += size;

    return 1;
}

b32
buffer_write_u8(Buffer* self, Format_Options opts, u8 value)
{
    uptr start = self->size;
    uptr size  = 0;
    u8   base  = opts.base;

    if (value == 0) size = 1;

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    for (u8 temp = value; temp != 0; temp /= base)
        size += 1;

    if (start < 0 || start + size > self->length)
        return 0;

    for (uptr i = size; i > 0; i -= 1) {
        u32 ascii = ascii_from_digit(value, base);

        if (ascii != ASCII_NULL) {
            self->memory[start + i] = pax_cast(u8, ascii);
        } else
            return 0;

        value /= base;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        self->memory[start] = ASCII_PLUS;

    self->size += size;

    return 1;
}
*/

} // namespace pax

#endif // PAX_FORMAT_UNSIGNED_CPP
