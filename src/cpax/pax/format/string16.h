#ifndef PX_FORMAT_STRING16_H
#define PX_FORMAT_STRING16_H

#include "options.h"

/* String from number */

PxString16
pxString16FromU8(PxArena* arena, PxFormatOptions options, pxu8 value);

PxString16
pxString16FromU16(PxArena* arena, PxFormatOptions options, pxu16 value);

PxString16
pxString16FromU32(PxArena* arena, PxFormatOptions options, pxu32 value);

PxString16
pxString16FromU64(PxArena* arena, PxFormatOptions options, pxu64 value);

PxString16
pxString16FromUWord(PxArena* arena, PxFormatOptions options, pxuword value);

PxString16
pxString16FromI8(PxArena* arena, PxFormatOptions options, pxi8 value);

PxString16
pxString16FromI16(PxArena* arena, PxFormatOptions options, pxi16 value);

PxString16
pxString16FromI32(PxArena* arena, PxFormatOptions options, pxi32 value);

PxString16
pxString16FromI64(PxArena* arena, PxFormatOptions options, pxi64 value);

PxString16
pxString16FromIWord(PxArena* arena, PxFormatOptions options, pxiword value);

/* Number from string */

pxb8
pxU8FromString16(pxu8* self, PxFormatOptions options, PxString16 string);

pxb8
pxU16FromString16(pxu16* self, PxFormatOptions options, PxString16 string);

pxb8
pxU32FromString16(pxu32* self, PxFormatOptions options, PxString16 string);

pxb8
pxU64FromString16(pxu64* self, PxFormatOptions options, PxString16 string);

pxb8
pxUWordFromString16(pxuword* self, PxFormatOptions options, PxString16 string);

pxb8
pxI8FromString16(pxi8* self, PxFormatOptions options, PxString16 string);

pxb8
pxI16FromString16(pxi16* self, PxFormatOptions options, PxString16 string);

pxb8
pxI32FromString16(pxi32* self, PxFormatOptions options, PxString16 string);

pxb8
pxI64FromString16(pxi64* self, PxFormatOptions options, PxString16 string);

pxb8
pxIWordFromString16(pxiword* self, PxFormatOptions options, PxString16 string);

#endif // PX_FORMAT_STRING16_H
