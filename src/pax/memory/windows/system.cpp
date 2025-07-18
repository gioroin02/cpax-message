#ifndef PAX_MEMORY_WINDOWS_SYSTEM_CPP
#define PAX_MEMORY_WINDOWS_SYSTEM_CPP

#include "system.hpp"

#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOMINMAX

#include <windows.h>

namespace pax {

uptr
windows_get_page_size()
{
    SYSTEM_INFO info = {};

    GetSystemInfo(&info);

    return pax_cast(uptr, info.dwPageSize);
}

Arena
windows_reserve(uptr pages)
{
    Arena result = {};
    uptr  length = windows_get_page_size();

    if (length <= U32_MAX / pages) {
        length *= pages;

        addr memory = VirtualAlloc(0, pax_cast(DWORD, length),
            MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

        result = arena_make(pax_cast(u8*, memory), length);
    }

    return result;
}

void
windows_release(Arena* arena)
{
    if (arena->memory != 0)
        VirtualFree(arena->memory, 0, MEM_RELEASE);

    arena->memory = 0;
    arena->length = 0;
    arena->offset = 0;
}

} // namespace pax

#endif // PAX_MEMORY_WINDOWS_SYSTEM_CPP
