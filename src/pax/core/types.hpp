#ifndef PAX_CORE_TYPES_HPP
#define PAX_CORE_TYPES_HPP

#include "defines.hpp"

//
// Defines
//

#define pax_f64(x) pax_cast(f64, x)
#define pax_f32(x) pax_cast(f32, x)

#define pax_u64(x) pax_cast(u64, x)
#define pax_u32(x) pax_cast(u32, x)
#define pax_u16(x) pax_cast(u16, x)
#define pax_u8(x)  pax_cast(u8,  x)

#define pax_i64(x) pax_cast(i64, x)
#define pax_i32(x) pax_cast(i32, x)
#define pax_i16(x) pax_cast(i16, x)
#define pax_i8(x)  pax_cast(i8,  x)

#define pax_b64(x) pax_cast(b64, x)
#define pax_b32(x) pax_cast(b32, x)
#define pax_b16(x) pax_cast(b16, x)
#define pax_b8(x)  pax_cast(b8,  x)

#define pax_addr(x) pax_cast(addr, x)
#define pax_uptr(x) pax_cast(uptr, x)
#define pax_iptr(x) pax_cast(iptr, x)

namespace pax {

//
// Types
//

#if PAX_ARCH == PAX_ARCH_64

    using f64 = double;
    using f32 = float;

    using u64 = unsigned long long;
    using u32 = unsigned int;
    using u16 = unsigned short;
    using u8  = unsigned char;

    using i64 = long long;
    using i32 = int;
    using i16 = short;
    using i8  = char;

    using b64 = u64;
    using b32 = u32;
    using b16 = u16;
    using b8  = u8;

    using addr = void*;

    using uptr = u64;
    using iptr = i64;

#else

    #error "Architecture not supported or unknown"

#endif

//
// Values
//

static const u64 __F64_ZERO__     = 0x0000000000000000;
static const u64 __F64_ZERO_POS__ = 0x0000000000000000;
static const u64 __F64_ZERO_NEG__ = 0x8000000000000000;
static const u64 __F64_INF__      = 0x7ff0000000000000;
static const u64 __F64_INF_POS__  = 0x7ff0000000000000;
static const u64 __F64_INF_NEG__  = 0xfff0000000000000;
static const u64 __F64_NAN__      = 0x7ff8000000000000;
static const u64 __F64_NAN_POS__  = 0x7ff8000000000000;
static const u64 __F64_NAN_NEG__  = 0xfff8000000000000;

static const f64 F64_ZERO     = *pax_cast(f64*, &__F64_ZERO__);
static const f64 F64_ZERO_POS = *pax_cast(f64*, &__F64_ZERO_POS__);
static const f64 F64_ZERO_NEG = *pax_cast(f64*, &__F64_ZERO_NEG__);
static const f64 F64_INF      = *pax_cast(f64*, &__F64_INF__);
static const f64 F64_INF_POS  = *pax_cast(f64*, &__F64_INF_POS__);
static const f64 F64_INF_NEG  = *pax_cast(f64*, &__F64_INF_NEG__);
static const f64 F64_NAN      = *pax_cast(f64*, &__F64_NAN__);
static const f64 F64_NAN_POS  = *pax_cast(f64*, &__F64_NAN_POS__);
static const f64 F64_NAN_NEG  = *pax_cast(f64*, &__F64_NAN_NEG__);

static const u64 F64_MASK_FRAC = 0x000fffffffffffff;
static const u64 F64_MASK_EXP  = 0x7ff0000000000000;
static const u64 F64_MASK_SIGN = 0x8000000000000000;

static const u64 F64_SIZE_FRAC = 52;
static const u64 F64_SIZE_EXP  = 11;
static const u64 F64_SIGE_SIGN = 1;

static const i32 F64_EXP_BIAS =  1023; // 16 + 16 bits
static const i32 F64_EXP_MAX  =  1023; // 16 + 16 bits
static const i32 F64_EXP_MIN  = -1022; // 16 + 16 bits

static const uptr F64_SIZE = pax_size_of(f64);

static const u32 __F32_ZERO__     = 0x00000000;
static const u32 __F32_ZERO_POS__ = 0x00000000;
static const u32 __F32_ZERO_NEG__ = 0x80000000;
static const u32 __F32_INF__      = 0x7f800000;
static const u32 __F32_INF_POS__  = 0x7f800000;
static const u32 __F32_INF_NEG__  = 0xff800000;
static const u32 __F32_NAN__      = 0x7fc00000;
static const u32 __F32_NAN_POS__  = 0x7fc00000;
static const u32 __F32_NAN_NEG__  = 0xffc00000;

static const f32 F32_ZERO     = *pax_cast(f32*, &__F32_ZERO__);
static const f32 F32_ZERO_POS = *pax_cast(f32*, &__F32_ZERO_POS__);
static const f32 F32_ZERO_NEG = *pax_cast(f32*, &__F32_ZERO_NEG__);
static const f32 F32_INF      = *pax_cast(f32*, &__F32_INF__);
static const f32 F32_INF_POS  = *pax_cast(f32*, &__F32_INF_POS__);
static const f32 F32_INF_NEG  = *pax_cast(f32*, &__F32_INF_NEG__);
static const f32 F32_NAN      = *pax_cast(f32*, &__F32_NAN__);
static const f32 F32_NAN_POS  = *pax_cast(f32*, &__F32_NAN_POS__);
static const f32 F32_NAN_NEG  = *pax_cast(f32*, &__F32_NAN_NEG__);

static const u32 F32_MASK_FRAC = 0x007fffff;
static const u32 F32_MASK_EXP  = 0x7f800000;
static const u32 F32_MASK_SIGN = 0x80000000;

static const u32 F32_SIZE_FRAC = 23;
static const u32 F32_SIZE_EXP  = 8;
static const u32 F32_SIZE_SIGN = 1;

static const i16 F32_EXP_BIAS =  127; // 8 + 8 bits
static const i16 F32_EXP_MAX  =  127; // 8 + 8 bits
static const i16 F32_EXP_MIN  = -126; // 8 + 8 bits

static const uptr F32_SIZE = pax_size_of(f32);

static const u64 U64_MAX  = 0xffffffffffffffff;
static const u64 U64_MIN  = 0x0000000000000000;
static const u64 U64_ZERO = 0x0000000000000000;

static const uptr U64_SIZE = pax_size_of(u64);

static const u32 U32_MAX  = 0xffffffff;
static const u32 U32_MIN  = 0x00000000;
static const u32 U32_ZERO = 0x00000000;

static const uptr U32_SIZE = pax_size_of(u32);

static const u16 U16_MAX  = 0xffff;
static const u16 U16_MIN  = 0x0000;
static const u16 U16_ZERO = 0x0000;

static const uptr U16_SIZE = pax_size_of(u16);

static const u8 U8_MAX  = 0xff;
static const u8 U8_MIN  = 0x00;
static const u8 U8_ZERO = 0x00;

static const uptr U8_SIZE = pax_size_of(u8);

static const i64 I64_MAX  = 0x7fffffffffffffff;
static const i64 I64_MIN  = 0x8000000000000000;
static const i64 I64_ZERO = 0x0000000000000000;

static const uptr I64_SIZE = pax_size_of(i64);

static const i32 I32_MAX  = 0x7fffffff;
static const i32 I32_MIN  = 0x80000000;
static const i32 I32_ZERO = 0x00000000;

static const uptr I32_SIZE = pax_size_of(i32);

static const i16 I16_MAX  = 0x7fff;
static const i16 I16_MIN  = 0x8000;
static const i16 I16_ZERO = 0x0000;

static const uptr I16_SIZE = pax_size_of(i16);

static const i8 I8_MAX  = 0x7f;
static const i8 I8_MIN  = 0x80;
static const i8 I8_ZERO = 0x00;

static const uptr I8_SIZE = pax_size_of(i8);

static const uptr B64_SIZE = pax_size_of(b64);
static const uptr B32_SIZE = pax_size_of(b32);
static const uptr B16_SIZE = pax_size_of(b16);
static const uptr B8_SIZE  = pax_size_of(b8);

static const uptr ADDR_SIZE = pax_size_of(addr);

static const uptr UPTR_SIZE = pax_size_of(uptr);
static const uptr IPTR_SIZE = pax_size_of(iptr);

#if PAX_ARCH == PAX_ARCH_64

    static const uptr UPTR_MAX  = U64_MAX;
    static const uptr UPTR_MIN  = U64_MIN;
    static const uptr UPTR_ZERO = U64_ZERO;

    static const iptr IPTR_MAX  = I64_MAX;
    static const iptr IPTR_MIN  = I64_MIN;
    static const iptr IPTR_ZERO = I64_ZERO;

#else

    #error "Architecture not supported or unknown"

#endif

} // namespace pax

#endif // PAX_CORE_TYPES_HPP
