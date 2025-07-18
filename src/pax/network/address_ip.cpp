#ifndef PAX_NETWORK_ADDRESS_IP_CPP
#define PAX_NETWORK_ADDRESS_IP_CPP

#include "address_ip.hpp"

namespace pax {

static u8  LOCALHOST_IP4[ADDRESS_IP4_GROUPS] = {127, 0, 0, 1};
static u16 LOCALHOST_IP6[ADDRESS_IP6_GROUPS] = {0, 0, 0, 0, 0, 0, 0, 1};

Address_IP4
address_ip4_any()
{
    Address_IP4 result = {};

    return result;
}

b32
address_ip4_is_equal(Address_IP4 self, Address_IP4 value)
{
    return mem8_is_equal(self.memory, value.memory, ADDRESS_IP4_GROUPS);
}

b32
ip4_from_str8(str8 self, Address_IP4* value)
{
    str8 group = self;
    str8 tail  = self;

    Format_Options opts = {};

    opts.flags = FORMAT_FLAG_LEADING_ZERO;
    opts.base  = 10;

    u8 temp[ADDRESS_IP4_GROUPS] = {};

    if (str8_is_equal(self, pax_str8("localhost")) != 0) {
        if (value != 0)
            mem8_copy(value->memory, LOCALHOST_IP4, ADDRESS_IP4_GROUPS);

        return 1;
    }

    if (str8_contains(self, pax_str8(".")) + 1 != ADDRESS_IP4_GROUPS)
        return 0;

    for (uptr i = 0; i < ADDRESS_IP4_GROUPS; i += 1) {
        group = str8_split_on(tail, pax_str8("."), &tail);

        if (u8_from_str8(group, opts, &temp[i]) == 0)
            return 0;
    }

    if (tail.length != 0) return 0;

    if (value != 0)
        mem8_copy(value->memory, temp, ADDRESS_IP4_GROUPS);

    return 1;
}

Address_IP6
address_ip6_any()
{
    Address_IP6 result = {};

    return result;
}

b32
address_ip6_is_equal(Address_IP6 self, Address_IP6 value)
{
    return mem16_is_equal(self.memory, value.memory, ADDRESS_IP6_GROUPS);
}

b32
ip6_from_str8(str8 self, Address_IP6* value)
{
    if (str8_is_equal(self, pax_str8("localhost")) != 0) {
        if (value != 0)
            mem16_copy(value->memory, LOCALHOST_IP6, ADDRESS_IP6_GROUPS);

        return 1;
    }

    Format_Options opts = {};

    opts.flags = FORMAT_FLAG_LEADING_ZERO;
    opts.base  = 16;

    u16 temp[ADDRESS_IP6_GROUPS] = {};

    switch (str8_contains(self, pax_str8("::")) + 1) {
        case 1: {
            str8 group = self;
            str8 tail  = self;

            if (str8_contains(self, pax_str8(":")) + 1 != ADDRESS_IP6_GROUPS)
                return 0;

            for (uptr i = 0; i < ADDRESS_IP6_GROUPS; i += 1) {
                group = str8_split_on(tail, pax_str8(":"), &tail);

                if (u16_from_str8(group, opts, &temp[i]) == 0)
                    return 0;
            }

            if (tail.length != 0) return 0;
        } break;

        case 2: {
            str8 group = self;
            str8 left  = self;
            str8 right = self;

            left = str8_split_on(self, pax_str8("::"), &right);

            uptr start = 0;
            uptr index = str8_contains(left, pax_str8(":")) + 1;
            uptr stop  = ADDRESS_IP6_GROUPS;

            if (index >= stop) return 0;

            for (uptr i = start; i < index; i += 1) {
                group = str8_split_on(left, pax_str8(":"), &left);

                if (group.length == 0) break;

                if (u16_from_str8(group, opts, &temp[i]) == 0)
                    return 0;
            }

            if (left.length != 0) return 0;

            start = index;
            index = str8_contains(right, pax_str8(":")) + 1;

            if (start + index >= stop) return 0;

            for (uptr i = stop - index; i < stop; i += 1) {
                group = str8_split_on(right, pax_str8(":"), &right);

                if (group.length == 0) break;

                if (u16_from_str8(group, opts, &temp[i]) == 0)
                    return 0;
            }

            if (right.length != 0) return 0;
        } break;

        default: return 0;
    }

    if (value != 0)
        mem16_copy(value->memory, temp, ADDRESS_IP6_GROUPS);

    return 1;
}

} // namespace pax

#endif // PAX_NETWORK_ADDRESS_IP_CPP
