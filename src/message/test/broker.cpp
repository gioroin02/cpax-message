#include "../exports.hpp"

#include "../../pax/memory/exports.hpp"
#include "../../pax/string/exports.hpp"

using namespace pax;

#include <stdio.h>

enum Event_Type
{
    EVENT_NONE,
    EVENT_WINDOW_CLOSE,
    EVENT_WINDOW_RESIZE,
    EVENT_WINDOW_MOVE,
};

struct Event_Window_Close
{
    uptr tick = 0;
};

struct Event_Window_Resize
{
    uptr tick   = 0;
    uptr size_x = 0;
    uptr size_y = 0;
};

struct Event_Window_Move
{
    uptr tick     = 0;
    uptr coords_x = 0;
    uptr coords_y = 0;
};

union Event
{
    Event_Window_Close  window_close;
    Event_Window_Resize window_resize;
    Event_Window_Move   window_move;
};

struct Timer
{
    uptr tick = 0;
};

static const str8 EVENT_NAMES[] =
{
    pax_to_str8(EVENT_NONE),
    pax_to_str8(EVENT_WINDOW_CLOSE),
    pax_to_str8(EVENT_WINDOW_RESIZE),
    pax_to_str8(EVENT_WINDOW_MOVE),
};

void
handle_time(Event message, uptr type, Timer* self)
{
    self->tick += 1;

    str8 name = EVENT_NAMES[type];

    printf("    \x1b[31mTIME\x1b[0m | type = \x1b[34m'%.*s'\x1b[0m, time = %llu\n",
        pax_cast(int, name.length), name.memory, self->tick);

    switch (type) {
        case EVENT_WINDOW_CLOSE: {
            printf("    tick: %llu\n", message.window_close.tick);
        } break;

        case EVENT_WINDOW_RESIZE: {
            printf("    tick: %llu, size_x: %llu, size_y: %llu\n", message.window_resize.tick,
                message.window_resize.size_x, message.window_resize.size_y);
        } break;

        case EVENT_WINDOW_MOVE: {
            printf("    tick: %llu, coords_x: %llu, coords_y: %llu\n", message.window_move.tick,
                message.window_move.coords_x, message.window_move.coords_y);
        } break;

        default: break;
    }
}

void
handle_gameplay(Event message, uptr type)
{
    str8 name = EVENT_NAMES[type];

    printf("\x1b[32mGAMEPLAY\x1b[0m | type = \x1b[34m'%.*s'\x1b[0m\n",
        pax_cast(int, name.length), name.memory);

    switch (type) {
        case EVENT_WINDOW_CLOSE: {
            printf("    tick: %llu\n", message.window_close.tick);
        } break;

        case EVENT_WINDOW_RESIZE: {
            printf("    tick: %llu, size_x: %llu, size_y: %llu\n", message.window_resize.tick,
                message.window_resize.size_x, message.window_resize.size_y);
        } break;

        case EVENT_WINDOW_MOVE: {
            printf("    tick: %llu, coords_x: %llu, coords_y: %llu\n", message.window_move.tick,
                message.window_move.coords_x, message.window_move.coords_y);
        } break;

        default: break;
    }
}

void
handle_graphics(Event message, uptr type)
{
    str8 name = EVENT_NAMES[type];

    printf("\x1b[33mGRAPHICS\x1b[0m | type = \x1b[34m'%.*s'\x1b[0m\n",
        pax_cast(int, name.length), name.memory);

    switch (type) {
        case EVENT_WINDOW_CLOSE: {
            printf("    tick: %llu\n", message.window_close.tick);
        } break;

        case EVENT_WINDOW_RESIZE: {
            printf("    tick: %llu, size_x: %llu, size_y: %llu\n", message.window_resize.tick,
                message.window_resize.size_x, message.window_resize.size_y);
        } break;

        case EVENT_WINDOW_MOVE: {
            printf("    tick: %llu, coords_x: %llu, coords_y: %llu\n", message.window_move.tick,
                message.window_move.coords_x, message.window_move.coords_y);
        } break;

        default: break;
    }
}

int
main(int argc, char** argv)
{
    Arena arena = system_reserve(16);

    Broker<Event> broker = broker_reserve<Event>(&arena, 256, 256);

    Timer timer = {};

    timer.tick = 256;

    broker_attach(&broker, 0, &handle_time, &timer);

    broker_attach_simple(&broker, EVENT_WINDOW_CLOSE, &handle_gameplay);
    broker_attach_simple(&broker, EVENT_WINDOW_RESIZE, &handle_graphics);

    Event window_close = {
        .window_close = {.tick = timer.tick}
    };

    Event window_resize = {
        .window_resize = {.tick = timer.tick, .size_x = 10, .size_y = 156},
    };

    Event window_move = {
        .window_move = {.tick = timer.tick, .coords_x = 34, .coords_y = 345},
    };

    broker_retain(&broker, EVENT_WINDOW_CLOSE,  window_close);
    broker_retain(&broker, EVENT_WINDOW_RESIZE, window_resize);
    broker_retain(&broker, EVENT_WINDOW_MOVE,   window_move);

    broker_notify(&broker);
}
