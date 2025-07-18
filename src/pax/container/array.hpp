#ifndef PAX_CONTAINER_ARRAY_HPP
#define PAX_CONTAINER_ARRAY_HPP

#include "imports.hpp"

namespace pax {

//
// Types
//

template <class Val>
struct Array
{
    Arena* arena = 0;

    Val* memory = 0;
    uptr length = 0;
    uptr size   = 0;
};

//
// Procs
//

template <class Val>
Array<Val>
array_make(Val* memory, uptr length);

template <class Val>
Array<Val>
array_reserve(Arena* arena, uptr length);

template <class Val>
void
array_release(Array<Val>* self);

template <class Val>
Array<Val>
array_copy(Arena* arena, Array<Val>* value);

template <class Val>
Array<Val>
array_copy_len(Arena* arena, Array<Val>* value, uptr length);

template <class Val>
b32
array_grow(Array<Val>* self, uptr length);

template <class Val>
b32
array_swap(Array<Val>* self, uptr index, uptr other);

template <class Val>
b32
array_swap_head(Array<Val>* self, uptr index);

template <class Val>
b32
array_swap_tail(Array<Val>* self, uptr index);

template <class Val>
void
array_clear(Array<Val>* self);

template <class Val>
b32
array_insert(Array<Val>* self, uptr index, Val value);

template <class Val>
b32
array_insert_head(Array<Val>* self, Val value);

template <class Val>
b32
array_insert_tail(Array<Val>* self, Val value);

template <class Val>
b32
array_remove(Array<Val>* self, uptr index, Val* value);

template <class Val>
b32
array_remove_head(Array<Val>* self, Val* value);

template <class Val>
b32
array_remove_tail(Array<Val>* self, Val* value);

template <class Val>
Val
array_remove_or(Array<Val>* self, uptr index, Val other);

template <class Val>
Val
array_remove_head_or(Array<Val>* self, Val other);

template <class Val>
Val
array_remove_tail_or(Array<Val>* self, Val other);

template <class Val>
b32
array_push(Array<Val>* self, uptr index, Val value);

template <class Val>
b32
array_push_head(Array<Val>* self, Val value);

template <class Val>
b32
array_push_tail(Array<Val>* self, Val value);

template <class Val>
b32
array_pop(Array<Val>* self, uptr index, Val* value);

template <class Val>
b32
array_pop_head(Array<Val>* self, Val* value);

template <class Val>
b32
array_pop_tail(Array<Val>* self, Val* value);

template <class Val>
Val
array_pop_or(Array<Val>* self, uptr index, Val other);

template <class Val>
Val
array_pop_head_or(Array<Val>* self, Val other);

template <class Val>
Val
array_pop_tail_or(Array<Val>* self, Val other);

template <class Val>
b32
array_get(Array<Val>* self, uptr index, Val* value);

template <class Val>
b32
array_get_head(Array<Val>* self, Val* value);

template <class Val>
b32
array_get_tail(Array<Val>* self, Val* value);

template <class Val>
Val
array_get_or(Array<Val>* self, uptr index, Val other);

template <class Val>
Val
array_get_head_or(Array<Val>* self, Val other);

template <class Val>
Val
array_get_tail_or(Array<Val>* self, Val other);

template <class Val>
b32
array_put(Array<Val>* self, uptr index, Val value);

template <class Val>
b32
array_put_head(Array<Val>* self, Val value);

template <class Val>
b32
array_put_tail(Array<Val>* self, Val value);

} // namespace pax

#include "array.cpp"

#endif // PAX_CONTAINER_ARRAY_HPP
