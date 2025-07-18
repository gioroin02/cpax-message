#ifndef PAX_CONTAINER_TABLE_CPP
#define PAX_CONTAINER_TABLE_CPP

#include "table.hpp"

namespace pax {

template <class Val>
Table<Val>
table_make(Val* memory, uptr length)
{
    Table<Val> result = {};

    if (memory != 0 && length != 0) {
        result.memory = memory;
        result.length = length;
    }

    return result;
}

template <class Val>
Table<Val>
table_reserve(Arena* arena, uptr length)
{
    Table<Val> result = {};

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
table_release(Table<Val>* self)
{
    if (self->arena != 0 && self->memory != 0)
        arena_release(self->arena, self->memory);

    self->arena  = 0;
    self->memory = 0;
    self->length = 0;
}

template <class Val>
Table<Val>
table_copy(Arena* arena, Table<Val>* value)
{
    return table_copy_len(arena, value, value->length);
}

template <class Val>
Table<Val>
table_copy_len(Arena* arena, Table<Val>* value, uptr length)
{
    Table<Val> result = table_reserve<Val>(arena, length);

    if (result.length == 0) return result;

    for (uptr i = 0; i < result.length; i += 1)
        result.memory[i] = value->memory[i];

    return result;
}

template <class Val>
b32
table_grow(Table<Val>* self, uptr length)
{
    Table<Val> copy = {};

    if (self->length >= length) return 1;

    copy = table_copy_len(self->arena, self, length);

    if (copy.length != 0) {
        table_release(self);

        self->arena  = copy.arena;
        self->memory = copy.memory;
        self->length = copy.length;

        return 1;
    }

    return 0;
}

template <class Val>
b32
table_get(Table<Val>* self, uptr index, Val* value)
{
    if (index < 0 || index >= self->length)
        return 0;

    if (value != 0)
        *value = self->memory[index];

    return 1;
}

template <class Val>
Val
table_get_or(Table<Val>* self, uptr index, Val other)
{
    Val result = other;

    if (index < 0 || index >= self->length)
        return result;

    result = self->memory[index];

    return result;
}

template <class Val>
b32
table_put(Table<Val>* self, uptr index, Val value)
{
    if (index < 0 || index >= self->length)
        return 0;

    self->memory[index] = value;

    return 1;
}

} // namespace pax

#endif // PAX_CONTAINER_TABLE_CPP
