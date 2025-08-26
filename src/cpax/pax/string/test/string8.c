#include "../export.h"

#include <stdio.h>

void
showString8(PxString8 self)
{
    pxiword units = 0;
    pxiword index = 0;
    pxi32   value = 0;

    while (pxString8Next(self, index, &units, &value) != 0) {
        printf("[%lli] %8li", index, value);

        if (pxUnicodeIsAscii(value) != 0)
            printf(" (%c)", pxCast(pxi8, value));

        printf("\n");

        index += units;
    }
}

int
main(int argc, char** argv)
{
    pxu8 memory[PX_MEMORY_KIB] = {0};

    PxArena arena = pxArenaMake(memory, pxSize(memory));

    PxString8 str1 = pxString8Copy(&arena, pxs8("ciao"));
    PxString8 str2 = pxString8CopyUnicode(&arena, 0x1f600);

    showString8(str1);

    printf("\n");

    showString8(str2);
}
