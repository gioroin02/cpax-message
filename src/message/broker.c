#ifndef PX_MESSAGE_BROKER_C
#define PX_MESSAGE_BROKER_C

#include "broker.h"

PxMessageBroker
pxMessageBrokerReserve(PxArena* arena, pxiword length)
{
    return (PxMessageBroker) {
        .messages = pxQueueReserve(arena, PxMessageCapsule, length),
    };
}

pxb8
pxMessageBrokerPublishMemory(PxMessageBroker* self, pxuword type, void* memory, pxiword stride)
{
    if (memory == 0 || stride <= 0) return 0;

    for (PxMessageHandler* h = self->head; h != 0; h = h->next) {
        if (h->type != 0 && h->type != type) continue;

        pxCast(PxMessageProc*, h->proc)(
            h->ctxt, type, memory, stride);
    }

    return 1;
}

pxb8
pxMessageBrokerRetainMemory(PxMessageBroker* self, PxArena* arena, pxuword type, void* memory, pxiword stride)
{
    if (memory == 0 || stride <= 0 || type == 0)
        return 0;

    PxMessageCapsule capsule = {
        .type   = type,
        .memory = memory,
        .stride = stride,
    };

    pxiword offset = pxArenaOffset(arena);

    PxMessageCapsule* item = pxArenaCopyMemory(arena,
        &capsule, 1, pxSize(PxMessageCapsule));

    if (item == 0) return 0;

    pxb8 state = pxQueueInsertTail(&self->messages,
        PxMessageCapsule, item);

    if (state == 0)
        pxArenaRewind(arena, offset);

    return state;
}

void
pxMessageBrokerNotify(PxMessageBroker* self)
{
    while (self->messages.size > 0) {
        PxMessageCapsule capsule = {0};

        pxb8 state = pxQueueRemoveHead(&self->messages,
            PxMessageCapsule, &capsule);

        if (state == 0) break;

        pxMessageBrokerPublishMemory(self,
            capsule.type, capsule.memory, capsule.stride);
    }
}

pxb8
pxMessageBrokerAttach(PxMessageBroker* self, PxArena* arena, pxuword type, void* proc, void* ctxt)
{
    PxMessageHandler handler = {
        .type = type, .ctxt = ctxt, .proc = proc,
    };

    PxMessageHandler* item = pxArenaCopyMemory(arena,
        &handler, 1, pxSize(PxMessageHandler));

    if (item == 0) return 0;

    if (self->head != 0)
        item->next = self->head;

    self->head = item;

    return 1;
}

#endif // PX_MESSAGE_BROKER_C
