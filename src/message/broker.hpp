#ifndef PAX_MESSAGE_BROKER_HPP
#define PAX_MESSAGE_BROKER_HPP

#include "imports.hpp"

namespace pax {

//
// Types
//

template <class Val>
using Broker_Proc_Simple = void (Val, uptr);

template <class Val, class Self>
using Broker_Proc = void (Val, uptr, Self*);

template <class Val>
struct Broker_Handler
{
    uptr type = 0;
    addr ctxt = 0;
    addr proc = 0;
};

template <class Val>
struct Broker_Message
{
    uptr type  = 0;
    Val  value = {};
};

template <class Val>
struct Broker
{
    Array<Broker_Handler<Val>> handlers = {};
    Queue<Broker_Message<Val>> messages = {};
};

//
// Procs
//

/* Broker */

template <class Val>
Broker<Val>
broker_reserve(Arena* arena, uptr messages, uptr handlers);

template <class Val>
b32
broker_retain(Broker<Val>* self, uptr type, Val value);

template <class Val>
void
broker_publish(Broker<Val>* self, uptr type, Val value);

template <class Val>
void
broker_notify(Broker<Val>* self);

template <class Val>
b32
broker_attach_simple(Broker<Val>* self, uptr type, Broker_Proc_Simple<Val>* proc);

template <class Val, class Self>
b32
broker_attach(Broker<Val>* self, uptr type, Broker_Proc<Val, Self>* proc, addr ctxt);

} // namespace pax

#include "broker.cpp"

#endif // PAX_MESSAGE_BROKER_HPP
