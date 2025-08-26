#include "../export.h"
#include "../../memory/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    PxFormatOptions options0 = pxFormatOptions(16,
        PX_FORMAT_FLAG_LEADING_PLUS | PX_FORMAT_FLAG_UPPER_CASE);

    PxFormatOptions options1 = pxFormatOptions(10, PX_FORMAT_FLAG_NONE);

    PxString8 string0 = pxString8FromI8(&arena, options0, 127);
    PxString8 string1 = pxString8FromI8(&arena, options0, -16);

    printf("%s\n", string0.memory);
    printf("%s\n", string1.memory);
}
