#ifndef PAX_PROCESS_SYSTEM_CPP
#define PAX_PROCESS_SYSTEM_CPP

#include "system.hpp"

#if PAX_PLATFORM == PAX_PLATFORM_WINDOWS

    #include "windows/system.cpp"

    #define __system_sleep__              windows_sleep
    #define __system_get_number_of_cpus__ windows_get_number_of_cpus
    #define __system_get_thread_ident__   windows_get_thread_ident

#else

    #error "Platform not supported or unknown"

#endif

namespace pax {

void
system_sleep(u32 millis)
{
    __system_sleep__(millis);
}

uptr
system_get_number_of_cpus()
{
    return __system_get_number_of_cpus__();
}

uptr
system_get_thread_ident()
{
    return __system_get_thread_ident__();
}

} // namespace pax

#endif // PAX_PROCESS_SYSTEM_CPP
