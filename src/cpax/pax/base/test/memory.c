#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    pxu8 memory[12] = {0};

    pxMemoryCopyFlipped(memory, "ciao", 2, 2);

    for (pxiword i = 0; i < 12; i += 1)
        printf("%03u ", memory[i]);
    printf("\n");

    printf("%s\n\n", memory);

    pxMemoryCopyForw(memory, 4, 4, 1);

    for (pxiword i = 0; i < 12; i += 1)
        printf("%03u ", memory[i]);
    printf("\n");

    printf("%s\n\n", memory);

    pxMemoryFlip(memory, 2, 2);

    for (pxiword i = 0; i < 12; i += 1)
        printf("%03u ", memory[i]);
    printf("\n");

    printf("%s\n\n", memory);

    pxMemoryCopyBack(memory + 2, 2, 2, 1);

    for (pxiword i = 0; i < 12; i += 1)
        printf("%03u ", memory[i]);
    printf("\n");

    printf("%s\n\n", memory);

    printf("equal = %u\n",
        pxMemoryIsEqual(memory, "ciao", 4, 1));
}
