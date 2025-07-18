#ifndef PAX_MEMORY_SYSTEM_HPP
#define PAX_MEMORY_SYSTEM_HPP

#include "imports.hpp"

namespace pax {

uptr
system_get_page_size();

Arena
system_reserve(uptr pages);

void
system_release(Arena* arena);

} // namespace pax

#endif // PAX_MEMORY_SYSTEM_HPP
