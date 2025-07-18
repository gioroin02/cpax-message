#ifndef PAX_PROCESS_THREAD_CPP
#define PAX_PROCESS_THREAD_CPP

#include "thread.hpp"

#if PAX_PLATFORM == PAX_PLATFORM_WINDOWS

    #include "windows/thread.cpp"

    #define __Routine__ Windows_Routine
    #define __Thread__  Windows_Thread

    #define __thread_create__     windows_thread_create
    #define __thread_destroy__    windows_thread_destroy
    #define __thread_wait__       windows_thread_wait
    #define __thread_detach__     windows_thread_detach
    #define __thread_is_running__ windows_thread_is_running

#else

    #error "Platform not supported or unknown"

#endif

#define pax_routine(self) pax_cast(__Routine__*, self)
#define pax_thread(self)  pax_cast(__Thread__*, self)

namespace pax {

Thread
thread_create(Arena* arena, Routine* routine, addr argumns)
{
    return __thread_create__(arena, pax_routine(routine), argumns);
}

void
thread_destroy(Thread self)
{
    __thread_destroy__(pax_thread(self));
}

void
thread_wait(Thread self)
{
    __thread_wait__(pax_thread(self));
}

void
thread_detach(Thread self)
{
    __thread_detach__(pax_thread(self));
}

b32
thread_is_running(Thread self)
{
    return __thread_is_running__(pax_thread(self));
}

} // namespace pax

#endif // PAX_PROCESS_THREAD_CPP
