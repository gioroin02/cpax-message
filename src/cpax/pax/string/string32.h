#ifndef PX_STRING_STRING32_H
#define PX_STRING_STRING32_H

#include "utf32.h"

typedef struct PxString32
{
    pxu32*  memory;
    pxiword length;
}
PxString32;

PxString32
pxString32FromMemory(void* memory, pxiword length);

PxString32
pxString32CopyUnicode(PxArena* arena, pxi32 value);

PxString32
pxString32Copy(PxArena* arena, PxString32 string);

PxString32
pxString32CopyMemory(PxArena* arena, pxu32* memory, pxiword length);

PxString32
pxString32Chain(PxString32 self, PxArena* arena, PxString32 value);

PxString32
pxString32ChainMemory(PxString32 self, PxArena* arena, pxu32* memory, pxiword length);

pxb8
pxString32Get(PxString32 self, pxiword index, pxu32* value);

pxu32
pxString32GetOr(PxString32 self, pxiword index, pxu32 value);

pxb8
pxString32IsEqual(PxString32 self, PxString32 value);

pxb8
pxString32IsEqualMemory(PxString32 self, pxu32* memory, pxiword length);

pxb8
pxString32BeginsWith(PxString32 self, PxString32 value);

pxb8
pxString32BeginsWithMemory(PxString32 self, pxu32* memory, pxiword length);

pxb8
pxString32EndsWith(PxString32 self, PxString32 value);

pxb8
pxString32EndsWithMemory(PxString32 self, pxu32* memory, pxiword length);

pxiword
pxString32Contains(PxString32 self, PxString32 value);

pxiword
pxString32ContainsMemory(PxString32 self, pxu32* memory, pxiword length);

PxString32
pxString32Slice(PxString32 self, pxiword start, pxiword stop);

PxString32
pxString32SliceLength(PxString32 self, pxiword index, pxiword length);

PxString32
pxString32TrimSpaces(PxString32 self);

PxString32
pxString32TrimSpacesHead(PxString32 self);

PxString32
pxString32TrimSpacesTail(PxString32 self);

PxString32
pxString32TrimPrefix(PxString32 self, PxString32 prefix);

PxString32
pxString32TrimPrefixMemory(PxString32 self, pxu32* memory, pxiword length);

PxString32
pxString32TrimSuffix(PxString32 self, PxString32 suffix);

PxString32
pxString32TrimSuffixMemory(PxString32 self, pxu32* memory, pxiword length);

pxb8
pxString32FindFirst(PxString32 self, pxiword start, PxString32 value, pxiword* index);

pxb8
pxString32FindFirstMemory(PxString32 self, pxiword start, pxu32* memory, pxiword length, pxiword* index);

pxb8
pxString32FindLast(PxString32 self, pxiword start, PxString32 value, pxiword* index);

pxb8
pxString32FindLastMemory(PxString32 self, pxiword start, pxu32* memory, pxiword length, pxiword* index);

pxb8
pxString32Split(PxString32 self, PxString32 pivot, PxString32* left, PxString32* right);

pxb8
pxString32SplitMemory(PxString32 self, pxu32* memory, pxiword length, PxString32* left, PxString32* right);

pxb8
pxString32Next(PxString32 self, pxiword index, pxiword* units, pxi32* value);

pxb8
pxString32Prev(PxString32 self, pxiword index, pxiword* units, pxi32* value);

#endif // PX_STRING_STRING32_H
