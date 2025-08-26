#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxByteOrder order = pxByteOrder();

    switch (order) {
        case PX_BYTE_ORDER_NETWORK:
            printf("Network\n");
        break;

        case PX_BYTE_ORDER_REVERSE:
            printf("Reverse\n");
        break;

        default:
            printf("Error\n");
        break;
    }
}
