#ifndef PAX_STRING_UTF8_HPP
#define PAX_STRING_UTF8_HPP

#include "unicode.hpp"

namespace pax {

//
// Values
//

static const uptr UTF8_MAX_UNITS = 4;
static const uptr UTF8_MIN_UNITS = 1;

//
// Types
//

struct UTF8
{
    union
    {
        struct
        {
            u8 a, b, c, d;
        };

        u8 memory[UTF8_MAX_UNITS] = {};
    };

    uptr size = 0;
};

//
// Procs
//

/* UTF8 */

b32
utf8_encode(UTF8* self, u32 value);

uptr
utf8_encode_forw(u8* memory, uptr length, uptr index, u32 value);

uptr
utf8_encode_forw_circ(u8* memory, uptr length, uptr index, u32 value);

b32
utf8_decode(UTF8* self, u32* value);

uptr
utf8_decode_forw(u8* memory, uptr length, uptr index, u32* value);

uptr
utf8_decode_forw_circ(u8* memory, uptr length, uptr index, u32* value);

uptr
utf8_decode_back(u8* memory, uptr length, uptr index, u32* value);

uptr
utf8_decode_back_circ(u8* memory, uptr length, uptr index, u32* value);

uptr
utf8_units_to_write(u32 value);

uptr
utf8_units_to_read(u8 value);

b32
utf8_is_trailing(u8 value);

b32
utf8_is_overlong(u32 value, uptr units);

} // namespace pax

#endif // PAX_STRING_UTF8_HPP
