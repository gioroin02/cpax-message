#ifndef PX_NETWORK_SYSTEM_C
#define PX_NETWORK_SYSTEM_C

#include "system.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../../windows/network/system.c"

    #define __pxNetworkStart__ pxWindowsNetworkStart
    #define __pxNetworkStop__  pxWindowsNetworkStop

#else

    #error "Unknown platform"

#endif

pxb8
pxNetworkStart()
{
    return __pxNetworkStart__();
}

void
pxNetworkStop()
{
    __pxNetworkStop__();
}

#endif // PX_NETWORK_SYSTEM_C
