#ifndef PAX_STORAGE_WINDOWS_FILE_CPP
#define PAX_STORAGE_WINDOWS_FILE_CPP

#include "file.hpp"

#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOMINMAX

#include <windows.h>

namespace pax {

struct Windows_File
{
    HANDLE handle = INVALID_HANDLE_VALUE;
};

b32
windows_file_delete(Arena* arena, str8 path, str8 name)
{
    uptr  offset = arena_offset(arena);
    buf16 buffer = buf16_reserve(arena, MEMORY_KIB);

    buf16_write_str8_tail(&buffer, path);
    buf16_write_str8_tail(&buffer, pax_str8("\\"));
    buf16_write_str8_tail(&buffer, name);

    str16 string = buf16_read_str16_head(&buffer, arena, buffer.size);

    b32 state = DeleteFileW(pax_cast(wchar_t*, string.memory));

    arena_rewind(arena, offset);

    if (state != 0) return 1;

    return 0;
}

Windows_File*
windows_file_open(Arena* arena, str8 path, str8 name, File_Perm perm)
{
    uptr offset = arena_offset(arena);
    uptr access = 0;

    switch (perm) {
        case FILE_PERM_READ:  { access = GENERIC_READ;    } break;
        case FILE_PERM_WRITE: { access = GENERIC_WRITE;   } break;
        case FILE_PERM_EXEC:  { access = GENERIC_EXECUTE; } break;

        case FILE_PERM_READ_WRITE: {
            access = GENERIC_READ | GENERIC_WRITE;
        } break;

        case FILE_PERM_READ_EXEC: {
            access = GENERIC_READ | GENERIC_EXECUTE;
        } break;

        case FILE_PERM_WRITE_EXEC: {
            access = GENERIC_WRITE | GENERIC_EXECUTE;
        } break;

        case FILE_PERM_FULL: {
            access = GENERIC_READ | GENERIC_WRITE | GENERIC_EXECUTE;
        } break;

        default: return 0;
    }

    Windows_File* result = arena_reserve_one<Windows_File>(arena);

    if (result != 0) {
        uptr  temp   = arena_offset(arena);
        buf16 buffer = buf16_reserve(arena, MEMORY_KIB);

        buf16_write_str8_tail(&buffer, path);
        buf16_write_str8_tail(&buffer, pax_str8("\\"));
        buf16_write_str8_tail(&buffer, name);

        str16 string = buf16_read_str16_head(&buffer, arena, buffer.size);

        result->handle = CreateFileW(pax_cast(wchar_t*, string.memory),
            access, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

        arena_rewind(arena, temp);

        if (result->handle != INVALID_HANDLE_VALUE)
            return result;

        arena_rewind(arena, offset);
    }

    return 0;
}

Windows_File*
windows_file_open_always(Arena* arena, str8 path, str8 name, File_Perm perm)
{
    uptr offset = arena_offset(arena);
    uptr access = 0;

    switch (perm) {
        case FILE_PERM_READ:  { access = GENERIC_READ;    } break;
        case FILE_PERM_WRITE: { access = GENERIC_WRITE;   } break;
        case FILE_PERM_EXEC:  { access = GENERIC_EXECUTE; } break;

        case FILE_PERM_READ_WRITE: {
            access = GENERIC_READ | GENERIC_WRITE;
        } break;

        case FILE_PERM_READ_EXEC: {
            access = GENERIC_READ | GENERIC_EXECUTE;
        } break;

        case FILE_PERM_WRITE_EXEC: {
            access = GENERIC_WRITE | GENERIC_EXECUTE;
        } break;

        case FILE_PERM_FULL: {
            access = GENERIC_READ | GENERIC_WRITE | GENERIC_EXECUTE;
        } break;

        default: return 0;
    }

    Windows_File* result = arena_reserve_one<Windows_File>(arena);

    if (result != 0) {
        uptr  temp   = arena_offset(arena);
        buf16 buffer = buf16_reserve(arena, MEMORY_KIB);

        buf16_write_str8_tail(&buffer, path);
        buf16_write_str8_tail(&buffer, pax_str8("\\"));
        buf16_write_str8_tail(&buffer, name);

        str16 string = buf16_read_str16_head(&buffer, arena, buffer.size);

        result->handle = CreateFileW(pax_cast(wchar_t*, string.memory),
            access, FILE_SHARE_READ, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

        arena_rewind(arena, temp);

        if (result->handle != INVALID_HANDLE_VALUE)
            return result;

        arena_rewind(arena, offset);
    }

    return 0;
}

Windows_File*
windows_file_open_new(Arena* arena, str8 path, str8 name, File_Perm perm)
{
    uptr offset = arena_offset(arena);
    uptr access = 0;

    switch (perm) {
        case FILE_PERM_READ:  { access = GENERIC_READ;    } break;
        case FILE_PERM_WRITE: { access = GENERIC_WRITE;   } break;
        case FILE_PERM_EXEC:  { access = GENERIC_EXECUTE; } break;

        case FILE_PERM_READ_WRITE: {
            access = GENERIC_READ | GENERIC_WRITE;
        } break;

        case FILE_PERM_READ_EXEC: {
            access = GENERIC_READ | GENERIC_EXECUTE;
        } break;

        case FILE_PERM_WRITE_EXEC: {
            access = GENERIC_WRITE | GENERIC_EXECUTE;
        } break;

        case FILE_PERM_FULL: {
            access = GENERIC_READ | GENERIC_WRITE | GENERIC_EXECUTE;
        } break;

        default: return 0;
    }

    Windows_File* result = arena_reserve_one<Windows_File>(arena);

    if (result != 0) {
        uptr  temp   = arena_offset(arena);
        buf16 buffer = buf16_reserve(arena, MEMORY_KIB);

        buf16_write_str8_tail(&buffer, path);
        buf16_write_str8_tail(&buffer, pax_str8("\\"));
        buf16_write_str8_tail(&buffer, name);

        str16 string = buf16_read_str16_head(&buffer, arena, buffer.size);

        result->handle = CreateFileW(pax_cast(wchar_t*, string.memory),
            access, FILE_SHARE_READ, 0, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);

        arena_rewind(arena, temp);

        if (result->handle != INVALID_HANDLE_VALUE)
            return result;

        arena_rewind(arena, offset);
    }

    return 0;
}

void
windows_file_close(Windows_File* self)
{
    if (self == 0) return;

    if (self->handle != INVALID_HANDLE_VALUE)
        CloseHandle(self->handle);

    self->handle = INVALID_HANDLE_VALUE;
}

uptr
windows_file_offset(Windows_File* self)
{
    LARGE_INTEGER value = {};

    value.QuadPart = 0;

    b32 state = SetFilePointerEx(self->handle, value,
        &value, FILE_CURRENT);

    if (state != 0)
        return pax_cast(uptr, value.QuadPart);

    return 0;
}

b32
windows_file_rewind(Windows_File* self, uptr offset)
{
    LARGE_INTEGER value = {};

    value.QuadPart = offset;

    b32 state = SetFilePointerEx(self->handle, value,
        &value, FILE_BEGIN);

    if (state != 0) return 1;

    return 0;
}

b32
windows_file_write(Windows_File* self, buf8* buffer)
{
    u8*  memory = buffer->memory + buffer->head;
    uptr length = buffer->size;

    b32 state = 0;

    if (buffer->head > buffer->tail) {
        memory = buffer->memory + buffer->head;
        length = buffer->length - buffer->head;

        state = windows_file_write_mem8(self, memory, length);

        if (state != 0) {
            buffer->size -= length;
            buffer->head  = (buffer->head + length) % buffer->length;
        } else
            return 0;

        memory = buffer->memory + buffer->head;
        length = buffer->size;
   }

    if (length != 0) {
        state = windows_file_write_mem8(self, memory, length);

        if (state != 0) {
            buffer->size = 0;
            buffer->head = 0;
            buffer->tail = 0;
        }
    }

    return state;
}

b32
windows_file_write_mem8(Windows_File* self, u8* memory, uptr length)
{
    DWORD size = 0;

    b32 state = WriteFile(self->handle, memory, length, &size, 0);

    if (state != 0 && length == size)
        return 1;

    return 0;
}

b32
windows_file_read(Windows_File* self, buf8* buffer)
{
    u8*  memory = buffer->memory + buffer->tail;
    uptr length = buffer->length - buffer->size;

    b32  state = 0;
    uptr size  = 0;

    if (buffer->head < buffer->tail) {
        memory = buffer->memory + buffer->tail;
        length = buffer->length - buffer->tail;

        state = windows_file_read_mem8(self, memory, length, &size);

        if (state != 0) {
            buffer->size += size;
            buffer->tail  = (buffer->tail + size) % buffer->length;
        } else
            return 0;

        if (size < length) return 1;

        memory = buffer->memory + buffer->tail;
        length = buffer->length - buffer->size;
    }

    if (length != 0) {
        state = windows_file_read_mem8(self, memory, length, &size);

        if (state != 0) {
            buffer->size += size;
            buffer->tail  = (buffer->tail + size) % buffer->length;
        }
    }

    return 1;
}

b32
windows_file_read_mem8(Windows_File* self, u8* memory, uptr length, uptr* size)
{
    DWORD result = 0;

    b32 state = ReadFile(self->handle, memory, length, &result, 0);

    if (state != 0 && result <= length) {
        if (size != 0)
            *size = result;

        return 1;
    }

    return 0;
}

} // namespace pax

#endif // PAX_STORAGE_WINDOWS_FILE_CPP
