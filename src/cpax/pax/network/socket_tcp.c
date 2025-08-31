#ifndef PX_NETWORK_SOCKET_TCP_C
#define PX_NETWORK_SOCKET_TCP_C

#include "socket_tcp.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../../windows/network/socket_tcp.c"

    #define __pxSocketTcpCreate__      pxWindowsSocketTcpCreate
    #define __pxSocketTcpDestroy__     pxWindowsSocketTcpDestroy
    #define __pxSocketTcpGetAddress__  pxWindowsSocketTcpGetAddress
    #define __pxSocketTcpGetPort__     pxWindowsSocketTcpGetPort
    #define __pxSocketTcpBind__        pxWindowsSocketTcpBind
    #define __pxSocketTcpListen__      pxWindowsSocketTcpListen
    #define __pxSocketTcpConnect__     pxWindowsSocketTcpConnect
    #define __pxSocketTcpAccept__      pxWindowsSocketTcpAccept
    #define __pxSocketTcpWriteMemory__ pxWindowsSocketTcpWriteMemory
    #define __pxSocketTcpReadMemory__  pxWindowsSocketTcpReadMemory

#else

    #error "Unknown platform"

#endif

PxSocketTcp
pxSocketTcpCreate(PxArena* arena, PxAddressType type)
{
    return __pxSocketTcpCreate__(arena, type);
}

void
pxSocketTcpDestroy(PxSocketTcp self)
{
    __pxSocketTcpDestroy__(self);
}

PxAddress
pxSocketTcpGetAddress(PxSocketTcp self)
{
    return __pxSocketTcpGetAddress__(self);
}

pxu16
pxSocketTcpGetPort(PxSocketTcp self)
{
    return __pxSocketTcpGetPort__(self);
}

pxb8
pxSocketTcpBind(PxSocketTcp self, PxAddress address, pxu16 port)
{
    return __pxSocketTcpBind__(self, address, port);
}

pxb8
pxSocketTcpListen(PxSocketTcp self)
{
    return __pxSocketTcpListen__(self);
}

pxb8
pxSocketTcpConnect(PxSocketTcp self, PxAddress address, pxu16 port)
{
    return __pxSocketTcpConnect__(self, address, port);
}

PxSocketTcp
pxSocketTcpAccept(PxSocketTcp self, PxArena* arena)
{
    return __pxSocketTcpAccept__(self, arena);
}

pxiword
pxSocketTcpWrite(PxSocketTcp self, PxBuffer8* buffer)
{
    pxBuffer8Normalize(buffer);

    pxu8*   memory = buffer->memory;
    pxiword size   = buffer->size;

    if (size <= 0) return 0;

    pxiword temp = pxSocketTcpWriteMemory(self, memory, size, 1);

    buffer->size -= temp;
    buffer->head  = (buffer->head + temp) % buffer->length;

    return temp;
}

pxiword
pxSocketTcpWriteMemory(PxSocketTcp self, void* memory, pxiword amount, pxiword stride)
{
    return __pxSocketTcpWriteMemory__(self, memory, amount, stride);
}

pxiword
pxSocketTcpRead(PxSocketTcp self, PxBuffer8* buffer)
{
    pxBuffer8Normalize(buffer);

    pxu8*   memory = buffer->memory + buffer->size;
    pxiword size   = buffer->length - buffer->size;

    if (size <= 0) return 0;

    pxiword temp = pxSocketTcpReadMemory(self, memory, size, 1);

    buffer->size += temp;
    buffer->tail  = (buffer->tail + temp) % buffer->length;

    return temp;
}

pxiword
pxSocketTcpReadMemory(PxSocketTcp self, void* memory, pxiword amount, pxiword stride)
{
    return __pxSocketTcpReadMemory__(self, memory, amount, stride);
}

PxWriter
pxSocketTcpWriter(PxSocketTcp self, PxBuffer8* buffer)
{
    if (self == 0 || buffer == 0)
        return (PxWriter) {0};

    return (PxWriter) {
        .buffer = buffer,
        .ctxt   = self,
        .proc   = &pxSocketTcpWrite,
    };
}

PxReader
pxSocketTcpReader(PxSocketTcp self, PxBuffer8* buffer)
{
    if (self == 0 || buffer == 0)
        return (PxReader) {0};

    return (PxReader) {
        .buffer = buffer,
        .ctxt   = self,
        .proc   = &pxSocketTcpRead,
    };
}

#endif // PX_NETWORK_SOCKET_TCP_C
