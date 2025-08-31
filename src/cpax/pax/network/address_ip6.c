#ifndef PX_NETWORK_ADDRESS_IP6_C
#define PX_NETWORK_ADDRESS_IP6_C

#include "address_ip6.h"

pxb8
pxAddressIp6FromString8(PxAddressIp6* self, PxString8 string)
{
    PxAddressIp6 temp = {0};

    PxFormatOption options =
        PX_FORMAT_OPTION_LEADING_ZERO;

    PxString8 left  = {0};
    PxString8 right = {0};
    PxString8 group = {0};

    switch (pxString8Contains(string, pxs8("::"))) {
        case 0: {
            pxiword groups = pxString8Contains(string, pxs8(":"));

            if (groups != PX_ADDRESS_IP6_GROUPS - 1) return 0;

            for (pxiword i = 0; i < PX_ADDRESS_IP6_GROUPS; i += 1) {
                pxString8Split(string, pxs8(":"), &group, &string);

                if (pxU16FromString8(&temp.memory[i], 16, options, group) == 0)
                    return 0;
            }
        } break;

        case 1: {
            pxString8Split(string, pxs8("::"), &left, &right);

            pxiword pivot = pxString8Contains(left, pxs8(":")) + 1;
            pxiword start = 0;
            pxiword stop  = PX_ADDRESS_IP6_GROUPS;

            if (pivot >= stop) return 0;

            for (pxiword i = start; i < pivot; i += 1) {
                pxString8Split(left, pxs8(":"), &group, &left);

                if (group.length <= 0) break;

                if (pxU16FromString8(&temp.memory[i], 16, options, group) == 0)
                    return 0;
            }

            if (left.length > 0) return 0;

            start = pivot;
            pivot = pxString8Contains(right, pxs8(":")) + 1;

            if (start + pivot >= stop) return 0;

            for (pxiword i = stop - pivot; i < stop; i += 1) {
                pxString8Split(right, pxs8(":"), &group, &right);

                if (group.length <= 0) break;

                if (pxU16FromString8(&temp.memory[i], 16, options, group) == 0)
                    return 0;
            }

            if (right.length > 0) return 0;
        } break;

        default: return 0;
    }

    if (self != 0)
        pxMemoryCopy(self->memory, temp.memory, PX_ADDRESS_IP6_GROUPS, 2);

    return 1;
}

pxb8
pxAddressIp6IsEqual(PxAddressIp6 self, PxAddressIp6 value)
{
    return pxMemoryIsEqual(self.memory, value.memory,
        PX_ADDRESS_IP6_GROUPS, 2);
}

#endif // PX_NETWORK_ADDRESS_IP6_C
