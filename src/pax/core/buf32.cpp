#ifndef PAX_CORE_BUF32_CPP
#define PAX_CORE_BUF32_CPP

#include "buf32.hpp"

namespace pax {

buf32
buf32_make(u32* memory, uptr length)
{
    buf32 result = {};

    if (memory != 0 && length != 0) {
        result.memory = memory;
        result.length = length;
    }

    return result;
}

buf32
buf32_full(u32* memory, uptr length)
{
    buf32 result = {};

    if (memory != 0 && length != 0) {
        result.memory = memory;
        result.length = length;
        result.size   = length;
        result.tail   = length;
    }

    return result;
}

buf32
buf32_reserve(Arena* arena, uptr length)
{
    return buf32_make(arena_reserve_arr<u32>(arena, length), length);
}

buf32
buf32_copy(Arena* arena, buf32 value)
{
    return buf32_copy_len(arena, value, value.length);
}

buf32
buf32_copy_len(Arena* arena, buf32 value, uptr length)
{
    buf32 result = buf32_reserve(arena, length);

    if (result.length == 0) return result;

    for (uptr i = 0; i < value.size; i += 1)
        result.memory[i] = value.memory[(value.head + i) % value.length];

    result.size = value.size;
    result.tail = value.size;

    return result;
}

buf32
buf32_copy_mem(Arena* arena, u32* memory, uptr length)
{
    buf32 result = buf32_reserve(arena, length);

    if (result.length == 0) return result;

    mem32_copy(result.memory, memory, result.length);

    result.size = length;
    result.tail = length;

    return result;
}

void
buf32_clear(buf32* self)
{
    self->size = 0;
    self->head = 0;
    self->tail = 0;
}

void
buf32_normalize(buf32* self)
{
    u32* memory = self->memory;
    uptr length = self->tail;
    uptr shift  = self->head;

    if (self->size == 0) return;

    if (self->head > self->tail) {
        memory = self->memory + self->length - self->head;
        shift  = self->head - self->tail;

        mem32_flip(self->memory + self->head,
            self->length - self->head);

        mem32_flip(self->memory, self->tail);
        mem32_flip(self->memory, self->length);
    }

    if (shift != 0)
        mem32_move_back(memory, length, shift);

    self->head = 0;
    self->tail = self->size;
}

uptr
buf32_drop_head(buf32* self, uptr offset)
{
    offset = pax_min(offset, self->size);

    uptr next = self->head + offset;

    self->size -= offset;
    self->head  = next % self->length;

    return offset;
}

uptr
buf32_drop_tail(buf32* self, uptr offset)
{
    offset = pax_min(offset, self->size);

    uptr prev = self->tail + self->length - offset;

    self->size -= offset;
    self->tail  = prev % self->length;

    return offset;
}

uptr
buf32_write_head(buf32* self, buf32* value)
{
    uptr size = pax_min(self->length - self->size, value->size);
    uptr prev = self->head + self->length - size;

    self->size += size;
    self->head  = prev % self->length;

    for (uptr i = 0; i < size; i += 1) {
        uptr j = (self->head + i) % self->length;
        uptr k = (value->head + i) % value->length;

        self->memory[j] = value->memory[k];
    }

    uptr next = value->head + size;

    value->size -= size;
    value->head  = next % value->length;

    return size;
}

uptr
buf32_write_mem32_head(buf32* self, u32* memory, uptr length)
{
    uptr size = pax_min(self->length - self->size, length);
    uptr prev = self->head + self->length - size;

    self->size += size;
    self->head  = prev % self->length;

    for (uptr i = 0; i < size; i += 1)
        self->memory[(self->head + i) % self->length] = memory[i];

    return size;
}

uptr
buf32_write_tail(buf32* self, buf32* value)
{
    uptr size = pax_min(self->length - self->size, value->size);
    uptr next = self->tail + size;

    for (uptr i = 0; i < size; i += 1) {
        uptr j = (self->tail + i) % self->length;
        uptr k = (value->head + i) % value->length;

        self->memory[j] = value->memory[k];
    }

    self->size += size;
    self->tail  = next % self->length;

    next = value->head + size;

    value->size -= size;
    value->head  = next % value->length;

    return size;
}

uptr
buf32_write_mem32_tail(buf32* self, u32* memory, uptr length)
{
    uptr size = pax_min(self->length - self->size, length);
    uptr next = self->tail + size;

    for (uptr i = 0; i < size; i += 1)
        self->memory[(self->tail + i) % self->length] = memory[i];

    self->size += size;
    self->tail  = next % self->length;

    return size;
}

uptr
buf32_read_head(buf32* self, buf32* value)
{
    uptr size = pax_min(self->size, value->length - value->size);
    uptr next = self->head + size;

    for (uptr i = 0; i < size; i += 1) {
        uptr j = (value->tail + i) % value->length;
        uptr k = (self->head + i) % self->length;

        value->memory[j] = self->memory[k];
    }

    self->size -= size;
    self->head  = next % self->length;

    next = value->tail + size;

    value->size += size;
    value->tail  = next % value->length;

    return size;
}

uptr
buf32_read_mem32_head(buf32* self, u32* memory, uptr length)
{
    uptr size = pax_min(self->size, length);
    uptr next = self->head + size;

    for (uptr i = 0; i < size; i += 1)
        memory[i] = self->memory[(self->head + i) % self->length];

    self->size -= size;
    self->head  = next % self->length;

    return size;
}

uptr
buf32_read_tail(buf32* self, buf32* value)
{
    uptr size = pax_min(self->size, value->length - self->size);
    uptr prev = self->tail + self->length - size;

    self->size -= size;
    self->tail  = prev % self->length;

    for (uptr i = 0; i < size; i += 1) {
        uptr j = (value->tail + i) % value->length;
        uptr k = (self->tail + i) % self->length;

        value->memory[j] = self->memory[k];
    }

    uptr next = value->tail + size;

    value->size += size;
    value->tail  = next % value->length;

    return size;
}

uptr
buf32_read_mem32_tail(buf32* self, u32* memory, uptr length)
{
    uptr size = pax_min(self->size, length);
    uptr prev = self->tail + self->length - size;

    self->size -= size;
    self->tail  = prev % self->length;

    for (uptr i = 0; i < size; i += 1)
        memory[i] = self->memory[(self->tail + i) % self->length];

    return size;
}

} // namespace pax

#endif // PAX_CORE_BUF32_CPP
