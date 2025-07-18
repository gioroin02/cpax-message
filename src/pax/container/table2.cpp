#ifndef PAX_CONTAINER_TABLE2_CPP
#define PAX_CONTAINER_TABLE2_CPP

#include "table2.hpp"

namespace pax {

template <class Val>
Table2<Val>
table2_make(Val* memory, uptr length, uptr height)
{
    Table2<Val> result = {};

    if (memory != 0 && length != 0 && height != 0) {
        result.memory = memory;
        result.length = length;
        result.height = height;
    }

    return result;
}

template <class Val>
Table2<Val>
table2_reserve(Arena* arena, uptr length, uptr height)
{
    Table2<Val> result = {};

    Val* memory = arena_reserve_arr<Val>(arena, length * height);

    result.arena = arena;

    if (memory != 0 && length != 0 && height != 0) {
        result.memory = memory;
        result.length = length;
        result.height = height;
    }

    return result;
}

template <class Val>
void
table2_release(Table2<Val>* self)
{
    if (self->arena != 0 && self->memory != 0)
        arena_release(self->arena, self->memory);

    self->arena  = 0;
    self->memory = 0;
    self->length = 0;
    self->height = 0;
}

template <class Val>
Table2<Val>
table2_copy(Arena* arena, Table2<Val>* value)
{
    return table2_copy_len(arena, value, value->length, value->height);
}

template <class Val>
Table2<Val>
table2_copy_len(Arena* arena, Table2<Val>* value, uptr length, uptr height)
{
    Table2<Val> result = table2_reserve<Val>(arena, length, height);

    if (result.length == 0 || result.height == 0)
        return result;

    for (uptr i = 0; i < result.length * result.height; i += 1)
        result.memory[i] = value->memory[i];

    return result;
}

template <class Val>
b32
table2_grow(Table2<Val>* self, uptr length, uptr height)
{
    Table2<Val> copy = {};

    if (self->length >= length && self->height >= height)
        return 1;

    copy = table2_copy_len(self->arena, self, length, height);

    if (copy.length != 0 && copy.height != 0) {
        table2_release(self);

        self->arena  = copy.arena;
        self->memory = copy.memory;
        self->length = copy.length;
        self->height = copy.height;

        return 1;
    }

    return 0;
}

template <class Val>
b32
table2_get(Table2<Val>* self, uptr row, uptr col, Val* value)
{
    if (col < 0 || col >= self->length) return 0;
    if (row < 0 || row >= self->height) return 0;

    if (value != 0)
        *value = self->memory[col * self->height + row];

    return 1;
}

template <class Val>
Val
table2_get_or(Table2<Val>* self, uptr row, uptr col, Val other)
{
    Val result = other;

    if (col < 0 || col >= self->length) return result;
    if (row < 0 || row >= self->height) return result;

    result = self->memory[col * self->height + row];

    return result;
}

template <class Val>
b32
table2_put(Table2<Val>* self, uptr row, uptr col, Val value)
{
    if (col < 0 || col >= self->length) return 0;
    if (row < 0 || row >= self->height) return 0;

    self->memory[col * self->height + row] = value;

    return 1;
}

} // namespace pax

#endif // PAX_CONTAINER_TABLE2_CPP
