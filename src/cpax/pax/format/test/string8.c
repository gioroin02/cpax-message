#include "../export.h"

#include <stdio.h>

#define RED(x)    "\x1b[31m" pxString(x) "\x1b[0m"
#define GREEN(x)  "\x1b[32m" pxString(x) "\x1b[0m"
#define YELLOW(x) "\x1b[33m" pxString(x) "\x1b[0m"
#define BLUE(x)   "\x1b[34m" pxString(x) "\x1b[0m"
#define PURPLE(x) "\x1b[35m" pxString(x) "\x1b[0m"
#define AZURE(x)  "\x1b[36m" pxString(x) "\x1b[0m"

#define TRUE  GREEN(T)
#define FALSE RED(F)

void
showString8FromUWord(PxArena* arena, pxuword radix, PxFormatOption options, pxuword value)
{
    PxString8 string = pxString8FromUWord(arena, radix, options, value);

    printf("write (" PURPLE("%llu") ") -> ", value);

    printf("\x1b[34m'");

    for (pxiword i = 0; i < string.length; i += 1)
        printf("%c", string.memory[i]);

    printf("'\x1b[0m (%lli)\n", string.length);
}

void
showUWordFromString8(pxuword radix, PxFormatOption options, PxString8 value)
{
    pxuword result = 0;
    pxb8    state  = pxUWordFromString8(&result, radix, options, value);

    printf("read (\x1b[34m'");

    for (pxiword i = 0; i < value.length; i += 1)
        printf("%c", value.memory[i]);

    printf("'\x1b[0m (%lli))", value.length);


    printf(" -> (" PURPLE("%llu") ", %s)\n", result,
        state != 0 ? TRUE : FALSE);
}

void
showString8FromIWord(PxArena* arena, pxuword radix, PxFormatOption options, pxiword value)
{
    PxString8 string = pxString8FromIWord(arena, radix, options, value);

    printf("write (" PURPLE("%lli") ") -> ", value);

    printf("\x1b[34m'");

    for (pxiword i = 0; i < string.length; i += 1)
        printf("%c", string.memory[i]);

    printf("'\x1b[0m (%lli)\n", string.length);
}

void
showIWordFromString8(pxuword radix, PxFormatOption options, PxString8 value)
{
    pxiword result = 0;
    pxb8    state  = pxIWordFromString8(&result, radix, options, value);

    printf("read (\x1b[34m'");

    for (pxiword i = 0; i < value.length; i += 1)
        printf("%c", value.memory[i]);

    printf("'\x1b[0m (%lli))", value.length);


    printf(" -> (" PURPLE("%lli") ", %s)\n", result,
        state != 0 ? TRUE : FALSE);
}

static pxu8 memory[PX_MEMORY_KIB] = {};

int
main(int argc, char** argv)
{
    PxArena arena = pxArenaMake(memory, PX_MEMORY_KIB);

    #define OPTIONS 5
    #define STRINGS 6

    pxuword radices[OPTIONS] = {
        10,
        10,
        2,
        8,
        16,
    };

    PxFormatOption options[OPTIONS] = {
        PX_FORMAT_OPTION_NONE,
        PX_FORMAT_OPTION_LEADING_ZERO | PX_FORMAT_OPTION_LEADING_PLUS,
        PX_FORMAT_OPTION_LEADING_PLUS,
        PX_FORMAT_OPTION_NONE,
        PX_FORMAT_OPTION_UPPER_CASE,
    };

    PxString8 strings[STRINGS] = {
        pxs8("0"),
        pxs8("1"),
        pxs8("-1"),
        pxs8("18446744073709551615"),
        pxs8("9223372036854775807"),
        pxs8("-9223372036854775808"),
    };

    for (pxiword i = 0; i < OPTIONS; i += 1) {
        printf("UWord:\n");

        showString8FromUWord(&arena, radices[i], options[i], 255);
        showString8FromUWord(&arena, radices[i], options[i], 0);

        printf("\nIWord:\n");

        showString8FromIWord(&arena, radices[i], options[i], 255);
        showString8FromIWord(&arena, radices[i], options[i], 0);
        showString8FromIWord(&arena, radices[i], options[i], -256);

        if (i + 1 != OPTIONS)
            printf("\n");
    }

    for (pxiword i = 0; i < OPTIONS; i += 1) {
        for (pxiword j = 0; j < STRINGS; j += 1) {
            printf("UWord:\n");

            showUWordFromString8(radices[i], options[i], strings[j]);

            printf("IWord:\n");

            showIWordFromString8(radices[i], options[i], strings[j]);
        }

        printf("\n");
    }
}
