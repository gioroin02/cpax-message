#ifndef PAX_STRING_BUF32_CPP
#define PAX_STRING_BUF32_CPP

#include "buf32.hpp"

namespace pax {

uptr
buf32_write_codepoint_head(buf32* self, u32 value)
{
    uptr size = utf32_units_to_write(value);
    uptr prev = self->head + self->length - size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    self->size -= size;
    self->head  = prev % self->length;

    utf32_encode_forw(self->memory,
        self->length, self->head, value);

    return size;
}

uptr
buf32_write_codepoint_tail(buf32* self, u32 value)
{
    uptr size = utf32_units_to_write(value);
    uptr next = self->tail + size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    utf32_encode_forw(self->memory,
        self->length, self->tail, value);

    self->size += size;
    self->tail  = next % self->length;

    return size;
}

uptr
buf32_write_str8_head(buf32* self, str8 value)
{
    uptr size = utf32_units_from_str8(value);
    uptr prev = self->head + self->length - size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    self->size += size;
    self->head  = prev % self->length;

    for (uptr i = 0, j = 0; j < size;) {
        u32 unicode = 0;

        i += utf8_decode_forw(value.memory,
            value.length, i, &unicode);

        j += utf32_encode_forw(self->memory, self->length,
            (self->head + j) % self->length, unicode);
    }

    return size;
}

uptr
buf32_write_str8_tail(buf32* self, str8 value)
{
    uptr size = utf32_units_from_str8(value);
    uptr next = self->tail + size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    for (uptr i = 0, j = 0; j < size;) {
        u32 unicode = 0;

        i += utf8_decode_forw(value.memory,
            value.length, i, &unicode);

        j += utf32_encode_forw(self->memory, self->length,
            (self->tail + j) % self->length, unicode);
    }

    self->size += size;
    self->tail  = next % self->length;

    return size;
}

uptr
buf32_write_str16_head(buf32* self, str16 value)
{
    uptr size = utf32_units_from_str16(value);
    uptr prev = self->head + self->length - size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    self->size += size;
    self->head  = prev % self->length;

    for (uptr i = 0, j = 0; j < size;) {
        u32 unicode = 0;

        i += utf16_decode_forw(value.memory,
            value.length, i, &unicode);

        j += utf32_encode_forw(self->memory, self->length,
            (self->head + j) % self->length, unicode);
    }

    return size;
}

uptr
buf32_write_str16_tail(buf32* self, str16 value)
{
    uptr size = utf32_units_from_str16(value);
    uptr next = self->tail + size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    for (uptr i = 0, j = 0; j < size;) {
        u32 unicode = 0;

        i += utf16_decode_forw(value.memory,
            value.length, i, &unicode);

        j += utf32_encode_forw(self->memory, self->length,
            (self->tail + j) % self->length, unicode);
    }

    self->size += size;
    self->tail  = next % self->length;

    return size;
}

uptr
buf32_write_str32_head(buf32* self, str32 value)
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
buf32_write_str32_tail(buf32* self, str32 value)
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
buf32_read_codepoint_head(buf32* self, u32* value)
{
    uptr size = utf32_decode_forw(self->memory,
        self->length, self->head, value);

    uptr next = self->head + size;

    self->size -= size;
    self->head  = next % self->length;

    return size;
}

uptr
buf32_read_codepoint_tail(buf32* self, u32* value)
{
    uptr prev = self->tail + self->length - 1;

    uptr size = utf32_decode_back(self->memory,
        self->length, prev % self->length, value);

    prev = self->tail + self->length - size;

    self->size -= size;
    self->tail  = prev % self->length;

    return size;
}

str32
buf32_read_str32_head(buf32* self, Arena* arena, uptr length)
{
    uptr size = pax_min(self->size, length);
    uptr next = self->head + size;

    str32 result = str32_reserve(arena, size);

    if (result.length == 0) return result;

    for (uptr i = 0; i < size; i += 1)
        result.memory[i] = self->memory[(self->head + i) % self->length];

    self->size -= size;
    self->head  = next % self->length;

    return result;
}

str32
buf32_read_str32_tail(buf32* self, Arena* arena, uptr length)
{
    uptr size = pax_min(self->size, length);
    uptr prev = self->tail + self->length - size;

    str32 result = str32_reserve(arena, size);

    if (result.length == 0) return result;

    self->size -= size;
    self->tail  = prev % self->length;

    for (uptr i = 0; i < size; i += 1)
        result.memory[i] = self->memory[(self->tail + i) % self->length];

    return result;
}

} // namespace pax

#endif // PAX_STRING_BUF32_CPP
