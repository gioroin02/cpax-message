#ifndef PAX_MESSAGE_BROKER_CPP
#define PAX_MESSAGE_BROKER_CPP

#include "broker.hpp"

namespace pax {

template <class Val>
Broker<Val>
broker_reserve(Arena* arena, uptr handlers, uptr messages)
{
    Broker<Val> result = {};

    result.handlers = array_reserve<Broker_Handler<Val>>(arena, handlers);
    result.messages = queue_reserve<Broker_Message<Val>>(arena, messages);

    return result;
}

template <class Val>
b32
broker_retain(Broker<Val>* self, uptr type, Val value)
{
    Broker_Message<Val> message = {};

    if (type == 0) return 0;

    message.type  = type;
    message.value = value;

    return queue_insert_tail(&self->messages, message);
}

template <class Val>
void
broker_publish(Broker<Val>* self, uptr type, Val value)
{
    for (uptr i = 0; i < self->handlers.size; i += 1) {
        Broker_Handler<Val> handler = array_get_or(&self->handlers, i, {});

        if (handler.type != 0 && handler.type != type) continue;

        if (handler.ctxt != 0)
            pax_cast(void(*)(Val, uptr, addr), handler.proc)(value, type, handler.ctxt);
        else
            pax_cast(void(*)(Val, uptr), handler.proc)(value, type);
    }
}

template <class Val>
void
broker_notify(Broker<Val>* self)
{
    while (self->messages.size != 0) {
        Broker_Message<Val> message = queue_remove_head_or(&self->messages, {});

        for (uptr i = 0; i < self->handlers.size; i += 1) {
            Broker_Handler<Val> handler = array_get_or(&self->handlers, i, {});

            if (handler.type != 0 && handler.type != message.type) continue;

            if (handler.ctxt != 0)
                pax_cast(void(*)(Val, uptr, addr), handler.proc)(message.value, message.type, handler.ctxt);
            else
                pax_cast(void(*)(Val, uptr), handler.proc)(message.value, message.type);
        }
    }
}

template <class Val>
b32
broker_attach_simple(Broker<Val>* self, uptr type, Broker_Proc_Simple<Val>* proc)
{
    Broker_Handler<Val> handler = {};

    handler.type = type;
    handler.proc = pax_cast(addr, proc);

    return array_insert_tail(&self->handlers, handler);
}

template <class Val, class Self>
b32
broker_attach(Broker<Val>* self, uptr type, Broker_Proc<Val, Self>* proc, addr ctxt)
{
    Broker_Handler<Val> handler = {};

    handler.type = type;
    handler.ctxt = ctxt;
    handler.proc = pax_cast(addr, proc);

    return array_insert_tail(&self->handlers, handler);
}

} // namespace pax

#endif // PAX_MESSAGE_BROKER_CPP
