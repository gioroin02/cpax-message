#ifndef PAX_STRING_UNICODE_CPP
#define PAX_STRING_UNICODE_CPP

#include "unicode.hpp"

namespace pax {

b32
unicode_is_codepoint(u32 value)
{
    return (value >= 0x0    && value <= 0xd7ff) ||
           (value >= 0xe000 && value <= 0x10ffff);
}

b32
unicode_is_surrogate(u32 value)
{
    return (value >= 0xd800 && value <= 0xdfff);
}

b32
unicode_is_surrogate_low(u32 value)
{
    return (value >= 0xdc00 && value <= 0xdfff);
}

b32
unicode_is_surrogate_high(u32 value)
{
    return (value >= 0xd800 && value <= 0xdbff);
}

} // namespace pax

#endif // PAX_STRING_UNICODE_CPP
