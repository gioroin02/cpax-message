#ifndef PAX_CORE_BUF8_HPP
#define PAX_CORE_BUF8_HPP

#include "memory.hpp"

namespace pax {

//
// Types
//

struct buf8
{
    u8*  memory = 0;
    uptr length = 0;
    uptr size   = 0;
    uptr head   = 0;
    uptr tail   = 0;
};

//
// Procs
//

/* buf8 */

buf8
buf8_make(u8* memory, uptr length);

buf8
buf8_full(u8* memory, uptr length);

buf8
buf8_reserve(Arena* arena, uptr length);

buf8
buf8_copy(Arena* arena, buf8 value);

buf8
buf8_copy_len(Arena* arena, buf8 value, uptr length);

buf8
buf8_copy_mem(Arena* arena, u8* memory, uptr length);

void
buf8_clear(buf8* self);

void
buf8_normalize(buf8* self);

uptr
buf8_drop_head(buf8* self, uptr offset);

uptr
buf8_drop_tail(buf8* self, uptr offset);

/* buf8 writing */

uptr
buf8_write_head(buf8* self, buf8* value);

uptr
buf8_write_mem8_head(buf8* self, u8* memory, uptr length);

uptr
buf8_write_tail(buf8* self, buf8* value);

uptr
buf8_write_mem8_tail(buf8* self, u8* memory, uptr length);

/* buf8 reading */

uptr
buf8_read_head(buf8* self, buf8* value);

uptr
buf8_read_mem8_head(buf8* self, u8* memory, uptr length);

uptr
buf8_read_tail(buf8* self, buf8* value);

uptr
buf8_read_mem8_tail(buf8* self, u8* memory, uptr length);

} // namespace pax

#endif // PAX_CORE_BUF8_HPP
