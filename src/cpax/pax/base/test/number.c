#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    pxi8  dir0 = pxDirectionF32(-1.56);
    pxf32 mag0 = pxMagnitudeF32(-1.56);

    printf("dir, mag = %i, %f\n", dir0, mag0);

    pxi8  dir1 = pxDirectionF32(+1.56);
    pxf32 mag1 = pxMagnitudeF32(+1.56);

    printf("dir, mag = %i, %f\n", dir1, mag1);

    pxi8  dir2 = pxDirectionF32(0);
    pxf32 mag2 = pxMagnitudeF32(0);

    printf("dir, mag = %i, %f\n", dir2, mag2);
}
