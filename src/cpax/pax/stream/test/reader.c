#include "../export.h"

#include <stdio.h>

void
readBytePerByte(PxReader* reader)
{
    pxu8 byte = pxReaderPeek(reader, 0);

    while (byte != 0) {
        printf("%3u", byte);

        if (pxUnicodeIsAscii(byte) != 0)
            printf(" (%c)", byte);

        printf("\n");

        byte = pxReaderDrop(reader, 1);
    }
}

int
main(int argc, char** argv)
{
    pxu8 memory[PX_MEMORY_KIB] = {0};

    PxArena arena = pxArenaMake(memory, pxSize(memory));

    PxBuffer8 source = pxBuffer8Reserve(&arena, 256);
    PxBuffer8 buffer = pxBuffer8Reserve(&arena, 256);

    PxReader reader = pxBufferReader(&source, &buffer);

    pxBuffer8WriteStringTail(&source, pxs8("ciao\narrivederci"));

    readBytePerByte(&reader);

    pxBuffer8WriteStringTail(&source, pxs8("ciao\narrivederci"));

    PxString8 line = pxReaderLine(&reader, &arena, 16);

    printf("%.*s\n", pxCast(int, line.length),
        line.memory);
}
