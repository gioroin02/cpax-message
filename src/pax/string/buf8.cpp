#ifndef PAX_STRING_BUF8_CPP
#define PAX_STRING_BUF8_CPP

#include "buf8.hpp"

namespace pax {

uptr
buf8_write_codepoint_head(buf8* self, u32 value)
{
    uptr size = utf8_units_to_write(value);
    uptr prev = self->head + self->length - size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    self->size -= size;
    self->head  = prev % self->length;

    utf8_encode_forw_circ(self->memory,
        self->length, self->head, value);

    return size;
}

uptr
buf8_write_codepoint_tail(buf8* self, u32 value)
{
    uptr size = utf8_units_to_write(value);
    uptr next = self->tail + size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    utf8_encode_forw_circ(self->memory,
        self->length, self->tail, value);

    self->size += size;
    self->tail  = next % self->length;

    return size;
}

uptr
buf8_write_str8_head(buf8* self, str8 value)
{
    uptr size = value.length;
    uptr prev = self->head + self->length - size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    self->size += size;
    self->head  = prev % self->length;

    for (uptr i = 0; i < size; i += 1)
        self->memory[(self->head + i) % self->length] = value.memory[i];

    return size;
}

uptr
buf8_write_str8_tail(buf8* self, str8 value)
{
    uptr size = value.length;
    uptr next = self->tail + size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    for (uptr i = 0; i < size; i += 1)
        self->memory[(self->tail + i) % self->length] = value.memory[i];

    self->size += size;
    self->tail  = next % self->length;

    return size;
}

uptr
buf8_write_str16_head(buf8* self, str16 value)
{
    uptr size = utf8_units_from_str16(value);
    uptr prev = self->head + self->length - size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    self->size += size;
    self->head  = prev % self->length;

    for (uptr i = 0, j = 0; j < size;) {
        u32 unicode = 0;

        i += utf16_decode_forw(value.memory,
            value.length, i, &unicode);

        j += utf8_encode_forw_circ(self->memory, self->length,
            (self->head + j) % self->length, unicode);
    }

    return size;
}

uptr
buf8_write_str16_tail(buf8* self, str16 value)
{
    uptr size = utf8_units_from_str16(value);
    uptr next = self->tail + size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    for (uptr i = 0, j = 0; j < size;) {
        u32 unicode = 0;

        i += utf16_decode_forw(value.memory,
            value.length, i, &unicode);

        j += utf8_encode_forw_circ(self->memory, self->length,
            (self->tail + j) % self->length, unicode);
    }

    self->size += size;
    self->tail  = next % self->length;

    return size;
}

uptr
buf8_write_str32_head(buf8* self, str32 value)
{
    uptr size = utf8_units_from_str32(value);
    uptr prev = self->head + self->length - size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    self->size += size;
    self->head  = prev % self->length;

    for (uptr i = 0, j = 0; j < size;) {
        u32 unicode = 0;

        i += utf32_decode_forw(value.memory,
            value.length, i, &unicode);

        j += utf8_encode_forw_circ(self->memory, self->length,
            (self->head + j) % self->length, unicode);
    }

    return size;
}

uptr
buf8_write_str32_tail(buf8* self, str32 value)
{
    uptr size = utf8_units_from_str32(value);
    uptr next = self->tail + size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    for (uptr i = 0, j = 0; j < size;) {
        u32 unicode = 0;

        i += utf32_decode_forw(value.memory,
            value.length, i, &unicode);

        j += utf8_encode_forw_circ(self->memory, self->length,
            (self->tail + j) % self->length, unicode);
    }

    self->size += size;
    self->tail  = next % self->length;

    return size;
}

uptr
buf8_read_codepoint_head(buf8* self, u32* value)
{
    uptr size = utf8_decode_forw_circ(self->memory,
        self->length, self->head, value);

    uptr next = self->head + size;

    self->size -= size;
    self->head  = next % self->length;

    return size;
}

uptr
buf8_read_codepoint_tail(buf8* self, u32* value)
{
    uptr prev = self->tail + self->length - 1;

    uptr size = utf8_decode_back_circ(self->memory,
        self->length, prev % self->length, value);

    prev = self->tail + self->length - size;

    self->size -= size;
    self->tail  = prev % self->length;

    return size;
}

str8
buf8_read_str8_head(buf8* self, Arena* arena, uptr length)
{
    uptr size = pax_min(self->size, length);
    uptr next = self->head + size;

    str8 result = str8_reserve(arena, size);

    if (result.length == 0) return result;

    for (uptr i = 0; i < size; i += 1)
        result.memory[i] = self->memory[(self->head + i) % self->length];

    self->size -= size;
    self->head  = next % self->length;

    return result;
}

str8
buf8_read_str8_tail(buf8* self, Arena* arena, uptr length)
{
    uptr size = pax_min(self->size, length);
    uptr prev = self->tail + self->length - size;

    str8 result = str8_reserve(arena, size);

    if (result.length == 0) return result;

    self->size -= size;
    self->tail  = prev % self->length;

    for (uptr i = 0; i < size; i += 1)
        result.memory[i] = self->memory[(self->tail + i) % self->length];

    return result;
}

} // namespace pax

#endif // PAX_STRING_BUF8_CPP
