#ifndef PX_FORMAT_OPTIONS_H
#define PX_FORMAT_OPTIONS_H

#include "import.h"

typedef enum PxFormatOption
{
    PX_FORMAT_OPTION_NONE         = 0x0,
    PX_FORMAT_OPTION_LEADING_ZERO = 0x1,
    PX_FORMAT_OPTION_LEADING_PLUS = 0x2,
    PX_FORMAT_OPTION_UPPER_CASE   = 0x4,
}
PxFormatOption;

#endif // PX_FORMAT_OPTIONS_H
