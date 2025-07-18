#ifndef PAX_CORE_BUF32_HPP
#define PAX_CORE_BUF32_HPP

#include "memory.hpp"

namespace pax {

//
// Types
//

struct buf32
{
    u32* memory = 0;
    uptr length = 0;
    uptr size   = 0;
    uptr head   = 0;
    uptr tail   = 0;
};

//
// Procs
//

/* buf32 */

buf32
buf32_make(u32* memory, uptr length);

buf32
buf32_full(u32* memory, uptr length);

buf32
buf32_reserve(Arena* arena, uptr length);

buf32
buf32_copy(Arena* arena, buf32 value);

buf32
buf32_copy_len(Arena* arena, buf32 value, uptr length);

buf32
buf32_copy_mem(Arena* arena, u32* memory, uptr length);

void
buf32_clear(buf32* self);

void
buf32_normalize(buf32* self);

uptr
buf32_drop_head(buf32* self, uptr offset);

uptr
buf32_drop_tail(buf32* self, uptr offset);

/* buf32 writing */

uptr
buf32_write_head(buf32* self, buf32* value);

uptr
buf32_write_mem32_head(buf32* self, u32* memory, uptr length);

uptr
buf32_write_tail(buf32* self, buf32* value);

uptr
buf32_write_mem32_tail(buf32* self, u32* memory, uptr length);

/* buf32 reading */

uptr
buf32_read_head(buf32* self, buf32* value);

uptr
buf32_read_mem32_head(buf32* self, u32* memory, uptr length);

uptr
buf32_read_tail(buf32* self, buf32* value);

uptr
buf32_read_mem32_tail(buf32* self, u32* memory, uptr length);

} // namespace pax

#endif // PAX_CORE_BUF8_HPP
