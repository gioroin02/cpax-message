#ifndef PX_NETWORK_ADDRESS_IP4_H
#define PX_NETWORK_ADDRESS_IP4_H

#include "import.h"

#define PX_ADDRESS_IP4_ANY       ((PxAddressIp4) {0})
#define PX_ADDRESS_IP4_LOCALHOST ((PxAddressIp4) {.a = 127, .d = 1})

#define PX_ADDRESS_IP4_GROUPS 4

typedef struct PxAddressIp4
{
    union
    {
        struct {
            pxu8 a, b, c, d;
        };

        pxu8 memory[PX_ADDRESS_IP4_GROUPS];
    };
}
PxAddressIp4;

pxb8
pxAddressIp4FromString(PxAddressIp4* self, PxString8 string);

pxb8
pxAddressIp4IsEqual(PxAddressIp4 self, PxAddressIp4 value);

#endif // PX_NETWORK_ADDRESS_IP4_H
