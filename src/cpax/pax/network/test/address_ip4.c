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
showAddressIp4FromString8(PxString8 string)
{
    PxAddressIp4 value = {};
    pxb8         state = pxAddressIp4FromString8(&value, string);

    printf("ip6 (" BLUE('%24s') ") -> %s, ",
        string.memory, state != 0 ? TRUE : FALSE);

    for (pxiword i = 0; i < PX_ADDRESS_IP4_GROUPS; i += 1)
        printf("%4u ", value.memory[i]);
    printf("\n");
}

int
main()
{
    printf("Valid IPv4:\n");

    showAddressIp4FromString8(pxs8("0.0.0.0"));
    showAddressIp4FromString8(pxs8("000.0.000.0"));
    showAddressIp4FromString8(pxs8("127.0.0.1"));
    showAddressIp4FromString8(pxs8("192.168.1.1"));
    showAddressIp4FromString8(pxs8("10.0.0.255"));
    showAddressIp4FromString8(pxs8("172.16.0.1"));
    showAddressIp4FromString8(pxs8("255.255.255.255"));
    showAddressIp4FromString8(pxs8("8.8.8.8"));
    showAddressIp4FromString8(pxs8("100.64.0.1"));
    showAddressIp4FromString8(pxs8("169.254.1.1"));
    showAddressIp4FromString8(pxs8("198.51.100.42"));
    showAddressIp4FromString8(pxs8("1.2.3.4"));
    showAddressIp4FromString8(pxs8("203.0.113.7"));
    showAddressIp4FromString8(pxs8("128.0.0.1"));
    showAddressIp4FromString8(pxs8("192.0.2.123"));
    showAddressIp4FromString8(pxs8("172.31.255.254"));
    showAddressIp4FromString8(pxs8("10.10.10.10"));
    showAddressIp4FromString8(pxs8("192.168.0.0"));
    showAddressIp4FromString8(pxs8("192.168.001.1"));
    showAddressIp4FromString8(pxs8("192.168.1.01"));
    showAddressIp4FromString8(pxs8("172.20.30.40"));
    showAddressIp4FromString8(pxs8("209.85.231.104"));
    showAddressIp4FromString8(pxs8("240.0.0.1"));

    printf("\nInvalid IPv4:\n");

    showAddressIp4FromString8(pxs8("localhost"));
    showAddressIp4FromString8(pxs8("256.1.2.3"));
    showAddressIp4FromString8(pxs8("1.2.3"));
    showAddressIp4FromString8(pxs8("1.2.3.4.5"));
    showAddressIp4FromString8(pxs8("10.0.0.0.1"));
    showAddressIp4FromString8(pxs8("172.16.1"));
    showAddressIp4FromString8(pxs8("192.168.1.1.1"));
    showAddressIp4FromString8(pxs8("1.2.3.4."));
    showAddressIp4FromString8(pxs8(".1.2.3.4"));
    showAddressIp4FromString8(pxs8("192.168.1.256"));
    showAddressIp4FromString8(pxs8("abc.def.ghi.jkl"));
    showAddressIp4FromString8(pxs8("192.168.1."));
    showAddressIp4FromString8(pxs8("192.168.1.1/24"));
    showAddressIp4FromString8(pxs8("192.168.1.1..2"));
    showAddressIp4FromString8(pxs8("192.168.-1.1"));
    showAddressIp4FromString8(pxs8("192.168.1.1a"));
    showAddressIp4FromString8(pxs8("192.168.1"));
    showAddressIp4FromString8(pxs8("192.168.1.999"));
    showAddressIp4FromString8(pxs8("192.168.1.1.2"));
    showAddressIp4FromString8(pxs8("192.168.1."));
    showAddressIp4FromString8(pxs8("192.168..1.1"));
    showAddressIp4FromString8(pxs8("192.168.1.1:80"));
    showAddressIp4FromString8(pxs8("300.400.500.600"));
    showAddressIp4FromString8(pxs8("192.168.1.1/32"));
}
