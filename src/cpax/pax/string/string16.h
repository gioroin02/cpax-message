#ifndef PX_STRING_STRING16_H
#define PX_STRING_STRING16_H

#include "utf16.h"

typedef struct PxString16
{
    pxu16*  memory;
    pxiword length;
}
PxString16;

PxString16
pxString16FromMemory(void* memory, pxiword length);

PxString16
pxString16CopyUnicode(PxArena* arena, pxi32 value);

PxString16
pxString16Copy(PxArena* arena, PxString16 string);

PxString16
pxString16CopyMemory(PxArena* arena, pxu16* memory, pxiword length);

PxString16
pxString16Chain(PxString16 self, PxArena* arena, PxString16 value);

PxString16
pxString16ChainMemory(PxString16 self, PxArena* arena, pxu16* memory, pxiword length);

pxb8
pxString16Get(PxString16 self, pxiword index, pxu16* value);

pxu16
pxString16GetOr(PxString16 self, pxiword index, pxu16 value);

pxb8
pxString16IsEqual(PxString16 self, PxString16 value);

pxb8
pxString16IsEqualMemory(PxString16 self, pxu16* memory, pxiword length);

pxb8
pxString16BeginsWith(PxString16 self, PxString16 value);

pxb8
pxString16BeginsWithMemory(PxString16 self, pxu16* memory, pxiword length);

pxb8
pxString16EndsWith(PxString16 self, PxString16 value);

pxb8
pxString16EndsWithMemory(PxString16 self, pxu16* memory, pxiword length);

pxiword
pxString16Contains(PxString16 self, PxString16 value);

pxiword
pxString16ContainsMemory(PxString16 self, pxu16* memory, pxiword length);

PxString16
pxString16Slice(PxString16 self, pxiword start, pxiword stop);

PxString16
pxString16SliceLength(PxString16 self, pxiword index, pxiword length);

PxString16
pxString16TrimSpaces(PxString16 self);

PxString16
pxString16TrimSpacesHead(PxString16 self);

PxString16
pxString16TrimSpacesTail(PxString16 self);

PxString16
pxString16TrimPrefix(PxString16 self, PxString16 prefix);

PxString16
pxString16TrimPrefixMemory(PxString16 self, pxu16* memory, pxiword length);

PxString16
pxString16TrimSuffix(PxString16 self, PxString16 suffix);

PxString16
pxString16TrimSuffixMemory(PxString16 self, pxu16* memory, pxiword length);

pxb8
pxString16FindFirst(PxString16 self, pxiword start, PxString16 value, pxiword* index);

pxb8
pxString16FindFirstMemory(PxString16 self, pxiword start, pxu16* memory, pxiword length, pxiword* index);

pxb8
pxString16FindLast(PxString16 self, pxiword start, PxString16 value, pxiword* index);

pxb8
pxString16FindLastMemory(PxString16 self, pxiword start, pxu16* memory, pxiword length, pxiword* index);

pxb8
pxString16Split(PxString16 self, PxString16 pivot, PxString16* left, PxString16* right);

pxb8
pxString16SplitMemory(PxString16 self, pxu16* memory, pxiword length, PxString16* left, PxString16* right);

pxb8
pxString16Next(PxString16 self, pxiword index, pxiword* units, pxi32* value);

pxb8
pxString16Prev(PxString16 self, pxiword index, pxiword* units, pxi32* value);

#endif // PX_STRING_STRING16_H
