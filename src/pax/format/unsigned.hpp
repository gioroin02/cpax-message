#ifndef PAX_FORMAT_UNSIGNED_HPP
#define PAX_FORMAT_UNSIGNED_HPP

#include "options.hpp"

namespace pax {

//
// Procs
//

/* str8 parsing */

b32
uptr_from_str8(str8 self, Format_Options opts, uptr* value);

b32
u64_from_str8(str8 self, Format_Options opts, u64* value);

b32
u32_from_str8(str8 self, Format_Options opts, u32* value);

b32
u16_from_str8(str8 self, Format_Options opts, u16* value);

b32
u8_from_str8(str8 self, Format_Options opts, u8* value);

/* str16 parsing */

b32
uptr_from_str16(str16 self, Format_Options opts, uptr* value);

b32
u64_from_str16(str16 self, Format_Options opts, u64* value);

b32
u32_from_str16(str16 self, Format_Options opts, u32* value);

b32
u16_from_str16(str16 self, Format_Options opts, u16* value);

b32
u8_from_str16(str16 self, Format_Options opts, u8* value);

/* str32 parsing */

b32
uptr_from_str32(str32 self, Format_Options opts, uptr* value);

b32
u64_from_str32(str32 self, Format_Options opts, u64* value);

b32
u32_from_str32(str32 self, Format_Options opts, u32* value);

b32
u16_from_str32(str32 self, Format_Options opts, u16* value);

b32
u8_from_str32(str32 self, Format_Options opts, u8* value);

/* Buffer parsing */

/*
b32
uptr_from_buffer(Buffer self, Format_Options opts, uptr *value);

b32
u64_from_buffer(Buffer self, Format_Options opts, u64* value);

b32
u32_from_buffer(Buffer self, Format_Options opts, u32* value);

b32
u16_from_buffer(Buffer self, Format_Options opts, u16* value);

b32
u8_from_buffer(Buffer self, Format_Options opts, u8* value);
*/

/* str8 printing */

str8
str8_from_uptr(Arena* arena, Format_Options opts, uptr value);

str8
str8_from_u64(Arena* arena, Format_Options opts, u64 value);

str8
str8_from_u32(Arena* arena, Format_Options opts, u32 value);

str8
str8_from_u16(Arena* arena, Format_Options opts, u16 value);

str8
str8_from_u8(Arena* arena, Format_Options opts, u8 value);

/* str16 printing */

str16
str16_from_uptr(Arena* arena, Format_Options opts, uptr value);

str16
str16_from_u64(Arena* arena, Format_Options opts, u64 value);

str16
str16_from_u32(Arena* arena, Format_Options opts, u32 value);

str16
str16_from_u16(Arena* arena, Format_Options opts, u16 value);

str16
str16_from_u8(Arena* arena, Format_Options opts, u8 value);

/* str32 printing */

str32
str32_from_uptr(Arena* arena, Format_Options opts, uptr value);

str32
str32_from_u64(Arena* arena, Format_Options opts, u64 value);

str32
str32_from_u32(Arena* arena, Format_Options opts, u32 value);

str32
str32_from_u16(Arena* arena, Format_Options opts, u16 value);

str32
str32_from_u8(Arena* arena, Format_Options opts, u8 value);

/* Buffer printing */

/*
b32
buffer_write_uptr(Buffer* self, Format_Options opts, uptr value);

b32
buffer_write_u64(Buffer* self, Format_Options opts, u64 value);

b32
buffer_write_u32(Buffer* self, Format_Options opts, u32 value);

b32
buffer_write_u16(Buffer* self, Format_Options opts, u16 value);

b32
buffer_write_u8(Buffer* self, Format_Options opts, u8 value);
*/

} // namespace pax

#endif // PAX_FORMAT_UNSIGNED_HPP
