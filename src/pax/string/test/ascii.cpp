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

int
main()
{
    static const u32 CODEPOINTS[18] = {
        ASCII_SLASH,
        ASCII_ZERO,
        ASCII_ONE,
        ASCII_TWO,
        ASCII_THREE,
        ASCII_FOUR,
        ASCII_FIVE,
        ASCII_SIX,
        ASCII_SEVEN,
        ASCII_EIGHT,
        ASCII_NINE,
        ASCII_UPPER_A,
        ASCII_UPPER_B,
        ASCII_UPPER_C,
        ASCII_UPPER_D,
        ASCII_UPPER_E,
        ASCII_UPPER_F,
        ASCII_UPPER_G,
    };

    for (uptr i = 0; i <= 16; i += 1) {
        printf("base = %3llu: { ", i);

        for (uptr j = 0; j < pax_array_length(CODEPOINTS); j += 1)
            printf("%s ", digit_from_ascii(CODEPOINTS[j], i) < i ? TRUE : FALSE);

        printf("}\n");
    }
}
