#ifndef PX_MESSAGE_BROKER_H
#define PX_MESSAGE_BROKER_H

#include "import.h"

#define pxMessageBrokerPublish(self, type, t, x) \
    pxMessageBrokerPublishMemory(self, type, x, pxSize(t))

#define pxMessageBrokerRetain(self, arena, type, t, x) \
    pxMessageBrokerRetainMemory(self, arena, type, x, pxSize(t))

typedef void (PxMessageProc) (void*, pxuword, void*, pxiword);

typedef struct PxMessageHandler
{
    pxuword type;
    void*   ctxt;
    void*   proc;

    struct PxMessageHandler* next;
}
PxMessageHandler;

typedef struct PxMessageCapsule
{
    pxuword type;
    void*   memory;
    pxiword stride;
}
PxMessageCapsule;

typedef struct PxMessageBroker
{
    PxQueue messages;

    PxMessageHandler* head;
}
PxMessageBroker;

PxMessageBroker
pxMessageBrokerReserve(PxArena* arena, pxiword length);

pxb8
pxMessageBrokerPublishMemory(PxMessageBroker* self, pxuword type, void* memory, pxiword stride);

pxb8
pxMessageBrokerRetainMemory(PxMessageBroker* self, PxArena* arena, pxuword type, void* memory, pxiword stride);

void
pxMessageBrokerNotify(PxMessageBroker* self);

pxb8
pxMessageBrokerAttach(PxMessageBroker* self, PxArena* arena, pxuword type, void* proc, void* ctxt);

#endif // PX_MESSAGE_BROKER_H
