#include "../exports.hpp"

using namespace pax;

#include <stdio.h>

int
main()
{
    Arena arena = system_reserve(2 * MEMORY_KIB);

    Array<u32> array = array_reserve<u32>(&arena, 5);

    for (uptr i = 0; i < array.length; i += 1)
        array_insert_tail(&array, pax_cast(u32, i));

    printf("swap = %u\n", array_swap_tail(&array, 0));
    printf("\n");

    for (uptr i = 0; i < array.size; i += 1)
        printf("%llu: %u\n", i, array_get_or(&array, i, U32_ZERO));

    printf("\n");
    printf("insert_head = %u\n", array_insert_head(&array, pax_cast(u32, 1200)));
    printf("\n");

    for (uptr i = 0; i < array.size; i += 1)
        printf("%llu: %u\n", i, array_get_or(&array, i, U32_ZERO));

    printf("\n");
    printf("pop = %u\n", array_pop(&array, 1, pax_null(u32)));
    printf("\n");

    for (uptr i = 0; i < array.size; i += 1)
        printf("%llu: %u\n", i, array_get_or(&array, i, U32_ZERO));

    printf("\n");
    printf("push = %u\n", array_push(&array, 2, pax_cast(u32, 250)));
    printf("\n");

    for (uptr i = 0; i < array.size; i += 1)
        printf("%llu: %u\n", i, array_get_or(&array, i, U32_ZERO));
}
