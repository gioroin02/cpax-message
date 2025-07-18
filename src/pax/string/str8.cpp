#ifndef PAX_STRING_STR8_CPP
#define PAX_STRING_STR8_CPP

#include "str8.hpp"

namespace pax {

str8
str8_make(u8* memory, uptr length)
{
    str8 result = {};

    if (memory != 0 && length != 0) {
        result.memory = memory;
        result.length = length;
    }

    return result;
}

str8
str8_reserve(Arena* arena, uptr length)
{
    return str8_make(arena_reserve_arr<u8>(arena, length + 1), length);
}

str8
str8_copy(Arena* arena, str8 value)
{
    return str8_copy_mem(arena, value.memory, value.length);
}

str8
str8_copy_mem(Arena* arena, u8* memory, uptr length)
{
    str8 result = str8_reserve(arena, length);

    if (result.length != 0)
        mem8_copy(result.memory, memory, result.length);

    return result;
}

str8
str8_from_unicode(Arena* arena, u32 value)
{
    str8 result = str8_reserve(arena,
        utf8_units_to_write(value));

    if (result.length == 0) return result;

    utf8_encode_forw(result.memory, result.length, 0, value);

    return result;
}

b32
str8_get(str8 self, uptr index, u8* value)
{
    if (index < 0 || index >= self.length)
        return 0;

    if (value != 0) *value = self.memory[index];

    return 1;
}

u8
str8_get_or(str8 self, uptr index, u8 value)
{
    if (index < 0 || index >= self.length)
        return value;

    return self.memory[index];
}

str8
str8_count(u8* memory)
{
    uptr index = 0;

    while (memory[index] != 0)
        index += 1;

    return str8_make(memory, index);
}

str8
str8_count_max(u8* memory, uptr limit)
{
    uptr index = 0;

    while (memory[index] != 0) {
        index += 1;

        if (index > limit)
            return {};
    }

    return str8_make(memory, index);
}

b32
str8_is_equal(str8 self, str8 value)
{
    if (self.length == value.length)
        return mem8_is_equal(self.memory, value.memory, self.length);

    return 0;
}

b32
str8_starts_with(str8 self, str8 value)
{
    uptr start  = 0;
    uptr length = value.length;

    str8 slice = str8_slice_len(self, start, length);

    if (self.length >= value.length)
        return str8_is_equal(slice, value);

    return 0;
}

b32
str8_ends_with(str8 self, str8 value)
{
    uptr start  = self.length - value.length;
    uptr length = value.length;

    str8 slice = str8_slice_len(self, start, length);

    if (self.length >= value.length)
        return str8_is_equal(slice, value);

    return 0;
}

str8
str8_slice(str8 self, uptr start, uptr stop)
{
    str8 result = {};

    start = pax_min(start, self.length);
    stop  = pax_min(stop, self.length);

    uptr length = stop - start;

    if (start <= stop)
        result = str8_make(self.memory + start, length);

    return result;
}

str8
str8_slice_len(str8 self, uptr start, uptr length)
{
    return str8_slice(self, start, start + length);
}

str8
str8_slice_until_first(str8 self, str8 value)
{
    uptr start = 0;
    uptr stop  = self.length;

    str8_find_first(self, value, &stop);

    return str8_slice(self, start, stop);
}

str8
str8_slice_until_last(str8 self, str8 value)
{
    uptr start = 0;
    uptr stop  = self.length;

    str8_find_last(self, value, &stop);

    return str8_slice(self, start, stop);
}

str8
str8_slice_since_first(str8 self, str8 value)
{
    uptr start = self.length;
    uptr stop  = self.length;

    str8_find_first(self, value, &start);

    return str8_slice(self, start + value.length, stop);
}

str8
str8_slice_since_last(str8 self, str8 value)
{
    uptr start = self.length;
    uptr stop  = self.length;

    str8_find_last(self, value, &start);

    return str8_slice(self, start + value.length, stop);
}

str8
str8_chain(Arena* arena, str8 value, str8 other)
{
    str8 result = str8_reserve(arena, value.length + other.length);

    if (result.length == 0) return result;

    mem8_copy(result.memory, value.memory, value.length);

    mem8_copy(result.memory + value.length, other.memory,
        other.length);

    return result;
}

str8
str8_split_on(str8 self, str8 pivot, str8* value)
{
    uptr start = 0;
    uptr index = self.length;
    uptr stop  = self.length;

    str8_find_first(self, pivot, &index);

    if (value != 0)
        *value = str8_slice(self, index + pivot.length, stop);

    return str8_slice(self, start, index);
}

str8
str8_trim_prefix(str8 self, str8 prefix)
{
    if (str8_starts_with(self, prefix) == 0)
        return self;

    return str8_slice(self, prefix.length, self.length);
}

str8
str8_trim_suffix(str8 self, str8 suffix)
{
    if (str8_ends_with(self, suffix) == 0)
        return self;

    uptr length = self.length - suffix.length;

    return str8_slice(self, 0, length);
}

str8
str8_trim_spaces(str8 self)
{
    return str8_trim_spaces_start(str8_trim_spaces_end(self));
}

str8
str8_trim_spaces_start(str8 self)
{
    uptr units = 0;
    uptr start = 0;
    uptr stop  = self.length;

    for (; start < stop; start += units) {
        u32 unicode = 0;

        units = utf8_decode_forw(self.memory,
            self.length, start, &unicode);

        if (units == 0) return self;

        if (ascii_is_space(unicode) == 0)
            break;
    }

    return str8_slice(self, start, stop);
}

str8
str8_trim_spaces_end(str8 self)
{
    uptr units = 0;
    uptr start = 0;
    uptr stop  = self.length;

    for (; start < stop; stop -= units) {
        u32 unicode = 0;

        units = utf8_decode_back(self.memory,
            self.length, stop - 1, &unicode);

        if (units == 0) return self;

        if (ascii_is_space(unicode) == 0)
            break;
    }

    return str8_slice(self, start, stop);
}

b32
str8_find_first(str8 self, str8 value, uptr* index)
{
    return str8_find_first_since(self, value, 0, index);
}

b32
str8_find_first_since(str8 self, str8 value, uptr start, uptr* index)
{
    start = pax_min(start, self.length);

    for (uptr i = start; i < self.length; i += 1) {
        str8 slice = str8_slice_len(self, i, value.length);

        if (str8_is_equal(slice, value) == 0)
            continue;

        if (index != 0) *index = i;

        return 1;
    }

    return 0;
}

b32
str8_find_last(str8 self, str8 value, uptr* index)
{
    return str8_find_last_until(self, value, self.length, index);
}

b32
str8_find_last_until(str8 self, str8 value, uptr start, uptr* index)
{
    start = pax_limit(start, 0, self.length);

    for (uptr i = start; i > 0; i -= 1) {
        str8 slice = str8_slice_len(self, i - value.length, value.length);

        if (str8_is_equal(slice, value) == 0)
            continue;

        if (index != 0) *index = i - value.length;

        return 1;
    }

    return 0;
}

uptr
str8_contains(str8 self, str8 value)
{
    uptr result = 0;

    if (value.length > self.length) return result;

    for (uptr i = 0; i < self.length; i += 1) {
        str8 slice = str8_slice_len(self, i, value.length);

        if (str8_is_equal(slice, value) != 0)
            result += 1;
    }

    return result;
}

b32
str8_next(str8 self, uptr index, uptr* units, u32* value)
{
    if (index < 0 || index >= self.length)
        return 0;

    uptr step = utf8_decode_forw(self.memory,
        self.length, index, value);

    if (step == 0) return 0;

    if (units != 0) *units = step;

    return 1;
}

b32
str8_prev(str8 self, uptr index, uptr* units, u32* value)
{
    if (index < 0 || index >= self.length)
        return 0;

    uptr step = utf8_decode_back(self.memory,
        self.length, index, value);

    if (step == 0) return 0;

    if (units != 0) *units = step;

    return 1;
}

} // namespace pax

#endif // PAX_STRING_STR8_CPP
