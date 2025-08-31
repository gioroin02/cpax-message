#ifndef PX_FORMAT_STRING32_H
#define PX_FORMAT_STRING32_H

#include "options.h"

/* String from number */

PxString32
pxString32FromU8(PxArena* arena, pxuword radix, PxFormatOption options, pxu8 value);

PxString32
pxString32FromU16(PxArena* arena, pxuword radix, PxFormatOption options, pxu16 value);

PxString32
pxString32FromU32(PxArena* arena, pxuword radix, PxFormatOption options, pxu32 value);

PxString32
pxString32FromU64(PxArena* arena, pxuword radix, PxFormatOption options, pxu64 value);

PxString32
pxString32FromUWord(PxArena* arena, pxuword radix, PxFormatOption options, pxuword value);

PxString32
pxString32FromI8(PxArena* arena, pxuword radix, PxFormatOption options, pxi8 value);

PxString32
pxString32FromI16(PxArena* arena, pxuword radix, PxFormatOption options, pxi16 value);

PxString32
pxString32FromI32(PxArena* arena, pxuword radix, PxFormatOption options, pxi32 value);

PxString32
pxString32FromI64(PxArena* arena, pxuword radix, PxFormatOption options, pxi64 value);

PxString32
pxString32FromIWord(PxArena* arena, pxuword radix, PxFormatOption options, pxiword value);

/* Number from string */

pxb8
pxU8FromString32(pxu8* self, pxuword radix, PxFormatOption options, PxString32 string);

pxb8
pxU16FromString32(pxu16* self, pxuword radix, PxFormatOption options, PxString32 string);

pxb8
pxU32FromString32(pxu32* self, pxuword radix, PxFormatOption options, PxString32 string);

pxb8
pxU64FromString32(pxu64* self, pxuword radix, PxFormatOption options, PxString32 string);

pxb8
pxUWordFromString32(pxuword* self, pxuword radix, PxFormatOption options, PxString32 string);

pxb8
pxI8FromString32(pxi8* self, pxuword radix, PxFormatOption options, PxString32 string);

pxb8
pxI16FromString32(pxi16* self, pxuword radix, PxFormatOption options, PxString32 string);

pxb8
pxI32FromString32(pxi32* self, pxuword radix, PxFormatOption options, PxString32 string);

pxb8
pxI64FromString32(pxi64* self, pxuword radix, PxFormatOption options, PxString32 string);

pxb8
pxIWordFromString32(pxiword* self, pxuword radix, PxFormatOption options, PxString32 string);

#endif // PX_FORMAT_STRING32_H
