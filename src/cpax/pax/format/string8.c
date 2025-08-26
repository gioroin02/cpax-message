#ifndef PX_FORMAT_STRING8_C
#define PX_FORMAT_STRING8_C

#include "string8.h"

PxString8
pxString8FromU8(PxArena* arena, PxFormatOptions options, pxu8 value)
{
    PxFormatFlag flags  = options.flags;
    pxu8         radix  = options.radix;
    pxiword      length = 0;
    pxu8         temp   = value;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            length += 1;
    } else
        length += 1;

    if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
        length += 1;

    pxiword offset = pxArenaOffset(arena);
    pxu8*   result = pxArenaReserve(arena, pxu8, length + 1);
    pxiword index  = length;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            options.flags & PX_FORMAT_FLAG_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            result[index] = pxCast(pxu8, digit);
        else
            break;
    }

    if (index == 0) {
        if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
            result[index] = PX_ASCII_PLUS;

        return (PxString8) {
            .memory = result,
            .length = length,
        };
    }

    pxArenaRewind(arena, offset);

    return (PxString8) {0};
}

PxString8
pxString8FromU16(PxArena* arena, PxFormatOptions options, pxu16 value)
{
    PxFormatFlag flags  = options.flags;
    pxu16        radix  = options.radix;
    pxiword      length = 0;
    pxu16        temp   = value;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            length += 1;
    } else
        length += 1;

    if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
        length += 1;

    pxiword offset = pxArenaOffset(arena);
    pxu8*   result = pxArenaReserve(arena, pxu8, length + 1);
    pxiword index  = length;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            options.flags & PX_FORMAT_FLAG_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            result[index] = pxCast(pxu8, digit);
        else
            break;
    }

    if (index == 0) {
        if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
            result[index] = PX_ASCII_PLUS;

        return (PxString8) {
            .memory = result,
            .length = length,
        };
    }

    pxArenaRewind(arena, offset);

    return (PxString8) {0};
}

PxString8
pxString8FromU32(PxArena* arena, PxFormatOptions options, pxu32 value)
{
    PxFormatFlag flags  = options.flags;
    pxu32        radix  = options.radix;
    pxiword      length = 0;
    pxu32        temp   = value;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            length += 1;
    } else
        length += 1;

    if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
        length += 1;

    pxiword offset = pxArenaOffset(arena);
    pxu8*   result = pxArenaReserve(arena, pxu8, length + 1);
    pxiword index  = length;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            options.flags & PX_FORMAT_FLAG_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            result[index] = pxCast(pxu8, digit);
        else
            break;
    }

    if (index == 0) {
        if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
            result[index] = PX_ASCII_PLUS;

        return (PxString8) {
            .memory = result,
            .length = length,
        };
    }

    pxArenaRewind(arena, offset);

    return (PxString8) {0};
}

PxString8
pxString8FromU64(PxArena* arena, PxFormatOptions options, pxu64 value)
{
    PxFormatFlag flags  = options.flags;
    pxu64        radix  = options.radix;
    pxiword      length = 0;
    pxu64        temp   = value;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            length += 1;
    } else
        length += 1;

    if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
        length += 1;

    pxiword offset = pxArenaOffset(arena);
    pxu8*   result = pxArenaReserve(arena, pxu8, length + 1);
    pxiword index  = length;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            options.flags & PX_FORMAT_FLAG_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            result[index] = pxCast(pxu8, digit);
        else
            break;
    }

    if (index == 0) {
        if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
            result[index] = PX_ASCII_PLUS;

        return (PxString8) {
            .memory = result,
            .length = length,
        };
    }

    pxArenaRewind(arena, offset);

    return (PxString8) {0};
}

PxString8
pxString8FromUWord(PxArena* arena, PxFormatOptions options, pxuword value)
{
    PxFormatFlag flags  = options.flags;
    pxuword      radix  = options.radix;
    pxiword      length = 0;
    pxuword      temp   = value;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            length += 1;
    } else
        length += 1;

    if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
        length += 1;

    pxiword offset = pxArenaOffset(arena);
    pxu8*   result = pxArenaReserve(arena, pxu8, length + 1);
    pxiword index  = length;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            options.flags & PX_FORMAT_FLAG_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            result[index] = pxCast(pxu8, digit);
        else
            break;
    }

    if (index == 0) {
        if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
            result[index] = PX_ASCII_PLUS;

        return (PxString8) {
            .memory = result,
            .length = length,
        };
    }

    pxArenaRewind(arena, offset);

    return (PxString8) {0};
}

PxString8
pxString8FromI8(PxArena* arena, PxFormatOptions options, pxi8 value)
{
    PxFormatFlag flags  = options.flags;
    pxu8         radix  = options.radix;
    pxiword      length = 0;
    pxu8         temp   = pxMagnitudeI8(value);
    pxb8         sign   = pxDirectionI8(value) < 0 ? 1 : 0;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            length += 1;
    } else
        length += 1;

    if (sign != 0 || (flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
        length += 1;

    pxiword offset = pxArenaOffset(arena);
    pxu8*   result = pxArenaReserve(arena, pxu8, length + 1);
    pxiword index  = length;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            options.flags & PX_FORMAT_FLAG_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            result[index] = pxCast(pxu8, digit);
        else
            break;
    }

    if (index == 0) {
        if (sign != 0) result[index] = PX_ASCII_MINUS;

        if (sign == 0 && (flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
            result[index] = PX_ASCII_PLUS;

        return (PxString8) {
            .memory = result,
            .length = length,
        };
    }

    pxArenaRewind(arena, offset);

    return (PxString8) {0};
}

PxString8
pxString8FromI16(PxArena* arena, PxFormatOptions options, pxi16 value)
{
    PxFormatFlag flags  = options.flags;
    pxu16        radix  = options.radix;
    pxiword      length = 0;
    pxu16        temp   = pxMagnitudeI16(value);
    pxb8         sign   = pxDirectionI16(value) < 0 ? 1 : 0;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            length += 1;
    } else
        length += 1;

    if (sign != 0 || (flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
        length += 1;

    pxiword offset = pxArenaOffset(arena);
    pxu8*   result = pxArenaReserve(arena, pxu8, length + 1);
    pxiword index  = length;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            options.flags & PX_FORMAT_FLAG_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            result[index] = pxCast(pxu8, digit);
        else
            break;
    }

    if (index == 0) {
        if (sign != 0) result[index] = PX_ASCII_MINUS;

        if (sign == 0 && (flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
            result[index] = PX_ASCII_PLUS;

        return (PxString8) {
            .memory = result,
            .length = length,
        };
    }

    pxArenaRewind(arena, offset);

    return (PxString8) {0};
}

PxString8
pxString8FromI32(PxArena* arena, PxFormatOptions options, pxi32 value)
{
    PxFormatFlag flags  = options.flags;
    pxu32        radix  = options.radix;
    pxiword      length = 0;
    pxu32        temp   = pxMagnitudeI32(value);
    pxb8         sign   = pxDirectionI32(value) < 0 ? 1 : 0;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            length += 1;
    } else
        length += 1;

    if (sign != 0 || (flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
        length += 1;

    pxiword offset = pxArenaOffset(arena);
    pxu8*   result = pxArenaReserve(arena, pxu8, length + 1);
    pxiword index  = length;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            options.flags & PX_FORMAT_FLAG_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            result[index] = pxCast(pxu8, digit);
        else
            break;
    }

    if (index == 0) {
        if (sign != 0) result[index] = PX_ASCII_MINUS;

        if (sign == 0 && (flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
            result[index] = PX_ASCII_PLUS;

        return (PxString8) {
            .memory = result,
            .length = length,
        };
    }

    pxArenaRewind(arena, offset);

    return (PxString8) {0};
}

PxString8
pxString8FromI64(PxArena* arena, PxFormatOptions options, pxi64 value)
{
    PxFormatFlag flags  = options.flags;
    pxu64        radix  = options.radix;
    pxiword      length = 0;
    pxu64        temp   = pxMagnitudeI64(value);
    pxb8         sign   = pxDirectionI64(value) < 0 ? 1 : 0;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            length += 1;
    } else
        length += 1;

    if (sign != 0 || (flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
        length += 1;

    pxiword offset = pxArenaOffset(arena);
    pxu8*   result = pxArenaReserve(arena, pxu8, length + 1);
    pxiword index  = length;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            options.flags & PX_FORMAT_FLAG_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            result[index] = pxCast(pxu8, digit);
        else
            break;
    }

    if (index == 0) {
        if (sign != 0) result[index] = PX_ASCII_MINUS;

        if (sign == 0 && (flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
            result[index] = PX_ASCII_PLUS;

        return (PxString8) {
            .memory = result,
            .length = length,
        };
    }

    pxArenaRewind(arena, offset);

    return (PxString8) {0};
}

PxString8
pxString8FromIWord(PxArena* arena, PxFormatOptions options, pxiword value)
{
    PxFormatFlag flags  = options.flags;
    pxuword      radix  = options.radix;
    pxiword      length = 0;
    pxuword      temp   = pxMagnitudeIWord(value);
    pxb8         sign   = pxDirectionIWord(value) < 0 ? 1 : 0;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            length += 1;
    } else
        length += 1;

    if (sign != 0 || (flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
        length += 1;

    pxiword offset = pxArenaOffset(arena);
    pxu8*   result = pxArenaReserve(arena, pxu8, length + 1);
    pxiword index  = length;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            options.flags & PX_FORMAT_FLAG_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            result[index] = pxCast(pxu8, digit);
        else
            break;
    }

    if (index == 0) {
        if (sign != 0) result[index] = PX_ASCII_MINUS;

        if (sign == 0 && (flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
            result[index] = PX_ASCII_PLUS;

        return (PxString8) {
            .memory = result,
            .length = length,
        };
    }

    pxArenaRewind(arena, offset);

    return (PxString8) {0};
}

pxb8
pxU8FromString8(pxu8* self, PxFormatOptions options, PxString8 string)
{
    PxFormatFlag flags = options.flags;
    pxu8         radix = options.radix;
    pxiword      index = 0;
    pxu8         temp  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS: {
            if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((flags & PX_FORMAT_FLAG_LEADING_ZERO) == 0) {
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiValueFromDigit(string.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        if (temp > (PX_U8_MAX - digit) / radix)
            return 0;

        temp = temp * radix + digit;
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxU16FromString8(pxu16* self, PxFormatOptions options, PxString8 string)
{
    PxFormatFlag flags = options.flags;
    pxu8         radix = options.radix;
    pxiword      index = 0;
    pxu16        temp  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS: {
            if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((flags & PX_FORMAT_FLAG_LEADING_ZERO) == 0) {
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiValueFromDigit(string.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        if (temp > (PX_U16_MAX - digit) / radix)
            return 0;

        temp = temp * radix + digit;
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxU32FromString8(pxu32* self, PxFormatOptions options, PxString8 string)
{
    PxFormatFlag flags = options.flags;
    pxu8         radix = options.radix;
    pxiword      index = 0;
    pxu32        temp  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS: {
            if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((flags & PX_FORMAT_FLAG_LEADING_ZERO) == 0) {
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiValueFromDigit(string.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        if (temp > (PX_U32_MAX - digit) / radix)
            return 0;

        temp = temp * radix + digit;
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxU64FromString8(pxu64* self, PxFormatOptions options, PxString8 string)
{
    PxFormatFlag flags = options.flags;
    pxu8         radix = options.radix;
    pxiword      index = 0;
    pxu64        temp  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS: {
            if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((flags & PX_FORMAT_FLAG_LEADING_ZERO) == 0) {
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiValueFromDigit(string.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        if (temp > (PX_U64_MAX - digit) / radix)
            return 0;

        temp = temp * radix + digit;
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxUWordFromString8(pxuword* self, PxFormatOptions options, PxString8 string)
{
    PxFormatFlag flags = options.flags;
    pxu8         radix = options.radix;
    pxiword      index = 0;
    pxuword      temp  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS: {
            if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((flags & PX_FORMAT_FLAG_LEADING_ZERO) == 0) {
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiValueFromDigit(string.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        if (temp > (PX_UWORD_MAX - digit) / radix)
            return 0;

        temp = temp * radix + digit;
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxI8FromString8(pxi8* self, PxFormatOptions options, PxString8 string)
{
    PxFormatFlag flags = options.flags;
    pxi8         radix = options.radix;
    pxiword      index = 0;
    pxi8         temp  = 0;
    pxb8         sign  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS: {
            if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case PX_ASCII_MINUS: {
            index += 1;
            sign   = 1;
        } break;

        default: break;
    }

    if ((flags & PX_FORMAT_FLAG_LEADING_ZERO) == 0) {
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiValueFromDigit(string.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        switch (sign) {
            case 0: {
                if (temp > (PX_I8_MAX - digit) / radix)
                    return 0;

                temp = temp * radix + digit;
            } break;

            case 1: {
                if (temp < (PX_I8_MIN + digit) / radix)
                    return 0;

                temp = temp * radix - digit;
            } break;

            default: return 0;
        }
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxI16FromString8(pxi16* self, PxFormatOptions options, PxString8 string)
{
    PxFormatFlag flags = options.flags;
    pxi8         radix = options.radix;
    pxiword      index = 0;
    pxi16        temp  = 0;
    pxb8         sign  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS: {
            if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case PX_ASCII_MINUS: {
            index += 1;
            sign   = 1;
        } break;

        default: break;
    }

    if ((flags & PX_FORMAT_FLAG_LEADING_ZERO) == 0) {
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiValueFromDigit(string.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        switch (sign) {
            case 0: {
                if (temp > (PX_I16_MAX - digit) / radix)
                    return 0;

                temp = temp * radix + digit;
            } break;

            case 1: {
                if (temp < (PX_I16_MIN + digit) / radix)
                    return 0;

                temp = temp * radix - digit;
            } break;

            default: return 0;
        }
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxI32FromString8(pxi32* self, PxFormatOptions options, PxString8 string)
{
    PxFormatFlag flags = options.flags;
    pxi8         radix = options.radix;
    pxiword      index = 0;
    pxi32        temp  = 0;
    pxb8         sign  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS: {
            if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case PX_ASCII_MINUS: {
            index += 1;
            sign   = 1;
        } break;

        default: break;
    }

    if ((flags & PX_FORMAT_FLAG_LEADING_ZERO) == 0) {
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiValueFromDigit(string.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        switch (sign) {
            case 0: {
                if (temp > (PX_I32_MAX - digit) / radix)
                    return 0;

                temp = temp * radix + digit;
            } break;

            case 1: {
                if (temp < (PX_I32_MIN + digit) / radix)
                    return 0;

                temp = temp * radix - digit;
            } break;

            default: return 0;
        }
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxI64FromString8(pxi64* self, PxFormatOptions options, PxString8 string)
{
    PxFormatFlag flags = options.flags;
    pxi8         radix = options.radix;
    pxiword      index = 0;
    pxi64        temp  = 0;
    pxb8         sign  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS: {
            if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case PX_ASCII_MINUS: {
            index += 1;
            sign   = 1;
        } break;

        default: break;
    }

    if ((flags & PX_FORMAT_FLAG_LEADING_ZERO) == 0) {
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiValueFromDigit(string.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        switch (sign) {
            case 0: {
                if (temp > (PX_I64_MAX - digit) / radix)
                    return 0;

                temp = temp * radix + digit;
            } break;

            case 1: {
                if (temp < (PX_I64_MIN + digit) / radix)
                    return 0;

                temp = temp * radix - digit;
            } break;

            default: return 0;
        }
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxIWordFromString8(pxiword* self, PxFormatOptions options, PxString8 string)
{
    PxFormatFlag flags = options.flags;
    pxi8         radix = options.radix;
    pxiword      index = 0;
    pxiword      temp  = 0;
    pxb8         sign  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS: {
            if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case PX_ASCII_MINUS: {
            index += 1;
            sign   = 1;
        } break;

        default: break;
    }

    if ((flags & PX_FORMAT_FLAG_LEADING_ZERO) == 0) {
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiValueFromDigit(string.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        switch (sign) {
            case 0: {
                if (temp > (PX_IWORD_MAX - digit) / radix)
                    return 0;

                temp = temp * radix + digit;
            } break;

            case 1: {
                if (temp < (PX_IWORD_MIN + digit) / radix)
                    return 0;

                temp = temp * radix - digit;
            } break;

            default: return 0;
        }
    }

    if (self != 0) *self = temp;

    return 1;
}

#endif // PX_FORMAT_STRING8_C
