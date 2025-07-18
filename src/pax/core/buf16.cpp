#ifndef PAX_CORE_BUF16_CPP
#define PAX_CORE_BUF16_CPP

#include "buf16.hpp"

namespace pax {

buf16
buf16_make(u16* memory, uptr length)
{
    buf16 result = {};

    if (memory != 0 && length != 0) {
        result.memory = memory;
        result.length = length;
    }

    return result;
}

buf16
buf16_full(u16* memory, uptr length)
{
    buf16 result = {};

    if (memory != 0 && length != 0) {
        result.memory = memory;
        result.length = length;
        result.size   = length;
        result.tail   = length;
    }

    return result;
}

buf16
buf16_reserve(Arena* arena, uptr length)
{
    return buf16_make(arena_reserve_arr<u16>(arena, length), length);
}

buf16
buf16_copy(Arena* arena, buf16 value)
{
    return buf16_copy_len(arena, value, value.length);
}

buf16
buf16_copy_len(Arena* arena, buf16 value, uptr length)
{
    buf16 result = buf16_reserve(arena, length);

    if (result.length == 0) return result;

    for (uptr i = 0; i < value.size; i += 1)
        result.memory[i] = value.memory[(value.head + i) % value.length];

    result.size = value.size;
    result.tail = value.size;

    return result;
}

buf16
buf16_copy_mem(Arena* arena, u16* memory, uptr length)
{
    buf16 result = buf16_reserve(arena, length);

    if (result.length == 0) return result;

    mem16_copy(result.memory, memory, result.length);

    result.size = length;
    result.tail = length;

    return result;
}

void
buf16_clear(buf16* self)
{
    self->size = 0;
    self->head = 0;
    self->tail = 0;
}

void
buf16_normalize(buf16* self)
{
    u16* memory = self->memory;
    uptr length = self->tail;
    uptr shift  = self->head;

    if (self->size == 0) return;

    if (self->head > self->tail) {
        memory = self->memory + self->length - self->head;
        shift  = self->head - self->tail;

        mem16_flip(self->memory + self->head,
            self->length - self->head);

        mem16_flip(self->memory, self->tail);
        mem16_flip(self->memory, self->length);
    }

    if (shift != 0)
        mem16_move_back(memory, length, shift);

    self->head = 0;
    self->tail = self->size;
}

uptr
buf16_drop_head(buf16* self, uptr offset)
{
    offset = pax_min(offset, self->size);

    uptr next = self->head + offset;

    self->size -= offset;
    self->head  = next % self->length;

    return offset;
}

uptr
buf16_drop_tail(buf16* self, uptr offset)
{
    offset = pax_min(offset, self->size);

    uptr prev = self->tail + self->length - offset;

    self->size -= offset;
    self->tail  = prev % self->length;

    return offset;
}

uptr
buf16_write_head(buf16* self, buf16* value)
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
buf16_write_mem16_head(buf16* self, u16* memory, uptr length)
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
buf16_write_tail(buf16* self, buf16* value)
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
buf16_write_mem16_tail(buf16* self, u16* memory, uptr length)
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
buf16_read_head(buf16* self, buf16* value)
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
buf16_read_mem16_head(buf16* self, u16* memory, uptr length)
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
buf16_read_tail(buf16* self, buf16* value)
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
buf16_read_mem16_tail(buf16* self, u16* memory, uptr length)
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

#endif // PAX_CORE_BUF16_CPP
