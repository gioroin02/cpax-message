#ifndef PX_NETWORK_ADDRESS_IP4_C
#define PX_NETWORK_ADDRESS_IP4_C

#include "address_ip4.h"

pxb8
pxAddressIp4FromString(PxAddressIp4* self, PxString8 string)
{
    PxAddressIp4 temp = {0};

    PxFormatOptions options = pxFormatOptions(10,
        PX_FORMAT_FLAG_LEADING_ZERO);

    pxiword groups = pxString8Contains(string, pxs8("."));

    if (groups != PX_ADDRESS_IP4_GROUPS - 1) return 0;

    PxString8 left  = {0};
    PxString8 right = string;

    for (pxiword i = 0; i < PX_ADDRESS_IP4_GROUPS; i += 1) {
        pxString8Split(right, pxs8("."), &left, &right);

        if (pxU8FromString8(&temp.memory[i], options, left) == 0)
            return 0;
    }

    if (self != 0)
        pxMemoryCopy(self->memory, temp.memory, PX_ADDRESS_IP4_GROUPS, 1);

    return 1;
}

pxb8
pxAddressIp4IsEqual(PxAddressIp4 self, PxAddressIp4 value)
{
    return pxMemoryIsEqual(self.memory, value.memory,
        PX_ADDRESS_IP4_GROUPS, 1);
}

#endif // PX_NETWORK_ADDRESS_IP4_C
