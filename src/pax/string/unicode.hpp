#ifndef PAX_STRING_UNICODE_HPP
#define PAX_STRING_UNICODE_HPP

#include "imports.hpp"

namespace pax {

//
// Procs
//

/* Unicode */

b32
unicode_is_codepoint(u32 value);

b32
unicode_is_surrogate(u32 value);

b32
unicode_is_surrogate_low(u32 value);

b32
unicode_is_surrogate_high(u32 value);

} // namespace pax

#endif // PAX_STRING_UNICODE_HPP
