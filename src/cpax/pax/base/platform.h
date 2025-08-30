#ifndef PX_BASE_PLATFORM_H
#define PX_BASE_PLATFORM_H

#define PX_WORD_NONE  0
#define PX_WORD_32    1
#define PX_WORD_64    2
#define PX_WORD_COUNT 3

#ifndef PX_WORD

    #if defined(_WIN64) || defined(__PL64__) || defined(__x86_64__) || defined(__amd64__) || defined(__aarch64__)

        #define PX_WORD PX_WORD_64

    #elif defined(_WIN32) || defined(__ILP32__) || defined(_i386_)

        #define PX_WORD PX_WORD_32

    #else

        #define PX_WORD PX_WORD_NONE

    #endif

#endif

#define PX_SYSTEM_NONE    0
#define PX_SYSTEM_WINDOWS 1
#define PX_SYSTEM_LINUX   2
#define PX_SYSTEM_MAX     3

#ifndef PX_SYSTEM

    #if defined(_WIN32)

        #define PX_SYSTEM PX_SYSTEM_WINDOWS

    #elif defined(__linux__)

        #define PX_SYSTEM PX_SYSTEM_LINUX

    #else

        #define PX_SYSTEM PX_SYSTEM_NONE

    #endif

#endif

#endif // PX_BASE_PLATFORM_H
