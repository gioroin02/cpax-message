#ifndef PAX_STRING_UTF16_HPP
#define PAX_STRING_UTF16_HPP

#include "unicode.hpp"

namespace pax {

//
// Values
//

static const uptr UTF16_MAX_UNITS = 2;
static const uptr UTF16_MIN_UNITS = 1;

//
// Types
//

struct UTF16
{
    union
    {
        struct
        {
            u16 a, b;
        };

        u16 memory[UTF16_MAX_UNITS] = {};
    };

    uptr size = 0;
};

//
// Procs
//

/* UTF16 */

b32
utf16_encode(UTF16* self, u32 value);

uptr
utf16_encode_forw(u16* memory, uptr length, uptr index, u32 value);

uptr
utf16_encode_forw_circ(u16* memory, uptr length, uptr index, u32 value);

b32
utf16_decode(UTF16* self, u32* value);

uptr
utf16_decode_forw(u16* memory, uptr length, uptr index, u32* value);

uptr
utf16_decode_forw_circ(u16* memory, uptr length, uptr index, u32* value);

uptr
utf16_decode_back(u16* memory, uptr length, uptr index, u32* value);

uptr
utf16_decode_back_circ(u16* memory, uptr length, uptr index, u32* value);

uptr
utf16_units_to_write(u32 value);

uptr
utf16_units_to_read(u16 value);

} // namespace pax

#endif // PAX_STRING_UTF16_HPP
