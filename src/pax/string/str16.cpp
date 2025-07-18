#ifndef PAX_STRING_STR16_CPP
#define PAX_STRING_STR16_CPP

#include "str16.hpp"

namespace pax {

str16
str16_make(u16* memory, uptr length)
{
    str16 result = {};

    if (memory != 0 && length != 0) {
        result.memory = memory;
        result.length = length;
    }

    return result;
}

str16
str16_reserve(Arena* arena, uptr length)
{
    return str16_make(arena_reserve_arr<u16>(arena, length + 1), length);
}

str16
str16_copy(Arena* arena, str16 value)
{
    return str16_copy_mem(arena, value.memory, value.length);
}

str16
str16_copy_mem(Arena* arena, u16* memory, uptr length)
{
    str16 result = str16_reserve(arena, length);

    if (result.length != 0)
        mem16_copy(result.memory, memory, result.length);

    return result;
}

str16
str16_from_unicode(Arena* arena, u32 value)
{
    str16 result = str16_reserve(arena,
        utf16_units_to_write(value));

    if (result.length == 0) return result;

    utf16_encode_forw(result.memory, result.length, 0, value);

    return result;
}

b32
str16_get(str16 self, uptr index, u16* value)
{
    if (index < 0 || index >= self.length)
        return 0;

    if (value != 0) *value = self.memory[index];

    return 1;
}

u16
str16_get_or(str16 self, uptr index, u16 value)
{
    if (index < 0 || index >= self.length)
        return value;

    return self.memory[index];
}

str16
str16_count(u16* memory)
{
    uptr index = 0;

    while (memory[index] != 0)
        index += 1;

    return str16_make(memory, index);
}

str16
str16_count_max(u16* memory, uptr limit)
{
    uptr index = 0;

    while (memory[index] != 0) {
        index += 1;

        if (index > limit)
            return {};
    }

    return str16_make(memory, index);
}

b32
str16_is_equal(str16 self, str16 value)
{
    if (self.length == value.length)
        return mem16_is_equal(self.memory, value.memory, self.length);

    return 0;
}

b32
str16_starts_with(str16 self, str16 value)
{
    uptr start  = 0;
    uptr length = value.length;

    str16 slice = str16_slice_len(self, start, length);

    if (self.length >= value.length)
        return str16_is_equal(slice, value);

    return 0;
}

b32
str16_ends_with(str16 self, str16 value)
{
    uptr start  = self.length - value.length;
    uptr length = value.length;

    str16 slice = str16_slice_len(self, start, length);

    if (self.length >= value.length)
        return str16_is_equal(slice, value);

    return 0;
}

str16
str16_slice(str16 self, uptr start, uptr stop)
{
    str16 result = {};

    start = pax_min(start, self.length);
    stop  = pax_min(stop, self.length);

    uptr length = stop - start;

    if (start <= stop)
        result = str16_make(self.memory + start, length);

    return result;
}

str16
str16_slice_len(str16 self, uptr start, uptr length)
{
    return str16_slice(self, start, start + length);
}

str16
str16_slice_until_first(str16 self, str16 value)
{
    uptr start = 0;
    uptr stop  = self.length;

    str16_find_first(self, value, &stop);

    return str16_slice(self, start, stop);
}

str16
str16_slice_until_last(str16 self, str16 value)
{
    uptr start = 0;
    uptr stop  = self.length;

    str16_find_last(self, value, &stop);

    return str16_slice(self, start, stop);
}

str16
str16_slice_since_first(str16 self, str16 value)
{
    uptr start = self.length;
    uptr stop  = self.length;

    str16_find_first(self, value, &start);

    return str16_slice(self, start + value.length, stop);
}

str16
str16_slice_since_last(str16 self, str16 value)
{
    uptr start = self.length;
    uptr stop  = self.length;

    str16_find_last(self, value, &start);

    return str16_slice(self, start + value.length, stop);
}

str16
str16_chain(Arena* arena, str16 value, str16 other)
{
    str16 result = str16_reserve(arena, value.length + other.length);

    if (result.length == 0) return result;

    mem16_copy(result.memory, value.memory, value.length);

    mem16_copy(result.memory + value.length, other.memory,
        other.length);

    return result;
}

str16
str16_split_on(str16 self, str16 pivot, str16* value)
{
    uptr start = 0;
    uptr index = self.length;
    uptr stop  = self.length;

    str16_find_first(self, pivot, &index);

    if (value != 0)
        *value = str16_slice(self, index + pivot.length, stop);

    return str16_slice(self, start, index);
}

str16
str16_trim_prefix(str16 self, str16 prefix)
{
    if (str16_starts_with(self, prefix) == 0)
        return self;

    return str16_slice(self, prefix.length, self.length);
}

str16
str16_trim_suffix(str16 self, str16 suffix)
{
    if (str16_ends_with(self, suffix) == 0)
        return self;

    uptr length = self.length - suffix.length;

    return str16_slice(self, 0, length);
}

str16
str16_trim_spaces(str16 self)
{
    return str16_trim_spaces_start(str16_trim_spaces_end(self));
}

str16
str16_trim_spaces_start(str16 self)
{
    uptr units = 0;
    uptr start = 0;
    uptr stop  = self.length;

    for (; start < stop; start += units) {
        u32 unicode = 0;

        units = utf16_decode_forw(self.memory,
            self.length, start, &unicode);

        if (units == 0) return self;

        if (ascii_is_space(unicode) == 0)
            break;
    }

    return str16_slice(self, start, stop);
}

str16
str16_trim_spaces_end(str16 self)
{
    uptr units = 0;
    uptr start = 0;
    uptr stop  = self.length;

    for (; start < stop; stop -= units) {
        u32 unicode = 0;

        units = utf16_decode_back(self.memory,
            self.length, stop - 1, &unicode);

        if (units == 0) return self;

        if (ascii_is_space(unicode) == 0)
            break;
    }

    return str16_slice(self, start, stop);
}

b32
str16_find_first(str16 self, str16 value, uptr* index)
{
    return str16_find_first_since(self, value, 0, index);
}

b32
str16_find_first_since(str16 self, str16 value, uptr start, uptr* index)
{
    start = pax_min(start, self.length);

    for (uptr i = start; i < self.length; i += 1) {
        str16 slice = str16_slice_len(self, i, value.length);

        if (str16_is_equal(slice, value) == 0)
            continue;

        if (index != 0) *index = i;

        return 1;
    }

    return 0;
}

b32
str16_find_last(str16 self, str16 value, uptr* index)
{
    return str16_find_last_until(self, value, self.length, index);
}

b32
str16_find_last_until(str16 self, str16 value, uptr start, uptr* index)
{
    start = pax_min(start, self.length);

    for (uptr i = start; i > 0; i -= 1) {
        str16 slice = str16_slice_len(self, i - value.length, value.length);

        if (str16_is_equal(slice, value) == 0)
            continue;

        if (index != 0) *index = i - value.length;

        return 1;
    }

    return 0;
}

uptr
str16_contains(str16 self, str16 value)
{
    uptr result = 0;

    if (value.length > self.length) return result;

    for (uptr i = 0; i < self.length; i += 1) {
        str16 slice = str16_slice_len(self, i, value.length);

        if (str16_is_equal(slice, value) != 0)
            result += 1;
    }

    return result;
}

b32
str16_next(str16 self, uptr index, uptr* units, u32* value)
{
    if (index < 0 || index >= self.length)
        return 0;

    uptr step = utf16_decode_forw(self.memory,
        self.length, index, value);

    if (step == 0) return 0;

    if (units != 0) *units = step;

    return 1;
}

b32
str16_prev(str16 self, uptr index, uptr* units, u32* value)
{
    if (index < 0 || index >= self.length)
        return 0;

    uptr step = utf16_decode_back(self.memory,
        self.length, index, value);

    if (step == 0) return 0;

    if (units != 0) *units = step;

    return 1;
}

} // namespace pax

#endif // PAX_STRING_STR16_CPP
