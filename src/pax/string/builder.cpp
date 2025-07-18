#ifndef PAX_STRING_BUILDER_CPP
#define PAX_STRING_BUILDER_CPP

#include "builder.hpp"

namespace pax {

static b32
str_builder_append(Str_Builder* self, str32 string)
{
    uptr offset = arena_offset(self->arena);

    Str_Chunk* chunk = arena_reserve_one<Str_Chunk>(self->arena);

    if (chunk != 0) {
        chunk->memory = string.memory;
        chunk->length = string.length;
        chunk->next   = 0;

        if (self->head != 0)
            self->tail->next = chunk;
        else
            self->head = chunk;

        self->tail = chunk;

        return 1;
    }

    arena_rewind(self->arena, offset);

    return 0;
}

uptr
utf8_units_from_str_builder(Str_Builder *self)
{
    uptr       result = 0;
    Str_Chunk* chunk  = self->head;

    for (; chunk != 0; chunk = chunk->next) {
        uptr units = utf8_units_from_utf32(
            chunk->memory, chunk->length);

        if (units > 0)
            result += units;
        else
            return 0;
    }

    return result;
}

uptr
utf16_units_from_str_builder(Str_Builder *self)
{
    uptr       result = 0;
    Str_Chunk* chunk  = self->head;

    for (; chunk != 0; chunk = chunk->next) {
        uptr units = utf16_units_from_utf32(
            chunk->memory, chunk->length);

        if (units > 0)
            result += units;
        else
            return 0;
    }

    return result;
}

uptr
utf32_units_from_str_builder(Str_Builder *self)
{
    uptr       result = 0;
    Str_Chunk* chunk  = self->head;

    for (; chunk != 0; chunk = chunk->next)
        result += chunk->length;

    return result;
}

Str_Builder
str_builder_make(Arena* arena)
{
    Str_Builder result = {};

    result.arena = arena;
    result.head  = 0;
    result.tail  = 0;

    return result;
}

void
str_builder_clear(Str_Builder* self)
{
    self->head = 0;
    self->tail = 0;
}

b32
str_builder_unicode(Str_Builder* self, u32 value)
{
    uptr  offset = arena_offset(self->arena);
    str32 string = str32_from_unicode(self->arena, value);

    if (string.length != 0) {
        if (str_builder_append(self, string) != 0)
            return 1;
    }

    arena_rewind(self->arena, offset);

    return 0;
}

b32
str_builder_str8(Str_Builder* self, str8 value)
{
    uptr  offset = arena_offset(self->arena);
    str32 string = str32_from_str8(self->arena, value);

    if (string.length != 0) {
        if (str_builder_append(self, string) != 0)
            return 1;
    }

    arena_rewind(self->arena, offset);

    return 0;
}

b32
str_builder_str16(Str_Builder* self, str16 value)
{
    uptr  offset = arena_offset(self->arena);
    str32 string = str32_from_str16(self->arena, value);

    if (string.length != 0) {
        if (str_builder_append(self, string) != 0)
            return 1;
    }

    arena_rewind(self->arena, offset);

    return 0;
}

b32
str_builder_str32(Str_Builder* self, str32 value)
{
    uptr  offset = arena_offset(self->arena);
    str32 string = str32_copy(self->arena, value);

    if (string.length != 0) {
        if (str_builder_append(self, string) != 0)
            return 1;
    }

    arena_rewind(self->arena, offset);

    return 0;
}

str8
str8_from_str_builder(Str_Builder* builder)
{
    uptr length = utf8_units_from_str_builder(builder);
    str8 result = str8_reserve(builder->arena, length);

    if (result.length == 0) return result;

    Str_Chunk* chunk = builder->head;
    uptr       index = 0;

    for (; chunk != 0; chunk = chunk->next) {
        for (uptr i = 0; i < chunk->length; i += 1) {
            index += utf8_encode_forw(result.memory, result.length,
                index, chunk->memory[i]);
        }
    }

    return result;
}

str16
str16_from_str_builder(Str_Builder* builder)
{
    uptr  length = utf16_units_from_str_builder(builder);
    str16 result = str16_reserve(builder->arena, length);

    if (result.length == 0) return result;

    Str_Chunk* chunk = builder->head;
    uptr       index = 0;

    for (; chunk != 0; chunk = chunk->next) {
        for (uptr i = 0; i < chunk->length; i += 1) {
            index += utf16_encode_forw(result.memory, result.length,
                index, chunk->memory[i]);
        }
    }

    return result;
}

str32
str32_from_str_builder(Str_Builder* builder)
{
    uptr  length = utf32_units_from_str_builder(builder);
    str32 result = str32_reserve(builder->arena, length);

    if (result.length == 0) return result;

    Str_Chunk* chunk = builder->head;
    uptr       index = 0;

    for (; chunk != 0; chunk = chunk->next) {
        for (uptr i = 0; i < chunk->length; i += 1)
            result.memory[i + index] = chunk->memory[i];

        index += chunk->length;
    }

    return result;
}

buf8
buf8_from_str_builder(Str_Builder* builder)
{
    uptr length = utf8_units_from_str_builder(builder);
    buf8 result = buf8_reserve(builder->arena, length);

    Str_Chunk* chunk = builder->head;
    uptr       index = 0;

    for (; chunk != 0; chunk = chunk->next) {
        for (uptr i = 0; i < chunk->length; i += 1) {
            index += utf8_encode_forw(result.memory, result.length,
                index, chunk->memory[i]);
        }
    }

    result.size = result.length;

    return result;
}

} // namespace pax

#endif // PAX_STRING_BUILDER_CPP
