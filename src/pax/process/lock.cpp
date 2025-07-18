#ifndef PAX_PROCESS_LOCK_CPP
#define PAX_PROCESS_LOCK_CPP

#include "lock.hpp"

#if PAX_PLATFORM == PAX_PLATFORM_WINDOWS

    #include "windows/lock.cpp"

    #define __Lock__ Windows_Lock

    #define __lock_create__  windows_lock_create
    #define __lock_destroy__ windows_lock_destroy
    #define __lock_enter__   windows_lock_enter
    #define __lock_leave__   windows_lock_leave

#else

    #error "Platform not supported or unknown"

#endif

#define pax_lock(self) pax_cast(__Lock__*, self)

namespace pax {

Lock
lock_create(Arena* arena)
{
    return __lock_create__(arena);
}

void
lock_destroy(Lock self)
{
    __lock_destroy__(pax_lock(self));
}

b32
lock_enter(Lock self)
{
    return __lock_enter__(pax_lock(self));
}

b32
lock_leave(Lock self)
{
    return __lock_leave__(pax_lock(self));
}

} // namespace pax

#endif // PAX_PROCESS_LOCK_CPP
