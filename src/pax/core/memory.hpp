#ifndef PAX_CORE_MEMORY_HPP
#define PAX_CORE_MEMORY_HPP

#include "types.hpp"

//
// Defines
//

#define pax_arena(expr) \
    arena_make(pax_cast(u8*, expr), pax_array_length(expr))

namespace pax {

//
// Values
//

static const uptr MEMORY_KB = 1000;
static const uptr MEMORY_MB = MEMORY_KB * MEMORY_KB;
static const uptr MEMORY_GB = MEMORY_MB * MEMORY_KB;

static const uptr MEMORY_KIB = 1024;
static const uptr MEMORY_MIB = MEMORY_KIB * MEMORY_KIB;
static const uptr MEMORY_GIB = MEMORY_MIB * MEMORY_KIB;

//
// Types
//

struct Arena
{
    u8*  memory = 0;
    uptr length = 0;
    uptr offset = 0;
};

//
// Procs
//

/* Memory */

addr
mem8_zero(addr memory, uptr length);

addr
mem8_copy(addr memory, addr value, uptr length);

addr
mem8_copy_flipped(addr memory, addr value, uptr length);

addr
mem8_move_back(addr memory, uptr length, uptr offset);

addr
mem8_move_forw(addr memory, uptr length, uptr offset);

addr
mem8_flip(addr memory, uptr length);

b32
mem8_is_equal(addr memory, addr value, uptr length);

addr
mem16_zero(addr memory, uptr length);

addr
mem16_copy(addr memory, addr value, uptr length);

addr
mem16_copy_flipped(addr memory, addr value, uptr length);

addr
mem16_move_back(addr memory, uptr length, uptr offset);

addr
mem16_move_forw(addr memory, uptr length, uptr offset);

addr
mem16_flip(addr memory, uptr length);

b32
mem16_is_equal(addr memory, addr value, uptr length);

addr
mem32_zero(addr memory, uptr length);

addr
mem32_copy(addr memory, addr value, uptr length);

addr
mem32_copy_flipped(addr memory, addr value, uptr length);

addr
mem32_move_back(addr memory, uptr length, uptr offset);

addr
mem32_move_forw(addr memory, uptr length, uptr offset);

addr
mem32_flip(addr memory, uptr length);

b32
mem32_is_equal(addr memory, addr value, uptr length);

addr
mem64_zero(addr memory, uptr length);

addr
mem64_copy(addr memory, addr value, uptr length);

addr
mem64_copy_flipped(addr memory, addr value, uptr length);

addr
mem64_move_back(addr memory, uptr length, uptr offset);

addr
mem64_move_forw(addr memory, uptr length, uptr offset);

addr
mem64_flip(addr memory, uptr length);

b32
mem64_is_equal(addr memory, addr value, uptr length);

uptr
align_forward(uptr value, uptr align);

/* Arena */

Arena
arena_make(u8* memory, uptr length);

Arena
arena_reserve(Arena* self, uptr size);

b32
arena_release(Arena* self, addr value);

void
arena_clear(Arena* self);

uptr
arena_offset(Arena* self);

b32
arena_rewind(Arena* self, uptr offset);

//
// Templs
//

template <class T>
T*
arena_reserve_one(Arena* self)
{
    uptr  size   = pax_size_of(T);
    Arena result = arena_reserve(self, size);

    return pax_cast(T*, result.memory);
}

template <class T>
T*
arena_reserve_arr(Arena* self, uptr amount)
{
    uptr  size   = pax_size_of(T) * amount;
    Arena result = arena_reserve(self, size);

    return pax_cast(T*, result.memory);
}

} // namespace pax

#endif // PAX_CORE_MEMORY_HPP
