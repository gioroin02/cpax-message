#ifndef PX_MESSAGE_MESSAGE_H
#define PX_MESSAGE_MESSAGE_H

#include "import.h"

#define pxMessageQueueInsert(self, arena, type, t, x) \
    pxMessageQueueInsertMemory(self, arena, type, x, pxSize(t))

#define pxMessageBrokerPublish(self, type, t, x) \
    pxMessageBrokerPublishMemory(self, type, x, pxSize(t))

typedef void (PxMessageProc) (void*, pxuword, void*, pxiword);

typedef struct PxMessageHandler
{
    pxuword type;
    void*   ctxt;
    void*   proc;

    struct PxMessageHandler* next;
    struct PxMessageHandler* prev;
}
PxMessageHandler;

typedef struct PxMessageCapsule
{
    pxuword type;
    void*   memory;
    pxiword stride;
}
PxMessageCapsule;

typedef struct PxMessageQueue
{
    PxQueue queue;
}
PxMessageQueue;

typedef struct PxMessageBroker
{
    PxArena* arena;

    PxMessageHandler* head;
    PxMessageHandler* tail;

    pxiword size;
}
PxMessageBroker;

PxMessageQueue
pxMessageQueueReserve(PxArena* arena, pxiword length);

pxiword
pxMessageQueueSize(PxMessageQueue* self);

void
pxMessageQueueClear(PxMessageQueue* self);

pxb8
pxMessageQueueInsertMemory(PxMessageQueue* self, PxArena* arena, pxuword type, void* memory, pxiword stride);

pxb8
pxMessageQueueRemove(PxMessageQueue* self, PxMessageCapsule* value);

PxMessageBroker
pxMessageBrokerMake(PxArena* arena);

pxb8
pxMessageBrokerPublishMemory(PxMessageBroker* self, pxuword type, void* memory, pxiword stride);

void
pxMessageBrokerPublishQueue(PxMessageBroker* self, PxMessageQueue* queue);

pxb8
pxMessageBrokerAttach(PxMessageBroker* self, pxuword type, void* proc, void* ctxt);

pxb8
pxMessageBrokerDetach(PxMessageBroker* self, pxuword type, void* proc, void* ctxt);

#endif // PX_MESSAGE_MESSAGE_H
