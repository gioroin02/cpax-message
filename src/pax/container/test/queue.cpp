#include "../exports.hpp"

using namespace pax;

#include <stdio.h>

int
main()
{
    Arena arena = system_reserve(2 * MEMORY_KIB);

    Queue<u32> queue = queue_reserve<u32>(&arena, 10);

    for (uptr i = 0; i < queue.length; i += 1)
        queue_insert_tail(&queue, pax_cast(u32, i));

    for (uptr i = 0; i < queue.length / 2; i += 1)
        queue_remove_head(&queue, pax_null(u32));

    for (uptr i = 0; i < queue.length / 2; i += 1)
        queue_insert_tail(&queue, pax_cast(u32, i));

    u32 temp = 0;

    printf("head = %llu, tail = %llu\n", queue.head, queue.tail);

    for (uptr i = 0; i < queue.size; i += 1)
        printf("%llu: %u\n", i, queue_get_or(&queue, i, U32_MAX));

    Queue copy = queue_copy(&arena, &queue);

    printf("head = %llu, tail = %llu\n", copy.head, copy.tail);

    for (uptr i = 0; i < copy.size; i += 1)
        printf("%llu: %u\n", i, queue_get_or(&queue, i, U32_MAX));

    queue = queue_copy(&arena, &copy);

    printf("head = %llu, tail = %llu\n", queue.head, queue.tail);

    for (uptr i = 0; i < queue.size; i += 1)
        printf("%llu: %u\n", i, queue_get_or(&queue, i, U32_MAX));
}
