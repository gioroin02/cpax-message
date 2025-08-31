#ifndef PX_STRING_STRING32_C
#define PX_STRING_STRING32_C

#include "string32.h"

PxString32
pxString32FromMemory(void* memory, pxiword length)
{
    for (pxiword i = 0; i < length; i += 1) {
        if (pxCast(pxu32*, memory)[i] != 0)
            continue;

        return (PxString32) {
            .memory = memory,
            .length = i,
        };
    }

    return (PxString32) {
        .memory = memory,
        .length = length,
    };
}

PxString32
pxString32CopyUnicode(PxArena* arena, pxi32 value)
{
    pxiword length = pxUtf32UnitsToWrite(value);
    pxu32*  result = pxArenaReserve(arena, pxu32, length + 1);

    if (result == 0 || length <= 0)
        return (PxString32) {0};

    pxUtf32WriteMemory32Forw(result, length, 0, value);

    return (PxString32) {
        .memory = result,
        .length = length,
    };
}

PxString32
pxString32Copy(PxArena* arena, PxString32 string)
{
    return pxString32CopyMemory32(arena, string.memory, string.length);
}

PxString32
pxString32CopyMemory32(PxArena* arena, pxu32* memory, pxiword length)
{
    pxu32* result = pxArenaReserve(arena, pxu32, length + 1);

    if (result == 0 || length <= 0)
        return (PxString32) {0};

    pxMemoryCopy(result, memory, length, 4);

    return (PxString32) {
        .memory = result,
        .length = length,
    };
}

PxString32
pxString32Chain(PxString32 self, PxArena* arena, PxString32 value)
{
    return pxString32ChainMemory32(self, arena, value.memory, value.length);
}

PxString32
pxString32ChainMemory32(PxString32 self, PxArena* arena, pxu32* memory, pxiword length)
{
    pxu32* result = pxArenaReserve(arena,
        pxu32, self.length + length + 1);

    if (result == 0) return (PxString32) {0};

    pxMemoryCopy(result, self.memory, self.length, 4);
    pxMemoryCopy(result + self.length, memory, length, 4);

    return (PxString32) {
        .memory = result,
        .length = length,
    };
}

pxb8
pxString32Get(PxString32 self, pxiword index, pxu32* value)
{
    if (index < 0 || index >= self.length)
        return 0;

    if (value != 0)
        *value = self.memory[index];

    return 1;
}

pxu32
pxString32GetOr(PxString32 self, pxiword index, pxu32 value)
{
    if (index < 0 || index >= self.length)
        return value;

    return self.memory[index];
}

pxb8
pxString32IsEqual(PxString32 self, PxString32 value)
{
    return pxString32IsEqualMemory32(self, value.memory, value.length);
}

pxb8
pxString32IsEqualMemory32(PxString32 self, pxu32* memory, pxiword length)
{
    if (self.length == length)
        return pxMemoryIsEqual(self.memory, memory, length, 4);

    return 0;
}

pxb8
pxString32BeginsWith(PxString32 self, PxString32 value)
{
    return pxString32BeginsWithMemory32(self, value.memory, value.length);
}

pxb8
pxString32BeginsWithMemory32(PxString32 self, pxu32* memory, pxiword length)
{
    PxString32 slice =
        pxString32SliceLength(self, 0, length);

    return pxString32IsEqualMemory32(slice, memory, length);
}

pxb8
pxString32EndsWith(PxString32 self, PxString32 value)
{
    return pxString32EndsWithMemory32(self, value.memory, value.length);
}

pxb8
pxString32EndsWithMemory32(PxString32 self, pxu32* memory, pxiword length)
{
    PxString32 slice =
        pxString32SliceLength(self, self.length - length, length);

    return pxString32IsEqualMemory32(slice, memory, length);
}

pxiword
pxString32Contains(PxString32 self, PxString32 value)
{
    return pxString32ContainsMemory32(self, value.memory, value.length);
}

pxiword
pxString32ContainsMemory32(PxString32 self, pxu32* memory, pxiword length)
{
    pxiword result = 0;

    if (self.length < length) return result;

    for (pxiword i = 0; i < self.length - length + 1; i += 1) {
        PxString32 slice = pxString32SliceLength(self, i, length);

        if (pxString32IsEqualMemory32(slice, memory, length) != 0)
            result += 1, i += length - 1;
    }

    return result;
}

PxString32
pxString32Slice(PxString32 self, pxiword start, pxiword stop)
{
    return pxString32SliceLength(self, start, stop - start);
}

PxString32
pxString32SliceLength(PxString32 self, pxiword index, pxiword length)
{
    if (length <= 0) return (PxString32) {0};

    if (index < 0 || index + length > self.length)
        return (PxString32) {0};

    pxu32* memory = self.memory + index;

    return (PxString32) {
        .memory = memory,
        .length = length,
    };
}

PxString32
pxString32TrimSpaces(PxString32 self)
{
    pxiword units = 0;
    pxiword start = 0;
    pxiword stop  = self.length;

    for (; start < stop; start += units) {
        pxi32 unicode = 0;

        units = pxUtf32ReadMemory32Forw(self.memory,
            self.length, start, &unicode);

        if (units <= 0) return (PxString32) {0};

        if (pxAsciiIsSpace(unicode) == 0)
            break;
    }

    for (; start < stop; stop -= units) {
        pxi32 unicode = 0;

        units = pxUtf32ReadMemory32Back(self.memory,
            self.length, stop - 1, &unicode);

        if (units <= 0) return (PxString32) {0};

        if (pxAsciiIsSpace(unicode) == 0)
            break;
    }

    return pxString32Slice(self, start, stop);
}

PxString32
pxString32TrimSpacesHead(PxString32 self)
{
    pxiword units = 0;
    pxiword start = 0;
    pxiword stop  = self.length;

    for (; start < stop; start += units) {
        pxi32 unicode = 0;

        units = pxUtf32ReadMemory32Forw(self.memory,
            self.length, start, &unicode);

        if (units <= 0) return (PxString32) {0};

        if (pxAsciiIsSpace(unicode) == 0)
            break;
    }

    return pxString32Slice(self, start, stop);
}

PxString32
pxString32TrimSpacesTail(PxString32 self)
{
    pxiword units = 0;
    pxiword start = 0;
    pxiword stop  = self.length;

    for (; start < stop; stop -= units) {
        pxi32 unicode = 0;

        units = pxUtf32ReadMemory32Back(self.memory,
            self.length, stop - 1, &unicode);

        if (units <= 0) return (PxString32) {0};

        if (pxAsciiIsSpace(unicode) == 0)
            break;
    }

    return pxString32Slice(self, start, stop);
}

PxString32
pxString32TrimPrefix(PxString32 self, PxString32 prefix)
{
    if (pxString32BeginsWith(self, prefix) != 0)
        return pxString32Slice(self, prefix.length, self.length);

    return pxString32SliceLength(self, 0, self.length);
}

PxString32
pxString32TrimPrefixMemory32(PxString32 self, pxu32* memory, pxiword length)
{
    if (pxString32BeginsWithMemory32(self, memory, length) != 0)
        return pxString32Slice(self, length, self.length);

    return pxString32SliceLength(self, 0, self.length);
}

PxString32
pxString32TrimSuffix(PxString32 self, PxString32 suffix)
{
    if (pxString32EndsWith(self, suffix) != 0)
        return pxString32Slice(self, 0, self.length - suffix.length);

    return pxString32SliceLength(self, 0, self.length);
}

PxString32
pxString32TrimSuffixMemory32(PxString32 self, pxu32* memory, pxiword length)
{
    if (pxString32EndsWithMemory32(self, memory, length) != 0)
        return pxString32Slice(self, 0, self.length - length);

    return pxString32SliceLength(self, 0, self.length);
}

pxb8
pxString32FindFirst(PxString32 self, pxiword start, PxString32 value, pxiword* index)
{
    return pxString32FindFirstMemory32(self, start, value.memory, value.length, index);
}

pxb8
pxString32FindFirstMemory32(PxString32 self, pxiword start, pxu32* memory, pxiword length, pxiword* index)
{
    start = pxClamp(start, 0, self.length);

    for (pxiword i = start; i < self.length; i += 1) {
        PxString32 slice = pxString32SliceLength(self, i, length);

        if (pxString32IsEqualMemory32(slice, memory, length) == 0)
            continue;

        if (index != 0) *index = i;

        return 1;
    }

    return 0;
}

pxb8
pxString32FindLast(PxString32 self, pxiword start, PxString32 value, pxiword* index)
{
    return pxString32FindLastMemory32(self, start, value.memory, value.length, index);
}

pxb8
pxString32FindLastMemory32(PxString32 self, pxiword start, pxu32* memory, pxiword length, pxiword* index)
{
    start = pxClamp(start, 0, self.length);

    for (pxiword i = start; i > 0; i -= 1) {
        PxString32 slice = pxString32SliceLength(self, i - length, length);

        if (pxString32IsEqualMemory32(slice, memory, length) == 0)
            continue;

        if (index != 0) *index = i - length;

        return 1;
    }

    return 0;
}

pxb8
pxString32Split(PxString32 self, PxString32 pivot, PxString32* left, PxString32* right)
{
    return pxString32SplitMemory32(self, pivot.memory, pivot.length, left, right);
}

pxb8
pxString32SplitMemory32(PxString32 self, pxu32* memory, pxiword length, PxString32* left, PxString32* right)
{
    pxiword start = 0;
    pxiword stop  = self.length;
    pxiword index = self.length;

    pxString32FindFirstMemory32(self, start, memory, length, &index);

    if (left != 0) *left = pxString32Slice(self, start, index);

    if (right != 0)
        *right = pxString32Slice(self, index + length, stop);

    return 1;
}

pxb8
pxString32Next(PxString32 self, pxiword index, pxiword* units, pxi32* value)
{
    if (index < 0 || index >= self.length)
        return 0;

    pxiword step = pxUtf32ReadMemory32Forw(self.memory,
        self.length, index, value);

    if (step == 0) return 0;

    if (units != 0) *units = step;

    return 1;
}

pxb8
pxString32Prev(PxString32 self, pxiword index, pxiword* units, pxi32* value)
{
    if (index < 0 || index >= self.length)
        return 0;

    pxiword step = pxUtf32ReadMemory32Back(self.memory,
        self.length, index, value);

    if (step == 0) return 0;

    if (units != 0) *units = step;

    return 1;
}

#endif // PX_STRING_STRING32_C
