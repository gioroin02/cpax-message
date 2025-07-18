#ifndef PAX_NETWORK_ADDRESS_CPP
#define PAX_NETWORK_ADDRESS_CPP

#include "address.hpp"

namespace pax {

Address
address_any(Address_Kind kind)
{
    Address result = {};

    result.kind = ADDRESS_KIND_NONE;

    switch (kind) {
        case ADDRESS_KIND_IP4: {
            result.ip4 = address_ip4_any();
        } break;

        case ADDRESS_KIND_IP6: {
            result.ip6 = address_ip6_any();
        } break;

        default: return result;
    }

    result.kind = kind;

    return result;
}

b32
address_is_equal(Address self, Address value)
{
    if (self.kind != value.kind) return 0;

    switch (self.kind) {
        case ADDRESS_KIND_IP4:
            return address_ip4_is_equal(self.ip4, value.ip4);

        case ADDRESS_KIND_IP6:
            return address_ip6_is_equal(self.ip6, value.ip6);

        default: break;
    }

    return 0;
}

b32
address_from_str8(str8 self, Address_Kind kind, Address *value)
{
    if (value == 0) return 0;

    value->kind = ADDRESS_KIND_NONE;

    switch (kind) {
        case ADDRESS_KIND_IP4: {
            if (ip4_from_str8(self, &value->ip4) == 0)
                return 0;
        } break;

        case ADDRESS_KIND_IP6: {
            if (ip6_from_str8(self, &value->ip6) == 0)
                return 0;
        } break;

        default: return 0;
    }

    value->kind = kind;

    return 1;
}

} // namespace pax

#endif // PAX_NETWORK_ADDRESS_CPP
