#ifndef PAX_CORE_DEFINES_HPP
#define PAX_CORE_DEFINES_HPP

#define PAX_ARCH_NONE 0
#define PAX_ARCH_32   1
#define PAX_ARCH_64   2
#define PAX_ARCH_MAX  3

#ifndef PAX_ARCH

    #if _WIN64 || __PL64__ || __x86_64__ || __amd64__ || __aarch64__

        #define PAX_ARCH PAX_ARCH_64

    #elif _WIN32 || __ILP32__ || _i386_

        #define PAX_ARCH PAX_ARCH_32

    #else

        #define PAX_ARCH PAX_ARCH_NONE

    #endif

#endif

#define PAX_PLATFORM_NONE    0
#define PAX_PLATFORM_WINDOWS 1
#define PAX_PLATFORM_MAX     2

#ifndef PAX_PLATFORM

    #if _WIN32

        #define PAX_PLATFORM PAX_PLATFORM_WINDOWS

    #else

        #define PAX_PLATFORM PAX_PLATFORM_NONE

    #endif

#endif

#define __pax_string__(expr)        (# expr)
#define __pax_concat__(left, right) (left ## right)

#define __pax_size_of__(expr) ((pax::uptr) (sizeof(expr)))

//
// Defines
//

#define pax_string(expr)        __pax_string__(expr)
#define pax_concat(left, right) __pax_concat__(left, right)

#define pax_size_of(expr) __pax_size_of__(expr)

#define pax_array_bytes(array)  pax_size_of(array)
#define pax_array_stride(array) pax_size_of((array)[0])

#define pax_array_length(array) \
    (pax_array_bytes(array) / pax_array_stride(array))

#define pax_cast(type, expr) ((type) (expr))
#define pax_null(type)       ((type*) (0))

#define pax_min(x, y) ((x) < (y) ? (x) : (y))
#define pax_max(x, y) ((x) < (y) ? (y) : (x))

#define pax_limit(x, y, z) pax_min(pax_max(x, y), z)

#endif // PAX_CORE_DEFINES_HPP
