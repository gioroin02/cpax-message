#ifndef PAX_STRING_BUF16_HPP
#define PAX_STRING_BUF16_HPP

#include "convert.hpp"

namespace pax {

//
// Procs
//

/* buf16 writing */

uptr
buf16_write_codepoint_head(buf16* self, u32 value);

uptr
buf16_write_codepoint_tail(buf16* self, u32 value);

uptr
buf16_write_str8_head(buf16* self, str8 value);

uptr
buf16_write_str8_tail(buf16* self, str8 value);

uptr
buf16_write_str16_head(buf16* self, str16 value);

uptr
buf16_write_str16_tail(buf16* self, str16 value);

uptr
buf16_write_str32_head(buf16* self, str32 value);

uptr
buf16_write_str32_tail(buf16* self, str32 value);

/* buf16 reading */

uptr
buf16_read_codepoint_head(buf16* self, u32* value);

uptr
buf16_read_codepoint_tail(buf16* self, u32* value);

str16
buf16_read_str16_head(buf16* self, Arena* arena, uptr length);

str16
buf16_read_str16_tail(buf16* self, Arena* arena, uptr length);

} // namespace pax

#endif // PAX_STRING_BUF16_HPP
