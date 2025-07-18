#include "../exports.hpp"

using namespace pax;

#include <stdio.h>

static u8 memory[MEMORY_KIB] = {};

int
main()
{
    Arena arena = pax_arena(memory);

    buf8 buffer = buf8_reserve(&arena, 4);

    buffer.head = 2;
    buffer.tail = 2;

    buf8_write_codepoint_tail(&buffer, 0x1f600);

    printf("%.*s\n", pax_cast(int, buffer.size),
        buffer.memory);

    u32 value = 0;

    buf8_read_codepoint_head(&buffer, &value);

    printf("%x\n", value);
}
