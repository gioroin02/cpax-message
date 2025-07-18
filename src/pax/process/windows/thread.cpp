#ifndef PAX_PROCESS_WINDOWS_THREAD_CPP
#define PAX_PROCESS_WINDOWS_THREAD_CPP

#include "thread.hpp"

#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOMINMAX

#include <windows.h>

namespace pax {

struct Windows_Thread
{
    HANDLE handle = 0;
    DWORD  ident  = 0;
};

//
// Procs
//

Windows_Thread*
windows_thread_create(Arena* arena, Windows_Routine* routine, addr argumns)
{
    uptr offset = arena_offset(arena);

    Windows_Thread* result = arena_reserve_one<Windows_Thread>(arena);

    if (result != 0) {
        LPTHREAD_START_ROUTINE temp = pax_cast(LPTHREAD_START_ROUTINE, routine);

        result->handle = CreateThread(0, 0, temp, argumns, 0, &result->ident);

        if (result->handle != 0)
            return result;

        arena_rewind(arena, offset);
    }

    return 0;
}

void
windows_thread_destroy(Windows_Thread* self)
{
    DWORD state = 0;

    if (self == 0) return;

    if (self->handle != 0) {
        GetExitCodeThread(self->handle, &state);

        if (state == STILL_ACTIVE)
            TerminateThread(self->handle, 0);

        CloseHandle(self->handle);
    }

    self->handle = 0;
    self->ident  = 0;
}

void
windows_thread_wait(Windows_Thread* self)
{
    WaitForSingleObject(self->handle, INFINITE);
}

void
windows_thread_detach(Windows_Thread* self)
{
    if (self->handle != 0)
        CloseHandle(self->handle);

    self->handle = 0;
}

b32
windows_thread_is_running(Windows_Thread* self)
{
    return self->handle != 0;
}

} // namespace pax

#endif // PAX_PROCESS_WINDOWS_THREAD_CPP
