#ifndef PAX_CONTAINER_QUEUE_CPP
#define PAX_CONTAINER_QUEUE_CPP

#include "queue.hpp"

namespace pax {

template <class Val>
Queue<Val>
queue_make(Val* memory, uptr length)
{
    Queue<Val> result = {};

    if (memory != 0 && length != 0) {
        result.memory = memory;
        result.length = length;
    }

    return result;
}

template <class Val>
Queue<Val>
queue_reserve(Arena* arena, uptr length)
{
    Queue<Val> result = {};

    Val* memory = arena_reserve_arr<Val>(arena, length);

    result.arena = arena;

    if (memory != 0 && length != 0) {
        result.memory = memory;
        result.length = length;
    }

    return result;
}

template <class Val>
void
queue_release(Queue<Val>* self)
{
    if (self->arena != 0 && self->memory != 0)
        arena_release(self->arena, self->memory);

    self->arena  = 0;
    self->memory = 0;
    self->length = 0;
    self->size   = 0;
    self->head   = 0;
    self->tail   = 0;
}

template <class Val>
Queue<Val>
queue_copy(Arena* arena, Queue<Val>* value)
{
    return queue_copy_len(arena, value, value->size);
}

template <class Val>
Queue<Val>
queue_copy_len(Arena* arena, Queue<Val>* value, uptr length)
{
    Queue<Val> result = queue_reserve<Val>(arena, length);

    if (result.length == 0) return result;

    result.size = pax_min(value->size, length);
    result.tail = result.size;

    for (uptr i = 0, j = value->head; i < result.size; i += 1, j += 1)
        result.memory[i] = value->memory[j % value->length];

    return result;
}

template <class Val>
b32
queue_grow(Queue<Val>* self, uptr length)
{
    Queue<Val> copy = {};

    if (self->length >= length) return 1;

    copy = queue_copy_len(self->arena, self, length);

    if (copy.length != 0) {
        queue_release(self);

        self->arena  = copy.arena;
        self->memory = copy.memory;
        self->size   = copy.size;
        self->head   = copy.head;
        self->tail   = copy.tail;

        return 1;
    }

    return 0;
}

template <class Val>
void
queue_clear(Queue<Val>* self)
{
    self->size = 0;
    self->head = 0;
    self->tail = 0;
}

template <class Val>
b32
queue_insert_head(Queue<Val>* self, Val value)
{
    if (self->size < 0 || self->size >= self->length) {
        uptr length = pax_max(self->length * 2, 16);

        if (queue_grow(self, length) == 0)
            return 0;
    }

    self->size += 1;
    self->head  = (self->head + self->length - 1) % self->length;

    self->memory[self->head] = value;

    return 1;
}

template <class Val>
b32
queue_insert_tail(Queue<Val>* self, Val value)
{
    if (self->size < 0 || self->size >= self->length) {
        uptr length = pax_max(self->length * 2, 16);

        if (queue_grow(self, length) == 0)
            return 0;
    }

    self->memory[self->tail] = value;

    self->size += 1;
    self->tail  = (self->tail + 1) % self->length;

    return 1;
}

template <class Val>
b32
queue_remove_head(Queue<Val>* self, Val* value)
{
    if (self->size <= 0 || self->size > self->length)
        return 0;

    if (value != 0) *value = self->memory[self->head];

    self->size -= 1;
    self->head  = (self->head + 1) % self->length;

    return 1;
}

template <class Val>
b32
queue_remove_tail(Queue<Val>* self, Val* value)
{
    if (self->size <= 0 || self->size > self->length)
        return 0;

    self->size -= 1;
    self->tail  = (self->tail + self->length - 1) % self->length;

    if (value != 0) *value = self->memory[self->tail];

    return 1;
}

template <class Val>
Val
queue_remove_head_or(Queue<Val>* self, Val other)
{
    Val result = other;

    if (self->size <= 0 || self->size > self->length)
        return result;

    result = self->memory[self->head];

    self->size -= 1;
    self->head  = (self->head + 1) % self->length;

    return result;
}

template <class Val>
Val
queue_remove_tail_or(Queue<Val>* self, Val other)
{
    Val result = other;

    if (self->size <= 0 || self->size > self->length)
        return result;

    self->size -= 1;
    self->tail  = (self->tail + self->length - 1) % self->length;

    result = self->memory[self->tail];

    return result;
}

template <class Val>
b32
queue_get(Queue<Val>* self, uptr index, Val* value)
{
    if (index < 0 || index >= self->size)
        return 0;

    index = (self->tail + self->length - index) % self->length;

    if (value != 0) *value = self->memory[index];

    return 1;
}

template <class Val>
b32
queue_get_head(Queue<Val>* self, Val* value)
{
    if (self->size < 0 || self->size >= self->length)
        return 0;

    uptr index = self->head;

    if (value != 0) *value = self->memory[index];

    return 1;
}

template <class Val>
b32
queue_get_tail(Queue<Val>* self, Val* value)
{
    if (self->size < 0 || self->size >= self->length)
        return 0;

    uptr index = (self->tail + self->length - 1) % self->length;

    if (value != 0) *value = self->memory[index];

    return 1;
}

template <class Val>
Val
queue_get_or(Queue<Val>* self, uptr index, Val other)
{
    Val result = other;

    if (index < 0 || index >= self->size)
        return result;

    index  = (self->tail + self->length - index) % self->length;
    result = self->memory[index];

    return result;
}

template <class Val>
Val
queue_get_head_or(Queue<Val>* self, Val other)
{
    Val result = other;

    if (self->size < 0 || self->size >= self->length)
        return result;

    uptr index = self->head;

    result = self->memory[index];

    return result;
}

template <class Val>
Val
queue_get_tail_or(Queue<Val>* self, Val other)
{
    Val result = other;

    if (self->size < 0 || self->size >= self->length)
        return result;

    uptr index = (self->tail + self->length - 1) % self->length;

    result = self->memory[index];

    return result;
}

} // namespace pax

#endif // PAX_CONTAINER_QUEUE_CPP
