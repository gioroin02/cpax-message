#ifndef PX_NETWORK_SOCKET_UDP_C
#define PX_NETWORK_SOCKET_UDP_C

#include "socket_udp.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../../windows/network/socket_udp.c"

    #define __pxSocketUdpCreate__          pxWindowsSocketUdpCreate
    #define __pxSocketUdpDestroy__         pxWindowsSocketUdpDestroy
    #define __pxSocketUdpGetAddress__      pxWindowsSocketUdpGetAddress
    #define __pxSocketUdpGetPort__         pxWindowsSocketUdpGetPort
    #define __pxSocketUdpBind__            pxWindowsSocketUdpBind
    #define __pxSocketUdpListen__          pxWindowsSocketUdpListen
    #define __pxSocketUdpConnect__         pxWindowsSocketUdpConnect
    #define __pxSocketUdpAccept__          pxWindowsSocketUdpAccept
    #define __pxSocketUdpWriteMemory__     pxWindowsSocketUdpWriteMemory
    #define __pxSocketUdpWriteMemoryAddr__ pxWindowsSocketUdpWriteMemoryAddr
    #define __pxSocketUdpReadMemory__      pxWindowsSocketUdpReadMemory
    #define __pxSocketUdpReadMemoryAddr__  pxWindowsSocketUdpReadMemoryAddr

#else

    #error "Unknown platform"

#endif

PxSocketUdp
pxSocketUdpCreate(PxArena* arena, PxAddressType type)
{
    return __pxSocketUdpCreate__(arena, type);
}

void
pxSocketUdpDestroy(PxSocketUdp self)
{
    __pxSocketUdpDestroy__(self);
}

PxAddress
pxSocketUdpGetAddress(PxSocketUdp self)
{
    return __pxSocketUdpGetAddress__(self);
}

pxu16
pxSocketUdpGetPort(PxSocketUdp self)
{
    return __pxSocketUdpGetPort__(self);
}

pxb8
pxSocketUdpBind(PxSocketUdp self, PxAddress address, pxu16 port)
{
    return __pxSocketUdpBind__(self, address, port);
}

pxb8
pxSocketUdpListen(PxSocketUdp self)
{
    return __pxSocketUdpListen__(self);
}

pxb8
pxSocketUdpConnect(PxSocketUdp self, PxAddress address, pxu16 port)
{
    return __pxSocketUdpConnect__(self, address, port);
}

PxSocketUdp
pxSocketUdpAccept(PxSocketUdp self, PxArena* arena)
{
    return __pxSocketUdpAccept__(self, arena);
}

pxiword
pxSocketUdpWrite(PxSocketUdp self, PxBuffer8* buffer)
{
    pxBuffer8Normalize(buffer);

    pxu8*   memory = buffer->memory;
    pxiword size   = buffer->size;

    if (size <= 0) return 0;

    pxiword amount = __pxSocketUdpWriteMemory__(self, memory, size);

    buffer->size -= amount;
    buffer->head  = (buffer->head + amount) % buffer->length;

    return amount;
}

pxiword
pxSocketUdpWriteMemory(PxSocketUdp self, pxu8* memory, pxiword length)
{
    return __pxSocketUdpWriteMemory__(self, memory, length);
}

pxiword
pxSocketUdpWriteAddr(PxSocketUdp self, PxBuffer8* buffer, PxAddress address, pxu16 port)
{
    pxBuffer8Normalize(buffer);

    pxu8*   memory = buffer->memory;
    pxiword size   = buffer->size;

    if (size <= 0) return 0;

    pxiword amount = __pxSocketUdpWriteMemoryAddr__(self, memory, size, address, port);

    buffer->size -= amount;
    buffer->head  = (buffer->head + amount) % buffer->length;

    return amount;
}

pxiword
pxSocketUdpWriteMemoryAddr(PxSocketUdp self, pxu8* memory, pxiword length, PxAddress address, pxu16 port)
{
    return __pxSocketUdpWriteMemoryAddr__(self, memory, length, address, port);
}

pxiword
pxSocketUdpRead(PxSocketUdp self, PxBuffer8* buffer)
{
    pxBuffer8Normalize(buffer);

    pxu8*   memory = buffer->memory + buffer->size;
    pxiword size   = buffer->length - buffer->size;

    if (size <= 0) return 0;

    pxiword amount = __pxSocketUdpReadMemory__(self, memory, size);

    buffer->size += amount;
    buffer->tail  = (buffer->tail + amount) % buffer->length;

    return amount;
}

pxiword
pxSocketUdpReadMemory(PxSocketUdp self, pxu8* memory, pxiword length)
{
    return __pxSocketUdpReadMemory__(self, memory, length);
}

pxiword
pxSocketUdpReadAddr(PxSocketUdp self, PxBuffer8* buffer, PxAddress* address, pxu16* port)
{
    pxBuffer8Normalize(buffer);

    pxu8*   memory = buffer->memory + buffer->size;
    pxiword size   = buffer->length - buffer->size;

    if (size <= 0) return 0;

    pxiword amount = __pxSocketUdpReadMemoryAddr__(self, memory, size, address, port);

    buffer->size += amount;
    buffer->tail  = (buffer->tail + amount) % buffer->length;

    return amount;
}

pxiword
pxSocketUdpReadMemoryAddr(PxSocketUdp self, pxu8* memory, pxiword length, PxAddress* address, pxu16* port)
{
    return __pxSocketUdpReadMemoryAddr__(self, memory, length, address, port);
}

PxWriter
pxSocketUdpWriter(PxSocketUdp self, PxBuffer8* buffer)
{
    if (self == 0 || buffer == 0)
        return (PxWriter) {0};

    return (PxWriter) {
        .buffer = buffer,
        .ctxt   = self,
        .proc   = &pxSocketUdpWrite,
    };
}

PxReader
pxSocketUdpReader(PxSocketUdp self, PxBuffer8* buffer)
{
    if (self == 0 || buffer == 0)
        return (PxReader) {0};

    return (PxReader) {
        .buffer = buffer,
        .ctxt   = self,
        .proc   = &pxSocketUdpRead,
    };
}

#endif // PX_NETWORK_SOCKET_UDP_C
