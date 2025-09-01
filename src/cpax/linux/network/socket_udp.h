#ifndef PX_LINUX_NETWORK_SOCKET_UDP_H
#define PX_LINUX_NETWORK_SOCKET_UDP_H

#include "import.h"

typedef struct PxLinuxSocketUdp;

PxLinuxSocketUdp*
pxLinuxSocketUdpCreate(PxArena* arena, PxAddressType type);

void
pxLinuxSocketUdpDestroy(PxLinuxSocketUdp* self);

PxAddress
pxLinuxSocketUdpGetAddress(PxLinuxSocketUdp* self);

pxu16
pxLinuxSocketUdpGetPort(PxLinuxSocketUdp* self);

pxb8
pxLinuxSocketUdpBind(PxLinuxSocketUdp* self, PxAddress address, pxu16 port);

pxb8
pxLinuxSocketUdpListen(PxLinuxSocketUdp* self);

pxb8
pxLinuxSocketUdpConnect(PxLinuxSocketUdp* self, PxAddress address, pxu16 port);

PxLinuxSocketUdp*
pxLinuxSocketUdpAccept(PxLinuxSocketUdp* self, PxArena* arena);

pxiword
pxLinuxSocketUdpWriteMemory(PxLinuxSocketUdp* self, void* memory, pxiword amount, pxiword stride);

pxiword
pxLinuxSocketUdpWriteHostMemory(PxLinuxSocketUdp* self, void* memory, pxiword amount, pxiword stride, PxAddress address, pxu16 port);

pxiword
pxLinuxSocketUdpReadMemory(PxLinuxSocketUdp* self, void* memory, pxiword amount, pxiword stride);

pxiword
pxLinuxSocketUdpReadHostMemory(PxLinuxSocketUdp* self, void* memory, pxiword amount, pxiword stride, PxAddress* address, pxu16* port);

#endif // PX_LINUX_NETWORK_SOCKET_UDP_H
