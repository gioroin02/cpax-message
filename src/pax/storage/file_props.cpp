#ifndef PAX_FILE_PROPS_CPP
#define PAX_FILE_PROPS_CPP

#include "file_props.hpp"

#if PAX_PLATFORM == PAX_PLATFORM_WINDOWS

    #include "windows/file_props.cpp"

    #define __file_props__ windows_file_props

#else

    #error "Platform not supported or unknown"

#endif

namespace pax {

b32
file_props(File_Props* self, Arena* arena, str8 path, str8 name)
{
    return __file_props__(self, arena, path, name);
}

uptr
file_size(File_Props* self)
{
    if (self != 0)
        return self->size;

    return 0;
}

b32
file_is_dir(File_Props* self)
{
    if (self != 0)
        return self->type == FILE_TYPE_DIRECTORY;

    return 0;
}

} // namespace pax

#endif // PAX_FILE_PROPS_CPP
