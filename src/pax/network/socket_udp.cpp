#ifndef PAX_NETWORK_SOCKET_UDP_CPP
#define PAX_NETWORK_SOCKET_UDP_CPP

#include "socket_udp.hpp"

#if PAX_PLATFORM == PAX_PLATFORM_WINDOWS

    #include "windows/socket_udp.cpp"

    #define __Socket_UDP__ Windows_Socket_UDP

    #define __socket_udp_create__         windows_socket_udp_create
    #define __socket_udp_destroy__        windows_socket_udp_destroy
    #define __socket_udp_bind__           windows_socket_udp_bind
    #define __socket_udp_listen__         windows_socket_udp_listen
    #define __socket_udp_connect__        windows_socket_udp_connect
    #define __socket_udp_accept__         windows_socket_udp_accept
    #define __socket_udp_write__          windows_socket_udp_write
    #define __socket_udp_write_to__       windows_socket_udp_write_to
    #define __socket_udp_write_mem8__     windows_socket_udp_write_mem8
    #define __socket_udp_write_mem8_to__  windows_socket_udp_write_mem8_to
    #define __socket_udp_read__           windows_socket_udp_read
    #define __socket_udp_read_from__      windows_socket_udp_read_from
    #define __socket_udp_read_mem8__      windows_socket_udp_read_mem8
    #define __socket_udp_read_mem8_from__ windows_socket_udp_read_mem8_from

#else

    #error "Platform not supported or unknown"

#endif

#define pax_socket_udp(self) pax_cast(__Socket_UDP__*, self)

namespace pax {

Socket_UDP
socket_udp_create(Arena* arena, Address_Kind kind)
{
    return __socket_udp_create__(arena, kind);
}

void
socket_udp_destroy(Socket_UDP self)
{
    __socket_udp_destroy__(pax_socket_udp(self));
}

b32
socket_udp_bind(Socket_UDP self, u16 port, Address address)
{
    return __socket_udp_bind__(pax_socket_udp(self), port, address);
}

b32
socket_udp_listen(Socket_UDP self)
{
    return __socket_udp_listen__(pax_socket_udp(self));
}

b32
socket_udp_connect(Socket_UDP self, u16 port, Address address)
{
    return __socket_udp_connect__(pax_socket_udp(self), port, address);
}

Socket_UDP
socket_udp_accept(Socket_UDP self, Arena* arena)
{
    return __socket_udp_accept__(pax_socket_udp(self), arena);
}

b32
socket_udp_write(Socket_UDP self, buf8* buffer)
{
    return __socket_udp_write__(pax_socket_udp(self), buffer);
}

b32
socket_udp_write_to(Socket_UDP self, buf8* buffer, u16 port, Address address)
{
    return __socket_udp_write_to__(pax_socket_udp(self), buffer, port, address);
}

b32
socket_udp_write_mem8(Socket_UDP self, u8* memory, uptr length)
{
    return __socket_udp_write_mem8__(pax_socket_udp(self), memory, length);
}

b32
socket_udp_write_mem8_to(Socket_UDP self, u8* memory, uptr length, u16 port, Address address)
{
    return __socket_udp_write_mem8_to__(pax_socket_udp(self), memory, length, port, address);
}

b32
socket_udp_read(Socket_UDP self, buf8* buffer)
{
    return __socket_udp_read__(pax_socket_udp(self), buffer);
}

b32
socket_udp_read_from(Socket_UDP self, buf8* buffer, u16* port, Address *address)
{
    return __socket_udp_read_from__(pax_socket_udp(self), buffer, port, address);
}

b32
socket_udp_read_mem8(Socket_UDP self, u8* memory, uptr length, uptr* size)
{
    return __socket_udp_read_mem8__(pax_socket_udp(self), memory, length, size);
}

b32
socket_udp_read_mem8_from(Socket_UDP self, u8* memory, uptr length, uptr* size, u16* port, Address *address)
{
    return __socket_udp_read_mem8_from__(pax_socket_udp(self), memory, length, size, port, address);
}

} // namespace pax

#endif // PAX_NETWORK_SOCKET_UDP_CPP
