#include "../export.h"

#include <stdio.h>

#define RED(x)    "\x1b[31m" pxString(x) "\x1b[0m"
#define GREEN(x)  "\x1b[32m" pxString(x) "\x1b[0m"
#define YELLOW(x) "\x1b[33m" pxString(x) "\x1b[0m"
#define BLUE(x)   "\x1b[34m" pxString(x) "\x1b[0m"
#define PURPLE(x) "\x1b[35m" pxString(x) "\x1b[0m"
#define AZURE(x)  "\x1b[36m" pxString(x) "\x1b[0m"

#define TRUE  GREEN("T")
#define FALSE RED("F")

void
showAddressFromString8(PxString8 string, PxAddressType type)
{
    PxAddress value = {};

    pxMemoryZero(&value, 1, pxSize(PxAddress));

    pxb8 state = pxAddressFromString8(&value, type, string);

    switch (type) {
        case PX_ADDRESS_TYPE_IP4: {
            printf("ip4 (" BLUE('%24s') ") -> %s, ",
                string.memory, state ? TRUE : FALSE);

            for (pxiword i = 0; i < PX_ADDRESS_IP4_GROUPS; i += 1)
                printf("%4u ", value.ip4.memory[i]);
            printf("\n");
        } break;

        case PX_ADDRESS_TYPE_IP6: {
            printf("ip6 (" BLUE('%48s') ") -> %s, ",
                string.memory, state ? TRUE : FALSE);

            for (pxiword i = 0; i < PX_ADDRESS_IP6_GROUPS; i += 1)
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

    showAddressFromString8(pxs8("0.0.0.0"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("000.0.000.0"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("127.0.0.1"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("192.168.1.1"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("10.0.0.255"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("172.16.0.1"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("255.255.255.255"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("8.8.8.8"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("100.64.0.1"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("169.254.1.1"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("198.51.100.42"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("1.2.3.4"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("203.0.113.7"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("128.0.0.1"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("192.0.2.123"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("172.31.255.254"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("10.10.10.10"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("192.168.0.0"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("192.168.001.1"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("192.168.1.01"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("172.20.30.40"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("209.85.231.104"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("240.0.0.1"), PX_ADDRESS_TYPE_IP4);

    printf("\nInvalid IPv4:\n");

    showAddressFromString8(pxs8("localhost"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("256.1.2.3"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("1.2.3"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("1.2.3.4.5"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("10.0.0.0.1"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("172.16.1"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("192.168.1.1.1"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("1.2.3.4."), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8(".1.2.3.4"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("192.168.1.256"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("abc.def.ghi.jkl"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("192.168.1."), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("192.168.1.1/24"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("192.168.1.1..2"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("192.168.-1.1"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("192.168.1.1a"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("192.168.1"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("192.168.1.999"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("192.168.1.1.2"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("192.168.1."), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("192.168..1.1"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("192.168.1.1:80"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("300.400.500.600"), PX_ADDRESS_TYPE_IP4);
    showAddressFromString8(pxs8("192.168.1.1/32"), PX_ADDRESS_TYPE_IP4);

    printf("\nValid IPv6:\n");

    showAddressFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:7334"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("fc00::1"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("::1"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("::"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("2001:db8::8a2e:370:7334"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("fe80::1"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("ff02::1"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("2001:0db8:0000:0000:0000:0000:0000:0001"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("2001:db8:0:0:0:0:0:1"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("2001:db8::1"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("3ffe:1900:4545:3:200:f8ff:fe21:67cf"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("2001:db8:1234::5678"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("ff00::"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("2001:0db8:85a3::8a2e:0370:7334"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("2001:db8:0:0:1:0:0:1"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("fe80::200:5eff:fe00:5213"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("2001:db8:abcd:1234:5678:90ab:cdef:1234"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("::ffff:0:0"), PX_ADDRESS_TYPE_IP6);

    printf("\nInvalid IPv6:\n");

    showAddressFromString8(pxs8("localhost"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("fe80:0:0:0:200:5efe:192.168.1.1"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("::ffff:192.168.1.1"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:7334:1"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("2001:0db8::85a3::7334"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("gggg:hhhh:iiii:jjjj:kkkk:llll:mmmm:nnnn"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:733g"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8(":2001:0db8:85a3:0000:0000:8a2e:0370:7334"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e::7334:1"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370.7334"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:7334/64"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e::7334:abcd"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("2001:0db8:::7334"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:7334:"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:7334::"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:FFFFF"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("2001::85a3::"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:port"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("::ffff:192.168.1.256"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e::-1"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:7334:5"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:733.4"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e::7334::"), PX_ADDRESS_TYPE_IP6);
    showAddressFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:"), PX_ADDRESS_TYPE_IP6);
}
