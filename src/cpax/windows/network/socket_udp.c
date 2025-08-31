#ifndef PX_WINDOWS_NETWORK_SOCKET_UDP_C
#define PX_WINDOWS_NETWORK_SOCKET_UDP_C

#include "import.h"

#define NOMINMAX
#define NOGDI
#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>

#ifndef PX_WINDOWS_NETWORK_SOCKET
#define PX_WINDOWS_NETWORK_SOCKET

typedef struct sockaddr_storage PxSockData;
typedef struct sockaddr         PxSock;
typedef struct sockaddr_in      PxSockIp4;
typedef struct sockaddr_in6     PxSockIp6;

#define PX_SOCK_DATA_SIZE pxSize(PxSockData)
#define PX_SOCK_IP4_SIZE  pxSize(PxSockIp4)
#define PX_SOCK_IP6_SIZE  pxSize(PxSockIp6)

#define pxSock(x)    pxCast(PxSock*, x)
#define pxSockIp4(x) pxCast(PxSockIp4*, x)
#define pxSockIp6(x) pxCast(PxSockIp6*, x)

#define pxSockIp4Addr(x) pxCast(void*,  &pxSockIp4(x)->sin_addr.s_addr)
#define pxSockIp4Port(x) pxCast(pxu16*, &pxSockIp4(x)->sin_port)

#define pxSockIp6Addr(x) pxCast(void*,  pxSockIp6(x)->sin6_addr.s6_addr)
#define pxSockIp6Port(x) pxCast(pxu16*, &pxSockIp6(x)->sin6_port)

#endif // PX_WINDOWS_NETWORK_SOCKET

typedef struct PxWindowsSocketUdp
{
    SOCKET     handle;
    PxSockData address;
}
PxWindowsSocketUdp;

PxWindowsSocketUdp*
pxWindowsSocketUdpCreate(PxArena* arena, PxAddressType type)
{
    pxiword offset = pxArenaOffset(arena);
    pxiword family = 0;

    switch (type) {
        case PX_ADDRESS_TYPE_IP4: family = AF_INET;  break;
        case PX_ADDRESS_TYPE_IP6: family = AF_INET6; break;

        default: return 0;
    }

    PxWindowsSocketUdp* result =
        pxArenaReserve(arena, PxWindowsSocketUdp, 1);

    if (result != 0) {
        result->handle = socket(family, SOCK_DGRAM, 0);

        result->address.ss_family = family;

        if (result->handle != INVALID_SOCKET)
            return result;
    }

    pxArenaRewind(arena, offset);

    return 0;
}

void
pxWindowsSocketUdpDestroy(PxWindowsSocketUdp* self)
{
    if (self == 0) return;

    if (self->handle != INVALID_SOCKET)
        closesocket(self->handle);

    self->handle  = INVALID_SOCKET;
    self->address = (PxSockData) {0};
}

PxAddress
pxWindowsSocketUdpGetAddress(PxWindowsSocketUdp* self)
{
    PxAddress result = {.type = PX_ADDRESS_TYPE_NONE};

    switch (self->address.ss_family) {
        case AF_INET: {
            result.type = PX_ADDRESS_TYPE_IP4;

            void* addr = pxSockIp4Addr(&self->address);

            pxMemoryCopy(result.ip4.memory, addr,
                PX_ADDRESS_IP4_GROUPS, 1);
        } break;

        case AF_INET6: {
            result.type = PX_ADDRESS_TYPE_IP6;

            void* addr = pxSockIp6Addr(&self->address);

            pxMemoryCopy(result.ip6.memory, addr,
                PX_ADDRESS_IP6_GROUPS, 2);

            pxMemoryFlip(result.ip6.memory,
                PX_ADDRESS_IP6_GROUPS, 2);

            pxMemoryFlip(result.ip6.memory,
                PX_ADDRESS_IP6_GROUPS * 2, 1);
        } break;

        default: break;
    }

    return result;
}

pxu16
pxWindowsSocketUdpGetPort(PxWindowsSocketUdp* self)
{
    pxu16 temp = 0;

    switch (self->address.ss_family) {
        case AF_INET:
            temp = *pxSockIp4Port(&self->address);
        break;

        case AF_INET6:
            temp = *pxSockIp6Port(&self->address);
        break;

        default: break;
    }

    return pxU16HostFromNet(temp);
}

pxb8
pxWindowsSocketUdpBind(PxWindowsSocketUdp* self, PxAddress address, pxu16 port)
{
    pxiword family = 0;

    switch (address.type) {
        case PX_ADDRESS_TYPE_IP4: family = AF_INET;  break;
        case PX_ADDRESS_TYPE_IP6: family = AF_INET6; break;

        default: return 0;
    }

    if (self->address.ss_family != family) return 0;

    PxSockData data = {0};
    pxiword    size = 0;

    switch (address.type) {
        case PX_ADDRESS_TYPE_IP4: {
            data.ss_family = AF_INET;
            size           = PX_SOCK_IP4_SIZE;

            pxMemoryCopy(pxSockIp4Addr(&data),
                address.ip4.memory, PX_ADDRESS_IP4_GROUPS, 1);

            pxMemoryCopyNetFromHost(pxSockIp4Port(&data),
                &port, 1, 2);
        } break;

        case PX_ADDRESS_TYPE_IP6: {
            data.ss_family = AF_INET6;
            size           = PX_SOCK_IP6_SIZE;

            pxMemoryCopy(pxSockIp6Addr(&data),
                address.ip6.memory, PX_ADDRESS_IP6_GROUPS, 2);

            pxMemoryFlip(pxSockIp6Addr(&data),
                PX_ADDRESS_IP6_GROUPS, 2);

            pxMemoryFlip(pxSockIp6Addr(&data),
                PX_ADDRESS_IP6_GROUPS * 2, 1);

            pxMemoryCopyNetFromHost(pxSockIp6Port(&data),
                &port, 1, 2);
        } break;

        default: return 0;
    }

    if (bind(self->handle, pxSock(&data), size) == SOCKET_ERROR)
        return 0;

    self->address = data;

    return 1;
}

pxb8
pxWindowsSocketUdpListen(PxWindowsSocketUdp* self)
{
    if (listen(self->handle, SOMAXCONN) == SOCKET_ERROR)
        return 0;

    return 1;
}

pxb8
pxWindowsSocketUdpConnect(PxWindowsSocketUdp* self, PxAddress address, pxu16 port)
{
    PxSockData data = {0};
    pxiword    size = 0;

    switch (address.type) {
        case PX_ADDRESS_TYPE_IP4: {
            data.ss_family = AF_INET;
            size           = PX_SOCK_IP4_SIZE;

            pxMemoryCopy(pxSockIp4Addr(&data),
                address.ip4.memory, PX_ADDRESS_IP4_GROUPS, 1);

            pxMemoryCopyNetFromHost(pxSockIp4Port(&data),
                &port, 1, 2);
        } break;

        case PX_ADDRESS_TYPE_IP6: {
            data.ss_family = AF_INET6;
            size           = PX_SOCK_IP6_SIZE;

            pxMemoryCopy(pxSockIp6Addr(&data),
                address.ip6.memory, PX_ADDRESS_IP6_GROUPS, 2);

            pxMemoryFlip(pxSockIp6Addr(&data),
                PX_ADDRESS_IP6_GROUPS, 2);

            pxMemoryFlip(pxSockIp6Addr(&data),
                PX_ADDRESS_IP6_GROUPS * 2, 1);

            pxMemoryCopyNetFromHost(pxSockIp6Port(&data),
                &port, 1, 2);
        } break;

        default: return 0;
    }

    if (connect(self->handle, pxSock(&data), size) == SOCKET_ERROR)
        return 0;

    self->address = data;

    return 1;
}

PxWindowsSocketUdp*
pxWindowsSocketUdpAccept(PxWindowsSocketUdp* self, PxArena* arena)
{
    pxiword offset = pxArenaOffset(arena);

    PxWindowsSocketUdp* result =
        pxArenaReserve(arena, PxWindowsSocketUdp, 1);

    if (result != 0) {
        PxSockData data = {0};
        pxiword    size = PX_SOCK_DATA_SIZE;

        result->handle = accept(self->handle,
            pxSock(&data), pxCast(int*, &size));

        result->address = data;

        if (result->handle != INVALID_SOCKET)
            return result;
    }

    pxArenaRewind(arena, offset);

    return 0;
}

pxiword
pxWindowsSocketUdpWriteMemory(PxWindowsSocketUdp* self, void* memory, pxiword amount, pxiword stride)
{
    pxiword length = amount * stride;

    for (pxiword i = 0; i < length;) {
        char* mem = pxCast(char*, memory + i);
        int   len = pxCast(int,   length - i);

        pxiword temp = send(self->handle, mem, len, 0);

        if (temp > 0 && temp <= length - i)
            i += temp;
        else
            return i;
    }

    return length;
}

pxiword
pxWindowsSocketUdpWriteHostMemory(PxWindowsSocketUdp* self, void* memory, pxiword amount, pxiword stride, PxAddress address, pxu16 port)
{
    PxSockData data = {0};
    pxiword    size = 0;

    switch (address.type) {
        case PX_ADDRESS_TYPE_IP4: {
            data.ss_family = AF_INET;
            size           = PX_SOCK_IP4_SIZE;

            pxMemoryCopy(pxSockIp4Addr(&data),
                address.ip4.memory, PX_ADDRESS_IP4_GROUPS, 1);

            pxMemoryCopyNetFromHost(pxSockIp4Port(&data),
                &port, 1, 2);
        } break;

        case PX_ADDRESS_TYPE_IP6: {
            data.ss_family = AF_INET6;
            size           = PX_SOCK_IP6_SIZE;

            pxMemoryCopy(pxSockIp6Addr(&data),
                address.ip6.memory, PX_ADDRESS_IP6_GROUPS, 2);

            pxMemoryFlip(pxSockIp6Addr(&data),
                PX_ADDRESS_IP6_GROUPS, 2);

            pxMemoryFlip(pxSockIp6Addr(&data),
                PX_ADDRESS_IP6_GROUPS * 2, 1);

            pxMemoryCopyNetFromHost(pxSockIp6Port(&data),
                &port, 1, 2);
        } break;

        default: return 0;
    }

    pxiword length = amount * stride;

    for (pxiword i = 0; i < length;) {
        char* mem = pxCast(char*, memory + i);
        int   len = pxCast(int,   length - i);

        pxiword temp = sendto(self->handle, mem, len, 0,
            pxSock(&data), size);

        if (temp > 0 && temp <= length - i)
            i += temp;
        else
            return i;
    }

    return length;
}

pxiword
pxWindowsSocketUdpReadMemory(PxWindowsSocketUdp* self, void* memory, pxiword amount, pxiword stride)
{
    pxiword length = amount * stride;

    char* mem = pxCast(char*, memory);
    int   len = pxCast(int,   length);

    pxiword temp = recv(self->handle, mem, len, 0);

    if (temp > 0 && temp <= length)
        return temp;

    return 0;
}

pxiword
pxWindowsSocketUdpReadHostMemory(PxWindowsSocketUdp* self, void* memory, pxiword amount, pxiword stride, PxAddress* address, pxu16* port)
{
    PxSockData data = {0};
    pxiword    size = PX_SOCK_DATA_SIZE;

    pxiword length = amount * stride;

    char* mem = pxCast(char*, memory);
    int   len = pxCast(int,   length);

    pxiword temp = recvfrom(self->handle, mem, len, 0,
        pxSock(&data), pxCast(int*, &size));

    if (temp <= 0 || temp > length) return 0;

    switch (data.ss_family) {
        case AF_INET: {
            if (port != 0)
                pxMemoryCopyHostFromNet(port, pxSockIp4Port(&data), 1, 2);

            if (address != 0) {
                address->type = PX_ADDRESS_TYPE_IP4;

                pxMemoryCopy(address->ip4.memory,
                    pxSockIp4Addr(&data), PX_ADDRESS_IP4_GROUPS, 1);
            }
        } break;

        case AF_INET6: {
            if (port != 0)
                pxMemoryCopyHostFromNet(port, pxSockIp6Port(&data), 1, 2);

            if (address != 0) {
                address->type = PX_ADDRESS_TYPE_IP6;

                pxMemoryCopy(address->ip6.memory,
                    pxSockIp6Addr(&data), PX_ADDRESS_IP6_GROUPS, 2);

                pxMemoryFlip(address->ip6.memory,
                    PX_ADDRESS_IP6_GROUPS, 2);

                pxMemoryFlip(address->ip6.memory,
                    PX_ADDRESS_IP6_GROUPS * 2, 1);
            }
        } break;

        default: break;
    }

    return temp;
}

#endif // PX_WINDOWS_NETWORK_SOCKET_UDP_C
