#include "../export.h"

#include <stdio.h>

void
showBuffer8(PxBuffer8* self)
{
    if (self->size <= 0) return;

    for (pxiword i = 0; i < self->length; i += 1) {
        pxb8 line = (self->head <= self->tail) &&
            (self->head <= i && i < self->tail);

        pxb8 circ = (self->head >= self->tail) &&
            (self->head <= i || i < self->tail);

        if (line != 0 || circ != 0)
            printf("[%c]", self->memory[i]);
        else
            printf("[_]");
    }

    printf("\n");

    for (pxiword i = 0; i < self->size; i += 1) {
        pxiword idx = (self->head + i) % self->length;
        pxu8    chr = self->memory[idx];

        printf("%lli. %c\n", idx, chr);
    }
}

static pxu8 memory[PX_MEMORY_KIB] = {};

int
main(int argc, char** argv)
{
    PxArena   arena  = pxArenaMake(memory, PX_MEMORY_KIB);
    PxBuffer8 buffer = pxBuffer8Reserve(&arena, 10);

    pxBuffer8WriteMemory8Tail(&buffer, pxCast(pxu8*, "coda"), 4);
    pxBuffer8WriteMemory8Head(&buffer, pxCast(pxu8*, "testa"), 5);

    #define TEMP 3

    pxu8 temp[TEMP] = {};

    pxBuffer8ReadMemory8Head(&buffer, temp, TEMP);

    printf("temp:\n");

    for (pxiword i = 0; i < TEMP; i += 1)
        printf("%lli. %c\n", i, temp[i]);

    printf("buffer:\n");

    showBuffer8(&buffer);

    PxBuffer8 copy = pxBuffer8Reserve(&arena, 16);

    pxBuffer8WriteTail(&copy, &buffer);
    pxBuffer8Normalize(&buffer);

    printf("buffer:\n");

    showBuffer8(&buffer);

    printf("copy:\n");

    showBuffer8(&copy);
}
