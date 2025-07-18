#include "../exports.hpp"

using namespace pax;

#include <stdio.h>

#define RED(str) "\x1b[31m" str "\x1b[0m"
#define GRN(str) "\x1b[32m" str "\x1b[0m"
#define YLW(str) "\x1b[33m" str "\x1b[0m"
#define BLU(str) "\x1b[34m" str "\x1b[0m"
#define PRP(str) "\x1b[35m" str "\x1b[0m"
#define AZR(str) "\x1b[36m" str "\x1b[0m"

int
main(int argc, const char* argv[])
{
    u8 memory[8 * MEMORY_KIB] = {};

    Arena arena = arena_make(memory, pax_array_length(memory));

    if (argc != 2) return 1;

    str8 path = str8_count_max(pax_cast(u8*, argv[1]), 128);

    File_Props props  = {};
    Dir_View   dir    = dir_view(&arena, path);

    uptr offset = arena_offset(&arena);

    while (dir_next(dir, &arena, &props) != 0) {
        str8 type = pax_str8(RED("E"));

        switch (props.type) {
            case FILE_TYPE_NORMAL:    { type = pax_str8(GRN("F")); } break;
            case FILE_TYPE_DIRECTORY: { type = pax_str8(BLU("D")); } break;

            default: break;
        }

        str8 perm = pax_str8(RED("E"));

        switch (props.perm) {
            case FILE_PERM_READ:       { perm = pax_str8(GRN("R") "__"); } break;
            case FILE_PERM_WRITE:      { perm = pax_str8("_" BLU("W") "_"); } break;
            case FILE_PERM_READ_WRITE: { perm = pax_str8(GRN("RW") "_"); } break;
            case FILE_PERM_EXEC:       { perm = pax_str8("__" GRN("E")); } break;
            case FILE_PERM_READ_EXEC:  { perm = pax_str8(GRN("R") "_" GRN("E")); } break;
            case FILE_PERM_WRITE_EXEC: { perm = pax_str8("_" GRN("RE")); } break;
            case FILE_PERM_FULL:       { perm = pax_str8(GRN("RWE")); } break;

            default: break;
        }

        printf("{ ");
        printf("path: " PRP("'%.*s'") ", ", pax_cast(int, props.path.length), props.path.memory);
        printf("name: " PRP("'%32.*s'") ", ", pax_cast(int, props.name.length), props.name.memory);
        printf("type: %s, ", type.memory);
        printf("perm: %s, ", perm.memory);
        printf("size: " YLW("%llu") " ", props.size);
        printf("}\n");

        arena_rewind(&arena, offset);
    }
}
