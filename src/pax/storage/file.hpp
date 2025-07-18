#ifndef PAX_STORAGE_FILE_HPP
#define PAX_STORAGE_FILE_HPP

#include "file_props.hpp"

namespace pax {

//
// Types
//

using File = addr;

//
// Procs
//

/* File */

b32
file_delete(Arena* arena, str8 path, str8 name);

File
file_open(Arena* arena, str8 path, str8 name, File_Perm perm);

File
file_open_always(Arena* arena, str8 path, str8 name, File_Perm perm);

File
file_open_new(Arena* arena, str8 path, str8 name, File_Perm perm);

void
file_close(File self);

uptr
file_offset(File self);

b32
file_rewind(File self, uptr offset);

b32
file_write(File self, buf8* buffer);

b32
file_write_mem8(File self, u8* memory, uptr length);

b32
file_read(File self, buf8* buffer);

b32
file_read_mem8(File self, u8* memory, uptr length, uptr* size);

} // namespace pax

#endif // PAX_STORAGE_FILE_HPP
