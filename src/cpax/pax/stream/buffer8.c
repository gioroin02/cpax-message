#ifndef PX_STREAM_BUFFER8_C
#define PX_STREAM_BUFFER8_C

#include "buffer8.h"

PxBuffer8
pxBuffer8Make(pxu8* memory, pxiword length)
{
    if (memory == 0 || length <= 0)
        return (PxBuffer8) {0};

    return (PxBuffer8) {
        .memory = memory,
        .length = length,
    };
}

PxBuffer8
pxBuffer8MakeFull(pxu8* memory, pxiword length)
{
    if (memory == 0 || length <= 0)
        return (PxBuffer8) {0};

    return (PxBuffer8) {
        .memory = memory,
        .length = length,
        .size   = length,
        .tail   = length,
    };
}

PxBuffer8
pxBuffer8Reserve(PxArena* arena, pxiword length)
{
    pxu8* memory =
        pxArenaReserve(arena, pxu8, length);

    return pxBuffer8Make(memory, length);
}

PxBuffer8
pxBuffer8ReserveFull(PxArena* arena, pxiword length)
{
    pxu8* memory =
        pxArenaReserve(arena, pxu8, length);

    return pxBuffer8MakeFull(memory, length);
}

PxBuffer8
pxBuffer8Copy(PxArena* arena, PxBuffer8 value)
{
    return pxBuffer8CopyAmount(arena, value, value.length);
}

PxBuffer8
pxBuffer8CopyAmount(PxArena* arena, PxBuffer8 value, pxiword length)
{
    PxBuffer8 result = pxBuffer8Reserve(arena, length);

    if (result.length <= 0) return result;

    result.size = pxMin(result.length, value.size);
    result.tail = result.size;

    for (pxiword i = 0; i < result.size; i += 1)
        result.memory[i] = value.memory[(value.head + i) % value.length];

    return result;
}

PxBuffer8
pxBuffer8CopyMemory8(PxArena* arena, pxu8* memory, pxiword length)
{
    PxBuffer8 result = pxBuffer8Reserve(arena, length);

    if (result.length <= 0) return result;

    result.size = result.length;
    result.tail = result.length;

    pxMemoryCopy(result.memory, memory, result.size, 1);

    return result;
}

void
pxBuffer8Clear(PxBuffer8* self)
{
    self->size = 0;
    self->head = 0;
    self->tail = 0;
}

void
pxBuffer8Fill(PxBuffer8* self)
{
    pxiword diff = self->length - self->size;

    self->size = self->length;
    self->tail = self->head;

    for (pxiword i = 0; i < diff; i += 1)
        self->memory[(self->head + i) % self->length] = 0;
}

void
pxBuffer8Normalize(PxBuffer8* self)
{
    pxu8*   memory = self->memory;
    pxiword length = self->tail;
    pxiword offset = self->head;

    if (self->head > self->tail) {
        memory = self->memory + self->length - self->head;
        offset = self->head - self->tail;

        pxMemoryFlip(self->memory + self->head,
            self->length - self->head, 1);

        pxMemoryFlip(self->memory, self->tail, 1);
        pxMemoryFlip(self->memory, self->length, 1);
    }

    if (offset > 0 && self->head > 0)
        pxMemoryCopyBack(memory + offset, length, offset, 1);

    self->head = 0;
    self->tail = self->size;
}

pxb8
pxBuffer8GetForw(PxBuffer8* self, pxiword index, pxu8* value)
{
    if (index < 0 || index >= self->size)
        return 0;

    index = (self->head + index) % self->length;

    if (value != 0)
        *value = self->memory[index];

    return 1;
}

pxu8
pxBuffer8GetForwOr(PxBuffer8* self, pxiword index, pxu8 value)
{
    if (index < 0 || index >= self->size)
        return value;

    index = (self->head + index) % self->length;

    return self->memory[index];
}

pxb8
pxBuffer8GetBack(PxBuffer8* self, pxiword index, pxu8* value)
{
    if (index < 0 || index >= self->size)
        return 0;

    index = (self->tail + self->length - index) % self->length;

    if (value != 0)
        *value = self->memory[index];

    return 1;
}

pxu8
pxBuffer8GetBackOr(PxBuffer8* self, pxiword index, pxu8 value)
{
    if (index < 0 || index >= self->size)
        return value;

    index = (self->tail + self->length - index) % self->length;

    return self->memory[index];
}

pxiword
pxBuffer8DropHead(PxBuffer8* self, pxiword amount)
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
pxBuffer8DropTail(PxBuffer8* self, pxiword amount)
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
pxBuffer8WriteHead(PxBuffer8* self, PxBuffer8* buffer)
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
pxBuffer8WriteMemory8Head(PxBuffer8* self, pxu8* memory, pxiword length)
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
pxBuffer8WriteString8Head(PxBuffer8* self, PxString8 string)
{
    return pxBuffer8WriteMemory8Head(self, string.memory, string.length);
}

pxiword
pxBuffer8WriteTail(PxBuffer8* self, PxBuffer8* buffer)
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
pxBuffer8WriteMemory8Tail(PxBuffer8* self, pxu8* memory, pxiword length)
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
pxBuffer8WriteString8Tail(PxBuffer8* self, PxString8 string)
{
    return pxBuffer8WriteMemory8Tail(self, string.memory, string.length);
}

pxiword
pxBuffer8ReadHead(PxBuffer8* self, PxBuffer8* buffer)
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
pxBuffer8ReadMemory8Head(PxBuffer8* self, pxu8* memory, pxiword length)
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

PxString8
pxBuffer8ReadString8Head(PxBuffer8* self, PxArena* arena, pxiword length)
{
    pxiword size = pxMin(self->size, length);

    if (size <= 0 || size > self->size) return (PxString8) {0};

    pxu8* result = pxArenaReserve(arena, pxu8, size + 1);

    if (result != 0) {
        pxBuffer8ReadMemory8Head(self, result, size);

        return (PxString8) {
            .memory = result,
            .length = size,
        };
    }

    return (PxString8) {0};
}

pxiword
pxBuffer8ReadTail(PxBuffer8* self, PxBuffer8* buffer)
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
pxBuffer8ReadMemory8Tail(PxBuffer8* self, pxu8* memory, pxiword length)
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

PxString8
pxBuffer8ReadString8Tail(PxBuffer8* self, PxArena* arena, pxiword length)
{
    pxiword size = pxMin(self->size, length);

    if (size <= 0 || size > self->size) return (PxString8) {0};

    pxu8* result = pxArenaReserve(arena, pxu8, size + 1);

    if (result != 0) {
        pxBuffer8ReadMemory8Tail(self, result, size);

        return (PxString8) {
            .memory = result,
            .length = size,
        };
    }

    return (PxString8) {0};
}

pxiword
pxBuffer8PeekHead(PxBuffer8* self, PxBuffer8* buffer)
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
pxBuffer8PeekMemory8Head(PxBuffer8* self, pxu8* memory, pxiword length)
{
    pxiword size = pxMin(self->size, length);

    if (size <= 0 || size > self->size) return 0;

    for (pxiword i = 0; i < size; i += 1)
        memory[i] = self->memory[(self->head + i) % self->length];

    return size;
}

PxString8
pxBuffer8PeekString8Head(PxBuffer8* self, PxArena* arena, pxiword length)
{
    pxiword size = pxMin(self->size, length);

    if (size <= 0 || size > self->size) return (PxString8) {0};

    pxu8* result = pxArenaReserve(arena, pxu8, size + 1);

    if (result != 0) {
        pxBuffer8PeekMemory8Head(self, result, size);

        return (PxString8) {
            .memory = result,
            .length = size,
        };
    }

    return (PxString8) {0};
}

pxiword
pxBuffer8PeekTail(PxBuffer8* self, PxBuffer8* buffer)
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
pxBuffer8PeekMemory8Tail(PxBuffer8* self, pxu8* memory, pxiword length)
{
    pxiword size = pxMin(self->size, length);

    if (size <= 0 || size > self->size) return 0;

    pxiword prev = self->tail + self->length - size;
    pxiword tail = prev % self->length;

    for (pxiword i = 0; i < size; i += 1)
        memory[i] = self->memory[(tail + i) % self->length];

    return size;
}

PxString8
pxBuffer8PeekString8Tail(PxBuffer8* self, PxArena* arena, pxiword length)
{
    pxiword size = pxMin(self->size, length);

    if (size <= 0 || size > self->size) return (PxString8) {0};

    pxu8* result = pxArenaReserve(arena, pxu8, size + 1);

    if (result != 0) {
        pxBuffer8PeekMemory8Tail(self, result, size);

        return (PxString8) {
            .memory = result,
            .length = size,
        };
    }

    return (PxString8) {0};
}

#endif // PX_STREAM_BUFFER8_C
