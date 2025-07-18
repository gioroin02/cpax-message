#ifndef PAX_STRING_UTF32_HPP
#define PAX_STRING_UTF32_HPP

#include "unicode.hpp"

namespace pax {

//
// Values
//

static const uptr UTF32_MAX_UNITS = 1;
static const uptr UTF32_MIN_UNITS = 1;

//
// Types
//

struct UTF32
{
    union
    {
        struct
        {
            u32 a;
        };

        u32 memory[UTF32_MAX_UNITS] = {};
    };

    uptr size = 0;
};

//
// Procs
//

/* UTF32 */

b32
utf32_encode(UTF32* self, u32 value);

uptr
utf32_encode_forw(u32* memory, uptr length, uptr index, u32 value);

b32
utf32_decode(UTF32* self, u32* value);

uptr
utf32_decode_forw(u32* memory, uptr length, uptr index, u32* value);

uptr
utf32_decode_back(u32* memory, uptr length, uptr index, u32* value);

uptr
utf32_units_to_write(u32 value);

uptr
utf32_units_to_read(u32 value);

} // namespace pax

#endif // PAX_STRING_UTF32_HPP
