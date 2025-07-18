#ifndef PAX_STRING_CONVERT_HPP
#define PAX_STRING_CONVERT_HPP

#include "str8.hpp"
#include "str16.hpp"
#include "str32.hpp"

namespace pax {

//
// Procs
//

/* Unicode */

uptr
utf8_units_from_utf16(u16* memory, uptr length);

uptr
utf8_units_from_utf32(u32* value, uptr length);

uptr
utf16_units_from_utf8(u8* memory, uptr length);

uptr
utf16_units_from_utf32(u32* value, uptr length);

uptr
utf32_units_from_utf8(u8* memory, uptr length);

uptr
utf32_units_from_utf16(u16* value, uptr length);

/* Unicode */

uptr
utf8_units_from_str16(str16 value);

uptr
utf8_units_from_str32(str32 value);

uptr
utf16_units_from_str8(str8 value);

uptr
utf16_units_from_str32(str32 value);

uptr
utf32_units_from_str8(str8 value);

uptr
utf32_units_from_str16(str16 value);

/* str8 */

str8
str8_from_str16(Arena* arena, str16 value);

str8
str8_from_str32(Arena* arena, str32 value);

/* str16 */

str16
str16_from_str8(Arena* arena, str8 value);

str16
str16_from_str32(Arena* arena, str32 value);

/* str32 */

str32
str32_from_str8(Arena* arena, str8 value);

str32
str32_from_str16(Arena* arena, str16 value);

} // namespace pax

#endif // PAX_STRING_CONVERT_HPP
