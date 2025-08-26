#ifndef PX_FORMAT_OPTIONS_C
#define PX_FORMAT_OPTIONS_C

#include "options.h"

PxFormatOptions
pxFormatOptionsRadix(pxu8 radix)
{
    return (PxFormatOptions) {
        .radix = radix
    };
}

PxFormatOptions
pxFormatOptions(pxu8 radix, PxFormatFlag flags)
{
    if (flags < 0)
        return (PxFormatOptions) {0};

    return (PxFormatOptions) {
        .flags = flags,
        .radix = radix,
    };
}

#endif // PX_FORMAT_OPTIONS_C
