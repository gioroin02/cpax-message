#ifndef PAX_CORE_BUF16_HPP
#define PAX_CORE_BUF16_HPP

#include "memory.hpp"

namespace pax {

//
// Types
//

struct buf16
{
    u16* memory = 0;
    uptr length = 0;
    uptr size   = 0;
    uptr head   = 0;
    uptr tail   = 0;
};

//
// Procs
//

/* buf16 */

buf16
buf16_make(u16* memory, uptr length);

buf16
buf16_full(u16* memory, uptr length);

buf16
buf16_reserve(Arena* arena, uptr length);

buf16
buf16_copy(Arena* arena, buf16 value);

buf16
buf16_copy_len(Arena* arena, buf16 value, uptr length);

buf16
buf16_copy_mem(Arena* arena, u16* memory, uptr length);

void
buf16_clear(buf16* self);

void
buf16_normalize(buf16* self);

uptr
buf16_drop_head(buf16* self, uptr offset);

uptr
buf16_drop_tail(buf16* self, uptr offset);

/* buf16 writing */

uptr
buf16_write_head(buf16* self, buf16* value);

uptr
buf16_write_mem16_head(buf16* self, u16* memory, uptr length);

uptr
buf16_write_tail(buf16* self, buf16* value);

uptr
buf16_write_mem16_tail(buf16* self, u16* memory, uptr length);

/* buf16 reading */

uptr
buf16_read_head(buf16* self, buf16* value);

uptr
buf16_read_mem16_head(buf16* self, u16* memory, uptr length);

uptr
buf16_read_tail(buf16* self, buf16* value);

uptr
buf16_read_mem16_tail(buf16* self, u16* memory, uptr length);

} // namespace pax

#endif // PAX_CORE_BUF8_HPP
