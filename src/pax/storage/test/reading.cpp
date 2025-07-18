#include "../exports.hpp"

using namespace pax;

#include <stdio.h>

int
main(int argc, const char* argv[])
{
    u8 memory[8 * MEMORY_KIB] = {};

    Arena arena = arena_make(memory, pax_array_length(memory));

    buf8 reading = buf8_reserve(&arena, 4 * MEMORY_KIB);

    if (argc != 2) return 1;

    str8 name = str8_count_max(pax_cast(u8*, argv[1]), 128);
    File file = file_open(&arena, pax_str8("."), name, FILE_PERM_READ);

    if (file == 0) return 1;

    file_read(file, &reading);

    char* ptr = pax_cast(char*, reading.memory);
    int   len = pax_cast(int, reading.size);

    printf("\x1b[32m%.*s\x1b[0m (%llu)\n", len, ptr,
        file_offset(file));

    file_rewind(file, 0);

    buf8_clear(&reading);

    file_read(file, &reading);

    ptr = pax_cast(char*, reading.memory);
    len = pax_cast(int, reading.size);

    printf("\x1b[34m%.*s\x1b[0m (%llu)\n", len, ptr,
        file_offset(file));

    file_close(file);
}
