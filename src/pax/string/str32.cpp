#ifndef PAX_STRING_STR32_CPP
#define PAX_STRING_STR32_CPP

#include "str32.hpp"

namespace pax {

str32
str32_make(u32* memory, uptr length)
{
    str32 result = {};

    if (memory != 0 && length != 0) {
        result.memory = memory;
        result.length = length;
    }

    return result;
}

str32
str32_reserve(Arena* arena, uptr length)
{
    return str32_make(arena_reserve_arr<u32>(arena, length + 1), length);
}

str32
str32_copy(Arena* arena, str32 value)
{
    return str32_copy_mem(arena, value.memory, value.length);
}

str32
str32_copy_mem(Arena* arena, u32* memory, uptr length)
{
    str32 result = str32_reserve(arena, length);

    if (result.length != 0)
        mem32_copy(result.memory, memory, result.length);

    return result;
}

str32
str32_from_unicode(Arena* arena, u32 value)
{
    str32 result = str32_reserve(arena,
        utf32_units_to_write(value));

    if (result.length == 0) return result;

    utf32_encode_forw(result.memory, result.length, 0, value);

    return result;
}

b32
str32_get(str32 self, uptr index, u32* value)
{
    if (index < 0 || index >= self.length)
        return 0;

    if (value != 0) *value = self.memory[index];

    return 1;
}

u32
str32_get_or(str32 self, uptr index, u32 value)
{
    if (index < 0 || index >= self.length)
        return value;

    return self.memory[index];
}

str32
str32_count(u32* memory)
{
    uptr index = 0;

    while (memory[index] != 0)
        index += 1;

    return str32_make(memory, index);
}

str32
str32_count_max(u32* memory, uptr limit)
{
    uptr index = 0;

    while (memory[index] != 0) {
        index += 1;

        if (index > limit)
            return {};
    }

    return str32_make(memory, index);
}

b32
str32_is_equal(str32 self, str32 value)
{
    if (self.length == value.length)
        return mem32_is_equal(self.memory, value.memory, self.length);

    return 0;
}

b32
str32_starts_with(str32 self, str32 value)
{
    uptr start  = 0;
    uptr length = value.length;

    str32 slice = str32_slice_len(self, start, length);

    if (self.length >= value.length)
        return str32_is_equal(slice, value);

    return 0;
}

b32
str32_ends_with(str32 self, str32 value)
{
    uptr start  = self.length - value.length;
    uptr length = value.length;

    str32 slice = str32_slice_len(self, start, length);

    if (self.length >= value.length)
        return str32_is_equal(slice, value);

    return 0;
}

str32
str32_slice(str32 self, uptr start, uptr stop)
{
    str32 result = {};

    start = pax_min(start, self.length);
    stop  = pax_min(stop, self.length);

    uptr length = stop - start;

    if (start <= stop)
        result = str32_make(self.memory + start, length);

    return result;
}

str32
str32_slice_len(str32 self, uptr start, uptr length)
{
    return str32_slice(self, start, start + length);
}

str32
str32_slice_until_first(str32 self, str32 value)
{
    uptr start = 0;
    uptr stop  = self.length;

    str32_find_first(self, value, &stop);

    return str32_slice(self, start, stop);
}

str32
str32_slice_until_last(str32 self, str32 value)
{
    uptr start = 0;
    uptr stop  = self.length;

    str32_find_last(self, value, &stop);

    return str32_slice(self, start, stop);
}

str32
str32_slice_since_first(str32 self, str32 value)
{
    uptr start = self.length;
    uptr stop  = self.length;

    str32_find_first(self, value, &start);

    return str32_slice(self, start + value.length, stop);
}

str32
str32_slice_since_last(str32 self, str32 value)
{
    uptr start = self.length;
    uptr stop  = self.length;

    str32_find_last(self, value, &start);

    return str32_slice(self, start + value.length, stop);
}

str32
str32_chain(Arena* arena, str32 value, str32 other)
{
    str32 result = str32_reserve(arena, value.length + other.length);

    if (result.length == 0) return result;

    mem32_copy(result.memory, value.memory, value.length);

    mem32_copy(result.memory + value.length, other.memory,
        other.length);

    return result;
}

str32
str32_split_on(str32 self, str32 pivot, str32* value)
{
    uptr start = 0;
    uptr index = self.length;
    uptr stop  = self.length;

    str32_find_first(self, pivot, &index);

    if (value != 0)
        *value = str32_slice(self, index + pivot.length, stop);

    return str32_slice(self, start, index);
}

str32
str32_trim_prefix(str32 self, str32 prefix)
{
    if (str32_starts_with(self, prefix) == 0)
        return self;

    return str32_slice(self, prefix.length, self.length);
}

str32
str32_trim_suffix(str32 self, str32 suffix)
{
    if (str32_ends_with(self, suffix) == 0)
        return self;

    uptr length = self.length - suffix.length;

    return str32_slice(self, 0, length);
}

str32
str32_trim_spaces(str32 self)
{
    return str32_trim_spaces_start(str32_trim_spaces_end(self));
}

str32
str32_trim_spaces_start(str32 self)
{
    uptr start = 0;
    uptr stop  = self.length;

    for (; start < stop; start += 1) {
        u32 unicode = self.memory[start];

        if (ascii_is_space(unicode) == 0)
            break;
    }

    return str32_slice(self, start, stop);
}

str32
str32_trim_spaces_end(str32 self)
{
    uptr start = 0;
    uptr stop  = self.length;

    for (; start < stop; stop -= 1) {
        u32 unicode = self.memory[stop - 1];

        if (ascii_is_space(unicode) == 0)
            break;
    }

    return str32_slice(self, start, stop);
}

b32
str32_find_first(str32 self, str32 value, uptr* index)
{
    return str32_find_first_since(self, value, 0, index);
}

b32
str32_find_first_since(str32 self, str32 value, uptr start, uptr* index)
{
    start = pax_min(start, self.length);

    for (uptr i = start; i < self.length; i += 1) {
        str32 slice = str32_slice_len(self, i, value.length);

        if (str32_is_equal(slice, value) == 0)
            continue;

        if (index != 0) *index = i;

        return 1;
    }

    return 0;
}

b32
str32_find_last(str32 self, str32 value, uptr* index)
{
    return str32_find_last_until(self, value, self.length, index);
}

b32
str32_find_last_until(str32 self, str32 value, uptr start, uptr* index)
{
    start = pax_min(start, self.length);

    for (uptr i = start; i > 0; i -= 1) {
        str32 slice = str32_slice_len(self, i - value.length, value.length);

        if (str32_is_equal(slice, value) == 0)
            continue;

        if (index != 0) *index = i - value.length;

        return 1;
    }

    return 0;
}

uptr
str32_contains(str32 self, str32 value)
{
    uptr result = 0;

    if (value.length > self.length) return result;

    for (uptr i = 0; i < self.length; i += 1) {
        str32 slice = str32_slice_len(self, i, value.length);

        if (str32_is_equal(slice, value) != 0)
            result += 1;
    }

    return result;
}

b32
str32_next(str32 self, uptr index, uptr* units, u32* value)
{
    if (index < 0 || index >= self.length)
        return 0;

    if (value != 0)
        *value = self.memory[index];

    if (units != 0) *units = 1;

    return 1;
}

b32
str32_prev(str32 self, uptr index, uptr* units, u32* value)
{
    if (index < 0 || index >= self.length)
        return 0;

    if (value != 0)
        *value = self.memory[index];

    if (units != 0) *units = 1;

    return 1;
}

} // namespace pax

#endif // PAX_STRING_STR32_CPP
