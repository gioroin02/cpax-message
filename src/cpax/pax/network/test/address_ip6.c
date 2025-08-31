#include "../export.h"

#include <stdio.h>

#define RED(x)    "\x1b[31m" pxString(x) "\x1b[0m"
#define GREEN(x)  "\x1b[32m" pxString(x) "\x1b[0m"
#define YELLOW(x) "\x1b[33m" pxString(x) "\x1b[0m"
#define BLUE(x)   "\x1b[34m" pxString(x) "\x1b[0m"
#define PURPLE(x) "\x1b[35m" pxString(x) "\x1b[0m"
#define AZURE(x)  "\x1b[36m" pxString(x) "\x1b[0m"

#define TRUE  GREEN(T)
#define FALSE RED(F)

void
showAddressIp6FromString8(PxString8 string)
{
    PxAddressIp6 value = {};
    pxb8         state = pxAddressIp6FromString8(&value, string);

    printf("ip6 (" BLUE('%48s') ") -> %s, ",
        string.memory, state != 0 ? TRUE : FALSE);

    for (pxiword i = 0; i < PX_ADDRESS_IP6_GROUPS; i += 1)
        printf("%4x ", value.memory[i]);
    printf("\n");
}

int
main(int argc, char** argv)
{
    printf("Valid IPv6:\n");

    showAddressIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:7334"));
    showAddressIp6FromString8(pxs8("fc00::1"));
    showAddressIp6FromString8(pxs8("::1"));
    showAddressIp6FromString8(pxs8("::"));
    showAddressIp6FromString8(pxs8("2001:db8::8a2e:370:7334"));
    showAddressIp6FromString8(pxs8("fe80::1"));
    showAddressIp6FromString8(pxs8("ff02::1"));
    showAddressIp6FromString8(pxs8("2001:0db8:0000:0000:0000:0000:0000:0001"));
    showAddressIp6FromString8(pxs8("2001:db8:0:0:0:0:0:1"));
    showAddressIp6FromString8(pxs8("2001:db8::1"));
    showAddressIp6FromString8(pxs8("3ffe:1900:4545:3:200:f8ff:fe21:67cf"));
    showAddressIp6FromString8(pxs8("2001:db8:1234::5678"));
    showAddressIp6FromString8(pxs8("ff00::"));
    showAddressIp6FromString8(pxs8("2001:0db8:85a3::8a2e:0370:7334"));
    showAddressIp6FromString8(pxs8("2001:db8:0:0:1:0:0:1"));
    showAddressIp6FromString8(pxs8("fe80::200:5eff:fe00:5213"));
    showAddressIp6FromString8(pxs8("2001:db8:abcd:1234:5678:90ab:cdef:1234"));
    showAddressIp6FromString8(pxs8("::ffff:0:0"));

    printf("\nInvalid IPv6:\n");

    showAddressIp6FromString8(pxs8("localhost"));
    showAddressIp6FromString8(pxs8("fe80:0:0:0:200:5efe:192.168.1.1"));
    showAddressIp6FromString8(pxs8("::ffff:192.168.1.1"));
    showAddressIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:7334:1"));
    showAddressIp6FromString8(pxs8("2001:0db8::85a3::7334"));
    showAddressIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370"));
    showAddressIp6FromString8(pxs8("gggg:hhhh:iiii:jjjj:kkkk:llll:mmmm:nnnn"));
    showAddressIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:733g"));
    showAddressIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:"));
    showAddressIp6FromString8(pxs8(":2001:0db8:85a3:0000:0000:8a2e:0370:7334"));
    showAddressIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e::7334:1"));
    showAddressIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370.7334"));
    showAddressIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:7334/64"));
    showAddressIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:"));
    showAddressIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e::7334:abcd"));
    showAddressIp6FromString8(pxs8("2001:0db8:::7334"));
    showAddressIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:7334:"));
    showAddressIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:7334::"));
    showAddressIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:FFFFF"));
    showAddressIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370"));
    showAddressIp6FromString8(pxs8("2001::85a3::"));
    showAddressIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:port"));
    showAddressIp6FromString8(pxs8("::ffff:192.168.1.256"));
    showAddressIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e::-1"));
    showAddressIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:7334:5"));
    showAddressIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:733.4"));
    showAddressIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e::7334::"));
    showAddressIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:"));
}
