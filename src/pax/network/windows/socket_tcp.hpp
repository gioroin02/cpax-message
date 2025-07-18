#ifndef PAX_NETWORK_WINDOWS_SOCKET_TCP_HPP
#define PAX_NETWORK_WINDOWS_SOCKET_TCP_HPP

#include "imports.hpp"

namespace pax {

//
// Types
//

struct Windows_Socket_TCP;

//
// Procs
//

/* Windows_Socket_TCP */

Windows_Socket_TCP*
windows_socket_tcp_create(Arena* arena, Address_Kind kind);

void
windows_socket_tcp_destroy(Windows_Socket_TCP* self);

Address
windows_socket_tcp_get_address(Windows_Socket_TCP* self);

u16
windows_socket_tcp_get_port(Windows_Socket_TCP* self);

b32
windows_socket_tcp_bind(Windows_Socket_TCP* self, u16 port, Address address);

b32
windows_socket_tcp_listen(Windows_Socket_TCP* self);

b32
windows_socket_tcp_connect(Windows_Socket_TCP* self, u16 port, Address address);

Windows_Socket_TCP*
windows_socket_tcp_accept(Windows_Socket_TCP* self, Arena* arena);

b32
windows_socket_tcp_write(Windows_Socket_TCP* self, buf8* buffer);

b32
windows_socket_tcp_write_mem8(Windows_Socket_TCP* self, u8* memory, uptr length);

b32
windows_socket_tcp_read(Windows_Socket_TCP* self, buf8* buffer);

b32
windows_socket_tcp_read_mem8(Windows_Socket_TCP* self, u8* memory, uptr length, uptr* size);

} // namespace pax

#endif // PAX_NETWORK_WINDOWS_SOCKET_TCP_HPP
