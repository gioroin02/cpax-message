#ifndef PX_NETWORK_SOCKET_TCP_H
#define PX_NETWORK_SOCKET_TCP_H

#include "address.h"

typedef void* PxSocketTcp;

PxSocketTcp
pxSocketTcpCreate(PxArena* arena, PxAddressType type);

void
pxSocketTcpDestroy(PxSocketTcp self);

PxAddress
pxSocketTcpGetAddress(PxSocketTcp self);

pxu16
pxSocketTcpGetPort(PxSocketTcp self);

pxb8
pxSocketTcpBind(PxSocketTcp self, PxAddress address, pxu16 port);

pxb8
pxSocketTcpListen(PxSocketTcp self);

pxb8
pxSocketTcpConnect(PxSocketTcp self, PxAddress address, pxu16 port);

PxSocketTcp
pxSocketTcpAccept(PxSocketTcp self, PxArena* arena);

pxiword
pxSocketTcpWrite(PxSocketTcp self, PxBuffer8* buffer);

pxiword
pxSocketTcpWriteMemory(PxSocketTcp self, void* memory, pxiword amount, pxiword stride);

pxiword
pxSocketTcpRead(PxSocketTcp self, PxBuffer8* buffer);

pxiword
pxSocketTcpReadMemory(PxSocketTcp self, void* memory, pxiword amount, pxiword stride);

PxReader
pxSocketTcpReader(PxSocketTcp self, PxBuffer8* buffer);

PxWriter
pxSocketTcpWriter(PxSocketTcp self, PxBuffer8* buffer);

#endif // PX_NETWORK_SOCKET_TCP_H
