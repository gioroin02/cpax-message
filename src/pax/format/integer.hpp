#ifndef PAX_FORMAT_INTEGER_HPP
#define PAX_FORMAT_INTEGER_HPP

#include "options.hpp"

namespace pax {

//
// Procs
//

/* str8 parsing */

b32
iptr_from_str8(str8 self, Format_Options opts, iptr* value);

b32
i64_from_str8(str8 self, Format_Options opts, i64* value);

b32
i32_from_str8(str8 self, Format_Options opts, i32* value);

b32
i16_from_str8(str8 self, Format_Options opts, i16* value);

b32
i8_from_str8(str8 self, Format_Options opts, i8* value);

/* str16 parsing */

b32
iptr_from_str16(str16 self, Format_Options opts, iptr* value);

b32
i64_from_str16(str16 self, Format_Options opts, i64* value);

b32
i32_from_str16(str16 self, Format_Options opts, i32* value);

b32
i16_from_str16(str16 self, Format_Options opts, i16* value);

b32
i8_from_str16(str16 self, Format_Options opts, i8* value);

/* str32 parsing */

b32
iptr_from_str32(str32 self, Format_Options opts, iptr* value);

b32
i64_from_str32(str32 self, Format_Options opts, i64* value);

b32
i32_from_str32(str32 self, Format_Options opts, i32* value);

b32
i16_from_str32(str32 self, Format_Options opts, i16* value);

b32
i8_from_str32(str32 self, Format_Options opts, i8* value);

/* Buffer parsing */

/*
b32
iptr_from_buffer(Buffer self, Format_Options opts, iptr* value);

b32
i64_from_buffer(Buffer self, Format_Options opts, i64* value);

b32
i32_from_buffer(Buffer self, Format_Options opts, i32* value);

b32
i16_from_buffer(Buffer self, Format_Options opts, i16* value);

b32
i8_from_buffer(Buffer self, Format_Options opts, i8* value);
*/

/* str8 printing */

str8
str8_from_iptr(Arena* arena, Format_Options opts, iptr value);

str8
str8_from_i64(Arena* arena, Format_Options opts, i64 value);

str8
str8_from_i32(Arena* arena, Format_Options opts, i32 value);

str8
str8_from_i16(Arena* arena, Format_Options opts, i16 value);

str8
str8_from_i8(Arena* arena, Format_Options opts, i8 value);

/* str16 printing */

str16
str16_from_iptr(Arena* arena, Format_Options opts, iptr value);

str16
str16_from_i64(Arena* arena, Format_Options opts, i64 value);

str16
str16_from_i32(Arena* arena, Format_Options opts, i32 value);

str16
str16_from_i16(Arena* arena, Format_Options opts, i16 value);

str16
str16_from_i8(Arena* arena, Format_Options opts, i8 value);

/* str32 printing */

str32
str32_from_iptr(Arena* arena, Format_Options opts, iptr value);

str32
str32_from_i64(Arena* arena, Format_Options opts, i64 value);

str32
str32_from_i32(Arena* arena, Format_Options opts, i32 value);

str32
str32_from_i16(Arena* arena, Format_Options opts, i16 value);

str32
str32_from_i8(Arena* arena, Format_Options opts, i8 value);

/* Buffer printing */

/*
b32
buffer_write_iptr(Buffer* self, Format_Options opts, iptr value);

b32
buffer_write_i64(Buffer* self, Format_Options opts, i64 value);

b32
buffer_write_i32(Buffer* self, Format_Options opts, i32 value);

b32
buffer_write_i16(Buffer* self, Format_Options opts, i16 value);

b32
buffer_write_i8(Buffer* self, Format_Options opts, i8 value);
*/

} // namespace pax

#endif // PAX_FORMAT_INTEGER_HPP
