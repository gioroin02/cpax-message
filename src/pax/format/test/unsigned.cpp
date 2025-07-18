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
show_u64_from_str8(Format_Options opts, str8 string)
{
    u64 value = 0;
    b32 state = u64_from_str8(string, opts, &value);

    printf("u64(" PRP("'%24.*s'") ") -> %s | %llu\n",
        pax_cast(int, string.length), string.memory,
        state ? TRUE : FALSE, value);
}

void
show_u32_from_str8(Format_Options opts, str8 string)
{
    u32 value = 0;
    b32 state = u32_from_str8(string, opts, &value);

    printf("u32(" PRP("'%24.*s'") ") -> %s | %u\n",
        pax_cast(int, string.length), string.memory,
        state ? TRUE : FALSE, value);
}

void
show_u16_from_str8(Format_Options opts, str8 string)
{
    u16 value = 0;
    b32 state = u16_from_str8(string, opts, &value);

    printf("u16(" PRP("'%24.*s'") ") -> %s | %u\n",
        pax_cast(int, string.length), string.memory,
        state ? TRUE : FALSE, value);
}

void
show_u8_from_str8(Format_Options opts, str8 string)
{
    u8  value = 0;
    b32 state = u8_from_str8(string, opts, &value);

    printf("u8(" PRP("'%24.*s'") ") -> %s | %u\n",
        pax_cast(int, string.length), string.memory,
        state ? TRUE : FALSE, value);
}

void
show_str8_from_u8(Arena* arena, Format_Options opts, u8 value)
{
    str8 string = str8_from_u8(arena, opts, value);

    printf("str8(%u) -> " PRP("'%24.*s'") "\n",
        value, pax_cast(int, string.length), string.memory);
}

int
main()
{
    u8 memory[MEMORY_KIB] = {};

    Arena arena = pax_arena(memory);

    Format_Options opts = format_options(10, FORMAT_FLAG_LEADING_ZERO |
        FORMAT_FLAG_LEADING_PLUS);

    show_u64_from_str8(opts, pax_str8("1"));
    show_u64_from_str8(opts, pax_str8("+1"));
    show_u64_from_str8(opts, pax_str8("0"));
    show_u64_from_str8(opts, pax_str8("+0001"));
    show_u64_from_str8(opts, pax_str8("01"));
    show_u64_from_str8(opts, pax_str8("255"));
    show_u64_from_str8(opts, pax_str8("256"));
    show_u64_from_str8(opts, pax_str8("65535"));
    show_u64_from_str8(opts, pax_str8("65536"));
    show_u64_from_str8(opts, pax_str8("4294967295"));
    show_u64_from_str8(opts, pax_str8("4294967296"));
    show_u64_from_str8(opts, pax_str8("18446744073709551615"));
    show_u64_from_str8(opts, pax_str8("18446744073709551616"));
    show_u64_from_str8(opts, pax_str8("-150"));

    printf("\n");

    show_u32_from_str8(opts, pax_str8("1"));
    show_u32_from_str8(opts, pax_str8("+1"));
    show_u32_from_str8(opts, pax_str8("0"));
    show_u32_from_str8(opts, pax_str8("+0"));
    show_u32_from_str8(opts, pax_str8("255"));
    show_u32_from_str8(opts, pax_str8("256"));
    show_u32_from_str8(opts, pax_str8("65535"));
    show_u32_from_str8(opts, pax_str8("65536"));
    show_u32_from_str8(opts, pax_str8("4294967295"));
    show_u32_from_str8(opts, pax_str8("4294967296"));
    show_u32_from_str8(opts, pax_str8("18446744073709551615"));
    show_u32_from_str8(opts, pax_str8("18446744073709551616"));
    show_u32_from_str8(opts, pax_str8("-150"));

    printf("\n");

    show_u16_from_str8(opts, pax_str8("1"));
    show_u16_from_str8(opts, pax_str8("+1"));
    show_u16_from_str8(opts, pax_str8("0"));
    show_u16_from_str8(opts, pax_str8("+0"));
    show_u16_from_str8(opts, pax_str8("255"));
    show_u16_from_str8(opts, pax_str8("256"));
    show_u16_from_str8(opts, pax_str8("65535"));
    show_u16_from_str8(opts, pax_str8("65536"));
    show_u16_from_str8(opts, pax_str8("4294967295"));
    show_u16_from_str8(opts, pax_str8("4294967296"));
    show_u16_from_str8(opts, pax_str8("18446744073709551615"));
    show_u16_from_str8(opts, pax_str8("18446744073709551616"));
    show_u16_from_str8(opts, pax_str8("-150"));

    printf("\n");

    show_u8_from_str8(opts, pax_str8("1"));
    show_u8_from_str8(opts, pax_str8("+1"));
    show_u8_from_str8(opts, pax_str8("0"));
    show_u8_from_str8(opts, pax_str8("+0"));
    show_u8_from_str8(opts, pax_str8("255"));
    show_u8_from_str8(opts, pax_str8("256"));
    show_u8_from_str8(opts, pax_str8("65535"));
    show_u8_from_str8(opts, pax_str8("65536"));
    show_u8_from_str8(opts, pax_str8("4294967295"));
    show_u8_from_str8(opts, pax_str8("4294967296"));
    show_u8_from_str8(opts, pax_str8("18446744073709551615"));
    show_u8_from_str8(opts, pax_str8("18446744073709551616"));
    show_u8_from_str8(opts, pax_str8("-150"));

    printf("\n");

    opts = format_options(2, FORMAT_FLAG_LEADING_ZERO |
        FORMAT_FLAG_LEADING_PLUS);

    show_u8_from_str8(opts, pax_str8("1101"));
    show_u8_from_str8(opts, pax_str8("11111111"));
    show_u8_from_str8(opts, pax_str8("111111110"));

    printf("\n");

    show_str8_from_u8(&arena, format_options(10, FORMAT_FLAG_NONE), 5);
    show_str8_from_u8(&arena, format_options(2,  FORMAT_FLAG_NONE), 5);
    show_str8_from_u8(&arena, format_options(10, FORMAT_FLAG_NONE), 255);
    show_str8_from_u8(&arena, format_options(16, FORMAT_FLAG_NONE), 255);
}
