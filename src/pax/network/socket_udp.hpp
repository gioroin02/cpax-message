#ifndef PAX_NETWORK_SOCKET_UDP_HPP
#define PAX_NETWORK_SOCKET_UDP_HPP

#include "address.hpp"

namespace pax {

//
// Types
//

using Socket_UDP = addr;

//
// Procs
//

/* Socket_UDP */

Socket_UDP
socket_udp_create(Arena* arena, Address_Kind kind);

void
socket_udp_destroy(Socket_UDP self);

b32
socket_udp_bind(Socket_UDP self, u16 port, Address address);

b32
socket_udp_listen(Socket_UDP self);

b32
socket_udp_connect(Socket_UDP self, u16 port, Address address);

Socket_UDP
socket_udp_accept(Socket_UDP self, Arena* arena);

b32
socket_udp_write(Socket_UDP self, buf8* buffer);

b32
socket_udp_write_to(Socket_UDP self, buf8* buffer, u16 port, Address address);

b32
socket_udp_write_mem8(Socket_UDP self, u8* memory, uptr length);

b32
socket_udp_write_mem8_to(Socket_UDP self, u8* memory, uptr length, u16 port, Address address);

b32
socket_udp_read(Socket_UDP self, buf8* buffer);

b32
socket_udp_read_from(Socket_UDP self, buf8* buffer, u16* port, Address *address);

b32
socket_udp_read_mem8(Socket_UDP* self, u8* memory, uptr length, uptr* size);

b32
socket_udp_read_mem8_from(Socket_UDP self, u8* memory, uptr length, uptr* size, u16* port, Address* address);

} // namespace pax

#endif // PAX_NETWORK_SOCKET_UDP_HPP
