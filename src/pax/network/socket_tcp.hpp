#ifndef PAX_NETWORK_SOCKET_TCP_HPP
#define PAX_NETWORK_SOCKET_TCP_HPP

#include "address.hpp"

namespace pax {

//
// Types
//

using Socket_TCP = addr;

//
// Procs
//

/* Socket_TCP */

Socket_TCP
socket_tcp_create(Arena* arena, Address_Kind kind);

void
socket_tcp_destroy(Socket_TCP self);

Address
socket_tcp_get_address(Socket_TCP self);

u16
socket_tcp_get_port(Socket_TCP self);

b32
socket_tcp_bind(Socket_TCP self, u16 port, Address address);

b32
socket_tcp_listen(Socket_TCP self);

b32
socket_tcp_connect(Socket_TCP self, u16 port, Address address);

Socket_TCP
socket_tcp_accept(Socket_TCP self, Arena* arena);

b32
socket_tcp_write(Socket_TCP self, buf8* buffer);

b32
socket_tcp_write_mem8(Socket_TCP self, u8* memory, uptr length);

b32
socket_tcp_read(Socket_TCP self, buf8* buffer);

b32
socket_tcp_read_mem8(Socket_TCP self, u8* memory, uptr length, uptr* size);

} // namespace pax

#endif // PAX_NETWORK_SOCKET_TCP_HPP
