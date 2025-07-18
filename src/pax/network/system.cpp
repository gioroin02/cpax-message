#ifndef PAX_NETWORK_SYSTEM_CPP
#define PAX_NETWORK_SYSTEM_CPP

#include "system.hpp"

#if PAX_PLATFORM == PAX_PLATFORM_WINDOWS

    #include "windows/system.cpp"

    #define __system_network_start__ windows_network_start
    #define __system_network_stop__  windows_network_stop

#else

    #error "Platform not supported or unknown"

#endif

namespace pax {

b32
system_network_start()
{
    return __system_network_start__();
}

void
system_network_stop()
{
    __system_network_stop__();
}

} // namespace pax

#endif // PAX_NETWORK_SYSTEM_CPP
