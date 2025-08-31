#ifndef PX_STREAM_BUFFER32_C
#define PX_STREAM_BUFFER32_C

#include "buffer32.h"

PxBuffer32
pxBuffer32Make(pxu32* memory, pxiword length)
{
    if (memory == 0 || length <= 0)
        return (PxBuffer32) {0};

    return (PxBuffer32) {
        .memory = memory,
        .length = length,
    };
}

PxBuffer32
pxBuffer32MakeFull(pxu32* memory, pxiword length)
{
    if (memory == 0 || length <= 0)
        return (PxBuffer32) {0};

    return (PxBuffer32) {
        .memory = memory,
        .length = length,
        .size   = length,
        .tail   = length,
    };
}

PxBuffer32
pxBuffer32Reserve(PxArena* arena, pxiword length)
{
    pxu32* memory =
        pxArenaReserve(arena, pxu32, length);

    return pxBuffer32Make(memory, length);
}

PxBuffer32
pxBuffer32ReserveFull(PxArena* arena, pxiword length)
{
    pxu32* memory =
        pxArenaReserve(arena, pxu32, length);

    return pxBuffer32MakeFull(memory, length);
}

PxBuffer32
pxBuffer32Copy(PxArena* arena, PxBuffer32 value)
{
    return pxBuffer32CopyAmount(arena, value, value.length);
}

PxBuffer32
pxBuffer32CopyAmount(PxArena* arena, PxBuffer32 value, pxiword length)
{
    PxBuffer32 result = pxBuffer32Reserve(arena, length);

    if (result.length <= 0) return result;

    result.size = pxMin(result.length, value.size);
    result.tail = result.size;

    for (pxiword i = 0; i < result.size; i += 1)
        result.memory[i] = value.memory[(value.head + i) % value.length];

    return result;
}

PxBuffer32
pxBuffer32CopyMemory32(PxArena* arena, pxu32* memory, pxiword length)
{
    PxBuffer32 result = pxBuffer32Reserve(arena, length);

    if (result.length <= 0) return result;

    result.size = result.length;
    result.tail = result.length;

    pxMemoryCopy(result.memory, memory, result.size, 4);

    return result;
}

void
pxBuffer32Clear(PxBuffer32* self)
{
    self->size = 0;
    self->head = 0;
    self->tail = 0;
}

void
pxBuffer32Fill(PxBuffer32* self)
{
    pxiword diff = self->length - self->size;

    self->size = self->length;
    self->tail = self->head;

    for (pxiword i = 0; i < diff; i += 1)
        self->memory[(self->head + i) % self->length] = 0;
}

void
pxBuffer32Normalize(PxBuffer32* self)
{
    pxu32*  memory = self->memory;
    pxiword length = self->tail;
    pxiword offset = self->head;

    if (self->head > self->tail) {
        memory = self->memory + self->length - self->head;
        offset = self->head - self->tail;

        pxMemoryFlip(self->memory + self->head,
            self->length - self->head, 4);

        pxMemoryFlip(self->memory, self->tail, 4);
        pxMemoryFlip(self->memory, self->length, 4);
    }

    if (offset > 0 && self->head > 0)
        pxMemoryCopyBack(memory + offset, length, offset, 4);

    self->head = 0;
    self->tail = self->size;
}

pxb8
pxBuffer32GetForw(PxBuffer32* self, pxiword index, pxu32* value)
{
    if (index < 0 || index >= self->size)
        return 0;

    index = (self->head + index) % self->length;

    if (value != 0)
        *value = self->memory[index];

    return 1;
}

pxu32
pxBuffer32GetForwOr(PxBuffer32* self, pxiword index, pxu32 value)
{
    if (index < 0 || index >= self->size)
        return value;

    index = (self->head + index) % self->length;

    return self->memory[index];
}

pxb8
pxBuffer32GetBack(PxBuffer32* self, pxiword index, pxu32* value)
{
    if (index < 0 || index >= self->size)
        return 0;

    index = (self->tail + self->length - index) % self->length;

    if (value != 0)
        *value = self->memory[index];

    return 1;
}

pxu32
pxBuffer32GetBackOr(PxBuffer32* self, pxiword index, pxu32 value)
{
    if (index < 0 || index >= self->size)
        return value;

    index = (self->tail + self->length - index) % self->length;

    return self->memory[index];
}

pxiword
pxBuffer32DropHead(PxBuffer32* self, pxiword amount)
{
    amount = pxMin(amount, self->size);

    if (amount > 0) {
        pxiword next = self->head + amount;

        self->size -= amount;
        self->head  = next % self->length;
    }

    return amount;
}

pxiword
pxBuffer32DropTail(PxBuffer32* self, pxiword amount)
{
    amount = pxMin(amount, self->size);

    if (amount > 0) {
        pxiword prev = self->tail + self->length - amount;

        self->size -= amount;
        self->tail  = prev % self->length;
    }

    return amount;
}

pxiword
pxBuffer32WriteHead(PxBuffer32* self, PxBuffer32* buffer)
{
    pxiword size = pxMin(buffer->size, self->length - self->size);

    if (size <= 0 || size > self->length) return 0;

    pxiword prev = self->head + self->length - size;

    self->size += size;
    self->head  = prev % self->length;

    for (pxiword i = 0; i < size; i += 1) {
        self->memory[(self->head + i) % self->length] =
            buffer->memory[(buffer->head + i) % buffer->length];
    }

    buffer->size -= size;
    buffer->head = (buffer->head + size) % buffer->length;

    return size;
}

pxiword
pxBuffer32WriteMemory32Head(PxBuffer32* self, pxu32* memory, pxiword length)
{
    pxiword size = pxMin(length, self->length - self->size);

    if (size <= 0 || size > self->length) return 0;

    pxiword prev = self->head + self->length - size;

    self->size += size;
    self->head  = prev % self->length;

    for (pxiword i = 0; i < size; i += 1)
        self->memory[(self->head + i) % self->length] = memory[i];

    return size;
}

pxiword
pxBuffer32WriteString32Head(PxBuffer32* self, PxString32 string)
{
    return pxBuffer32WriteMemory32Head(self, string.memory, string.length);
}

pxiword
pxBuffer32WriteTail(PxBuffer32* self, PxBuffer32* buffer)
{
    pxiword size = pxMin(buffer->size, self->length - self->size);

    if (size <= 0 || size > self->length) return 0;

    pxiword next = self->tail + size;

    for (pxiword i = 0; i < size; i += 1) {
        self->memory[(self->tail + i) % self->length] =
            buffer->memory[(buffer->head + i) % buffer->length];
    }

    self->size += size;
    self->tail  = next % self->length;

    buffer->size -= size;
    buffer->head  = (buffer->head + size) % buffer->length;

    return size;
}

pxiword
pxBuffer32WriteMemory32Tail(PxBuffer32* self, pxu32* memory, pxiword length)
{
    pxiword size = pxMin(length, self->length - self->size);

    if (size <= 0 || size > self->length) return 0;

    pxiword next = self->tail + size;

    for (pxiword i = 0; i < size; i += 1)
        self->memory[(self->tail + i) % self->length] = memory[i];

    self->size += size;
    self->tail  = next % self->length;

    return size;
}

pxiword
pxBuffer32WriteString32Tail(PxBuffer32* self, PxString32 string)
{
    return pxBuffer32WriteMemory32Tail(self, string.memory, string.length);
}

pxiword
pxBuffer32ReadHead(PxBuffer32* self, PxBuffer32* buffer)
{
    pxiword size = pxMin(self->size, buffer->length - buffer->size);

    if (size <= 0 || size > self->size) return 0;

    pxiword next = self->head + size;

    for (pxiword i = 0; i < size; i += 1) {
        buffer->memory[(buffer->tail + i) % buffer->length] =
            self->memory[(self->head + i) % self->length];
    }

    self->size -= size;
    self->head  = next % self->length;

    buffer->size += size;
    buffer->tail  = (buffer->tail + size) % buffer->length;

    return size;
}

pxiword
pxBuffer32ReadMemory32Head(PxBuffer32* self, pxu32* memory, pxiword length)
{
    pxiword size = pxMin(self->size, length);

    if (size <= 0 || size > self->size) return 0;

    pxiword next = self->head + size;

    for (pxiword i = 0; i < size; i += 1)
        memory[i] = self->memory[(self->head + i) % self->length];

    self->size -= size;
    self->head  = next % self->length;

    return size;
}

PxString32
pxBuffer32ReadString32Head(PxBuffer32* self, PxArena* arena, pxiword length)
{
    pxiword size = pxMin(self->size, length);

    if (size <= 0 || size > self->size) return (PxString32) {0};

    pxu32* result = pxArenaReserve(arena, pxu32, size + 1);

    if (result != 0) {
        pxBuffer32ReadMemory32Head(self, result, size);

        return (PxString32) {
            .memory = result,
            .length = size,
        };
    }

    return (PxString32) {0};
}

pxiword
pxBuffer32ReadTail(PxBuffer32* self, PxBuffer32* buffer)
{
    pxiword size = pxMin(self->size, buffer->length - buffer->size);

    if (size <= 0 || size > self->size) return 0;

    pxiword prev = self->tail + self->length - size;

    self->size -= size;
    self->tail  = prev % self->length;

    for (pxiword i = 0; i < size; i += 1) {
        buffer->memory[(buffer->tail + i) % buffer->length] =
            self->memory[(self->tail + i) % self->length];
    }

    buffer->size += size;
    buffer->tail  = (buffer->tail + size) % buffer->length;

    return size;
}

pxiword
pxBuffer32ReadMemory32Tail(PxBuffer32* self, pxu32* memory, pxiword length)
{
    pxiword size = pxMin(self->size, length);

    if (size <= 0 || size > self->size) return 0;

    pxiword prev = self->tail + self->length - size;

    self->size -= size;
    self->tail  = prev % self->length;

    for (pxiword i = 0; i < size; i += 1)
        memory[i] = self->memory[(self->tail + i) % self->length];

    return size;
}

PxString32
pxBuffer32ReadString32Tail(PxBuffer32* self, PxArena* arena, pxiword length)
{
    pxiword size = pxMin(self->size, length);

    if (size <= 0 || size > self->size) return (PxString32) {0};

    pxu32* result = pxArenaReserve(arena, pxu32, size + 1);

    if (result != 0) {
        pxBuffer32ReadMemory32Tail(self, result, size);

        return (PxString32) {
            .memory = result,
            .length = size,
        };
    }

    return (PxString32) {0};
}

pxiword
pxBuffer32PeekHead(PxBuffer32* self, PxBuffer32* buffer)
{
    pxiword size = pxMin(self->size, buffer->length - buffer->size);

    if (size <= 0 || size > self->size) return 0;

    for (pxiword i = 0; i < size; i += 1) {
        buffer->memory[(buffer->tail + i) % buffer->length] =
            self->memory[(self->head + i) % self->length];
    }

    buffer->size += size;
    buffer->tail  = (buffer->tail + size) % buffer->length;

    return size;
}

pxiword
pxBuffer32PeekMemory32Head(PxBuffer32* self, pxu32* memory, pxiword length)
{
    pxiword size = pxMin(self->size, length);

    if (size <= 0 || size > self->size) return 0;

    for (pxiword i = 0; i < size; i += 1)
        memory[i] = self->memory[(self->head + i) % self->length];

    return size;
}

PxString32
pxBuffer32PeekString32Head(PxBuffer32* self, PxArena* arena, pxiword length)
{
    pxiword size = pxMin(self->size, length);

    if (size <= 0 || size > self->size) return (PxString32) {0};

    pxu32* result = pxArenaReserve(arena, pxu32, size + 1);

    if (result != 0) {
        pxBuffer32PeekMemory32Head(self, result, size);

        return (PxString32) {
            .memory = result,
            .length = size,
        };
    }

    return (PxString32) {0};
}

pxiword
pxBuffer32PeekTail(PxBuffer32* self, PxBuffer32* buffer)
{
    pxiword size = pxMin(self->size, buffer->length - buffer->size);

    if (size <= 0 || size > self->size) return 0;

    pxiword prev = self->tail + self->length - size;
    pxiword tail = prev % self->length;

    for (pxiword i = 0; i < size; i += 1) {
        buffer->memory[(buffer->tail + i) % buffer->length] =
            self->memory[(tail + i) % self->length];
    }

    buffer->size += size;
    buffer->tail  = (buffer->tail + size) % buffer->length;

    return size;
}

pxiword
pxBuffer32PeekMemory32Tail(PxBuffer32* self, pxu32* memory, pxiword length)
{
    pxiword size = pxMin(self->size, length);

    if (size <= 0 || size > self->size) return 0;

    pxiword prev = self->tail + self->length - size;
    pxiword tail = prev % self->length;

    for (pxiword i = 0; i < size; i += 1)
        memory[i] = self->memory[(tail + i) % self->length];

    return size;
}

PxString32
pxBuffer32PeekString32Tail(PxBuffer32* self, PxArena* arena, pxiword length)
{
    pxiword size = pxMin(self->size, length);

    if (size <= 0 || size > self->size) return (PxString32) {0};

    pxu32* result = pxArenaReserve(arena, pxu32, size + 1);

    if (result != 0) {
        pxBuffer32PeekMemory32Tail(self, result, size);

        return (PxString32) {
            .memory = result,
            .length = size,
        };
    }

    return (PxString32) {0};
}

#endif // PX_STREAM_BUFFER32_C
