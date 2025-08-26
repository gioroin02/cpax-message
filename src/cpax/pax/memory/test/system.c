#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    printf("%p, %lli, %lli\n", arena.memory,
        arena.length, arena.offset);

    pxMemoryRelease(&arena);
}
