#ifndef PAX_MEMORY_ORDER_HPP
#define PAX_MEMORY_ORDER_HPP

#include "imports.hpp"

namespace pax {

//
// Procs
//

/* Memory */

b32
mem_is_lower_first();

b32
mem_is_upper_first();

addr
mem_host_from_net(addr memory, uptr length);

addr
mem_copy_host_from_net(addr memory, addr value, uptr length);

addr
mem_net_from_host(addr memory, uptr length);

addr
mem_copy_net_from_host(addr memory, addr value, uptr length);

/* 64 bits */

f64
f64_host_from_net(u64 value);

i64
i64_host_from_net(u64 value);

u64
u64_host_from_net(u64 value);

u64
f64_net_from_host(f64 value);

u64
i64_net_from_host(i64 value);

u64
u64_net_from_host(u64 value);

/* 32 bits */

f32
f32_host_from_net(u32 value);

i32
i32_host_from_net(u32 value);

u32
u32_host_from_net(u32 value);

u32
f32_net_from_host(f32 value);

u32
i32_net_from_host(i32 value);

u32
u32_net_from_host(u32 value);

/* 16 bits */

i16
i16_host_from_net(u16 value);

u16
u16_host_from_net(u16 value);

u16
i16_net_from_host(i16 value);

u16
u16_net_from_host(u16 value);

} // namespace pax

#endif // PAX_MEMORY_ORDER_HPP
