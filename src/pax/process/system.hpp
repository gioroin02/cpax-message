#ifndef PAX_PROCESS_SYSTEM_HPP
#define PAX_PROCESS_SYSTEM_HPP

#include "imports.hpp"

namespace pax {

//
// Procs
//

/* System */

void
system_sleep(u32 millis);

uptr
system_get_number_of_cpus();

uptr
system_get_thread_ident();

} // namespace pax

#endif // PAX_PROCESS_SYSTEM_HPP
