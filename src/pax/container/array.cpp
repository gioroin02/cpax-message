#ifndef PAX_CONTAINER_ARRAY_CPP
#define PAX_CONTAINER_ARRAY_CPP

#include "array.hpp"

namespace pax {

template <class Val>
Array<Val>
array_make(Val* memory, uptr length)
{
    Array<Val> result = {};

    if (memory != 0 && length != 0) {
        result.memory = memory;
        result.length = length;
    }

    return result;
}

template <class Val>
Array<Val>
array_reserve(Arena* arena, uptr length)
{
    Array<Val> result = {};

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
array_release(Array<Val>* self)
{
    if (self->arena != 0 && self->memory != 0)
        arena_release(self->arena, self->memory);

    self->arena  = 0;
    self->memory = 0;
    self->length = 0;
    self->size   = 0;
}

template <class Val>
Array<Val>
array_copy(Arena* arena, Array<Val>* value)
{
    return array_copy_len(arena, value, value->size);
}

template <class Val>
Array<Val>
array_copy_len(Arena* arena, Array<Val>* value, uptr length)
{
    Array<Val> result = array_reserve<Val>(arena, length);

    if (result.length == 0) return result;

    result.size = pax_min(value->size, length);

    for (uptr i = 0; i < result.size; i += 1)
        result.memory[i] = value->memory[i];

    return result;
}

template <class Val>
b32
array_grow(Array<Val>* self, uptr length)
{
    Array<Val> copy = {};

    if (self->length >= length) return 1;

    copy = array_copy_len(self->arena, self, length);

    if (copy.length != 0) {
        array_release(self);

        self->arena  = copy.arena;
        self->memory = copy.memory;
        self->length = copy.length;
        self->size   = copy.size;

        return 1;
    }

    return 0;
}

template <class Val>
b32
array_swap(Array<Val>* self, uptr index, uptr other)
{
    if (index < 0 || index >= self->size)
        return 0;

    if (other < 0 || other >= self->size)
        return 0;

    if (index != other) {
        Val left  = self->memory[index];
        Val right = self->memory[other];

        self->memory[index] = right;
        self->memory[other] = left;
    }

    return 1;
}

template <class Val>
b32
array_swap_head(Array<Val>* self, uptr index)
{
    return array_swap(self, index, 0);
}

template <class Val>
b32
array_swap_tail(Array<Val>* self, uptr index)
{
    return array_swap(self, index, self->size - 1);
}

template <class Val>
void
array_clear(Array<Val>* self)
{
    self->size = 0;
}

template <class Val>
b32
array_insert(Array<Val>* self, uptr index, Val value)
{
    if (index < 0 || index > self->size) return 0;

    if (self->size < 0 || self->size >= self->length) {
        uptr length = pax_max(self->length * 2, 16);

        if (array_grow(self, length) == 0)
            return 0;
    }

    if (index != self->size)
        self->memory[self->size] = self->memory[index];

    self->size += 1;

    self->memory[index] = value;

    return 1;
}

template <class Val>
b32
array_insert_head(Array<Val>* self, Val value)
{
    return array_insert(self, 0, value);
}

template <class Val>
b32
array_insert_tail(Array<Val>* self, Val value)
{
    return array_insert(self, self->size, value);
}

template <class Val>
b32
array_remove(Array<Val>* self, uptr index, Val* value)
{
    if (index < 0 || index >= self->size)
        return 0;

    if (value != 0) *value = self->memory[index];

    self->size -= 1;

    if (index != self->size)
        self->memory[index] = self->memory[self->size];

    return 1;
}

template <class Val>
b32
array_remove_head(Array<Val>* self, Val* value)
{
    return array_remove(self, 0, value);
}

template <class Val>
b32
array_remove_tail(Array<Val>* self, Val* value)
{
    return array_remove(self, self->size - 1, value);
}

template <class Val>
b32
array_remove_or(Array<Val>* self, uptr index, Val other)
{
    Val result = other;

    if (index < 0 || index >= self->size)
        return result;

    result = self->memory[index];

    self->size -= 1;

    if (index != self->size)
        self->memory[index] = self->memory[self->size];

    return result;
}

template <class Val>
Val
array_remove_head_or(Array<Val>* self, Val other)
{
    return array_remove_or(self, 0, other);
}

template <class Val>
Val
array_remove_tail_or(Array<Val>* self, Val other)
{
    return array_remove_or(self, self->size - 1, other);
}

template <class Val>
b32
array_push(Array<Val>* self, uptr index, Val value)
{
    if (index < 0 || index > self->size) return 0;

    if (self->size < 0 || self->size >= self->length) {
        uptr length = pax_max(self->length * 2, 16);

        if (array_grow(self, length) == 0)
            return 0;
    }

    for (uptr i = self->size; i > index; i -= 1)
        self->memory[i] = self->memory[i - 1];

    self->memory[index] = value;

    self->size += 1;

    return 1;
}

template <class Val>
b32
array_push_head(Array<Val>* self, Val value)
{
    return array_push(self, 0, value);
}

template <class Val>
b32
array_push_tail(Array<Val>* self, Val value)
{
    if (self->size < 0 || self->size >= self->length) {
        uptr length = pax_max(self->length * 2, 16);

        if (array_grow(self, length) == 0)
            return 0;
    }

    self->memory[self->size] = value;

    self->size += 1;

    return 1;
}

template <class Val>
b32
array_pop(Array<Val>* self, uptr index, Val* value)
{
    if (index < 0 || index >= self->size)
        return 0;

    self->size -= 1;

    if (value != 0) *value = self->memory[index];

    for (uptr i = index; i < self->size; i += 1)
        self->memory[i] = self->memory[i + 1];

    return 1;
}

template <class Val>
b32
array_pop_head(Array<Val>* self, Val* value)
{
    return array_pop(self, 0, value);
}

template <class Val>
b32
array_pop_tail(Array<Val>* self, Val* value)
{
    if (self->size < 0 || self->size >= self->length)
        return 0;

    self->size -= 1;

    if (value != 0) *value = self->memory[self->size];

    return 1;
}

template <class Val>
Val
array_pop_or(Array<Val>* self, uptr index, Val other)
{
    Val result = other;

    if (index < 0 || index >= self->size)
        return result;

    self->size -= 1;

    result = self->memory[index];

    for (uptr i = index; i < self->size; i += 1)
        self->memory[i] = self->memory[i + 1];

    return result;
}

template <class Val>
Val
array_pop_head_or(Array<Val>* self, Val other)
{
    return array_pop_or(self, 0, other);
}

template <class Val>
Val
array_pop_tail_or(Array<Val>* self, Val other)
{
    Val result = other;

    if (self->size < 0 || self->size >= self->length)
        return result;

    self->size -= 1;

    result = self->memory[self->size];

    return result;
}

template <class Val>
b32
array_get(Array<Val>* self, uptr index, Val* value)
{
    if (index < 0 || index >= self->size)
        return 0;

    if (value != 0)
        *value = self->memory[index];

    return 1;
}

template <class Val>
b32
array_get_head(Array<Val>* self, Val* value)
{
    return array_get(self, 0, value);
}

template <class Val>
b32
array_get_tail(Array<Val>* self, Val* value)
{
    return array_get(self, self->size - 1, value);
}

template <class Val>
Val
array_get_or(Array<Val>* self, uptr index, Val other)
{
    if (index < 0 || index >= self->size)
        return other;

    return self->memory[index];
}

template <class Val>
Val
array_get_head_or(Array<Val>* self,  Val other)
{
    return array_get_or(self, 0, other);
}

template <class Val>
Val
array_get_tail_or(Array<Val>* self, Val other)
{
    return array_get_or(self, self->size - 1, other);
}

template <class Val>
b32
array_put(Array<Val>* self, uptr index, Val value)
{
    if (index < 0 || index >= self->size)
        return 0;

    self->memory[index] = value;

    return 1;
}

template <class Val>
b32
array_put_head(Array<Val>* self, Val value)
{
    return array_put(self, 0, value);
}

template <class Val>
b32
array_put_tail(Array<Val>* self, Val value)
{
    return array_put(self, self->size - 1, value);
}

} // namespace pax

#endif // PAX_CONTAINER_ARRAY_CPP
