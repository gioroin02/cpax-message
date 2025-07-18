#include "../exports.hpp"

using namespace pax;

#include <stdio.h>

#define RED(str) "\x1b[31m" str "\x1b[0m"
#define GRN(str) "\x1b[32m" str "\x1b[0m"
#define YLW(str) "\x1b[33m" str "\x1b[0m"
#define BLU(str) "\x1b[34m" str "\x1b[0m"
#define PRP(str) "\x1b[35m" str "\x1b[0m"
#define AZR(str) "\x1b[36m" str "\x1b[0m"

#define TRUE  GRN("T")
#define FALSE RED("F")

void
show_i64_from_str8(Format_Options opts, str8 string)
{
    i64 value = 0;
    b32 state = i64_from_str8(string, opts, &value);

    printf("i64(" PRP("'%24.*s'") ") -> %s | %lli\n",
        pax_cast(int, string.length), string.memory,
        state ? TRUE : FALSE, value);
}

void
show_i32_from_str8(Format_Options opts, str8 string)
{
    i32 value = 0;
    b32 state = i32_from_str8(string, opts, &value);

    printf("i32(" PRP("'%24.*s'") ") -> %s | %i\n",
        pax_cast(int, string.length), string.memory,
        state ? TRUE : FALSE, value);
}

void
show_i16_from_str8(Format_Options opts, str8 string)
{
    i16 value = 0;
    b32 state = i16_from_str8(string, opts, &value);

    printf("i16(" PRP("'%24.*s'") ") -> %s | %i\n",
        pax_cast(int, string.length), string.memory,
        state ? TRUE : FALSE, value);
}

void
show_i8_from_str8(Format_Options opts, str8 string)
{
    i8  value = 0;
    b32 state = i8_from_str8(string, opts, &value);

    printf("i8(" PRP("'%24.*s'") ") -> %s | %i\n",
        pax_cast(int, string.length), string.memory,
        state ? TRUE : FALSE, value);
}

void
show_str8_from_i8(Arena* arena, Format_Options opts, i8 value)
{
    str8 string = str8_from_i8(arena, opts, value);

    printf("str8(%i) -> " PRP("'%24.*s'") "\n",
        value, pax_cast(int, string.length), string.memory);
}

int
main()
{
    u8 memory[MEMORY_KIB] = {};

    Arena arena = pax_arena(memory);

    Format_Options opts = format_options(10, FORMAT_FLAG_LEADING_ZERO |
        FORMAT_FLAG_LEADING_PLUS);

    show_i64_from_str8(opts, pax_str8("1"));
    show_i64_from_str8(opts, pax_str8("+1"));
    show_i64_from_str8(opts, pax_str8("0"));
    show_i64_from_str8(opts, pax_str8("+0"));
    show_i64_from_str8(opts, pax_str8("127"));
    show_i64_from_str8(opts, pax_str8("128"));
    show_i64_from_str8(opts, pax_str8("-128"));
    show_i64_from_str8(opts, pax_str8("-129"));
    show_i64_from_str8(opts, pax_str8("32767"));
    show_i64_from_str8(opts, pax_str8("32768"));
    show_i64_from_str8(opts, pax_str8("-32768"));
    show_i64_from_str8(opts, pax_str8("-32769"));
    show_i64_from_str8(opts, pax_str8("2147483647"));
    show_i64_from_str8(opts, pax_str8("2147483648"));
    show_i64_from_str8(opts, pax_str8("-2147483648"));
    show_i64_from_str8(opts, pax_str8("-2147483649"));
    show_i64_from_str8(opts, pax_str8("9223372036854775807"));
    show_i64_from_str8(opts, pax_str8("9223372036854775808"));
    show_i64_from_str8(opts, pax_str8("-9223372036854775808"));
    show_i64_from_str8(opts, pax_str8("-9223372036854775809"));
    show_i64_from_str8(opts, pax_str8("-150"));

    printf("\n");

    show_i32_from_str8(opts, pax_str8("1"));
    show_i32_from_str8(opts, pax_str8("+1"));
    show_i32_from_str8(opts, pax_str8("0"));
    show_i32_from_str8(opts, pax_str8("+0"));
    show_i32_from_str8(opts, pax_str8("127"));
    show_i32_from_str8(opts, pax_str8("128"));
    show_i32_from_str8(opts, pax_str8("-128"));
    show_i32_from_str8(opts, pax_str8("-129"));
    show_i32_from_str8(opts, pax_str8("32767"));
    show_i32_from_str8(opts, pax_str8("32768"));
    show_i32_from_str8(opts, pax_str8("-32768"));
    show_i32_from_str8(opts, pax_str8("-32769"));
    show_i32_from_str8(opts, pax_str8("2147483647"));
    show_i32_from_str8(opts, pax_str8("2147483648"));
    show_i32_from_str8(opts, pax_str8("-2147483648"));
    show_i32_from_str8(opts, pax_str8("-2147483649"));
    show_i32_from_str8(opts, pax_str8("9223372036854775807"));
    show_i32_from_str8(opts, pax_str8("9223372036854775808"));
    show_i32_from_str8(opts, pax_str8("-9223372036854775808"));
    show_i32_from_str8(opts, pax_str8("-9223372036854775809"));
    show_i32_from_str8(opts, pax_str8("-150"));

    printf("\n");

    show_i16_from_str8(opts, pax_str8("1"));
    show_i16_from_str8(opts, pax_str8("+1"));
    show_i16_from_str8(opts, pax_str8("0"));
    show_i16_from_str8(opts, pax_str8("+0"));
    show_i16_from_str8(opts, pax_str8("127"));
    show_i16_from_str8(opts, pax_str8("128"));
    show_i16_from_str8(opts, pax_str8("-128"));
    show_i16_from_str8(opts, pax_str8("-129"));
    show_i16_from_str8(opts, pax_str8("32767"));
    show_i16_from_str8(opts, pax_str8("32768"));
    show_i16_from_str8(opts, pax_str8("-32768"));
    show_i16_from_str8(opts, pax_str8("-32769"));
    show_i16_from_str8(opts, pax_str8("2147483647"));
    show_i16_from_str8(opts, pax_str8("2147483648"));
    show_i16_from_str8(opts, pax_str8("-2147483648"));
    show_i16_from_str8(opts, pax_str8("-2147483649"));
    show_i16_from_str8(opts, pax_str8("9223372036854775807"));
    show_i16_from_str8(opts, pax_str8("9223372036854775808"));
    show_i16_from_str8(opts, pax_str8("-9223372036854775808"));
    show_i16_from_str8(opts, pax_str8("-9223372036854775809"));
    show_i16_from_str8(opts, pax_str8("-150"));

    printf("\n");

    show_i8_from_str8(opts, pax_str8("1"));
    show_i8_from_str8(opts, pax_str8("+1"));
    show_i8_from_str8(opts, pax_str8("0"));
    show_i8_from_str8(opts, pax_str8("+0"));
    show_i8_from_str8(opts, pax_str8("127"));
    show_i8_from_str8(opts, pax_str8("128"));
    show_i8_from_str8(opts, pax_str8("-128"));
    show_i8_from_str8(opts, pax_str8("-129"));
    show_i8_from_str8(opts, pax_str8("32767"));
    show_i8_from_str8(opts, pax_str8("32768"));
    show_i8_from_str8(opts, pax_str8("-32768"));
    show_i8_from_str8(opts, pax_str8("-32769"));
    show_i8_from_str8(opts, pax_str8("2147483647"));
    show_i8_from_str8(opts, pax_str8("2147483648"));
    show_i8_from_str8(opts, pax_str8("-2147483648"));
    show_i8_from_str8(opts, pax_str8("-2147483649"));
    show_i8_from_str8(opts, pax_str8("9223372036854775807"));
    show_i8_from_str8(opts, pax_str8("9223372036854775808"));
    show_i8_from_str8(opts, pax_str8("-9223372036854775808"));
    show_i8_from_str8(opts, pax_str8("-9223372036854775809"));
    show_i8_from_str8(opts, pax_str8("-150"));

    printf("\n");

    opts = format_options(2, FORMAT_FLAG_LEADING_ZERO |
        FORMAT_FLAG_LEADING_PLUS);

    show_i8_from_str8(opts, pax_str8("1101"));
    show_i8_from_str8(opts, pax_str8("01111111"));
    show_i8_from_str8(opts, pax_str8("10000000"));
    show_i8_from_str8(opts, pax_str8("-10000000"));
    show_i8_from_str8(opts, pax_str8("-10000001"));

    printf("\n");

    show_str8_from_i8(&arena, format_options(10, FORMAT_FLAG_NONE), 5);
    show_str8_from_i8(&arena, format_options(2,  FORMAT_FLAG_NONE), 5);
    show_str8_from_i8(&arena, format_options(10, FORMAT_FLAG_NONE), -128);
    show_str8_from_i8(&arena, format_options(10, FORMAT_FLAG_NONE), -64);
    show_str8_from_i8(&arena, format_options(16, FORMAT_FLAG_NONE), -128);
}
