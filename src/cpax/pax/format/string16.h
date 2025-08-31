#ifndef PX_FORMAT_STRING16_H
#define PX_FORMAT_STRING16_H

#include "options.h"

/* String from number */

PxString16
pxString16FromU8(PxArena* arena, pxuword radix, PxFormatOption options, pxu8 value);

PxString16
pxString16FromU16(PxArena* arena, pxuword radix, PxFormatOption options, pxu16 value);

PxString16
pxString16FromU32(PxArena* arena, pxuword radix, PxFormatOption options, pxu32 value);

PxString16
pxString16FromU64(PxArena* arena, pxuword radix, PxFormatOption options, pxu64 value);

PxString16
pxString16FromUWord(PxArena* arena, pxuword radix, PxFormatOption options, pxuword value);

PxString16
pxString16FromI8(PxArena* arena, pxuword radix, PxFormatOption options, pxi8 value);

PxString16
pxString16FromI16(PxArena* arena, pxuword radix, PxFormatOption options, pxi16 value);

PxString16
pxString16FromI32(PxArena* arena, pxuword radix, PxFormatOption options, pxi32 value);

PxString16
pxString16FromI64(PxArena* arena, pxuword radix, PxFormatOption options, pxi64 value);

PxString16
pxString16FromIWord(PxArena* arena, pxuword radix, PxFormatOption options, pxiword value);

/* Number from string */

pxb8
pxU8FromString16(pxu8* self, pxuword radix, PxFormatOption options, PxString16 string);

pxb8
pxU16FromString16(pxu16* self, pxuword radix, PxFormatOption options, PxString16 string);

pxb8
pxU32FromString16(pxu32* self, pxuword radix, PxFormatOption options, PxString16 string);

pxb8
pxU64FromString16(pxu64* self, pxuword radix, PxFormatOption options, PxString16 string);

pxb8
pxUWordFromString16(pxuword* self, pxuword radix, PxFormatOption options, PxString16 string);

pxb8
pxI8FromString16(pxi8* self, pxuword radix, PxFormatOption options, PxString16 string);

pxb8
pxI16FromString16(pxi16* self, pxuword radix, PxFormatOption options, PxString16 string);

pxb8
pxI32FromString16(pxi32* self, pxuword radix, PxFormatOption options, PxString16 string);

pxb8
pxI64FromString16(pxi64* self, pxuword radix, PxFormatOption options, PxString16 string);

pxb8
pxIWordFromString16(pxiword* self, pxuword radix, PxFormatOption options, PxString16 string);

#endif // PX_FORMAT_STRING16_H
