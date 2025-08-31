#ifndef PX_NETWORK_ADDRESS_C
#define PX_NETWORK_ADDRESS_C

#include "address.h"

PxAddress
pxAddressAny(PxAddressType type)
{
    PxAddress result = {.type = type};

    switch (result.type) {
        case PX_ADDRESS_TYPE_IP4:
            result.ip4 = PX_ADDRESS_IP4_ANY;
        break;

        case PX_ADDRESS_TYPE_IP6:
            result.ip6 = PX_ADDRESS_IP6_ANY;
        break;

        default: break;
    }

    return result;
}

PxAddress
pxAddressLocalhost(PxAddressType type)
{
    PxAddress result = {.type = type};

    switch (result.type) {
        case PX_ADDRESS_TYPE_IP4:
            result.ip4 = PX_ADDRESS_IP4_LOCALHOST;
        break;

        case PX_ADDRESS_TYPE_IP6:
            result.ip6 = PX_ADDRESS_IP6_LOCALHOST;
        break;

        default: break;
    }

    return result;
}

pxb8
pxAddressFromString8(PxAddress* self, PxAddressType type, PxString8 string)
{
    if (self == 0) return 0;

    self->type = type;

    switch (self->type) {
        case PX_ADDRESS_TYPE_IP4:
            return pxAddressIp4FromString8(&self->ip4, string);

        case PX_ADDRESS_TYPE_IP6:
            return pxAddressIp6FromString8(&self->ip6, string);

        default: break;
    }

    return 0;
}

pxb8
pxAddressIsEqual(PxAddress self, PxAddress value)
{
    if (self.type != value.type) return 0;

    switch (self.type) {
        case PX_ADDRESS_TYPE_IP4:
            return pxAddressIp4IsEqual(self.ip4, value.ip4);

        case PX_ADDRESS_TYPE_IP6:
            return pxAddressIp6IsEqual(self.ip6, value.ip6);

        default: break;
    }

    return 0;
}

#endif // PX_NETWORK_ADDRESS_C
