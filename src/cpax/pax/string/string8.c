#ifndef PX_STRING_STRING8_C
#define PX_STRING_STRING8_C

#include "string8.h"

PxString8
pxString8FromMemory(void* memory, pxiword length)
{
    for (pxiword i = 0; i < length; i += 1) {
        if (pxCast(pxu8*, memory)[i] != 0)
            continue;

        return (PxString8) {
            .memory = memory,
            .length = i,
        };
    }

    return (PxString8) {
        .memory = memory,
        .length = length,
    };
}

PxString8
pxString8CopyUnicode(PxArena* arena, pxi32 value)
{
    pxiword length = pxUtf8UnitsToWrite(value);
    pxu8*   result = pxArenaReserve(arena, pxu8, length + 1);

    if (result == 0 || length <= 0)
        return (PxString8) {0};

    pxUtf8WriteMemory8Forw(result, length, 0, value);

    return (PxString8) {
        .memory = result,
        .length = length,
    };
}

PxString8
pxString8Copy(PxArena* arena, PxString8 string)
{
    return pxString8CopyMemory8(arena, string.memory, string.length);
}

PxString8
pxString8CopyMemory8(PxArena* arena, pxu8* memory, pxiword length)
{
    pxu8* result = pxArenaReserve(arena, pxu8, length + 1);

    if (result == 0 || length <= 0)
        return (PxString8) {0};

    pxMemoryCopy(result, memory, length, 1);

    return (PxString8) {
        .memory = result,
        .length = length,
    };
}

PxString8
pxString8Chain(PxString8 self, PxArena* arena, PxString8 value)
{
    return pxString8ChainMemory8(self, arena, value.memory, value.length);
}

PxString8
pxString8ChainMemory8(PxString8 self, PxArena* arena, pxu8* memory, pxiword length)
{
    pxu8* result = pxArenaReserve(arena,
        pxu8, self.length + length + 1);

    if (result == 0) return (PxString8) {0};

    pxMemoryCopy(result, self.memory, self.length, 1);
    pxMemoryCopy(result + self.length, memory, length, 1);

    return (PxString8) {
        .memory = result,
        .length = length,
    };
}

pxb8
pxString8Get(PxString8 self, pxiword index, pxu8* value)
{
    if (index < 0 || index >= self.length)
        return 0;

    if (value != 0)
        *value = self.memory[index];

    return 1;
}

pxu8
pxString8GetOr(PxString8 self, pxiword index, pxu8 value)
{
    if (index < 0 || index >= self.length)
        return value;

    return self.memory[index];
}

pxb8
pxString8IsEqual(PxString8 self, PxString8 value)
{
    return pxString8IsEqualMemory8(self, value.memory, value.length);
}

pxb8
pxString8IsEqualMemory8(PxString8 self, pxu8* memory, pxiword length)
{
    if (self.length == length)
        return pxMemoryIsEqual(self.memory, memory, length, 1);

    return 0;
}

pxb8
pxString8BeginsWith(PxString8 self, PxString8 value)
{
    return pxString8BeginsWithMemory8(self, value.memory, value.length);
}

pxb8
pxString8BeginsWithMemory8(PxString8 self, pxu8* memory, pxiword length)
{
    PxString8 slice =
        pxString8SliceLength(self, 0, length);

    return pxString8IsEqualMemory8(slice, memory, length);
}

pxb8
pxString8EndsWith(PxString8 self, PxString8 value)
{
    return pxString8EndsWithMemory8(self, value.memory, value.length);
}

pxb8
pxString8EndsWithMemory8(PxString8 self, pxu8* memory, pxiword length)
{
    PxString8 slice =
        pxString8SliceLength(self, self.length - length, length);

    return pxString8IsEqualMemory8(slice, memory, length);
}

pxiword
pxString8Contains(PxString8 self, PxString8 value)
{
    return pxString8ContainsMemory8(self, value.memory, value.length);
}

pxiword
pxString8ContainsMemory8(PxString8 self, pxu8* memory, pxiword length)
{
    pxiword result = 0;

    if (self.length < length) return result;

    for (pxiword i = 0; i < self.length - length + 1; i += 1) {
        PxString8 slice = pxString8SliceLength(self, i, length);

        if (pxString8IsEqualMemory8(slice, memory, length) != 0)
            result += 1, i += length - 1;
    }

    return result;
}

PxString8
pxString8Slice(PxString8 self, pxiword start, pxiword stop)
{
    return pxString8SliceLength(self, start, stop - start);
}

PxString8
pxString8SliceLength(PxString8 self, pxiword index, pxiword length)
{
    if (length <= 0) return (PxString8) {0};

    if (index < 0 || index + length > self.length)
        return (PxString8) {0};

    pxu8* memory = self.memory + index;

    return (PxString8) {
        .memory = memory,
        .length = length,
    };
}

PxString8
pxString8TrimSpaces(PxString8 self)
{
    pxiword units = 0;
    pxiword start = 0;
    pxiword stop  = self.length;

    for (; start < stop; start += units) {
        pxi32 unicode = 0;

        units = pxUtf8ReadMemory8Forw(self.memory,
            self.length, start, &unicode);

        if (units <= 0) return (PxString8) {0};

        if (pxAsciiIsSpace(unicode) == 0)
            break;
    }

    for (; start < stop; stop -= units) {
        pxi32 unicode = 0;

        units = pxUtf8ReadMemory8Back(self.memory,
            self.length, stop - 1, &unicode);

        if (units <= 0) return (PxString8) {0};

        if (pxAsciiIsSpace(unicode) == 0)
            break;
    }

    return pxString8Slice(self, start, stop);
}

PxString8
pxString8TrimSpacesHead(PxString8 self)
{
    pxiword units = 0;
    pxiword start = 0;
    pxiword stop  = self.length;

    for (; start < stop; start += units) {
        pxi32 unicode = 0;

        units = pxUtf8ReadMemory8Forw(self.memory,
            self.length, start, &unicode);

        if (units <= 0) return (PxString8) {0};

        if (pxAsciiIsSpace(unicode) == 0)
            break;
    }

    return pxString8Slice(self, start, stop);
}

PxString8
pxString8TrimSpacesTail(PxString8 self)
{
    pxiword units = 0;
    pxiword start = 0;
    pxiword stop  = self.length;

    for (; start < stop; stop -= units) {
        pxi32 unicode = 0;

        units = pxUtf8ReadMemory8Back(self.memory,
            self.length, stop - 1, &unicode);

        if (units <= 0) return (PxString8) {0};

        if (pxAsciiIsSpace(unicode) == 0)
            break;
    }

    return pxString8Slice(self, start, stop);
}

PxString8
pxString8TrimPrefix(PxString8 self, PxString8 prefix)
{
    if (pxString8BeginsWith(self, prefix) != 0)
        return pxString8Slice(self, prefix.length, self.length);

    return pxString8SliceLength(self, 0, self.length);
}

PxString8
pxString8TrimPrefixMemory8(PxString8 self, pxu8* memory, pxiword length)
{
    if (pxString8BeginsWithMemory8(self, memory, length) != 0)
        return pxString8Slice(self, length, self.length);

    return pxString8SliceLength(self, 0, self.length);
}

PxString8
pxString8TrimSuffix(PxString8 self, PxString8 suffix)
{
    if (pxString8EndsWith(self, suffix) != 0)
        return pxString8Slice(self, 0, self.length - suffix.length);

    return pxString8SliceLength(self, 0, self.length);
}

PxString8
pxString8TrimSuffixMemory8(PxString8 self, pxu8* memory, pxiword length)
{
    if (pxString8EndsWithMemory8(self, memory, length) != 0)
        return pxString8Slice(self, 0, self.length - length);

    return pxString8SliceLength(self, 0, self.length);
}

pxb8
pxString8FindFirst(PxString8 self, pxiword start, PxString8 value, pxiword* index)
{
    return pxString8FindFirstMemory8(self, start, value.memory, value.length, index);
}

pxb8
pxString8FindFirstMemory8(PxString8 self, pxiword start, pxu8* memory, pxiword length, pxiword* index)
{
    start = pxClamp(start, 0, self.length);

    for (pxiword i = start; i < self.length; i += 1) {
        PxString8 slice = pxString8SliceLength(self, i, length);

        if (pxString8IsEqualMemory8(slice, memory, length) == 0)
            continue;

        if (index != 0) *index = i;

        return 1;
    }

    return 0;
}

pxb8
pxString8FindLast(PxString8 self, pxiword start, PxString8 value, pxiword* index)
{
    return pxString8FindLastMemory8(self, start, value.memory, value.length, index);
}

pxb8
pxString8FindLastMemory8(PxString8 self, pxiword start, pxu8* memory, pxiword length, pxiword* index)
{
    start = pxClamp(start, 0, self.length);

    for (pxiword i = start; i > 0; i -= 1) {
        PxString8 slice = pxString8SliceLength(self, i - length, length);

        if (pxString8IsEqualMemory8(slice, memory, length) == 0)
            continue;

        if (index != 0) *index = i - length;

        return 1;
    }

    return 0;
}

pxb8
pxString8Split(PxString8 self, PxString8 pivot, PxString8* left, PxString8* right)
{
    return pxString8SplitMemory8(self, pivot.memory, pivot.length, left, right);
}

pxb8
pxString8SplitMemory8(PxString8 self, pxu8* memory, pxiword length, PxString8* left, PxString8* right)
{
    pxiword start = 0;
    pxiword stop  = self.length;
    pxiword index = self.length;

    pxString8FindFirstMemory8(self, start, memory, length, &index);

    if (left != 0) *left = pxString8Slice(self, start, index);

    if (right != 0)
        *right = pxString8Slice(self, index + length, stop);

    return 1;
}

pxb8
pxString8Next(PxString8 self, pxiword index, pxiword* units, pxi32* value)
{
    if (index < 0 || index >= self.length)
        return 0;

    pxiword step = pxUtf8ReadMemory8Forw(self.memory,
        self.length, index, value);

    if (step == 0) return 0;

    if (units != 0) *units = step;

    return 1;
}

pxb8
pxString8Prev(PxString8 self, pxiword index, pxiword* units, pxi32* value)
{
    if (index < 0 || index >= self.length)
        return 0;

    pxiword step = pxUtf8ReadMemory8Back(self.memory,
        self.length, index, value);

    if (step == 0) return 0;

    if (units != 0) *units = step;

    return 1;
}

#endif // PX_STRING_STRING8_C
