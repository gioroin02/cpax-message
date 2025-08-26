#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    PxAddressIp4 address = {0};

    PxString8 string = pxString8Copy(&arena, pxs8("192.168.65.65"));

    pxAddressIp4FromString(&address, string);

    for (pxiword i = 0; i < PX_ADDRESS_IP4_GROUPS; i += 1)
        printf("%u\n", address.memory[i]);
}
