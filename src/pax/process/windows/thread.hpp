#ifndef PAX_PROCESS_WINDOWS_THREAD_HPP
#define PAX_PROCESS_WINDOWS_THREAD_HPP

#include "imports.hpp"

//
// Defines
//

namespace pax {

//
// Types
//

using Windows_Routine = u32 (addr);

struct Windows_Thread;

//
// Procs
//

/* Windows_Thread */

Windows_Thread*
windows_thread_create(Arena* arena, Windows_Routine* routine, addr argumns);

void
windows_thread_destroy(Windows_Thread* self);

void
windows_thread_wait(Windows_Thread* self);

void
windows_thread_detach(Windows_Thread* self);

b32
windows_thread_is_running(Windows_Thread* self);

} // namespace pax

#endif // PAX_PROCESS_WINDOWS_THREAD_HPP
