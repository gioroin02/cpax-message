#include "../exports.hpp"

using namespace pax;

#include <stdio.h>

#define RED(str) "\x1b[31m" str "\x1b[0m"
#define GRN(str) "\x1b[32m" str "\x1b[0m"
#define YLW(str) "\x1b[33m" str "\x1b[0m"
#define BLU(str) "\x1b[34m" str "\x1b[0m"
#define PRP(str) "\x1b[35m" str "\x1b[0m"
#define AZR(str) "\x1b[36m" str "\x1b[0m"

#define TRUE  GRN("T")
#define FALSE RED("F")

u32
thread_routine_a(addr argumns)
{
    for (uptr i = 0; i < 15; i += 1) {
        printf("ROUTINE " RED("A") "\n");

        system_sleep(500);
    }

    return 0;
}

u32
thread_routine_b(addr argumns)
{
    for (uptr i = 0; i < 5; i += 1) {
        printf("ROUTINE " BLU("B") "\n");

        system_sleep(1500);
    }

    return 0;
}

int
main()
{
    Arena arena = system_reserve(4);

    printf("number of cpus = %llu\n", system_get_number_of_cpus());
    printf("thread ident   = %llu\n", system_get_thread_ident());

    printf("thread start...\n");

    Thread a = thread_create(&arena, &thread_routine_a, 0);
    Thread b = thread_create(&arena, &thread_routine_b, 0);

    thread_wait(a);
    thread_wait(b);

    printf("thread stop...\n");
}
