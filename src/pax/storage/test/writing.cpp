#include "../exports.hpp"

using namespace pax;

#include <stdio.h>

int
main(int argc, const char* argv[])
{
    u8 memory[8 * MEMORY_KIB] = {};

    Arena arena = arena_make(memory, pax_array_length(memory));

    buf8 writing = buf8_reserve(&arena, 2 * MEMORY_KIB);
    buf8 reading = buf8_reserve(&arena, 2 * MEMORY_KIB);

    if (argc != 2) return 1;

    str8 content = str8_count_max(pax_cast(u8*, argv[1]), 2 * MEMORY_KIB);
    File file    = file_open_new(&arena, pax_str8("."), pax_str8(".temp.txt"), FILE_PERM_READ_WRITE);

    if (file == 0) return 1;

    buf8_write_str8_tail(&writing, content);

    file_write(file, &writing);
    file_rewind(file, 0);
    file_read(file, &reading);

    char* ptr = pax_cast(char*, reading.memory);
    int   len = pax_cast(int, reading.size);

    printf("\x1b[34m%.*s\x1b[0m (%llu)\n", len, ptr,
        file_offset(file));

    getchar();

    file_close(file);

    file_delete(&arena, pax_str8("."), pax_str8(".temp.txt"));
}
