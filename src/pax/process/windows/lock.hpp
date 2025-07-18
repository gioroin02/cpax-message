#ifndef PAX_PROCESS_WINDOWS_LOCK_HPP
#define PAX_PROCESS_WINDOWS_LOCK_HPP

#include "imports.hpp"

namespace pax {

//
// Types
//

struct Windows_Lock;

//
// Procs
//

/* Windows_Lock */

Windows_Lock*
windows_lock_create(Arena* arena);

void
windows_lock_destroy(Windows_Lock* self);

b32
windows_lock_enter(Windows_Lock* self);

b32
windows_lock_leave(Windows_Lock* self);

} // namespace pax

#endif // PAX_PROCESS_WINDOWS_LOCK_HPP
