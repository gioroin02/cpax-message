#include "../export.h"

#include "../../cpax/pax/memory/export.h"
#include "../../cpax/pax/string/export.h"

#include <stdio.h>

#define COLOR_RESET "\x1b[0m"

#define FRONT_RED    "\x1b[31m"
#define FRONT_GREEN  "\x1b[32m"
#define FRONT_YELLOW "\x1b[33m"
#define FRONT_BLUE   "\x1b[34m"
#define FRONT_PURPLE "\x1b[35m"
#define FRONT_AZURE  "\x1b[36m"

#define RED(expr)    FRONT_RED    expr COLOR_RESET
#define GREEN(expr)  FRONT_GREEN  expr COLOR_RESET
#define YELLOW(expr) FRONT_YELLOW expr COLOR_RESET
#define BLUE(expr)   FRONT_BLUE   expr COLOR_RESET
#define PURPLE(expr) FRONT_PURPLE expr COLOR_RESET
#define AZURE(expr)  FRONT_AZURE  expr COLOR_RESET

typedef enum EventType
{
    EVENT_NONE,
    EVENT_WINDOW_CLOSE,
    EVENT_WINDOW_RESIZE,
    EVENT_WINDOW_MOVE,
}
EventType;

typedef struct EventWindowClose
{
    pxiword window;
}
EventWindowClose;

typedef struct EventWindowResize
{
    pxiword window;
    pxiword size_x;
    pxiword size_y;
}
EventWindowResize;

typedef struct EventWindowMove
{
    pxiword window;
    pxiword coords_x;
    pxiword coords_y;
}
EventWindowMove;

typedef union EventBody
{
    EventWindowClose  window_close;
    EventWindowResize window_resize;
    EventWindowMove   window_move;
}
EventBody;

typedef struct Event
{
    EventType type;

    union
    {
        EventWindowClose  window_close;
        EventWindowResize window_resize;
        EventWindowMove   window_move;
    };
}
Event;

typedef struct Timer
{
    pxuword tick;
}
Timer;

static const PxString8 EVENT_NAMES[] =
{
    pxs8(pxString(EVENT_NONE)),
    pxs8(pxString(EVENT_WINDOW_CLOSE)),
    pxs8(pxString(EVENT_WINDOW_RESIZE)),
    pxs8(pxString(EVENT_WINDOW_MOVE)),
};

void
timeHandler(void* ctxt, pxuword type, void* memory, pxiword stride)
{
    Timer*     self  = pxCast(Timer*, ctxt);
    EventBody* event = pxCast(EventBody*, memory);
    PxString8  name = EVENT_NAMES[type];

    self->tick += 1;

    printf(RED("TIME") " --- | type = " BLUE("'%.*s'") ", time = " PURPLE("%llu") "\n",
        pxCast(int, name.length), name.memory, self->tick);

    switch (type) {
        case EVENT_WINDOW_CLOSE: break;

        case EVENT_WINDOW_RESIZE: {
            printf("    size_x: %lli\n    size_y: %lli\n",
                event->window_resize.size_x, event->window_resize.size_y);
        } break;

        case EVENT_WINDOW_MOVE: {
            printf("    coords_x: %lli\n    coords_y: %lli\n",
                event->window_move.coords_x, event->window_move.coords_y);
        } break;

        default: break;
    }
}

void
gameplayHandler(void* ctxt, pxuword type, void* memory, pxiword stride)
{
    EventBody* event = pxCast(EventBody*, memory);
    PxString8  name  = EVENT_NAMES[type];

    printf(RED("GAMEPLAY") " | type = " BLUE("'%.*s'") "\n",
        pxCast(int, name.length), name.memory);

    switch (type) {
        case EVENT_WINDOW_CLOSE: break;

        case EVENT_WINDOW_RESIZE: {
            printf("    size_x: %llu\n    size_y: %llu\n",
                event->window_resize.size_x, event->window_resize.size_y);
        } break;

        case EVENT_WINDOW_MOVE: {
            printf("    coords_x: %llu\n    coords_y: %llu\n",
                event->window_move.coords_x, event->window_move.coords_y);
        } break;

        default: break;
    }
}

void
graphicsHandler(void* ctxt, pxuword type, void* memory, pxiword stride)
{
    EventBody* event = pxCast(EventBody*, memory);
    PxString8  name  = EVENT_NAMES[type];

    printf(RED("GRAPHICS") " | type = " BLUE("'%.*s'") "\n",
        pxCast(int, name.length), name.memory);

    switch (type) {
        case EVENT_WINDOW_CLOSE: break;

        case EVENT_WINDOW_RESIZE: {
            printf("    size_x: %llu\n    size_y: %llu\n",
                event->window_resize.size_x, event->window_resize.size_y);
        } break;

        case EVENT_WINDOW_MOVE: {
            printf("    coords_x: %llu\n    coords_y: %llu\n",
                event->window_move.coords_x, event->window_move.coords_y);
        } break;

        default: break;
    }
}

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    PxMessageQueue  queue  = pxMessageQueueReserve(&arena, 256);
    PxMessageBroker broker = pxMessageBrokerMake(&arena);

    Timer timer = {.tick = 256};

    pxMessageBrokerAttach(&broker,
        EVENT_NONE, &timeHandler, &timer);

    pxMessageBrokerAttach(&broker,
        EVENT_WINDOW_CLOSE, &gameplayHandler, 0);

    pxMessageBrokerAttach(&broker,
        EVENT_WINDOW_MOVE, &gameplayHandler, 0);

    pxMessageBrokerAttach(&broker,
        EVENT_WINDOW_RESIZE, &graphicsHandler, 0);

    EventWindowClose  window_close  = {0};
    EventWindowResize window_resize = {0};
    EventWindowMove   window_move   = {0};

    window_close = (EventWindowClose) {.window = 1};

    pxMessageQueueInsert(&queue, &arena,
        EVENT_WINDOW_CLOSE, EventBody, &window_close);

    window_resize = (EventWindowResize) {
        .window = 1, .size_x = 10, .size_y = 156,
    };

    pxMessageQueueInsert(&queue, &arena,
        EVENT_WINDOW_RESIZE, EventBody, &window_resize);

    printf("IMMEDIATE\n");

    printf("\n");

    window_move = (EventWindowMove) {
        .window = 1, .coords_x = 34, .coords_y = 345,
    };

    pxMessageBrokerPublish(&broker,
        EVENT_WINDOW_MOVE, EventBody, &window_move);

    printf("\n");

    printf("RETAINED\n");

    printf("\n");

    pxMessageBrokerPublishQueue(&broker, &queue);

    window_close = (EventWindowClose) {.window = 1};

    pxMessageQueueInsert(&queue, &arena,
        EVENT_WINDOW_CLOSE, EventBody, &window_close);

    window_resize = (EventWindowResize) {
        .window = 1, .size_x = 10, .size_y = 156,
    };

    pxMessageQueueInsert(&queue, &arena,
        EVENT_WINDOW_RESIZE, EventBody, &window_resize);

    pxMessageBrokerDetach(&broker, EVENT_NONE, &timeHandler, &timer);

    printf("\n");

    printf("RETAINED\n");

    printf("\n");

    pxMessageBrokerPublishQueue(&broker, &queue);
}
