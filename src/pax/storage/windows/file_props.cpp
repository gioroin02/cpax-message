#ifndef PAX_STORAGE_WINDOWS_FILE_PROPS_CPP
#define PAX_STORAGE_WINDOWS_FILE_PROPS_CPP

#include "file_props.hpp"

#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOMINMAX

#include <windows.h>

namespace pax {

b32
windows_file_props(File_Props* self, Arena* arena, str8 path, str8 name)
{
    uptr  offset = arena_offset(arena);
    buf16 buffer = buf16_reserve(arena, MEMORY_KIB);

    buf16_write_str8_tail(&buffer, path);
    buf16_write_str8_tail(&buffer, pax_str8("\\"));
    buf16_write_str8_tail(&buffer, name);

    str16 string = buf16_read_str16_head(&buffer, arena, buffer.size);

    wchar_t* memory = pax_cast(wchar_t*, string.memory);

    WIN32_FIND_DATAW data   = {};
    HANDLE           handle = FindFirstFileW(memory, &data);

    arena_rewind(arena, offset);

    if (handle == INVALID_HANDLE_VALUE) return 0;

    self->path = str8_copy(arena, path);
    self->name = str8_copy(arena, name);

    self->type = FILE_TYPE_NORMAL;
    self->perm = FILE_PERM_READ_WRITE;

    if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
        self->type = FILE_TYPE_DIRECTORY;

    if (self->type != FILE_TYPE_DIRECTORY) {
        self->size  = data.nFileSizeLow;
        self->size += data.nFileSizeHigh * (MAXWORD + 1);

        if ((data.dwFileAttributes & FILE_ATTRIBUTE_READONLY) != 0)
            self->perm = FILE_PERM_READ;
    }

    FindClose(handle);

    return 1;
}

} // namespace pax

#endif // PAX_STORAGE_WINDOWS_FILE_PROPS_CPP
