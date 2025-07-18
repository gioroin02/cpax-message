#ifndef PAX_MEMORY_SYSTEM_CPP
#define PAX_MEMORY_SYSTEM_CPP

#include "system.hpp"

#if PAX_PLATFORM == PAX_PLATFORM_WINDOWS

    #include "windows/system.cpp"

    #define __system_get_page_size__ windows_get_page_size
    #define __system_reserve__       windows_reserve
    #define __system_release__       windows_release

#else

    #error "Platform not supported or unknown"

#endif

namespace pax {

uptr
system_get_page_size()
{
    return __system_get_page_size__();
}

Arena
system_reserve(uptr pages)
{
    return __system_reserve__(pages);
}

void
system_release(Arena* arena)
{
    __system_release__(arena);
}

} // namespace pax

#endif // PAX_MEMORY_SYSTEM_CPP
