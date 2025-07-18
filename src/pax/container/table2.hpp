#ifndef PAX_CONTAINER_TABLE2_HPP
#define PAX_CONTAINER_TABLE2_HPP

#include "imports.hpp"

namespace pax {

//
// Types
//

template <class Val>
struct Table2
{
    Arena* arena = 0;

    Val* memory = 0;
    uptr length = 0;
    uptr height = 0;
};

//
// Procs
//

template <class Val>
Table2<Val>
table2_make(Val* memory, uptr length, uptr height);

template <class Val>
Table2<Val>
table2_reserve(Arena* arena, uptr length, uptr height);

template <class Val>
void
table2_release(Table2<Val>* self);

template <class Val>
Table2<Val>
table2_copy(Arena* arena, Table2<Val>* value);

template <class Val>
Table2<Val>
table2_copy_len(Arena* arena, Table2<Val>* value, uptr length, uptr height);

template <class Val>
b32
table2_grow(Table2<Val>* self, uptr length, uptr height);

template <class Val>
b32
table2_get(Table2<Val>* self, uptr row, uptr col, Val* value);

template <class Val>
Val
table2_get_or(Table2<Val>* self, uptr row, uptr col, Val other);

template <class Val>
b32
table2_put(Table2<Val>* self, uptr row, uptr col, Val value);

} // namespace pax

#include "table2.cpp"

#endif // PAX_CONTAINER_TABLE2_HPP
