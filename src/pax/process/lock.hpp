#ifndef PAX_PROCESS_LOCK_HPP
#define PAX_PROCESS_LOCK_HPP

#include "imports.hpp"

namespace pax {

//
// Types
//

using Lock = addr;

//
// Procs
//

/* Lock */

Lock
lock_create(Arena* arena);

void
lock_destroy(Lock self);

b32
lock_enter(Lock self);

b32
lock_leave(Lock self);

} // namespace pax

#endif // PAX_PROCESS_LOCK_HPP
