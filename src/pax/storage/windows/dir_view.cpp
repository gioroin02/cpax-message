#ifndef PAX_STORAGE_WINDOWS_DIR_VIEW_CPP
#define PAX_STORAGE_WINDOWS_DIR_VIEW_CPP

#include "dir_view.hpp"

#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOMINMAX

#include <windows.h>

namespace pax {

struct Windows_Dir_View
{
    HANDLE handle = INVALID_HANDLE_VALUE;
    str8   name   = {};

    WIN32_FIND_DATAW data = {};
};

Windows_Dir_View*
windows_dir_view(Arena* arena, str8 path)
{
    uptr offset = arena_offset(arena);

    Windows_Dir_View* result = arena_reserve_one<Windows_Dir_View>(arena);

    if (result != 0) {
        uptr  temp   = arena_offset(arena);
        buf16 buffer = buf16_reserve(arena, MEMORY_KIB);

        buf16_write_str8_tail(&buffer, path);
        buf16_write_str8_tail(&buffer, pax_str8("\\*.*"));

        str16 string = buf16_read_str16_head(&buffer, arena, buffer.size);

        wchar_t* memory = pax_cast(wchar_t*, string.memory);

        result->name   = str8_copy(arena, path);
        result->handle = FindFirstFileW(memory, &result->data);

        arena_rewind(arena, temp);

        if (result->handle != INVALID_HANDLE_VALUE)
            return result;
    }

    arena_rewind(arena, offset);

    return 0;
}

b32
windows_dir_next(Windows_Dir_View* self, Arena* arena, File_Props* value)
{
    if (self == 0 || self->handle == INVALID_HANDLE_VALUE)
        return 0;

    if (value != 0) {
        u16*  memory = pax_cast(u16*, self->data.cFileName);
        str16 string = str16_count(memory);

        value->path = str8_copy(arena, self->name);
        value->name = str8_from_str16(arena, string);

        value->type = FILE_TYPE_NORMAL;
        value->perm = FILE_PERM_READ_WRITE;

        if ((self->data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
            value->type = FILE_TYPE_DIRECTORY;

        if (value->type != FILE_TYPE_DIRECTORY) {
            value->size  = self->data.nFileSizeLow;
            value->size += self->data.nFileSizeHigh * (MAXWORD + 1);

            if ((self->data.dwFileAttributes & FILE_ATTRIBUTE_READONLY) != 0)
                value->perm = FILE_PERM_READ;
        }
    }

    if (FindNextFileW(self->handle, &self->data) != 0) return 1;

    FindClose(self->handle);

    self->name   = {};
    self->data   = {};
    self->handle = INVALID_HANDLE_VALUE;

    return 0;
}

} // namespace pax

#endif // PAX_STORAGE_WINDOWS_DIR_VIEW_CPP
