#ifndef PAX_STORAGE_DIR_VIEW_CPP
#define PAX_STORAGE_DIR_VIEW_CPP

#include "dir_view.hpp"

#if PAX_PLATFORM == PAX_PLATFORM_WINDOWS

    #include "windows/dir_view.cpp"

    #define __Dir_View__ Windows_Dir_View

    #define __dir_view__  windows_dir_view
    #define __dir_next__  windows_dir_next

#else

    #error "Platform not supported or unknown"

#endif

#define pax_dir_view(self) pax_cast(__Dir_View__*, self)

namespace pax {

Dir_View
dir_view(Arena* arena, str8 path)
{
    return __dir_view__(arena, path);
}

b32
dir_next(Dir_View self, Arena* arena, File_Props* value)
{
    return __dir_next__(pax_dir_view(self), arena, value);
}

} // namespace pax

#endif // PAX_STORAGE_DIR_VIEW_CPP
