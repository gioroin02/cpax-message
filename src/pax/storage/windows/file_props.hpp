#ifndef PAX_STORAGE_WINDOWS_FILE_PROPS_HPP
#define PAX_STORAGE_WINDOWS_FILE_PROPS_HPP

#include "imports.hpp"

namespace pax {

//
// Procs
//

/* File_Props */

b32
windows_file_props(File_Props* self, Arena* arena, str8 path, str8 name);

} // namespace pax

#endif // PAX_STORAGE_WINDOWS_FILE_PROPS_HPP
