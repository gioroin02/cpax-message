#ifndef PAX_STORAGE_WINDOWS_DIR_VIEW_HPP
#define PAX_STORAGE_WINDOWS_DIR_VIEW_HPP

#include "imports.hpp"

namespace pax {

//
// Types
//

struct Windows_Dir_View;

//
// Procs
//

/* Windows_Dir_View */

Windows_Dir_View*
windows_dir_view(Arena* arena, str8 path);

b32
windows_dir_next(Windows_Dir_View* self, Arena* arena, File_Props* value);

} // namespace pax

#endif // PAX_STORAGE_WINDOWS_DIR_VIEW_HPP
