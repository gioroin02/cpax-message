#ifndef PX_LINUX_NETWORK_SOCKET_TCP_H
#define PX_LINUX_NETWORK_SOCKET_TCP_H

#include "import.h"

typedef struct PxLinuxSocketTcp;

PxLinuxSocketTcp*
pxLinuxSocketTcpCreate(PxArena* arena, PxAddressType type);

void
pxLinuxSocketTcpDestroy(PxLinuxSocketTcp* self);

PxAddress
pxLinuxSocketTcpGetAddress(PxLinuxSocketTcp* self);

pxu16
pxLinuxSocketTcpGetPort(PxLinuxSocketTcp* self);

pxb8
pxLinuxSocketTcpBind(PxLinuxSocketTcp* self, PxAddress address, pxu16 port);

pxb8
pxLinuxSocketTcpListen(PxLinuxSocketTcp* self);

pxb8
pxLinuxSocketTcpConnect(PxLinuxSocketTcp* self, PxAddress address, pxu16 port);

PxLinuxSocketTcp*
pxLinuxSocketTcpAccept(PxLinuxSocketTcp* self, PxArena* arena);

pxiword
pxLinuxSocketTcpWriteMemory(PxLinuxSocketTcp* self, void* memory, pxiword amount, pxiword stride);

pxiword
pxLinuxSocketTcpReadMemory(PxLinuxSocketTcp* self, void* memory, pxiword amount, pxiword stride);

#endif // PX_LINUX_NETWORK_SOCKET_TCP_H
