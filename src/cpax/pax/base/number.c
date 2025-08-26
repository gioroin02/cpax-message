#ifndef PX_BASE_NUMBER_C
#define PX_BASE_NUMBER_C

#include "number.h"

pxu8
pxMagnitudeI8(pxi8 value)
{
    if (value < 0)
        return -pxCast(pxu8, value);

    return pxCast(pxu8, value);
}

pxu16
pxMagnitudeI16(pxi16 value)
{
    if (value < 0)
        return -pxCast(pxu16, value);

    return pxCast(pxu16, value);
}

pxu32
pxMagnitudeI32(pxi32 value)
{
    if (value < 0)
        return -pxCast(pxu32, value);

    return pxCast(pxu32, value);
}

pxu64
pxMagnitudeI64(pxi64 value)
{
    if (value < 0)
        return -pxCast(pxu64, value);

    return pxCast(pxu64, value);
}

pxuword
pxMagnitudeIWord(pxiword value)
{
    if (value < 0)
        return -pxCast(pxuword, value);

    return pxCast(pxuword, value);
}

pxf32
pxMagnitudeF32(pxf32 value)
{
    pxu32* bits =
        pxCast(pxu32*, &value);

    *bits &= ~PX_F32_SIGN_MASK;

    return value;
}

pxf64
pxMagnitudeF64(pxf64 value)
{
    pxu64* bits =
        pxCast(pxu64*, &value);

    *bits &= ~PX_F64_SIGN_MASK;

    return value;
}

pxfword
pxMagnitudeFWord(pxfword value)
{
    pxuword* bits =
        pxCast(pxuword*, &value);

    *bits &= ~PX_FWORD_SIGN_MASK;

    return value;
}

pxi8
pxDirectionI8(pxi8 value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

pxi8
pxDirectionI16(pxi16 value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

pxi8
pxDirectionI32(pxi32 value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

pxi8
pxDirectionI64(pxi64 value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

pxi8
pxDirectionIWord(pxiword value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

pxi8
pxDirectionF32(pxf32 value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

pxi8
pxDirectionF64(pxf64 value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

pxi8
pxDirectionFWord(pxfword value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

#endif // PX_BASE_NUMBER_C
