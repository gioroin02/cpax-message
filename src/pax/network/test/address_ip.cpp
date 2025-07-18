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
show_ip4_from_str8(str8 string)
{
    Address_IP4 value = {};
    b32         state = ip4_from_str8(string, &value);

    printf("ip4 (" PRP("'%24.*s'") ") -> %s, ", pax_cast(int, string.length),
        string.memory, state ? TRUE : FALSE);

    for (uptr i = 0; i < ADDRESS_IP4_GROUPS; i += 1)
        printf("%4u ", value.memory[i]);
    printf("\n");
}

void
show_ip6_from_str8(str8 string)
{
    Address_IP6 value = {};
    b32         state = ip6_from_str8(string, &value);

    printf("ip6 (" PRP("'%48.*s'") ") -> %s, ", pax_cast(int, string.length),
        string.memory, state ? TRUE : FALSE);

    for (uptr i = 0; i < ADDRESS_IP6_GROUPS; i += 1)
        printf("%4x ", value.memory[i]);
    printf("\n");
}

int
main()
{
    printf("Valid IPv4:\n");

    show_ip4_from_str8(pax_str8("localhost"));
    show_ip4_from_str8(pax_str8("0.0.0.0"));
    show_ip4_from_str8(pax_str8("000.0.000.0"));
    show_ip4_from_str8(pax_str8("127.0.0.1"));
    show_ip4_from_str8(pax_str8("192.168.1.1"));
    show_ip4_from_str8(pax_str8("10.0.0.255"));
    show_ip4_from_str8(pax_str8("172.16.0.1"));
    show_ip4_from_str8(pax_str8("255.255.255.255"));
    show_ip4_from_str8(pax_str8("8.8.8.8"));
    show_ip4_from_str8(pax_str8("100.64.0.1"));
    show_ip4_from_str8(pax_str8("169.254.1.1"));
    show_ip4_from_str8(pax_str8("198.51.100.42"));
    show_ip4_from_str8(pax_str8("1.2.3.4"));
    show_ip4_from_str8(pax_str8("203.0.113.7"));
    show_ip4_from_str8(pax_str8("128.0.0.1"));
    show_ip4_from_str8(pax_str8("192.0.2.123"));
    show_ip4_from_str8(pax_str8("172.31.255.254"));
    show_ip4_from_str8(pax_str8("10.10.10.10"));
    show_ip4_from_str8(pax_str8("192.168.0.0"));
    show_ip4_from_str8(pax_str8("192.168.001.1"));
    show_ip4_from_str8(pax_str8("192.168.1.01"));
    show_ip4_from_str8(pax_str8("172.20.30.40"));
    show_ip4_from_str8(pax_str8("209.85.231.104"));
    show_ip4_from_str8(pax_str8("240.0.0.1"));

    printf("\nInvalid IPv4:\n");

    show_ip4_from_str8(pax_str8("256.1.2.3"));
    show_ip4_from_str8(pax_str8("1.2.3"));
    show_ip4_from_str8(pax_str8("1.2.3.4.5"));
    show_ip4_from_str8(pax_str8("10.0.0.0.1"));
    show_ip4_from_str8(pax_str8("172.16.1"));
    show_ip4_from_str8(pax_str8("192.168.1.1.1"));
    show_ip4_from_str8(pax_str8("1.2.3.4."));
    show_ip4_from_str8(pax_str8(".1.2.3.4"));
    show_ip4_from_str8(pax_str8("192.168.1.256"));
    show_ip4_from_str8(pax_str8("abc.def.ghi.jkl"));
    show_ip4_from_str8(pax_str8("192.168.1."));
    show_ip4_from_str8(pax_str8("192.168.1.1/24"));
    show_ip4_from_str8(pax_str8("192.168.1.1..2"));
    show_ip4_from_str8(pax_str8("192.168.-1.1"));
    show_ip4_from_str8(pax_str8("192.168.1.1a"));
    show_ip4_from_str8(pax_str8("192.168.1"));
    show_ip4_from_str8(pax_str8("192.168.1.999"));
    show_ip4_from_str8(pax_str8("192.168.1.1.2"));
    show_ip4_from_str8(pax_str8("192.168.1."));
    show_ip4_from_str8(pax_str8("192.168..1.1"));
    show_ip4_from_str8(pax_str8("192.168.1.1:80"));
    show_ip4_from_str8(pax_str8("300.400.500.600"));
    show_ip4_from_str8(pax_str8("192.168.1.1/32"));

    printf("\nValid IPv6:\n");

    show_ip6_from_str8(pax_str8("localhost"));
    show_ip6_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:7334"));
    show_ip6_from_str8(pax_str8("fc00::1"));
    show_ip6_from_str8(pax_str8("::1"));
    show_ip6_from_str8(pax_str8("::"));
    show_ip6_from_str8(pax_str8("2001:db8::8a2e:370:7334"));
    show_ip6_from_str8(pax_str8("fe80::1"));
    show_ip6_from_str8(pax_str8("ff02::1"));
    show_ip6_from_str8(pax_str8("2001:0db8:0000:0000:0000:0000:0000:0001"));
    show_ip6_from_str8(pax_str8("2001:db8:0:0:0:0:0:1"));
    show_ip6_from_str8(pax_str8("2001:db8::1"));
    show_ip6_from_str8(pax_str8("3ffe:1900:4545:3:200:f8ff:fe21:67cf"));
    show_ip6_from_str8(pax_str8("2001:db8:1234::5678"));
    show_ip6_from_str8(pax_str8("ff00::"));
    show_ip6_from_str8(pax_str8("2001:0db8:85a3::8a2e:0370:7334"));
    show_ip6_from_str8(pax_str8("2001:db8:0:0:1:0:0:1"));
    show_ip6_from_str8(pax_str8("fe80::200:5eff:fe00:5213"));
    show_ip6_from_str8(pax_str8("2001:db8:abcd:1234:5678:90ab:cdef:1234"));
    show_ip6_from_str8(pax_str8("::ffff:0:0"));

    printf("\nInvalid IPv6:\n");

    show_ip6_from_str8(pax_str8("fe80:0:0:0:200:5efe:192.168.1.1"));
    show_ip6_from_str8(pax_str8("::ffff:192.168.1.1"));
    show_ip6_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:7334:1"));
    show_ip6_from_str8(pax_str8("2001:0db8::85a3::7334"));
    show_ip6_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370"));
    show_ip6_from_str8(pax_str8("gggg:hhhh:iiii:jjjj:kkkk:llll:mmmm:nnnn"));
    show_ip6_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:733g"));
    show_ip6_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:"));
    show_ip6_from_str8(pax_str8(":2001:0db8:85a3:0000:0000:8a2e:0370:7334"));
    show_ip6_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e::7334:1"));
    show_ip6_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370.7334"));
    show_ip6_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:7334/64"));
    show_ip6_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:"));
    show_ip6_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e::7334:abcd"));
    show_ip6_from_str8(pax_str8("2001:0db8:::7334"));
    show_ip6_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:7334:"));
    show_ip6_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:7334::"));
    show_ip6_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:FFFFF"));
    show_ip6_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370"));
    show_ip6_from_str8(pax_str8("2001::85a3::"));
    show_ip6_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:port"));
    show_ip6_from_str8(pax_str8("::ffff:192.168.1.256"));
    show_ip6_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e::-1"));
    show_ip6_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:7334:5"));
    show_ip6_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:733.4"));
    show_ip6_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e::7334::"));
    show_ip6_from_str8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:"));
}
