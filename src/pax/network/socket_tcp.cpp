#ifndef PAX_NETWORK_SOCKET_TCP_CPP
#define PAX_NETWORK_SOCKET_TCP_CPP

#include "socket_tcp.hpp"

#if PAX_PLATFORM == PAX_PLATFORM_WINDOWS

    #include "windows/socket_tcp.cpp"

    #define __Socket_TCP__ Windows_Socket_TCP

    #define __socket_tcp_create__      windows_socket_tcp_create
    #define __socket_tcp_destroy__     windows_socket_tcp_destroy
    #define __socket_tcp_get_address__ windows_socket_tcp_get_address
    #define __socket_tcp_get_port__    windows_socket_tcp_get_port
    #define __socket_tcp_bind__        windows_socket_tcp_bind
    #define __socket_tcp_listen__      windows_socket_tcp_listen
    #define __socket_tcp_connect__     windows_socket_tcp_connect
    #define __socket_tcp_accept__      windows_socket_tcp_accept
    #define __socket_tcp_write__       windows_socket_tcp_write
    #define __socket_tcp_write_mem8__  windows_socket_tcp_write_mem8
    #define __socket_tcp_read__        windows_socket_tcp_read
    #define __socket_tcp_read_mem8__   windows_socket_tcp_read_mem8

#else

    #error "Platform not supported or unknown"

#endif

#define pax_socket_tcp(self) pax_cast(__Socket_TCP__*, self)

namespace pax {

Socket_TCP
socket_tcp_create(Arena* arena, Address_Kind kind)
{
    return __socket_tcp_create__(arena, kind);
}

void
socket_tcp_destroy(Socket_TCP self)
{
    __socket_tcp_destroy__(pax_socket_tcp(self));
}

Address
socket_tcp_get_address(Socket_TCP self)
{
    return __socket_tcp_get_address__(pax_socket_tcp(self));
}

u16
socket_tcp_get_port(Socket_TCP self)
{
    return __socket_tcp_get_port__(pax_socket_tcp(self));
}

b32
socket_tcp_bind(Socket_TCP self, u16 port, Address address)
{
    return __socket_tcp_bind__(pax_socket_tcp(self), port, address);
}

b32
socket_tcp_listen(Socket_TCP self)
{
    return __socket_tcp_listen__(pax_socket_tcp(self));
}

b32
socket_tcp_connect(Socket_TCP self, u16 port, Address address)
{
    return __socket_tcp_connect__(pax_socket_tcp(self), port, address);
}

Socket_TCP
socket_tcp_accept(Socket_TCP self, Arena* arena)
{
    return __socket_tcp_accept__(pax_socket_tcp(self), arena);
}

b32
socket_tcp_write(Socket_TCP self, buf8* buffer)
{
    return __socket_tcp_write__(pax_socket_tcp(self), buffer);
}

b32
socket_tcp_write_mem8(Socket_TCP self, u8* memory, uptr length)
{
    return __socket_tcp_write_mem8__(pax_socket_tcp(self), memory, length);
}

b32
socket_tcp_read(Socket_TCP self, buf8* buffer)
{
    return __socket_tcp_read__(pax_socket_tcp(self), buffer);
}

b32
socket_tcp_read_mem8(Socket_TCP self, u8* memory, uptr length, uptr* size)
{
    return __socket_tcp_read_mem8__(pax_socket_tcp(self), memory, length, size);
}

} // namespace pax

#endif // PAX_NETWORK_SOCKET_TCP_CPP
