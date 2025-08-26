#ifndef PX_BASE_PLATFORM_H
#define PX_BASE_PLATFORM_H

#define PX_WORD_NONE  0
#define PX_WORD_32    1
#define PX_WORD_64    2
#define PX_WORD_COUNT 3

#ifndef PX_WORD

    #if _WIN64 || __PL64__ || __x86_64__ || __amd64__ || __aarch64__

        #define PX_WORD PX_WORD_64

    #elif _WIN32 || __ILP32__ || _i386_

        #define PX_WORD PX_WORD_32

    #else

        #define PX_WORD PX_WORD_NONE

    #endif

#endif

#define PX_SYSTEM_NONE    0
#define PX_SYSTEM_WINDOWS 1
#define PX_SYSTEM_MAX     2

#ifndef PX_SYSTEM

    #if _WIN32

        #define PX_SYSTEM PX_SYSTEM_WINDOWS

    #else

        #define PX_SYSTEM PX_SYSTEM_NONE

    #endif

#endif

#endif // PX_BASE_PLATFORM_H
