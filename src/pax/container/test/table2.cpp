#include "../exports.hpp"

using namespace pax;

#include <stdio.h>

int
main()
{
/*
    Arena  arena = system_reserve(2 * MEMORY_KIB);
    Table2 table = table2_reserve_type<u32>(&arena, 3, 3);

    for (uptr i = 0; i < table.length; i += 1) {
        for (uptr j = 0; j < table.height; j += 1)
            table2_put_type<u32>(&table, i, j, i * table.height + j);
    }

    u32 temp = 0;

    for (uptr j = 0; j < table.height; j += 1) {
        printf("[");

        for (uptr i = 0; i < table.length; i += 1) {
            table2_get_type<u32>(&table, i, j, &temp);

            printf(" %lu", temp);
        }

        printf(" ]\n");
    }
*/
}
