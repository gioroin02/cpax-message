#ifndef PX_FORMAT_STRING8_H
#define PX_FORMAT_STRING8_H

#include "options.h"

/* String from number */

PxString8
pxString8FromU8(PxArena* arena, PxFormatOptions options, pxu8 value);

PxString8
pxString8FromU16(PxArena* arena, PxFormatOptions options, pxu16 value);

PxString8
pxString8FromU32(PxArena* arena, PxFormatOptions options, pxu32 value);

PxString8
pxString8FromU64(PxArena* arena, PxFormatOptions options, pxu64 value);

PxString8
pxString8FromUWord(PxArena* arena, PxFormatOptions options, pxuword value);

PxString8
pxString8FromI8(PxArena* arena, PxFormatOptions options, pxi8 value);

PxString8
pxString8FromI16(PxArena* arena, PxFormatOptions options, pxi16 value);

PxString8
pxString8FromI32(PxArena* arena, PxFormatOptions options, pxi32 value);

PxString8
pxString8FromI64(PxArena* arena, PxFormatOptions options, pxi64 value);

PxString8
pxString8FromIWord(PxArena* arena, PxFormatOptions options, pxiword value);

/* Number from string */

pxb8
pxU8FromString8(pxu8* self, PxFormatOptions options, PxString8 string);

pxb8
pxU16FromString8(pxu16* self, PxFormatOptions options, PxString8 string);

pxb8
pxU32FromString8(pxu32* self, PxFormatOptions options, PxString8 string);

pxb8
pxU64FromString8(pxu64* self, PxFormatOptions options, PxString8 string);

pxb8
pxUWordFromString8(pxuword* self, PxFormatOptions options, PxString8 string);

pxb8
pxI8FromString8(pxi8* self, PxFormatOptions options, PxString8 string);

pxb8
pxI16FromString8(pxi16* self, PxFormatOptions options, PxString8 string);

pxb8
pxI32FromString8(pxi32* self, PxFormatOptions options, PxString8 string);

pxb8
pxI64FromString8(pxi64* self, PxFormatOptions options, PxString8 string);

pxb8
pxIWordFromString8(pxiword* self, PxFormatOptions options, PxString8 string);

#endif // PX_FORMAT_STRING8_H
