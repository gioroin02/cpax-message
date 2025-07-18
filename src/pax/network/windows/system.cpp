#ifndef PAX_NETWORK_WINDOWS_SYSTEM_CPP
#define PAX_NETWORK_WINDOWS_SYSTEM_CPP

#include "system.hpp"

#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOMINMAX

#include <winsock2.h>

namespace pax {

b32
windows_network_start()
{
    WSADATA data = {};

    if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
        return 0;

    return 1;
}

void
windows_network_stop()
{
    WSACleanup();
}

} // namespace pax

#endif // PAX_NETWORK_WINDOWS_SYSTEM_CPP
