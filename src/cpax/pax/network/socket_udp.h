#ifndef PX_NETWORK_SOCKET_UDP_H
#define PX_NETWORK_SOCKET_UDP_H

#include "address.h"

typedef void* PxSocketUdp;

PxSocketUdp
pxSocketUdpCreate(PxArena* arena, PxAddressType type);

void
pxSocketUdpDestroy(PxSocketUdp self);

PxAddress
pxSocketUdpGetAddress(PxSocketUdp self);

pxu16
pxSocketUdpGetPort(PxSocketUdp self);

pxb8
pxSocketUdpBind(PxSocketUdp self, PxAddress address, pxu16 port);

pxb8
pxSocketUdpListen(PxSocketUdp self);

pxb8
pxSocketUdpConnect(PxSocketUdp self, PxAddress address, pxu16 port);

PxSocketUdp
pxSocketUdpAccept(PxSocketUdp self, PxArena* arena);

pxiword
pxSocketUdpWrite(PxSocketUdp self, PxBuffer8* buffer);

pxiword
pxSocketUdpWriteMemory(PxSocketUdp self, pxu8* memory, pxiword length);

pxiword
pxSocketUdpWriteAddr(PxSocketUdp self, PxBuffer8* buffer, PxAddress address, pxu16 port);

pxiword
pxSocketUdpWriteMemoryAddr(PxSocketUdp self, pxu8* memory, pxiword length, PxAddress address, pxu16 port);

pxiword
pxSocketUdpRead(PxSocketUdp self, PxBuffer8* buffer);

pxiword
pxSocketUdpReadMemory(PxSocketUdp self, pxu8* memory, pxiword length);

pxiword
pxSocketUdpReadAddr(PxSocketUdp self, PxBuffer8* buffer, PxAddress* address, pxu16* port);

pxiword
pxSocketUdpReadMemoryAddr(PxSocketUdp self, pxu8* memory, pxiword length, PxAddress* address, pxu16* port);

PxReader
pxSocketUdpReader(PxSocketUdp self, PxBuffer8* buffer);

PxWriter
pxSocketUdpWriter(PxSocketUdp self, PxBuffer8* buffer);

#endif // PX_NETWORK_SOCKET_UDP_H
