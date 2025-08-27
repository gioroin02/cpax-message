#ifndef PX_WINDOWS_NETWORK_SOCKET_TCP_C
#define PX_WINDOWS_NETWORK_SOCKET_TCP_C

#include "import.h"

#define NOMINMAX
#define NOGDI
#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>

typedef struct sockaddr_storage PxSockTcpData;
typedef struct sockaddr         PxSockTcpAddr;
typedef struct sockaddr_in      PxSockTcpIp4;
typedef struct sockaddr_in6     PxSockTcpIp6;

#define PX_SOCK_TCP_DATA_SIZE pxSize(PxSockTcpData)
#define PX_SOCK_TCP_IP4_SIZE  pxSize(PxSockTcpIp4)
#define PX_SOCK_TCP_IP6_SIZE  pxSize(PxSockTcpIp6)

#define pxSockTcpAddr(x) pxCast(PxSockTcpAddr*, x)
#define pxSockTcpIp4(x)  pxCast(PxSockTcpIp4*, x)
#define pxSockTcpIp6(x)  pxCast(PxSockTcpIp6*, x)

#define pxSockTcpIp4Addr(x) pxCast(void*,  &pxSockTcpIp4(&x)->sin_addr.s_addr)
#define pxSockTcpIp4Port(x) pxCast(pxu16*, &pxSockTcpIp4(&x)->sin_port)

#define pxSockTcpIp6Addr(x) pxCast(void*,  pxSockTcpIp6(&x)->sin6_addr.s6_addr)
#define pxSockTcpIp6Port(x) pxCast(pxu16*, &pxSockTcpIp6(&x)->sin6_port)

typedef struct PxWindowsSocketTcp
{
    SOCKET        handle;
    PxSockTcpData address;
}
PxWindowsSocketTcp;

PxWindowsSocketTcp*
pxWindowsSocketTcpCreate(PxArena* arena, PxAddressType type)
{
    pxiword offset = pxArenaOffset(arena);
    pxiword family = 0;

    switch (type) {
        case PX_ADDRESS_TYPE_IP4: family = AF_INET;  break;
        case PX_ADDRESS_TYPE_IP6: family = AF_INET6; break;

        default: return 0;
    }

    PxWindowsSocketTcp* result =
        pxArenaReserve(arena, PxWindowsSocketTcp, 1);

    if (result != 0) {
        result->handle  = socket(family, SOCK_STREAM, 0);
        result->address = (PxSockTcpData) {.ss_family = family};

        if (result->handle != INVALID_SOCKET)
            return result;

        pxArenaRewind(arena, offset);
    }

    return 0;
}

void
pxWindowsSocketTcpDestroy(PxWindowsSocketTcp* self)
{
    if (self == 0) return;

    if (self->handle != INVALID_SOCKET)
        closesocket(self->handle);

    self->handle  = INVALID_SOCKET;
    self->address = (PxSockTcpData) {0};
}

PxAddress
pxWindowsSocketTcpGetAddress(PxWindowsSocketTcp* self)
{
    PxAddress result = {.type = PX_ADDRESS_TYPE_NONE};

    switch (self->address.ss_family) {
        case AF_INET: {
            result.type = PX_ADDRESS_TYPE_IP4;

            void* addr = pxSockTcpIp4Addr(self->address);

            pxMemoryCopy(&result.ip4.memory, addr,
                PX_ADDRESS_IP4_GROUPS, 1);
        } break;

        case AF_INET6: {
            result.type = PX_ADDRESS_TYPE_IP6;

            void* addr = pxSockTcpIp6Addr(self->address);

            pxMemoryCopy(&result.ip6.memory, addr,
                PX_ADDRESS_IP6_GROUPS, 2);
        } break;

        default: break;
    }

    return result;
}

pxu16
pxWindowsSocketTcpGetPort(PxWindowsSocketTcp* self)
{
    switch (self->address.ss_family) {
        case AF_INET:
            return *pxSockTcpIp4Port(self->address);

        case AF_INET6:
            return *pxSockTcpIp6Port(self->address);

        default: break;
    }

    return 0;
}

pxb8
pxWindowsSocketTcpBind(PxWindowsSocketTcp* self, PxAddress address, pxu16 port)
{
    pxiword family = 0;

    switch (address.type) {
        case PX_ADDRESS_TYPE_IP4: family = AF_INET;  break;
        case PX_ADDRESS_TYPE_IP6: family = AF_INET6; break;

        default: return 0;
    }

    if (self->address.ss_family != family) return 0;

    PxSockTcpData data = {0};
    pxiword       size = 0;

    switch (address.type) {
        case PX_ADDRESS_TYPE_IP4: {
            data.ss_family = AF_INET;
            size           = PX_SOCK_TCP_IP4_SIZE;

            pxMemoryCopy(pxSockTcpIp4Addr(data),
                &address.ip4.memory, PX_ADDRESS_IP4_GROUPS, 1);

            pxMemoryNetCopyLocal(pxSockTcpIp4Port(data),
                &port, 1, 2);
        } break;

        case PX_ADDRESS_TYPE_IP6: {
            data.ss_family = AF_INET6;
            size           = PX_SOCK_TCP_IP6_SIZE;

            pxMemoryCopy(pxSockTcpIp6Addr(data),
                &address.ip6.memory, PX_ADDRESS_IP6_GROUPS, 2);

            pxMemoryNetCopyLocal(pxSockTcpIp6Port(data),
                &port, 1, 2);
        } break;

        default: return 0;
    }

    if (bind(self->handle, pxSockTcpAddr(&data), size) == SOCKET_ERROR)
        return 0;

    self->address = data;

    return 1;
}

pxb8
pxWindowsSocketTcpListen(PxWindowsSocketTcp* self)
{
    if (listen(self->handle, SOMAXCONN) == SOCKET_ERROR)
        return 0;

    return 1;
}

pxb8
pxWindowsSocketTcpConnect(PxWindowsSocketTcp* self, PxAddress address, pxu16 port)
{
    PxSockTcpData data = {0};
    pxiword       size = 0;

    switch (address.type) {
        case PX_ADDRESS_TYPE_IP4: {
            data.ss_family = AF_INET;
            size           = PX_SOCK_TCP_IP4_SIZE;

            pxMemoryCopy(pxSockTcpIp4Addr(data),
                &address.ip4.memory, PX_ADDRESS_IP4_GROUPS, 1);

            pxMemoryNetCopyLocal(pxSockTcpIp4Port(data),
                &port, 1, 2);
        } break;

        case PX_ADDRESS_TYPE_IP6: {
            data.ss_family = AF_INET6;
            size           = PX_SOCK_TCP_IP6_SIZE;

            pxMemoryCopy(pxSockTcpIp6Addr(data),
                &address.ip6.memory, PX_ADDRESS_IP6_GROUPS, 2);

            pxMemoryNetCopyLocal(pxSockTcpIp6Port(data),
                &port, 1, 2);
        } break;

        default: return 0;
    }

    if (connect(self->handle, pxSockTcpAddr(&data), size) == SOCKET_ERROR)
        return 0;

    self->address = data;

    return 1;
}

PxWindowsSocketTcp*
pxWindowsSocketTcpAccept(PxWindowsSocketTcp* self, PxArena* arena)
{
    pxiword offset = pxArenaOffset(arena);

    PxWindowsSocketTcp* result =
        pxArenaReserve(arena, PxWindowsSocketTcp, 1);

    if (result != 0) {
        PxSockTcpData data = {0};
        pxiword       size = PX_SOCK_TCP_DATA_SIZE;

        result->handle = accept(self->handle,
            pxSockTcpAddr(&data), pxCast(int*, &size));

        result->address = data;

        if (result->handle != INVALID_SOCKET)
            return result;

        pxArenaRewind(arena, offset);
    }

    return 0;
}

pxiword
pxWindowsSocketTcpWriteMemory(PxWindowsSocketTcp* self, pxu8* memory, pxiword length)
{
    for (pxiword i = 0; i < length;) {
        char* mem = pxCast(char*, memory + i);
        int   len = pxCast(int,   length - i);

        pxiword amount = send(self->handle, mem, len, 0);

        if (amount > 0 && amount <= length - i)
            i += amount;
        else
            return i;
    }

    return length;
}

pxiword
pxWindowsSocketTcpReadMemory(PxWindowsSocketTcp* self, pxu8* memory, pxiword length)
{
    char* mem = pxCast(char*, memory);
    int   len = pxCast(int,   length);

    pxiword amount = recv(self->handle, mem, len, 0);

    if (amount > 0 && amount <= length)
        return amount;

    return 0;
}

#endif // PX_WINDOWS_NETWORK_SOCKET_TCP_C
