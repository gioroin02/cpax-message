#ifndef PAX_STRING_BUILDER_HPP
#define PAX_STRING_BUILDER_HPP

#include "convert.hpp"

namespace pax {

//
// Types
//

struct Str_Chunk
{
    u32* memory = 0;
    uptr length = 0;

    Str_Chunk* next = 0;
};

struct Str_Builder
{
    Arena* arena = 0;

    Str_Chunk* head = 0;
    Str_Chunk* tail = 0;
};

//
// Procs
//

/* Unicode */

uptr
utf8_units_from_str_builder(Str_Builder* self);

uptr
utf16_units_from_str_builder(Str_Builder* self);

uptr
utf32_units_from_str_builder(Str_Builder* self);

/* Str_Builder */

Str_Builder
str_builder_make(Arena* arena);

void
str_builder_clear(Str_Builder* self);

b32
str_builder_unicode(Str_Builder* self, u32 value);

b32
str_builder_str8(Str_Builder* self, str8 value);

b32
str_builder_str16(Str_Builder* self, str16 value);

b32
str_builder_str32(Str_Builder* self, str32 value);

str8
str8_from_str_builder(Str_Builder* builder);

str16
str16_from_str_builder(Str_Builder* builder);

str32
str32_from_str_builder(Str_Builder* builder);

buf8
buf8_from_str_builder(Str_Builder* builder);

} // namespace pax

#endif // PAX_STRING_BUILDER_HPP
