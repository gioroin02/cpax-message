#include "../export.h"
#include "../../memory/export.h"

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

typedef struct Entity
{
    PxString8 name;
    pxuword   code;
}
Entity;

void
jsonWriteEntity(Entity* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriterNext(writer, arena, pxJsonEventObjectOpen());

    pxJsonWriterNext(writer, arena,
        pxJsonEventString(self->name, pxs8("name")));

    pxJsonWriterNext(writer, arena,
        pxJsonEventUnsigned(self->code, pxs8("code")));

    pxJsonWriterNext(writer, arena, pxJsonEventObjectClose());
}

void
showJsonEvent(PxJsonReader* reader, PxArena* arena)
{
    PxJsonEvent event = pxJsonEventNone();

    while (event.type != PX_JSON_EVENT_COUNT) {
        event = pxJsonReaderNext(reader, arena);

        if (event.type == PX_JSON_EVENT_COUNT) break;

        switch (event.type) {
            case PX_JSON_EVENT_ERROR: {
                PxString8 message = event.error.message;
                PxString8 subject = event.error.subject;

                printf(RED("%.*s: %.*s"),
                    pxCast(int, message.length), message.memory,
                    pxCast(int, subject.length), subject.memory);

                event.type = PX_JSON_EVENT_COUNT;
            } break;

            case PX_JSON_EVENT_OBJECT_OPEN:
                printf("OBJECT_OPEN");
            break;

            case PX_JSON_EVENT_OBJECT_CLOSE:
                printf("OBJECT_CLOSE");
            break;

            case PX_JSON_EVENT_ARRAY_OPEN:
                printf("ARRAY_OPEN");
            break;

            case PX_JSON_EVENT_ARRAY_CLOSE:
                printf("ARRAY_CLOSE");
            break;

            case PX_JSON_EVENT_NAME:
                printf(AZURE("%.*s"), pxCast(int, event.name.length),
                    event.name.memory);
            break;

            case PX_JSON_EVENT_STRING: {
                if (event.name.length > 0) {
                    printf(AZURE("'%.*s'") ": ", pxCast(int, event.name.length),
                        event.name.memory);
                }

                printf(BLUE("'%.*s'"),
                    pxCast(int, event.svalue.length), event.svalue.memory);
            } break;

            case PX_JSON_EVENT_UNSIGNED: {
                if (event.name.length > 0) {
                    printf(AZURE("'%.*s'") ": ", pxCast(int, event.name.length),
                        event.name.memory);
                }

                printf(PURPLE("%llu"), event.uvalue);
            } break;

            case PX_JSON_EVENT_INTEGER: {
                if (event.name.length > 0) {
                    printf(AZURE("'%.*s'") ": ", pxCast(int, event.name.length),
                        event.name.memory);
                }

                printf(PURPLE("%lli"), event.ivalue);
            } break;

            case PX_JSON_EVENT_FLOATING: {
                if (event.name.length > 0) {
                    printf(AZURE("'%.*s'") ": ", pxCast(int, event.name.length),
                        event.name.memory);
                }

                printf(PURPLE("%lf"), event.fvalue);
            } break;

            case PX_JSON_EVENT_BOOLEAN: {
                if (event.name.length > 0) {
                    printf(AZURE("'%.*s'") ": ", pxCast(int, event.name.length),
                        event.name.memory);
                }

                printf("%s", event.bvalue != 0 ? GREEN("true") : RED("false"));
            } break;

            default: break;
        }

        printf("\n");
    }
}

int
main(int argc, char** argv)
{
    PxArena   arena  = pxMemoryReserve(16);
    PxBuffer8 source = pxBuffer8Reserve(&arena, 256);
    PxBuffer8 buffer = pxBuffer8Reserve(&arena, 256);

    PxJsonWriter writer = pxJsonWriterMake(&arena, 16,
        pxBufferWriter(&source, &buffer));

    jsonWriteEntity(&(Entity) {.name = pxs8("gio"), .code = 156}, &writer, &arena);

    printf(YELLOW("[start]") "\n%.*s\n" YELLOW("[stop]") "\n",
        pxCast(int, source.size), source.memory);

    printf("\n");

    pxBuffer8Clear(&buffer);

    PxJsonReader reader = pxJsonReaderMake(&arena, 16,
        pxBufferReader(&source, &buffer));

    showJsonEvent(&reader, &arena);
}
