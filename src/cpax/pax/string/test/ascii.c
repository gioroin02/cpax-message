#include "../export.h"

#include <stdio.h>

#define RED(x)    "\x1b[31m" pxString(x) "\x1b[0m"
#define GREEN(x)  "\x1b[32m" pxString(x) "\x1b[0m"
#define YELLOW(x) "\x1b[33m" pxString(x) "\x1b[0m"
#define BLUE(x)   "\x1b[34m" pxString(x) "\x1b[0m"
#define PURPLE(x) "\x1b[35m" pxString(x) "\x1b[0m"
#define AZURE(x)  "\x1b[36m" pxString(x) "\x1b[0m"

#define TRUE  GREEN("T")
#define FALSE RED("F")

#define ASCII_COUNT 128

static const PxString8 ASCII_NAMES[ASCII_COUNT] = {
    pxs8(pxString(PX_ASCII_NULL)),
    pxs8(pxString(PX_ASCII_1)),
    pxs8(pxString(PX_ASCII_2)),
    pxs8(pxString(PX_ASCII_3)),
    pxs8(pxString(PX_ASCII_4)),
    pxs8(pxString(PX_ASCII_5)),
    pxs8(pxString(PX_ASCII_6)),
    pxs8(pxString(PX_ASCII_7)),
    pxs8(pxString(PX_ASCII_BACK_SPACE)),
    pxs8(pxString(PX_ASCII_HORIZONTAL_TAB)),
    pxs8(pxString(PX_ASCII_LINE_FEED)),
    pxs8(pxString(PX_ASCII_VERTICAL_TAB)),
    pxs8(pxString(PX_ASCII_PAGE_FEED)),
    pxs8(pxString(PX_ASCII_CARRIAGE_RETURN)),
    pxs8(pxString(PX_ASCII_14)),
    pxs8(pxString(PX_ASCII_15)),
    pxs8(pxString(PX_ASCII_16)),
    pxs8(pxString(PX_ASCII_17)),
    pxs8(pxString(PX_ASCII_18)),
    pxs8(pxString(PX_ASCII_19)),
    pxs8(pxString(PX_ASCII_20)),
    pxs8(pxString(PX_ASCII_21)),
    pxs8(pxString(PX_ASCII_22)),
    pxs8(pxString(PX_ASCII_23)),
    pxs8(pxString(PX_ASCII_CANCEL)),
    pxs8(pxString(PX_ASCII_25)),
    pxs8(pxString(PX_ASCII_26)),
    pxs8(pxString(PX_ASCII_ESCAPE)),
    pxs8(pxString(PX_ASCII_28)),
    pxs8(pxString(PX_ASCII_29)),
    pxs8(pxString(PX_ASCII_30)),
    pxs8(pxString(PX_ASCII_31)),
    pxs8(pxString(PX_ASCII_SPACE)),
    pxs8(pxString(PX_ASCII_EXCLAMATION)),
    pxs8(pxString(PX_ASCII_QUOTE)),
    pxs8(pxString(PX_ASCII_SHARP)),
    pxs8(pxString(PX_ASCII_DOLLAR)),
    pxs8(pxString(PX_ASCII_PERCENT)),
    pxs8(pxString(PX_ASCII_AMPERSAND)),
    pxs8(pxString(PX_ASCII_APOSTROPHE)),
    pxs8(pxString(PX_ASCII_PAREN_LEFT)),
    pxs8(pxString(PX_ASCII_PAREN_RIGHT)),
    pxs8(pxString(PX_ASCII_ASTERISK)),
    pxs8(pxString(PX_ASCII_PLUS)),
    pxs8(pxString(PX_ASCII_COMMA)),
    pxs8(pxString(PX_ASCII_MINUS)),
    pxs8(pxString(PX_ASCII_POINT)),
    pxs8(pxString(PX_ASCII_SLASH)),
    pxs8(pxString(PX_ASCII_ZERO)),
    pxs8(pxString(PX_ASCII_ONE)),
    pxs8(pxString(PX_ASCII_TWO)),
    pxs8(pxString(PX_ASCII_THREE)),
    pxs8(pxString(PX_ASCII_FOUR)),
    pxs8(pxString(PX_ASCII_FIVE)),
    pxs8(pxString(PX_ASCII_SIX)),
    pxs8(pxString(PX_ASCII_SEVEN)),
    pxs8(pxString(PX_ASCII_EIGHT)),
    pxs8(pxString(PX_ASCII_NINE)),
    pxs8(pxString(PX_ASCII_COLON)),
    pxs8(pxString(PX_ASCII_SEMI_COLON)),
    pxs8(pxString(PX_ASCII_LESS)),
    pxs8(pxString(PX_ASCII_EQUAL)),
    pxs8(pxString(PX_ASCII_MORE)),
    pxs8(pxString(PX_ASCII_QUESTION)),
    pxs8(pxString(PX_ASCII_COMMERCIAL)),
    pxs8(pxString(PX_ASCII_UPPER_A)),
    pxs8(pxString(PX_ASCII_UPPER_B)),
    pxs8(pxString(PX_ASCII_UPPER_C)),
    pxs8(pxString(PX_ASCII_UPPER_D)),
    pxs8(pxString(PX_ASCII_UPPER_E)),
    pxs8(pxString(PX_ASCII_UPPER_F)),
    pxs8(pxString(PX_ASCII_UPPER_G)),
    pxs8(pxString(PX_ASCII_UPPER_H)),
    pxs8(pxString(PX_ASCII_UPPER_I)),
    pxs8(pxString(PX_ASCII_UPPER_J)),
    pxs8(pxString(PX_ASCII_UPPER_K)),
    pxs8(pxString(PX_ASCII_UPPER_L)),
    pxs8(pxString(PX_ASCII_UPPER_M)),
    pxs8(pxString(PX_ASCII_UPPER_N)),
    pxs8(pxString(PX_ASCII_UPPER_O)),
    pxs8(pxString(PX_ASCII_UPPER_P)),
    pxs8(pxString(PX_ASCII_UPPER_Q)),
    pxs8(pxString(PX_ASCII_UPPER_R)),
    pxs8(pxString(PX_ASCII_UPPER_S)),
    pxs8(pxString(PX_ASCII_UPPER_T)),
    pxs8(pxString(PX_ASCII_UPPER_U)),
    pxs8(pxString(PX_ASCII_UPPER_V)),
    pxs8(pxString(PX_ASCII_UPPER_W)),
    pxs8(pxString(PX_ASCII_UPPER_X)),
    pxs8(pxString(PX_ASCII_UPPER_Y)),
    pxs8(pxString(PX_ASCII_UPPER_Z)),
    pxs8(pxString(PX_ASCII_SQUARE_LEFT)),
    pxs8(pxString(PX_ASCII_BACK_SLASH)),
    pxs8(pxString(PX_ASCII_SQUARE_RIGHT)),
    pxs8(pxString(PX_ASCII_CIRCUMFLEX)),
    pxs8(pxString(PX_ASCII_UNDER_SCORE)),
    pxs8(pxString(PX_ASCII_BACK_TICK)),
    pxs8(pxString(PX_ASCII_LOWER_A)),
    pxs8(pxString(PX_ASCII_LOWER_B)),
    pxs8(pxString(PX_ASCII_LOWER_C)),
    pxs8(pxString(PX_ASCII_LOWER_D)),
    pxs8(pxString(PX_ASCII_LOWER_E)),
    pxs8(pxString(PX_ASCII_LOWER_F)),
    pxs8(pxString(PX_ASCII_LOWER_G)),
    pxs8(pxString(PX_ASCII_LOWER_H)),
    pxs8(pxString(PX_ASCII_LOWER_I)),
    pxs8(pxString(PX_ASCII_LOWER_J)),
    pxs8(pxString(PX_ASCII_LOWER_K)),
    pxs8(pxString(PX_ASCII_LOWER_L)),
    pxs8(pxString(PX_ASCII_LOWER_M)),
    pxs8(pxString(PX_ASCII_LOWER_N)),
    pxs8(pxString(PX_ASCII_LOWER_O)),
    pxs8(pxString(PX_ASCII_LOWER_P)),
    pxs8(pxString(PX_ASCII_LOWER_Q)),
    pxs8(pxString(PX_ASCII_LOWER_R)),
    pxs8(pxString(PX_ASCII_LOWER_S)),
    pxs8(pxString(PX_ASCII_LOWER_T)),
    pxs8(pxString(PX_ASCII_LOWER_U)),
    pxs8(pxString(PX_ASCII_LOWER_V)),
    pxs8(pxString(PX_ASCII_LOWER_W)),
    pxs8(pxString(PX_ASCII_LOWER_X)),
    pxs8(pxString(PX_ASCII_LOWER_Y)),
    pxs8(pxString(PX_ASCII_LOWER_Z)),
    pxs8(pxString(PX_ASCII_BRACE_LEFT)),
    pxs8(pxString(PX_ASCII_PIPE)),
    pxs8(pxString(PX_ASCII_BRACE_RIGHT)),
    pxs8(pxString(PX_ASCII_TILDE)),
    pxs8(pxString(PX_ASCII_DELETE)),
};

void
showAsciiIsSpace()
{
    printf("Space:\n");

    for (pxiword i = 0; i < ASCII_COUNT; i += 1) {
        PxString8 name = ASCII_NAMES[i];

        if (pxAsciiIsSpace(i) != 0)
            printf("- %s\n", name.memory);
    }
}

void
showAsciiIsLetter()
{
    printf("Letter:\n");

    for (pxiword i = 0; i < ASCII_COUNT; i += 1) {
        PxString8 name = ASCII_NAMES[i];

        if (pxAsciiIsLetter(i) != 0)
            printf("- %s\n", name.memory);
    }
}

/*
void
show_ascii_index_from_letter()
{
    for (pxiword i = 0; i < ASCII_COUNT; i += 1) {
        PxString8 name   = ASCII_NAMES[i];
        pxiword letter = ascii_index_from_letter(i);

        if (letter != 26) {
            printf("- %.*s, %llu\n",
                pax_as_i32(name.length), name.memory, letter);
        }
    }
}

void
show_ascii_letter_from_index()
{
    for (pxiword i = 0; i < 26; i += 1) {
        pxiword lower = ascii_letter_from_index(i, 0);
        pxiword upper = ascii_letter_from_index(i, 1);

        printf("- %llu", i);

        if (lower != ASCII_NULL) printf(": %c", lower);
        if (upper != ASCII_NULL) printf(", %c", upper);

        printf("\n");
    }
}
*/

void
showAsciiIsLetterLower()
{
    printf("Lower:\n");

    for (pxiword i = 0; i < ASCII_COUNT; i += 1) {
        PxString8 name = ASCII_NAMES[i];

        if (pxAsciiIsLetterLower(i) != 0)
            printf("- %s\n", name.memory);
    }
}

/*
void
show_ascii_index_from_lower()
{
    for (pxiword i = 0; i < ASCII_COUNT; i += 1) {
        PxString8 name   = ASCII_NAMES[i];
        pxiword letter = ascii_index_from_lower(i);

        if (letter != 26) {
            printf("- %.*s, %llu\n",
                pax_as_i32(name.length), name.memory, letter);
        }
    }
}

void
show_ascii_lower_from_index()
{
    for (pxiword i = 0; i < 26; i += 1) {
        pxiword lower = ascii_lower_from_index(i);

        printf("- %llu", i);

        if (lower != ASCII_NULL)
            printf(": %c", lower);

        printf("\n");
    }
}
*/

void
showAsciiIsLetterUpper()
{
    printf("Upper:\n");

    for (pxiword i = 0; i < ASCII_COUNT; i += 1) {
        PxString8 name = ASCII_NAMES[i];

        if (pxAsciiIsLetterUpper(i) != 0)
            printf("- %s\n", name.memory);
    }
}

/*
void
show_ascii_index_from_upper()
{
    for (pxiword i = 0; i < ASCII_COUNT; i += 1) {
        PxString8 name   = ASCII_NAMES[i];
        pxiword letter = ascii_index_from_upper(i);

        if (letter != 26) {
            printf("- %.*s, %llu\n",
                pax_as_i32(name.length), name.memory, letter);
        }
    }
}

void
show_ascii_upper_from_index()
{
    for (pxiword i = 0; i < 26; i += 1) {
        pxiword upper = ascii_upper_from_index(i);

        printf("- %llu", i);

        if (upper != ASCII_NULL)
            printf(": %c", upper);

        printf("\n");
    }
}
*/

void
showAsciiIsNumeric()
{
    for (pxiword j = 2; j <= 16; j += 1) {
        printf("Numeric (%lli):\n", j);

        for (pxiword i = 0; i < ASCII_COUNT; i += 1) {
            PxString8 name = ASCII_NAMES[i];

            if (pxAsciiIsNumeric(i, j, 0) != 0 || pxAsciiIsNumeric(i, j, 1) != 0)
                printf("- %s\n", name.memory);
        }
    }
}

void
showAsciiIsDigit()
{
    for (pxiword j = 2; j <= 16; j += 1) {
        printf("Digit (%lli):\n", j);

        for (pxiword i = 0; i < ASCII_COUNT; i += 1) {
            PxString8 name = ASCII_NAMES[i];

            if (pxAsciiIsDigit(i, j, 0) != 0 || pxAsciiIsDigit(i, j, 1) != 0)
                printf("- %s\n", name.memory);
        }
    }
}

void
showAsciiValueFromDigit()
{
    for (pxiword j = 2; j <= 16; j += 1) {
        printf("Digit (%lli):\n", j);

        for (pxiword i = 0; i < ASCII_COUNT; i += 1) {
            PxString8 name  = ASCII_NAMES[i];
            pxiword   lower = pxAsciiValueFromDigit(i, j, 0);
            pxiword   upper = pxAsciiValueFromDigit(i, j, 1);

            if (lower != j || upper != j) {
                printf("- %s", name.memory);

                if (lower != j)
                    printf(", lower = %llu", lower);

                if (upper != j)
                    printf(", upper = %llu", upper);

                printf("\n");
            }
        }
    }
}

void
showAsciiDigitFromValue()
{
    for (pxiword j = 2; j <= 16; j += 1) {
        printf("Digit (%lli):\n", j);

        for (pxiword i = 0; i < j; i += 1) {
            pxi32 lower = pxAsciiDigitFromValue(i, j, 0);
            pxi32 upper = pxAsciiDigitFromValue(i, j, 1);

            if (lower != PX_ASCII_NULL || upper != PX_ASCII_NULL) {
                printf("- %llu", i);

                if (lower != PX_ASCII_NULL) {
                    printf(", lower = %li", lower);

                    if (pxUnicodeIsAscii(lower) != 0)
                        printf(" %c", pxCast(pxu8, lower));
                }

                if (upper != PX_ASCII_NULL) {
                    printf(", upper = %li", upper);

                    if (pxUnicodeIsAscii(upper) != 0)
                        printf(" %c", pxCast(pxu8, upper));
                }

                printf("\n");
            }
        }
    }
}

int
main()
{
    showAsciiIsSpace();

    showAsciiIsLetterLower();
    // show_ascii_index_from_lower();
    // show_ascii_lower_from_index();

    showAsciiIsLetterUpper();
    // show_ascii_index_from_upper();
    // show_ascii_upper_from_index();

    showAsciiIsLetter();
    // show_ascii_index_from_letter();
    // show_ascii_letter_from_index();

    showAsciiIsNumeric();

    showAsciiIsDigit();
    showAsciiValueFromDigit();
    showAsciiDigitFromValue();
}
