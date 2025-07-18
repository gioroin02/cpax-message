#ifndef PAX_PROCESS_THREAD_HPP
#define PAX_PROCESS_THREAD_HPP

#include "imports.hpp"

namespace pax {

//
// Types
//

using Routine = u32 (addr);
using Thread  = addr;

//
// Procs
//

/* Thread */

Thread
thread_create(Arena* arena, Routine* routine, addr argumns);

void
thread_destroy(Thread self);

void
thread_wait(Thread self);

void
thread_detach(Thread self);

b32
thread_is_running(Thread self);

} // namespace pax

#endif // PAX_PROCESS_THREAD_HPP
