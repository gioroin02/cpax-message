#include "../exports.hpp"

using namespace pax;

#include <stdio.h>

uptr
u32_hash(u32 key)
{
    return key;
}

int
main()
{
    Arena arena = system_reserve(2 * MEMORY_KIB);

    Hash_Map<u32, u32> map = hash_map_reserve<u32, u32>(&arena, 22, &u32_hash);

    printf("insert = %u\n", hash_map_insert(&map, pax_cast(u32,       5), pax_cast(u32,        16)));
    printf("insert = %u\n", hash_map_insert(&map, pax_cast(u32,    3453), pax_cast(u32,        1)));
    printf("insert = %u\n", hash_map_insert(&map, pax_cast(u32, 3453453), pax_cast(u32, 13453453)));

    printf("get    = %u\n", hash_map_get_or(&map, pax_cast(u32, 5), U32_MAX));

    printf("Map {\n");

    for (uptr i = 0; i < map.outer.length; i += 1) {
        uptr outer = table_get_or(&map.outer, i, UPTR_MAX);

        printf("    [%3llu] ", outer);

        if (i < map.inner.size) {
            uptr inner = array_get_or(&map.inner, i, UPTR_MAX);
            u32  key   = array_get_or(&map.key, i, U32_MAX);
            u32  value = array_get_or(&map.value, i, U32_MAX);

            printf("[%3llu] %u => %u", inner, key, value);
        } else
            printf("[  0]");

        printf("\n");
    }

    printf("}\n");

    u32 updated = 0;
    u32 removed = 0;

    hash_map_update(&map, pax_cast(u32,    5), U32_MAX, &updated);
    hash_map_remove(&map, pax_cast(u32, 3453),          &removed);

    printf("updated = %u, removed = %u\n", updated, removed);

    printf("\n");
    printf("Map {\n");

    for (uptr i = 0; i < map.outer.length; i += 1) {
        uptr outer = table_get_or(&map.outer, i, UPTR_MAX);

        printf("    [%3llu] ", outer);

        if (i < map.inner.size) {
            uptr inner = array_get_or(&map.inner, i, UPTR_MAX);
            u32  key   = array_get_or(&map.key, i, U32_MAX);
            u32  value = array_get_or(&map.value, i, U32_MAX);

            printf("[%3llu] %u => %u", inner, key, value);
        } else
            printf("[  0]");

        printf("\n");
    }

    printf("}\n");
}
