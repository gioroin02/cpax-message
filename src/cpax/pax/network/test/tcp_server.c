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

#define SERVER_MSG pxs8("Hello client!")

#define SERVER_ARG_IP_VERSION pxs8("--server-ip-version=")
#define SERVER_ARG_PORT       pxs8("--server-port=")
#define SERVER_ARG_LIFETIME   pxs8("--server-lifetime=")

typedef struct ServerConfig
{
    PxAddressType type;
    pxu16         port;
    pxu32         lifetime;
}
ServerConfig;

typedef struct ServerState
{
    PxSocketTcp socket;
}
ServerState;

typedef struct ServerSession
{
    PxSocketTcp socket;
    PxBuffer8   request;
    PxBuffer8   response;
}
ServerSession;

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    if (pxNetworkStart() == 0) return 1;

    ServerConfig config = {
        .type = PX_ADDRESS_TYPE_IP4,
        .port = 8000,
        .lifetime = 1,
    };

    if (argc > 1) {
        PxFormatOption options = PX_FORMAT_OPTION_NONE;

        for (pxiword i = 1; i < argc; i += 1) {
            PxString8 arg = pxString8FromMemory(argv[i], 32);

            if (pxString8BeginsWith(arg, SERVER_ARG_IP_VERSION) != 0) {
                arg = pxString8TrimPrefix(arg, SERVER_ARG_IP_VERSION);
                arg = pxString8TrimSpaces(arg);

                if (pxString8IsEqual(arg, pxs8("ipv6")) != 0)
                    config.type = PX_ADDRESS_TYPE_IP6;
            }

            if (pxString8BeginsWith(arg, SERVER_ARG_PORT) != 0) {
                arg = pxString8TrimPrefix(arg, SERVER_ARG_PORT);
                arg = pxString8TrimSpaces(arg);

                pxU16FromString8(&config.port, 10, options, arg);
            }

            if (pxString8BeginsWith(arg, SERVER_ARG_LIFETIME) != 0) {
                arg = pxString8TrimPrefix(arg, SERVER_ARG_LIFETIME);
                arg = pxString8TrimSpaces(arg);

                pxU32FromString8(&config.lifetime, 10, options, arg);
            }
        }
    }

    ServerState server = {0};

    server.socket = pxSocketTcpCreate(&arena, config.type);

    if (server.socket == 0) return 1;

    PxAddress address = pxAddressAny(config.type);

    if (pxSocketTcpBind(server.socket, address, config.port) == 0)
        return 1;

    if (pxSocketTcpListen(server.socket) == 0) return 1;

    pxiword offset = pxArenaOffset(&arena);

    for (pxu32 i = 0; i < config.lifetime; i += 1) {
        ServerSession session = {0};

        session.socket = pxSocketTcpAccept(server.socket, &arena);

        if (session.socket == 0) continue;

        session.request  = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);
        session.response = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);

        pxb8 state = pxSocketTcpRead(session.socket, &session.request);

        if (state != 0) {
            PxString8 string = pxBuffer8ReadString8Head(
                &session.request, &arena, session.request.size);

            printf(INFO " " BLUE('%s') "\n", string.memory);

            pxBuffer8WriteString8Tail(&session.response, SERVER_MSG);

            pxSocketTcpWrite(session.socket, &session.response);
        }

        pxSocketTcpDestroy(session.socket);

        pxArenaRewind(&arena, offset);
    }

    pxSocketTcpDestroy(server.socket);

    pxNetworkStop();
}
