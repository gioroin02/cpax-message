#ifndef PAX_STRING_STR16_HPP
#define PAX_STRING_STR16_HPP

#include "ascii.hpp"
#include "utf16.hpp"

//
// Defines
//

#define pax_str16(memory) \
    str16_make(pax_cast(u16*, memory), pax_array_length(memory) - 1)

#define pax_str16_cnt(memory) \
    str16_count(pax_cast(u16*, memory))

#define pax_str16_max(memory, limit) \
    str16_count_max(pax_cast(u16*, memory), limit)

#define pax_to_str16(expr) pax_str16(L pax_string(expr))

namespace pax {

//
// Types
//

struct str16
{
    u16* memory = 0;
    uptr length = 0;
};

//
// Procs
//

/* str16 */

str16
str16_make(u16* memory, uptr length);

str16
str16_reserve(Arena* arena, uptr length);

str16
str16_copy(Arena* arena, str16 value);

str16
str16_copy_mem(Arena* arena, u16* memory, uptr length);

str16
str16_from_unicode(Arena* arena, u32 value);

b32
str16_get(str16 self, uptr index, u16* value);

u16
str16_get_or(str16 self, uptr index, u16 value);

/* str16 counting */

str16
str16_count(u16* memory);

str16
str16_count_max(u16* memory, uptr limit);

/* str16 comparison */

b32
str16_is_equal(str16 self, str16 value);

b32
str16_starts_with(str16 self, str16 value);

b32
str16_ends_with(str16 self, str16 value);

/* str16 slicing */

str16
str16_slice(str16 self, uptr start, uptr stop);

str16
str16_slice_len(str16 self, uptr start, uptr length);

str16
str16_slice_until_first(str16 self, str16 value);

str16
str16_slice_until_last(str16 self, str16 value);

str16
str16_slice_since_first(str16 self, str16 value);

str16
str16_slice_since_last(str16 self, str16 value);

/* str16 chaining */

str16
str16_chain(Arena* arena, str16 value, str16 other);

/* str16 splitting */

str16
str16_split_on(str16 self, str16 pivot, str16* value);

/* str16 trimming */

str16
str16_trim_prefix(str16 self, str16 prefix);

str16
str16_trim_suffix(str16 self, str16 suffix);

str16
str16_trim_spaces(str16 self);

str16
str16_trim_spaces_start(str16 self);

str16
str16_trim_spaces_end(str16 self);

/* str16 searching */

b32
str16_find_first(str16 self, str16 value, uptr* index);

b32
str16_find_first_since(str16 self, str16 value, uptr start, uptr* index);

b32
str16_find_last(str16 self, str16 value, uptr* index);

b32
str16_find_last_until(str16 self, str16 value, uptr start, uptr* index);

uptr
str16_contains(str16 self, str16 value);

/* str16 iterating */

b32
str16_next(str16 self, uptr index, uptr* units, u32* value);

b32
str16_prev(str16 self, uptr index, uptr* units, u32* value);

} // namespace pax

#endif // PAX_STRING_STIRNG16_HPP
