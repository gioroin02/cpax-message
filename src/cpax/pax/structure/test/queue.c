#include "../export.h"
#include "../../memory/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);
    PxQueue queue = pxQueueReserve(&arena, pxi32, 8);

    pxi32 x = 5;
    pxi32 y = 0;

    pxQueueInsertHead(&queue, pxi32, &x);
    pxQueueCreateHead(&queue);
    pxQueueCreateHead(&queue);
    pxQueueCreateHead(&queue);

    for (pxiword i = 0; i < queue.size; i += 1) {
        pxi32 value = 0;

        pxQueueRead(&queue, i, pxi32, &value);

        printf("%li\n", value);
    }

    pxQueueRemoveTail(&queue, pxi32, &y);

    printf("\n");

    printf("remove = %li\n", y);

    printf("\n");

    for (pxiword i = 0; i < queue.size; i += 1) {
        pxi32 value = 0;

        pxQueueRead(&queue, i, pxi32, &value);

        printf("%li\n", value);
    }
}
