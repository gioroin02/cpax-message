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

void
show_address_from_str8(str8 string, Address_Kind kind)
{
    Address value = {};

    mem8_zero(&value, pax_size_of(Address));

    b32 state = address_from_str8(string, kind, &value);

    switch (kind) {
        case ADDRESS_KIND_IP4: {
            printf("ip4 (" PRP("'%24.*s'") ") -> %s, ", pax_cast(int, string.length),
                string.memory, state ? TRUE : FALSE);

            for (uptr i = 0; i < ADDRESS_IP4_GROUPS; i += 1)
                printf("%4u ", value.ip4.memory[i]);
            printf("\n");
        } break;

        case ADDRESS_KIND_IP6: {
            printf("ip6 (" PRP("'%48.*s'") ") -> %s, ", pax_cast(int, string.length),
                string.memory, state ? TRUE : FALSE);

            for (uptr i = 0; i < ADDRESS_IP6_GROUPS; i += 1)
                printf("%4x ", value.ip6.memory[i]);
            printf("\n");
        } break;

        default: break;
    }
}

int
main()
{
    printf("Valid IPv4:\n");

    show_address_from_str8(pax_str8("localhost"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("0.0.0.0"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("000.0.000.0"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("127.0.0.1"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("192.168.1.1"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("10.0.0.255"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("172.16.0.1"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("255.255.255.255"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("8.8.8.8"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("100.64.0.1"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("169.254.1.1"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("198.51.100.42"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("1.2.3.4"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("203.0.113.7"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("128.0.0.1"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("192.0.2.123"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("172.31.255.254"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("10.10.10.10"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("192.168.0.0"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("192.168.001.1"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("192.168.1.01"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("172.20.30.40"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("209.85.231.104"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("240.0.0.1"), ADDRESS_KIND_IP4);

    printf("\nInvalid IPv4:\n");

    show_address_from_str8(pax_str8("256.1.2.3"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("1.2.3"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("1.2.3.4.5"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("10.0.0.0.1"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("172.16.1"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("192.168.1.1.1"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("1.2.3.4."), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8(".1.2.3.4"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("192.168.1.256"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("abc.def.ghi.jkl"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("192.168.1."), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("192.168.1.1/24"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("192.168.1.1..2"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("192.168.-1.1"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("192.168.1.1a"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("192.168.1"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("192.168.1.999"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("192.168.1.1.2"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("192.168.1."), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("192.168..1.1"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("192.168.1.1:80"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("300.400.500.600"), ADDRESS_KIND_IP4);
    show_address_from_str8(pax_str8("192.168.1.1/32"), ADDRESS_KIND_IP4);

    printf("\nValid IPv6:\n");

    show_address_from_str8(pax_str8("localhost"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:7334"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("fc00::1"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("::1"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("::"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("2001:db8::8a2e:370:7334"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("fe80::1"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("ff02::1"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("2001:0db8:0000:0000:0000:0000:0000:0001"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("2001:db8:0:0:0:0:0:1"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("2001:db8::1"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("3ffe:1900:4545:3:200:f8ff:fe21:67cf"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("2001:db8:1234::5678"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("ff00::"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("2001:0db8:85a3::8a2e:0370:7334"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("2001:db8:0:0:1:0:0:1"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("fe80::200:5eff:fe00:5213"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("2001:db8:abcd:1234:5678:90ab:cdef:1234"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("::ffff:0:0"), ADDRESS_KIND_IP6);

    printf("\nInvalid IPv6:\n");

    show_address_from_str8(pax_str8("fe80:0:0:0:200:5efe:192.168.1.1"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("::ffff:192.168.1.1"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:7334:1"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("2001:0db8::85a3::7334"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("gggg:hhhh:iiii:jjjj:kkkk:llll:mmmm:nnnn"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:733g"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8(":2001:0db8:85a3:0000:0000:8a2e:0370:7334"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e::7334:1"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370.7334"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:7334/64"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e::7334:abcd"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("2001:0db8:::7334"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:7334:"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:7334::"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:FFFFF"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("2001::85a3::"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:port"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("::ffff:192.168.1.256"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e::-1"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:7334:5"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:733.4"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e::7334::"), ADDRESS_KIND_IP6);
    show_address_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:"), ADDRESS_KIND_IP6);
}
