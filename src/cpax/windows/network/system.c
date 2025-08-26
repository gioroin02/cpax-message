#ifndef PX_WINDOWS_NETWORK_SYSTEM_C
#define PX_WINDOWS_NETWORK_SYSTEM_C

#include "system.h"

#define NOMINMAX
#define NOGDI
#define WIN32_MEAN_AND_LEAN

#include <winsock2.h>

pxb8
pxWindowsNetworkStart()
{
    WSADATA data = {0};

    if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
        return 0;

    return 1;
}

void
pxWindowsNetworkStop()
{
    WSACleanup();
}

#endif // PX_WINDOWS_NETWORK_SYSTEM_C
