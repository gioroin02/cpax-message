#ifndef PAX_MEMORY_WINDOWS_SYSTEM_HPP
#define PAX_MEMORY_WINDOWS_SYSTEM_HPP

#include "imports.hpp"

namespace pax {

//
// Procs
//

/* System */

uptr
windows_get_page_size();

Arena
windows_reserve(uptr pages);

void
windows_release(Arena* arena);

} // namespace pax

#endif // PAX_MEMORY_WINDOWS_SYSTEM_HPP
