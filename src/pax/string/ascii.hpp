#ifndef PAX_STRING_ASCII_HPP
#define PAX_STRING_ASCII_HPP

#include "imports.hpp"

namespace pax {

//
// Values
//

static const uptr ASCII_COUNT = 128;

//
// Types
//

enum ASCII
{
    ASCII_NULL,
    ASCII_1,
    ASCII_2,
    ASCII_3,
    ASCII_4,
    ASCII_5,
    ASCII_6,
    ASCII_7,
    ASCII_SPACE_BACK,
    ASCII_TAB_HORIZONTAL,
    ASCII_NEW_LINE,
    ASCII_TAB_VERTICAL,
    ASCII_NEW_PAGE,
    ASCII_CARRIAGE_RETURN,
    ASCII_14,
    ASCII_15,
    ASCII_16,
    ASCII_17,
    ASCII_18,
    ASCII_19,
    ASCII_20,
    ASCII_21,
    ASCII_22,
    ASCII_23,
    ASCII_CANCEL,
    ASCII_25,
    ASCII_26,
    ASCII_ESCAPE,
    ASCII_28,
    ASCII_29,
    ASCII_30,
    ASCII_31,
    ASCII_SPACE,
    ASCII_EXCLAMATION,
    ASCII_QUOTATION,
    ASCII_SHARP,
    ASCII_DOLLAR,
    ASCII_PERCENT,
    ASCII_AMPERSAND,
    ASCII_APOSTROPHE,
    ASCII_PAREN_LEFT,
    ASCII_PAREN_RIGHT,
    ASCII_ASTERISK,
    ASCII_PLUS,
    ASCII_COMMA,
    ASCII_MINUS,
    ASCII_POINT,
    ASCII_SLASH,
    ASCII_ZERO,
    ASCII_ONE,
    ASCII_TWO,
    ASCII_THREE,
    ASCII_FOUR,
    ASCII_FIVE,
    ASCII_SIX,
    ASCII_SEVEN,
    ASCII_EIGHT,
    ASCII_NINE,
    ASCII_COLON,
    ASCII_COLON_SEMI,
    ASCII_LESS,
    ASCII_EQUAL,
    ASCII_MORE,
    ASCII_QUESTION,
    ASCII_COMMERCIAL,
    ASCII_UPPER_A,
    ASCII_UPPER_B,
    ASCII_UPPER_C,
    ASCII_UPPER_D,
    ASCII_UPPER_E,
    ASCII_UPPER_F,
    ASCII_UPPER_G,
    ASCII_UPPER_H,
    ASCII_UPPER_I,
    ASCII_UPPER_J,
    ASCII_UPPER_K,
    ASCII_UPPER_L,
    ASCII_UPPER_M,
    ASCII_UPPER_N,
    ASCII_UPPER_O,
    ASCII_UPPER_P,
    ASCII_UPPER_Q,
    ASCII_UPPER_R,
    ASCII_UPPER_S,
    ASCII_UPPER_T,
    ASCII_UPPER_U,
    ASCII_UPPER_V,
    ASCII_UPPER_W,
    ASCII_UPPER_X,
    ASCII_UPPER_Y,
    ASCII_UPPER_Z,
    ASCII_SQUARE_LEFT,
    ASCII_SLASH_BACK,
    ASCII_SQUARE_RIGHT,
    ASCII_CIRCUMFLEX,
    ASCII_UNDERSCORE,
    ASCII_TICK_BACK,
    ASCII_LOWER_A,
    ASCII_LOWER_B,
    ASCII_LOWER_C,
    ASCII_LOWER_D,
    ASCII_LOWER_E,
    ASCII_LOWER_F,
    ASCII_LOWER_G,
    ASCII_LOWER_H,
    ASCII_LOWER_I,
    ASCII_LOWER_J,
    ASCII_LOWER_K,
    ASCII_LOWER_L,
    ASCII_LOWER_M,
    ASCII_LOWER_N,
    ASCII_LOWER_O,
    ASCII_LOWER_P,
    ASCII_LOWER_Q,
    ASCII_LOWER_R,
    ASCII_LOWER_S,
    ASCII_LOWER_T,
    ASCII_LOWER_U,
    ASCII_LOWER_V,
    ASCII_LOWER_W,
    ASCII_LOWER_X,
    ASCII_LOWER_Y,
    ASCII_LOWER_Z,
    ASCII_BRACE_LEFT,
    ASCII_PIPE,
    ASCII_BRACE_RIGHT,
    ASCII_TILDE,
    ASCII_DELETE,
};

//
// Procs
//

/* ASCII */

b32
ascii_is_space(u32 value);

b32
ascii_is_digit(u32 value, uptr base);

b32
ascii_is_letter(u32 value);

b32
ascii_is_lower(u32 value);

b32
ascii_is_upper(u32 value);

uptr
digit_from_ascii(u32 value, uptr base);

uptr
letter_from_ascii(u32 value);

u32
ascii_from_digit(uptr value, uptr base);

u32
ascii_from_upper(uptr value);

u32
ascii_from_lower(uptr value);

} // namespace pax

#endif // PAX_STRING_ASCII_HPP
