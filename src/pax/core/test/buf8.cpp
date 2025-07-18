#include "../exports.hpp"

using namespace pax;

#include <stdio.h>

void
show_buf8(buf8* self)
{
    if (self->size == 0) return;

    for (uptr i = 0; i < self->length; i += 1) {
        b32 line = (self->head <= self->tail) &&
            (self->head <= i && i < self->tail);

        b32 circ = (self->head >= self->tail) &&
            (self->head <= i || i < self->tail);

        if (line != 0 || circ != 0)
            printf("[%c]", self->memory[i]);
        else
            printf("[_]");
    }

    printf("\n");

    for (uptr i = 0; i < self->size; i += 1) {
        uptr idx = (self->head + i) % self->length;
        u8   chr = self->memory[idx];

        printf("%llu. %c\n", idx, chr);
    }
}

int
main(int argc, const char* argv[])
{
    u8 memory[MEMORY_KIB] = {};

    Arena arena = pax_arena(memory);

    buf8 buffer = buf8_reserve(&arena, 10);

    buf8_write_mem8_tail(&buffer, pax_cast(u8*, "coda"), 4);
    buf8_write_mem8_head(&buffer, pax_cast(u8*, "testa"), 5);

    u8 temp[3] = {};

    buf8_read_mem8_head(&buffer, temp, pax_array_bytes(temp));

    printf("temp:\n");

    for (uptr i = 0; i < pax_array_bytes(temp); i += 1)
        printf("%llu. %c\n", i, temp[i]);

    printf("buffer:\n");
    show_buf8(&buffer);

    buf8 copy = buf8_reserve(&arena, 16);

    buf8_write_tail(&copy, &buffer);
    buf8_normalize(&buffer);

    printf("buffer:\n");
    show_buf8(&buffer);

    printf("copy:\n");
    show_buf8(&copy);
}
