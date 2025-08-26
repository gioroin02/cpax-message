#ifndef PX_FORMAT_STRING32_H
#define PX_FORMAT_STRING32_H

#include "options.h"

/* String from number */

PxString32
pxString32FromU8(PxArena* arena, PxFormatOptions options, pxu8 value);

PxString32
pxString32FromU16(PxArena* arena, PxFormatOptions options, pxu16 value);

PxString32
pxString32FromU32(PxArena* arena, PxFormatOptions options, pxu32 value);

PxString32
pxString32FromU64(PxArena* arena, PxFormatOptions options, pxu64 value);

PxString32
pxString32FromUWord(PxArena* arena, PxFormatOptions options, pxuword value);

PxString32
pxString32FromI8(PxArena* arena, PxFormatOptions options, pxi8 value);

PxString32
pxString32FromI16(PxArena* arena, PxFormatOptions options, pxi16 value);

PxString32
pxString32FromI32(PxArena* arena, PxFormatOptions options, pxi32 value);

PxString32
pxString32FromI64(PxArena* arena, PxFormatOptions options, pxi64 value);

PxString32
pxString32FromIWord(PxArena* arena, PxFormatOptions options, pxiword value);

/* Number from string */

pxb8
pxU8FromString32(pxu8* self, PxFormatOptions options, PxString32 string);

pxb8
pxU16FromString32(pxu16* self, PxFormatOptions options, PxString32 string);

pxb8
pxU32FromString32(pxu32* self, PxFormatOptions options, PxString32 string);

pxb8
pxU64FromString32(pxu64* self, PxFormatOptions options, PxString32 string);

pxb8
pxUWordFromString32(pxuword* self, PxFormatOptions options, PxString32 string);

pxb8
pxI8FromString32(pxi8* self, PxFormatOptions options, PxString32 string);

pxb8
pxI16FromString32(pxi16* self, PxFormatOptions options, PxString32 string);

pxb8
pxI32FromString32(pxi32* self, PxFormatOptions options, PxString32 string);

pxb8
pxI64FromString32(pxi64* self, PxFormatOptions options, PxString32 string);

pxb8
pxIWordFromString32(pxiword* self, PxFormatOptions options, PxString32 string);

#endif // PX_FORMAT_STRING32_H
