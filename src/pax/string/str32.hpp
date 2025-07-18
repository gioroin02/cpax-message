#ifndef PAX_STRING_STR32_HPP
#define PAX_STRING_STR32_HPP

#include "ascii.hpp"
#include "utf32.hpp"

namespace pax {

//
// Types
//

struct str32
{
    u32* memory = 0;
    uptr length = 0;
};

//
// Procs
//

/* str32 */

str32
str32_make(u32* memory, uptr length);

str32
str32_reserve(Arena* arena, uptr length);

str32
str32_copy(Arena* arena, str32 value);

str32
str32_copy_mem(Arena* arena, u32* memory, uptr length);

str32
str32_from_unicode(Arena* arena, u32 value);

b32
str32_get(str32 self, uptr index, u32* value);

u32
str32_get_or(str32 self, uptr index, u32 value);

/* str32 counting */

str32
str32_count(u32* memory);

str32
str32_count_max(u32* memory, uptr limit);

/* str32 comparison */

b32
str32_is_equal(str32 self, str32 value);

b32
str32_starts_with(str32 self, str32 value);

b32
str32_ends_with(str32 self, str32 value);

/* str32 slicing */

str32
str32_slice(str32 self, uptr start, uptr stop);

str32
str32_slice_len(str32 self, uptr start, uptr length);

str32
str32_slice_until_first(str32 self, str32 value);

str32
str32_slice_until_last(str32 self, str32 value);

str32
str32_slice_since_first(str32 self, str32 value);

str32
str32_slice_since_last(str32 self, str32 value);

/* str32 chaining */

str32
str32_chain(Arena* arena, str32 value, str32 other);

/* str32 splitting */

str32
str32_split_on(str32 self, str32 pivot, str32* value);

/* str32 trimming */

str32
str32_trim_prefix(str32 self, str32 prefix);

str32
str32_trim_suffix(str32 self, str32 suffix);

str32
str32_trim_spaces(str32 self);

str32
str32_trim_spaces_start(str32 self);

str32
str32_trim_spaces_end(str32 self);

/* str32 searching */

b32
str32_find_first(str32 self, str32 value, uptr* index);

b32
str32_find_first_since(str32 self, str32 value, uptr start, uptr* index);

b32
str32_find_last(str32 self, str32 value, uptr* index);

b32
str32_find_last_until(str32 self, str32 value, uptr start, uptr* index);

uptr
str32_contains(str32 self, str32 value);

/* str32 iterating */

b32
str32_next(str32 self, uptr index, uptr* units, u32* value);

b32
str32_prev(str32 self, uptr index, uptr* units, u32* value);

} // namespace pax

#endif // PAX_STRING_STR32_HPP
