#ifndef PAX_CONTAINER_QUEUE_HPP
#define PAX_CONTAINER_QUEUE_HPP

#include "imports.hpp"

namespace pax {

//
// Types
//

template <class Val>
struct Queue
{
    Arena* arena = 0;

    Val* memory = 0;
    uptr length = 0;
    uptr size   = 0;
    uptr head   = 0;
    uptr tail   = 0;
};

//
// Procs
//

template <class Val>
Queue<Val>
queue_make(Val* memory, uptr length);

template <class Val>
Queue<Val>
queue_reserve(Arena* arena, uptr length);

template <class Val>
void
queue_release(Queue<Val>* self);

template <class Val>
Queue<Val>
queue_copy(Arena* arena, Queue<Val>* value);

template <class Val>
Queue<Val>
queue_copy_len(Arena* arena, Queue<Val>* value, uptr length);

template <class Val>
b32
queue_grow(Queue<Val>* self, uptr length);

template <class Val>
void
queue_clear(Queue<Val>* self);

template <class Val>
b32
queue_insert_head(Queue<Val>* self, Val value);

template <class Val>
b32
queue_insert_tail(Queue<Val>* self, Val value);

template <class Val>
b32
queue_remove_head(Queue<Val>* self, Val* value);

template <class Val>
b32
queue_remove_tail(Queue<Val>* self, Val* value);

template <class Val>
Val
queue_remove_head_or(Queue<Val>* self, Val othre);

template <class Val>
Val
queue_remove_tail_or(Queue<Val>* self, Val other);

template <class Val>
b32
queue_get(Queue<Val>* self, uptr index, Val* value);

template <class Val>
b32
queue_get_head(Queue<Val>* self, Val* value);

template <class Val>
b32
queue_get_tail(Queue<Val>* self, Val* value);

template <class Val>
Val
queue_get_or(Queue<Val>* self, uptr index, Val other);

template <class Val>
Val
queue_get_head_or(Queue<Val>* self, Val other);

template <class Val>
Val
queue_get_tail_or(Queue<Val>* self, Val other);

} // namespace pax

#include "queue.cpp"

#endif // PAX_CONTAINER_QUEUE_HPP
