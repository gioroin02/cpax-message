#ifndef PAX_CONTAINER_TABLE_HPP
#define PAX_CONTAINER_TABLE_HPP

#include "imports.hpp"

namespace pax {

//
// Types
//

template <class Val>
struct Table
{
    Arena* arena = 0;

    Val* memory = 0;
    uptr length = 0;
};

//
// Procs
//

template <class Val>
Table<Val>
table_make(Val* memory, uptr length);

template <class Val>
Table<Val>
table_reserve(Arena* arena, uptr length);

template <class Val>
void
table_release(Table<Val>* self);

template <class Val>
Table<Val>
table_copy(Arena* arena, Table<Val>* value);

template <class Val>
Table<Val>
table_copy_len(Arena* arena, Table<Val>* value, uptr length);

template <class Val>
b32
table_grow(Table<Val>* self, uptr length);

template <class Val>
b32
table_get(Table<Val>* self, uptr index, Val* value);

template <class Val>
Val
table_get_or(Table<Val>* self, uptr index, Val other);

template <class Val>
b32
table_put(Table<Val>* self, uptr index, Val value);

} // namespace pax

#include "table.cpp"

#endif // PAX_CONTAINER_TABLE_HPP
