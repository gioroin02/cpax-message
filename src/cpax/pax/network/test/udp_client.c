#include "../export.h"

#include <stdio.h>

#define RED(x)    "\x1b[31m" pxString(x) "\x1b[0m"
#define GREEN(x)  "\x1b[32m" pxString(x) "\x1b[0m"
#define YELLOW(x) "\x1b[33m" pxString(x) "\x1b[0m"
#define BLUE(x)   "\x1b[34m" pxString(x) "\x1b[0m"
#define PURPLE(x) "\x1b[35m" pxString(x) "\x1b[0m"
#define AZURE(x)  "\x1b[36m" pxString(x) "\x1b[0m"

#define PANIC PURPLE(PANIC)
#define ERROR RED(ERROR)
#define WARN  YELLOW(WARN)
#define INFO  BLUE(INFO)
#define DEBUG GREEN(DEBUG)
#define TRACE AZURE(TRACE)

#define CLIENT_MSG pxs8("Hello server!")

#define CLIENT_ARG_IPV4 pxs8("--server-ipv4=")
#define CLIENT_ARG_IPV6 pxs8("--server-ipv6=")
#define CLIENT_ARG_PORT pxs8("--server-port=")

typedef struct ClientConfig
{
    PxAddress addr;
    pxu16     port;
}
ClientConfig;

typedef struct ClientState
{
    PxSocketUdp socket;
    PxBuffer8   request;
    PxBuffer8   response;
}
ClientState;

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    if (pxNetworkStart() == 0) return 1;

    ClientConfig config = {
        .addr = pxAddressLocalhost(PX_ADDRESS_TYPE_IP4),
        .port = 8000,
    };

    if (argc > 1) {
        PxFormatOption options = PX_FORMAT_OPTION_NONE;

        for (pxiword i = 1; i < argc; i += 1) {
            PxString8 arg = pxString8FromMemory(argv[i], 32);

            if (pxString8BeginsWith(arg, CLIENT_ARG_IPV4) != 0) {
                arg = pxString8TrimPrefix(arg, CLIENT_ARG_IPV4);
                arg = pxString8TrimSpaces(arg);

                pxAddressFromString8(&config.addr, PX_ADDRESS_TYPE_IP4, arg);
            }

            if (pxString8BeginsWith(arg, CLIENT_ARG_IPV6) != 0) {
                arg = pxString8TrimPrefix(arg, CLIENT_ARG_IPV6);
                arg = pxString8TrimSpaces(arg);

                pxAddressFromString8(&config.addr, PX_ADDRESS_TYPE_IP6, arg);
            }

            if (pxString8BeginsWith(arg, CLIENT_ARG_PORT) != 0) {
                arg = pxString8TrimPrefix(arg, CLIENT_ARG_PORT);
                arg = pxString8TrimSpaces(arg);

                pxU16FromString8(&config.port, 10, options, arg);
            }
        }
    }

    ClientState client = {0};

    client.socket = pxSocketUdpCreate(&arena, config.addr.type);

    if (client.socket == 0) return 1;

    client.request  = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);
    client.response = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);

    pxBuffer8WriteString8Tail(&client.request, CLIENT_MSG);

    pxSocketUdpWriteHost(client.socket,
        &client.request, config.addr, config.port);

    PxAddress addr = {0};
    pxu16     port = 0;

    pxb8 state = pxSocketUdpReadHost(client.socket,
        &client.response, &addr, &port);

    if (state != 0) {
        if (port == config.port && pxAddressIsEqual(addr, config.addr) != 0) {
            PxString8 string = pxBuffer8ReadString8Head(
                &client.response, &arena, client.response.size);

            printf(INFO " " BLUE('%s') "\n", string.memory);
        } else
            printf(ERROR " Indirizzo o porta inaspettati...\n");
    }

    pxSocketUdpDestroy(client.socket);

    pxNetworkStop();
}
