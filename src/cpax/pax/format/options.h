#ifndef PX_FORMAT_OPTIONS_H
#define PX_FORMAT_OPTIONS_H

#include "import.h"

typedef enum PxFormatFlag
{
    PX_FORMAT_FLAG_NONE         = 0x0,
    PX_FORMAT_FLAG_LEADING_ZERO = 0x1,
    PX_FORMAT_FLAG_LEADING_PLUS = 0x2,
    PX_FORMAT_FLAG_UPPER_CASE   = 0x4,
}
PxFormatFlag;

typedef struct PxFormatOptions
{
    PxFormatFlag flags;
    pxu8         radix;
}
PxFormatOptions;

PxFormatOptions
pxFormatOptionsRadix(pxu8 radix);

PxFormatOptions
pxFormatOptions(pxu8 radix, PxFormatFlag flags);

#endif // PX_FORMAT_OPTIONS_H
