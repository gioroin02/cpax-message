#ifndef PAX_STORAGE_WINDOWS_FILE_HPP
#define PAX_STORAGE_WINDOWS_FILE_HPP

#include "imports.hpp"

namespace pax {

//
// Types
//

struct Windows_File;

//
// Procs
//

/* Windows_File */

b32
windows_file_delete(Arena* arena, str8 path, str8 name);

Windows_File*
windows_file_open(Arena* arena, str8 path, str8 name, File_Perm perm);

Windows_File*
windows_file_open_always(Arena* arena, str8 path, str8 name, File_Perm perm);

Windows_File*
windows_file_open_new(Arena* arena, str8 path, str8 name, File_Perm perm);

void
windows_file_close(Windows_File* self);

uptr
windows_file_offset(Windows_File* self);

b32
windows_file_rewind(Windows_File* self, uptr offset);

b32
windows_file_write(Windows_File* self, buf8* buffer);

b32
windows_file_write_mem8(Windows_File* self, u8* memory, uptr length);

b32
windows_file_read(Windows_File* self, buf8* buffer);

b32
windows_file_read_mem8(Windows_File* self, u8* memory, uptr length, uptr* size);

} // namespace pax

#endif // PAX_STORAGE_WINDOWS_FILE_HPP
