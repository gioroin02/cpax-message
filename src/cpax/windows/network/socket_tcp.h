#ifndef PX_WINDOWS_NETWORK_SOCKET_TCP_H
#define PX_WINDOWS_NETWORK_SOCKET_TCP_H

#include "import.h"

typedef struct PxWindowsSocketTcp;

PxWindowsSocketTcp*
pxWindowsSocketTcpCreate(PxArena* arena, PxAddressType type);

void
pxWindowsSocketTcpDestroy(PxWindowsSocketTcp* self);

PxAddress
pxWindowsSocketTcpGetAddress(PxWindowsSocketTcp* self);

pxu16
pxWindowsSocketTcpGetPort(PxWindowsSocketTcp* self);

pxb8
pxWindowsSocketTcpBind(PxWindowsSocketTcp* self, PxAddress address, pxu16 port);

pxb8
pxWindowsSocketTcpListen(PxWindowsSocketTcp* self);

pxb8
pxWindowsSocketTcpConnect(PxWindowsSocketTcp* self, PxAddress address, pxu16 port);

PxWindowsSocketTcp*
pxWindowsSocketTcpAccept(PxWindowsSocketTcp* self, PxArena* arena);

pxiword
pxWindowsSocketTcpWriteMemory(PxWindowsSocketTcp* self, pxu8* memory, pxiword length);

pxiword
pxWindowsSocketTcpReadMemory(PxWindowsSocketTcp* self, pxu8* memory, pxiword length);

#endif // PX_WINDOWS_NETWORK_SOCKET_TCP_H
