#ifndef PX_MESSAGE_MESSAGE_C
#define PX_MESSAGE_MESSAGE_C

#include "message.h"

PxMessageQueue
pxMessageQueueReserve(PxArena* arena, pxiword length)
{
    return (PxMessageQueue) {
        .queue = pxQueueReserve(arena, PxMessageCapsule, length),
    };
}

pxiword
pxMessageQueueSize(PxMessageQueue* self)
{
    return self->queue.size;
}

void
pxMessageQueueClear(PxMessageQueue* self)
{
    pxQueueClear(&self->queue);
}

pxb8
pxMessageQueueInsertMemory(PxMessageQueue* self, PxArena* arena, pxuword type, void* memory, pxiword stride)
{
    if (memory == 0 || stride <= 0 || type == 0)
        return 0;

    pxiword offset = pxArenaOffset(arena);

    PxMessageCapsule capsule = {
        .type   = type,
        .memory = pxArenaCopyMemory(arena, memory, 1, stride),
        .stride = stride,
    };

    if (capsule.memory == 0) return 0;

    pxb8 state = pxQueueInsertTail(&self->queue,
        PxMessageCapsule, &capsule);

    if (state == 0)
        pxArenaRewind(arena, offset);

    return state;
}

pxb8
pxMessageQueueRemove(PxMessageQueue* self, PxMessageCapsule* value)
{
    return pxQueueRemoveTail(&self->queue, PxMessageCapsule, value);
}

PxMessageBroker
pxMessageBrokerMake(PxArena* arena)
{
    return (PxMessageBroker) {
        .arena = arena,
    };
}

pxb8
pxMessageBrokerPublishMemory(PxMessageBroker* self, pxuword type, void* memory, pxiword stride)
{
    if (memory == 0 || stride <= 0 || type == 0)
        return 0;

    for (PxMessageHandler* h = self->head; h != 0; h = h->next) {
        if (h->type != type && h->type != 0) continue;

        pxCast(PxMessageProc*, h->proc)
            (h->ctxt, type, memory, stride);
    }

    return 1;
}

void
pxMessageBrokerPublishQueue(PxMessageBroker* self, PxMessageQueue* queue)
{
    while (pxMessageQueueSize(queue) > 0) {
        PxMessageCapsule capsule = {0};

        if (pxMessageQueueRemove(queue, &capsule) == 0)
            break;

        pxMessageBrokerPublishMemory(self,
            capsule.type, capsule.memory, capsule.stride);
    }

    if (pxMessageQueueSize(queue) > 0)
        pxMessageQueueClear(queue);
}

pxb8
pxMessageBrokerAttach(PxMessageBroker* self, pxuword type, void* proc, void* ctxt)
{
    PxMessageHandler temp = {
        .type = type, .ctxt = ctxt, .proc = proc,
    };

    PxMessageHandler* handler = pxArenaCopyMemory(
        self->arena, &temp, 1, pxSize(PxMessageHandler));

    if (handler == 0) return 0;

    pxMessageBrokerDetach(self, type, proc, ctxt);

    if (self->head == 0)
        self->head = handler;

    if (self->tail != 0) {
        handler->prev    = self->tail;
        self->tail->next = handler;
    }

    self->tail  = handler;
    self->size += 1;

    return 1;
}

pxb8
pxMessageBrokerDetach(PxMessageBroker* self, pxuword type, void* proc, void* ctxt)
{
    for (PxMessageHandler* h = self->head; h != 0; h = h->next) {
        PxMessageHandler* prev = h->prev;
        PxMessageHandler* next = h->next;

        if (h->type != type || h->proc != proc || h->ctxt != ctxt)
            continue;

        if (prev != 0) prev->next = next;
        if (next != 0) next->prev = prev;

        if (self->head == h) self->head = next;
        if (self->tail == h) self->tail = prev;
    }

    return 1;
}

#endif // PX_MESSAGE_MESSAGE_C
