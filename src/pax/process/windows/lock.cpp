#ifndef PAX_PROCESS_WINDOWS_LOCK_CPP
#define PAX_PROCESS_WINDOWS_LOCK_CPP

#include "lock.hpp"

#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOMINMAX

#include <windows.h>

namespace pax {

struct Windows_Lock
{
    HANDLE handle = 0;
};

Windows_Lock*
windows_lock_create(Arena* arena)
{
    uptr offset = arena_offset(arena);

    Windows_Lock* result = arena_reserve_one<Windows_Lock>(arena);

    if (result != 0) {
        result->handle = CreateMutex(0, 0, 0);

        if (result->handle != 0)
            return result;

        arena_rewind(arena, offset);
    }

    return 0;
}

void
windows_lock_destroy(Windows_Lock* self)
{
    if (self == 0) return;

    if (self->handle != 0)
        CloseHandle(self->handle);

    self->handle = 0;
}

b32
windows_lock_enter(Windows_Lock* self)
{
    return WaitForSingleObject(self->handle, INFINITE) != WAIT_ABANDONED;
}

b32
windows_lock_leave(Windows_Lock* self)
{
    return ReleaseMutex(self->handle) != 0;
}

} // namespace pax

#endif // PAX_PROCESS_WINDOWS_LOCK_CPP
