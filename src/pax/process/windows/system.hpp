#ifndef PAX_PROCESS_WINDOWS_SYSTEM_HPP
#define PAX_PROCESS_WINDOWS_SYSTEM_HPP

#include "imports.hpp"

namespace pax {

//
// Procs
//

/* System */

void
windows_sleep(u32 millis);

uptr
windows_get_number_of_cpus();

uptr
windows_get_thread_ident();

} // namespace pax

#endif // PAX_PROCESS_WINDOWS_SYSTEM_HPP
