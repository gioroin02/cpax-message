#ifndef PAX_STORAGE_DIR_VIEW_HPP
#define PAX_STORAGE_DIR_VIEW_HPP

#include "file_props.hpp"

namespace pax {

//
// Types
//

using Dir_View = addr;

//
// Procs
//

/* Dir_View */

Dir_View
dir_view(Arena* arena, str8 path);

b32
dir_next(Dir_View self, Arena* arena, File_Props* value);

} // namespace pax

#endif // PAX_STORAGE_DIR_VIEW_HPP
