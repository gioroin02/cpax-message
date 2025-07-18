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
show_str8(str8 string)
{
    uptr index = 0;
    uptr units = 0;
    u32  value = 0;

    printf("str8 forward:\n");

    while (str8_next(string, index, &units, &value) != 0) {
        printf("%2lli: %6x ", index, value);

        for (uptr i = 0; i < units; i += 1)
            printf("[%02x] ", string.memory[i + index]);

        printf("\n");

        index += units;
    }

    printf("\nstr8 backward:\n");

    index = string.length - 1;

    while (str8_prev(string, index, &units, &value) != 0) {
        printf("%2lli: %6x ", index, value);

        index -= units;

        for (uptr i = 0; i < units; i += 1)
            printf("[%02x] ", string.memory[i + index + 1]);

        printf("\n");
    }
}

void
show_str16(str16 string)
{
    uptr index = 0;
    uptr units = 0;
    u32  value = 0;

    printf("str16 forward:\n");

    while (str16_next(string, index, &units, &value) != 0) {
        printf("%2lli: %6x ", index, value);

        for (uptr i = 0; i < units; i += 1)
            printf("[%04x] ", string.memory[i + index]);

        printf("\n");

        index += units;
    }

    printf("\nstr16 backward:\n");

    index = string.length - 1;

    while (str16_prev(string, index, &units, &value) != 0) {
        printf("%2lli: %6x ", index, value);

        index -= units;

        for (uptr i = 0; i < units; i += 1)
            printf("[%04x] ", string.memory[i + index + 1]);

        printf("\n");
    }
}

int
main()
{
    u8 memory[2 * MEMORY_KIB] = {};

    Arena arena = arena_make(memory, pax_array_bytes(memory));

    str8  str1 = str8_from_unicode(&arena, 0x1f600);
    str16 str2 = str16_from_str8(&arena, pax_str8("prova"));

    show_str8(str1);

    printf("\n");

    str8 str3 = str8_slice_until_last(pax_str8("prova"), pax_str8("o"));

    show_str8(str3);

    printf("\n");

    str8 str4 = str8_slice_since_last(pax_str8("prova"), pax_str8("o"));

    show_str8(str4);

    printf("\n");

    show_str16(str2);
}
