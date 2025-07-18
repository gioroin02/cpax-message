#ifndef PAX_STRING_BUF8_HPP
#define PAX_STRING_BUF8_HPP

#include "convert.hpp"

namespace pax {

//
// Procs
//

/* buf8 writing */

uptr
buf8_write_codepoint_head(buf8* self, u32 value);

uptr
buf8_write_codepoint_tail(buf8* self, u32 value);

uptr
buf8_write_str8_head(buf8* self, str8 value);

uptr
buf8_write_str8_tail(buf8* self, str8 value);

uptr
buf8_write_str16_head(buf8* self, str16 value);

uptr
buf8_write_str16_tail(buf8* self, str16 value);

uptr
buf8_write_str32_head(buf8* self, str32 value);

uptr
buf8_write_str32_tail(buf8* self, str32 value);

/* buf8 reading */

uptr
buf8_read_codepoint_head(buf8* self, u32* value);

uptr
buf8_read_codepoint_tail(buf8* self, u32* value);

str8
buf8_read_str8_head(buf8* self, Arena* arena, uptr length);

str8
buf8_read_str8_tail(buf8* self, Arena* arena, uptr length);

} // namespace pax

#endif // PAX_STRING_BUF8_HPP
