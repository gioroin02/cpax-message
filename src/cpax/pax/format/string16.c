#ifndef PX_FORMAT_STRING16_C
#define PX_FORMAT_STRING16_C

#include "string16.h"

PxString16
pxString16FromU8(PxArena* arena, pxuword radix, PxFormatOption options, pxu8 value)
{
    pxiword length = 0;
    pxu8    temp   = value;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            length += 1;
    } else
        length += 1;

    if ((options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        length += 1;

    pxiword offset = pxArenaOffset(arena);
    pxu16*  result = pxArenaReserve(arena, pxu16, length + 1);
    pxiword index  = length;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            result[index] = pxCast(pxu16, digit);
        else
            break;
    }

    if (index == 0) {
        if ((options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
            result[index] = PX_ASCII_PLUS;

        return (PxString16) {
            .memory = result,
            .length = length,
        };
    }

    pxArenaRewind(arena, offset);

    return (PxString16) {0};
}

PxString16
pxString16FromU16(PxArena* arena, pxuword radix, PxFormatOption options, pxu16 value)
{
    pxiword length = 0;
    pxu16   temp   = value;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            length += 1;
    } else
        length += 1;

    if ((options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        length += 1;

    pxiword offset = pxArenaOffset(arena);
    pxu16*  result = pxArenaReserve(arena, pxu16, length + 1);
    pxiword index  = length;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            result[index] = pxCast(pxu16, digit);
        else
            break;
    }

    if (index == 0) {
        if ((options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
            result[index] = PX_ASCII_PLUS;

        return (PxString16) {
            .memory = result,
            .length = length,
        };
    }

    pxArenaRewind(arena, offset);

    return (PxString16) {0};
}

PxString16
pxString16FromU32(PxArena* arena, pxuword radix, PxFormatOption options, pxu32 value)
{
    pxiword length = 0;
    pxu32   temp   = value;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            length += 1;
    } else
        length += 1;

    if ((options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        length += 1;

    pxiword offset = pxArenaOffset(arena);
    pxu16*  result = pxArenaReserve(arena, pxu16, length + 1);
    pxiword index  = length;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            result[index] = pxCast(pxu16, digit);
        else
            break;
    }

    if (index == 0) {
        if ((options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
            result[index] = PX_ASCII_PLUS;

        return (PxString16) {
            .memory = result,
            .length = length,
        };
    }

    pxArenaRewind(arena, offset);

    return (PxString16) {0};
}

PxString16
pxString16FromU64(PxArena* arena, pxuword radix, PxFormatOption options, pxu64 value)
{
    pxiword length = 0;
    pxu64   temp   = value;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            length += 1;
    } else
        length += 1;

    if ((options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        length += 1;

    pxiword offset = pxArenaOffset(arena);
    pxu16*  result = pxArenaReserve(arena, pxu16, length + 1);
    pxiword index  = length;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            result[index] = pxCast(pxu16, digit);
        else
            break;
    }

    if (index == 0) {
        if ((options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
            result[index] = PX_ASCII_PLUS;

        return (PxString16) {
            .memory = result,
            .length = length,
        };
    }

    pxArenaRewind(arena, offset);

    return (PxString16) {0};
}

PxString16
pxString16FromUWord(PxArena* arena, pxuword radix, PxFormatOption options, pxuword value)
{
    pxiword length = 0;
    pxuword temp   = value;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            length += 1;
    } else
        length += 1;

    if ((options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        length += 1;

    pxiword offset = pxArenaOffset(arena);
    pxu16*  result = pxArenaReserve(arena, pxu16, length + 1);
    pxiword index  = length;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            result[index] = pxCast(pxu16, digit);
        else
            break;
    }

    if (index == 0) {
        if ((options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
            result[index] = PX_ASCII_PLUS;

        return (PxString16) {
            .memory = result,
            .length = length,
        };
    }

    pxArenaRewind(arena, offset);

    return (PxString16) {0};
}

PxString16
pxString16FromI8(PxArena* arena, pxuword radix, PxFormatOption options, pxi8 value)
{
    pxiword length = 0;
    pxu8    temp   = pxMagnitudeI8(value);
    pxb8    sign   = pxDirectionI8(value) < 0 ? 1 : 0;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            length += 1;
    } else
        length += 1;

    if (sign != 0 || (options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        length += 1;

    pxiword offset = pxArenaOffset(arena);
    pxu16*  result = pxArenaReserve(arena, pxu16, length + 1);
    pxiword index  = length;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            result[index] = pxCast(pxu16, digit);
        else
            break;
    }

    if (index == 0) {
        if (sign != 0) result[index] = PX_ASCII_MINUS;

        if (sign == 0 && (options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
            result[index] = PX_ASCII_PLUS;

        return (PxString16) {
            .memory = result,
            .length = length,
        };
    }

    pxArenaRewind(arena, offset);

    return (PxString16) {0};
}

PxString16
pxString16FromI16(PxArena* arena, pxuword radix, PxFormatOption options, pxi16 value)
{
    pxiword length = 0;
    pxu16   temp   = pxMagnitudeI16(value);
    pxb8    sign   = pxDirectionI16(value) < 0 ? 1 : 0;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            length += 1;
    } else
        length += 1;

    if (sign != 0 || (options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        length += 1;

    pxiword offset = pxArenaOffset(arena);
    pxu16*  result = pxArenaReserve(arena, pxu16, length + 1);
    pxiword index  = length;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            result[index] = pxCast(pxu16, digit);
        else
            break;
    }

    if (index == 0) {
        if (sign != 0) result[index] = PX_ASCII_MINUS;

        if (sign == 0 && (options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
            result[index] = PX_ASCII_PLUS;

        return (PxString16) {
            .memory = result,
            .length = length,
        };
    }

    pxArenaRewind(arena, offset);

    return (PxString16) {0};
}

PxString16
pxString16FromI32(PxArena* arena, pxuword radix, PxFormatOption options, pxi32 value)
{
    pxiword length = 0;
    pxu32   temp   = pxMagnitudeI32(value);
    pxb8    sign   = pxDirectionI32(value) < 0 ? 1 : 0;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            length += 1;
    } else
        length += 1;

    if (sign != 0 || (options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        length += 1;

    pxiword offset = pxArenaOffset(arena);
    pxu16*  result = pxArenaReserve(arena, pxu16, length + 1);
    pxiword index  = length;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            result[index] = pxCast(pxu16, digit);
        else
            break;
    }

    if (index == 0) {
        if (sign != 0) result[index] = PX_ASCII_MINUS;

        if (sign == 0 && (options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
            result[index] = PX_ASCII_PLUS;

        return (PxString16) {
            .memory = result,
            .length = length,
        };
    }

    pxArenaRewind(arena, offset);

    return (PxString16) {0};
}

PxString16
pxString16FromI64(PxArena* arena, pxuword radix, PxFormatOption options, pxi64 value)
{
    pxiword length = 0;
    pxu64   temp   = pxMagnitudeI64(value);
    pxb8    sign   = pxDirectionI64(value) < 0 ? 1 : 0;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            length += 1;
    } else
        length += 1;

    if (sign != 0 || (options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        length += 1;

    pxiword offset = pxArenaOffset(arena);
    pxu16*  result = pxArenaReserve(arena, pxu16, length + 1);
    pxiword index  = length;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            result[index] = pxCast(pxu16, digit);
        else
            break;
    }

    if (index == 0) {
        if (sign != 0) result[index] = PX_ASCII_MINUS;

        if (sign == 0 && (options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
            result[index] = PX_ASCII_PLUS;

        return (PxString16) {
            .memory = result,
            .length = length,
        };
    }

    pxArenaRewind(arena, offset);

    return (PxString16) {0};
}

PxString16
pxString16FromIWord(PxArena* arena, pxuword radix, PxFormatOption options, pxiword value)
{
    pxiword length = 0;
    pxuword temp   = pxMagnitudeIWord(value);
    pxb8    sign   = pxDirectionIWord(value) < 0 ? 1 : 0;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            length += 1;
    } else
        length += 1;

    if (sign != 0 || (options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        length += 1;

    pxiword offset = pxArenaOffset(arena);
    pxu16*  result = pxArenaReserve(arena, pxu16, length + 1);
    pxiword index  = length;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            result[index] = pxCast(pxu16, digit);
        else
            break;
    }

    if (index == 0) {
        if (sign != 0) result[index] = PX_ASCII_MINUS;

        if (sign == 0 && (options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
            result[index] = PX_ASCII_PLUS;

        return (PxString16) {
            .memory = result,
            .length = length,
        };
    }

    pxArenaRewind(arena, offset);

    return (PxString16) {0};
}

pxb8
pxU8FromString16(pxu8* self, pxuword radix, PxFormatOption options, PxString16 string)
{
    pxiword index = 0;
    pxu8    temp  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS: {
            if ((options & PX_FORMAT_OPTION_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((options & PX_FORMAT_OPTION_LEADING_ZERO) == 0) {
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiValueFromDigit(string.memory[index], radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        if (digit < 0 || digit >= radix) return 0;

        if (temp > (PX_U8_MAX - digit) / radix)
            return 0;

        temp = temp * radix + digit;
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxU16FromString16(pxu16* self, pxuword radix, PxFormatOption options, PxString16 string)
{
    pxiword index = 0;
    pxu16   temp  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS: {
            if ((options & PX_FORMAT_OPTION_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((options & PX_FORMAT_OPTION_LEADING_ZERO) == 0) {
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiValueFromDigit(string.memory[index], radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        if (digit < 0 || digit >= radix) return 0;

        if (temp > (PX_U16_MAX - digit) / radix)
            return 0;

        temp = temp * radix + digit;
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxU32FromString16(pxu32* self, pxuword radix, PxFormatOption options, PxString16 string)
{
    pxiword index = 0;
    pxu32   temp  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS: {
            if ((options & PX_FORMAT_OPTION_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((options & PX_FORMAT_OPTION_LEADING_ZERO) == 0) {
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiValueFromDigit(string.memory[index], radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        if (digit < 0 || digit >= radix) return 0;

        if (temp > (PX_U32_MAX - digit) / radix)
            return 0;

        temp = temp * radix + digit;
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxU64FromString16(pxu64* self, pxuword radix, PxFormatOption options, PxString16 string)
{
    pxiword index = 0;
    pxu64   temp  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS: {
            if ((options & PX_FORMAT_OPTION_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((options & PX_FORMAT_OPTION_LEADING_ZERO) == 0) {
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiValueFromDigit(string.memory[index], radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        if (digit < 0 || digit >= radix) return 0;

        if (temp > (PX_U64_MAX - digit) / radix)
            return 0;

        temp = temp * radix + digit;
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxUWordFromString16(pxuword* self, pxuword radix, PxFormatOption options, PxString16 string)
{
    pxiword index = 0;
    pxuword temp  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS: {
            if ((options & PX_FORMAT_OPTION_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((options & PX_FORMAT_OPTION_LEADING_ZERO) == 0) {
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiValueFromDigit(string.memory[index], radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        if (digit < 0 || digit >= radix) return 0;

        if (temp > (PX_UWORD_MAX - digit) / radix)
            return 0;

        temp = temp * radix + digit;
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxI8FromString16(pxi8* self, pxuword radix, PxFormatOption options, PxString16 string)
{
    pxiword index = 0;
    pxi8    temp  = 0;
    pxb8    sign  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS: {
            if ((options & PX_FORMAT_OPTION_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case PX_ASCII_MINUS: {
            index += 1;
            sign   = 1;
        } break;

        default: break;
    }

    if ((options & PX_FORMAT_OPTION_LEADING_ZERO) == 0) {
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiValueFromDigit(string.memory[index], radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        if (digit < 0 || digit >= radix) return 0;

        switch (sign) {
            case 0: {
                if (temp > (PX_I8_MAX - digit) / pxCast(pxiword, radix))
                    return 0;

                temp = temp * radix + digit;
            } break;

            case 1: {
                if (temp < (PX_I8_MIN + digit) / pxCast(pxiword, radix))
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
pxI16FromString16(pxi16* self, pxuword radix, PxFormatOption options, PxString16 string)
{
    pxiword index = 0;
    pxi16   temp  = 0;
    pxb8    sign  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS: {
            if ((options & PX_FORMAT_OPTION_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case PX_ASCII_MINUS: {
            index += 1;
            sign   = 1;
        } break;

        default: break;
    }

    if ((options & PX_FORMAT_OPTION_LEADING_ZERO) == 0) {
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiValueFromDigit(string.memory[index], radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        if (digit < 0 || digit >= radix) return 0;

        switch (sign) {
            case 0: {
                if (temp > (PX_I16_MAX - digit) / pxCast(pxiword, radix))
                    return 0;

                temp = temp * radix + digit;
            } break;

            case 1: {
                if (temp < (PX_I16_MIN + digit) / pxCast(pxiword, radix))
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
pxI32FromString16(pxi32* self, pxuword radix, PxFormatOption options, PxString16 string)
{
    pxiword index = 0;
    pxi32   temp  = 0;
    pxb8    sign  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS: {
            if ((options & PX_FORMAT_OPTION_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case PX_ASCII_MINUS: {
            index += 1;
            sign   = 1;
        } break;

        default: break;
    }

    if ((options & PX_FORMAT_OPTION_LEADING_ZERO) == 0) {
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiValueFromDigit(string.memory[index], radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        if (digit < 0 || digit >= radix) return 0;

        switch (sign) {
            case 0: {
                if (temp > (PX_I32_MAX - digit) / pxCast(pxiword, radix))
                    return 0;

                temp = temp * radix + digit;
            } break;

            case 1: {
                if (temp < (PX_I32_MIN + digit) / pxCast(pxiword, radix))
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
pxI64FromString16(pxi64* self, pxuword radix, PxFormatOption options, PxString16 string)
{
    pxiword index = 0;
    pxi64   temp  = 0;
    pxb8    sign  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS: {
            if ((options & PX_FORMAT_OPTION_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case PX_ASCII_MINUS: {
            index += 1;
            sign   = 1;
        } break;

        default: break;
    }

    if ((options & PX_FORMAT_OPTION_LEADING_ZERO) == 0) {
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiValueFromDigit(string.memory[index], radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        if (digit < 0 || digit >= radix) return 0;

        switch (sign) {
            case 0: {
                if (temp > (PX_I64_MAX - digit) / pxCast(pxiword, radix))
                    return 0;

                temp = temp * radix + digit;
            } break;

            case 1: {
                if (temp < (PX_I64_MIN + digit) / pxCast(pxiword, radix))
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
pxIWordFromString16(pxiword* self, pxuword radix, PxFormatOption options, PxString16 string)
{
    pxiword index = 0;
    pxiword temp  = 0;
    pxb8    sign  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS: {
            if ((options & PX_FORMAT_OPTION_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case PX_ASCII_MINUS: {
            index += 1;
            sign   = 1;
        } break;

        default: break;
    }

    if ((options & PX_FORMAT_OPTION_LEADING_ZERO) == 0) {
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiValueFromDigit(string.memory[index], radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        if (digit < 0 || digit >= radix) return 0;

        switch (sign) {
            case 0: {
                if (temp > (PX_IWORD_MAX - digit) / pxCast(pxiword, radix))
                    return 0;

                temp = temp * radix + digit;
            } break;

            case 1: {
                if (temp < (PX_IWORD_MIN + digit) / pxCast(pxiword, radix))
                    return 0;

                temp = temp * radix - digit;
            } break;

            default: return 0;
        }
    }

    if (self != 0) *self = temp;

    return 1;
}

#endif // PX_FORMAT_STRING16_C
