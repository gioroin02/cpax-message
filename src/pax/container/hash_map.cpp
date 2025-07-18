#ifndef PAX_CONTAINER_HASH_MAP_CPP
#define PAX_CONTAINER_HASH_MAP_CPP

#include "hash_map.hpp"

namespace pax {

template <class Key>
uptr
empty_hash_proc(Key key)
{
    return 0;
}

template <class Key, class Val>
Hash_Map<Key, Val>
hash_map_reserve(Arena* arena, uptr length, Hash_Proc<Key>* proc)
{
    Hash_Map<Key, Val> result = {};

    result.hash = empty_hash_proc;

    if (proc != 0) result.hash = proc;

    result.outer = table_reserve<uptr>(arena, length);
    result.inner = array_reserve<uptr>(arena, 0);
    result.key   = array_reserve<Key>(arena,  0);
    result.value = array_reserve<Val>(arena,  0);

    return result;
}

template <class Key, class Val>
Hash_Proc<Key>*
hash_map_set_hash_proc(Hash_Map<Key, Val>* self, Hash_Proc<Key>* proc)
{
    Hash_Proc<Key>* result = self->hash;

    if (proc != 0)
        self->hash = proc;
    else
        return 0;

    return result;
}

template <class Key, class Val>
void
hash_map_clear(Hash_Map<Key, Val>* self)
{
    uptr value = 0;

    for (uptr i = 0; i < self->outer.length; i += 1)
        table_put(&self->outer, i, value);

    array_clear(&self->inner);
    array_clear(&self->key);
    array_clear(&self->value);
}

template <class Key, class Val>
b32
hash_map_insert(Hash_Map<Key, Val>* self, Key key, Val value)
{
    if (self->inner.size < 0) return 0;

    if (self->inner.size >= self->outer.length) return 0;

    uptr hash  = self->hash(key);
    uptr index = hash % self->outer.length + 1;
    uptr inner = 0;
    uptr outer = 0;

    table_get(&self->outer, index - 1, &inner);

    b32 state = array_get(&self->inner, inner - 1, &outer);

    if (state != 0 && index == outer) return 0;

    array_push_tail(&self->inner, index);
    array_push_tail(&self->key,   key);
    array_push_tail(&self->value, value);

    table_put(&self->outer, index - 1, self->inner.size);

    if (self->key.size != self->value.size) return 0;
    if (self->key.size != self->inner.size) return 0;

    return 1;
}

template <class Key, class Val>
b32
hash_map_update(Hash_Map<Key, Val>* self, Key key, Val value, Val* other)
{
    if (self->inner.size <= 0) return 0;

    if (self->inner.size > self->outer.length) return 0;

    uptr hash  = self->hash(key);
    uptr index = hash % self->outer.length + 1;
    uptr inner = 0;
    uptr outer = 0;

    table_get(&self->outer, index - 1, &inner);

    b32 state = array_get(&self->inner, inner - 1, &outer);

    if (state == 0 || index != outer) return 0;

    if (other != 0)
        array_get(&self->value, inner - 1, other);

    array_put(&self->value, inner - 1, value);

    return 1;
}

template <class Key, class Val>
b32
hash_map_remove(Hash_Map<Key, Val>* self, Key key, Val* value)
{
    if (self->inner.size <= 0) return 0;

    if (self->inner.size > self->outer.length) return 0;

    uptr hash  = self->hash(key);
    uptr index = hash % self->outer.length + 1;
    uptr inner = 0;
    uptr outer = 0;

    table_get(&self->outer, index - 1, &inner);

    b32 state = array_get(&self->inner, inner - 1, &outer);

    if (state == 0 || index != outer) return 0;

    array_get_tail(&self->inner, &outer);

    if (outer <= 0 || outer > self->outer.length)
        return 0;

    if (value != 0)
        array_get(&self->value, inner - 1, value);

    array_remove(&self->inner, inner - 1, pax_null(uptr));
    array_remove(&self->key,   inner - 1, pax_null(Key));
    array_remove(&self->value, inner - 1, pax_null(Val));

    table_put(&self->outer, outer - 1, inner);

    return 1;
}

template <class Key, class Val>
Val
hash_map_remove_or(Hash_Map<Key, Val>* self, Key key, Val other)
{
    Val result = other;

    if (self->inner.size <= 0) return result;

    if (self->inner.size > self->outer.length) return result;

    uptr hash  = self->hash(key);
    uptr index = hash % self->outer.length + 1;
    uptr inner = 0;
    uptr outer = 0;

    table_get(&self->outer, index - 1, &inner);

    b32 state = array_get(&self->inner, inner - 1, &outer);

    if (state == 0 || index != outer) return result;

    array_get_tail(&self->inner, &outer);

    if (outer <= 0 || outer > self->outer.length)
        return result;

    result = array_get_or(&self->value, inner - 1, other);

    array_remove(&self->inner, inner - 1, pax_null(uptr));
    array_remove(&self->key,   inner - 1, pax_null(Key));
    array_remove(&self->value, inner - 1, pax_null(Val));

    table_put(&self->outer, outer - 1, inner);

    return result;
}

template <class Key, class Val>
b32
hash_map_get(Hash_Map<Key, Val>* self, Key key, Val* value)
{
    if (self->inner.size <= 0) return 0;

    if (self->inner.size > self->outer.length) return 0;

    uptr hash  = self->hash(key);
    uptr index = hash % self->outer.length + 1;
    uptr inner = 0;
    uptr outer = 0;

    table_get(&self->outer, index - 1, &inner);

    b32 state = array_get(&self->inner, inner - 1, &outer);

    if (state != 0 && index == outer)
        return array_get(&self->value, inner - 1, value);

    return 0;
}

template <class Key, class Val>
Val
hash_map_get_or(Hash_Map<Key, Val>* self, Key key, Val other)
{
    Val result = other;

    if (self->inner.size <= 0) return result;

    if (self->inner.size > self->outer.length) return result;

    uptr hash  = self->hash(key);
    uptr index = hash % self->outer.length + 1;
    uptr inner = 0;
    uptr outer = 0;

    table_get(&self->outer, index - 1, &inner);

    b32 state = array_get(&self->inner, inner - 1, &outer);

    if (state != 0 && index == outer)
        result = array_get_or(&self->value, inner - 1, other);

    return result;
}

template <class Key, class Val>
b32
hash_map_put(Hash_Map<Key, Val>* self, Key key, Val value)
{
    if (hash_map_update(self, key, value, pax_null(Val)) != 0)
        return 1;

    return hash_map_insert(self, key, value);
}

} // namespace pax

#endif // PAX_CONTAINER_HASH_MAP_CPP
