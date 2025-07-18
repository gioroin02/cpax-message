#ifndef PAX_NETWORK_WINDOWS_SOCKET_UDP_HPP
#define PAX_NETWORK_WINDOWS_SOCKET_UDP_HPP

#include "imports.hpp"

namespace pax {

//
// Types
//

struct Windows_Socket_UDP;

//
// Procs
//

/* Windows_Socket_UDP */

Windows_Socket_UDP*
windows_socket_udp_create(Arena* arena, Address_Kind kind);

void
windows_socket_udp_destroy(Windows_Socket_UDP* self);

Address
windows_socket_udp_get_address(Windows_Socket_UDP* self);

u16
windows_socket_udp_get_port(Windows_Socket_UDP* self);

b32
windows_socket_udp_bind(Windows_Socket_UDP* self, u16 port, Address address);

b32
windows_socket_udp_listen(Windows_Socket_UDP* self);

b32
windows_socket_udp_connect(Windows_Socket_UDP* self, u16 port, Address address);

Windows_Socket_UDP*
windows_socket_udp_accept(Windows_Socket_UDP* self, Arena* arena);

b32
windows_socket_udp_write(Windows_Socket_UDP* self, buf8* buffer);

b32
windows_socket_udp_write_to(Windows_Socket_UDP* self, buf8* buffer, u16 port, Address address);

b32
windows_socket_udp_write_mem8(Windows_Socket_UDP* self, u8* memory, uptr length);

b32
windows_socket_udp_write_mem8_to(Windows_Socket_UDP* self, u8* memory, uptr length, u16 port, Address address);

b32
windows_socket_udp_read(Windows_Socket_UDP* self, buf8* buffer);

b32
windows_socket_udp_read_from(Windows_Socket_UDP* self, buf8* buffer, u16* port, Address* address);

b32
windows_socket_udp_read_mem8(Windows_Socket_UDP* self, u8* memory, uptr length, uptr* size);

b32
windows_socket_udp_read_mem8_from(Windows_Socket_UDP* self, u8* memory, uptr length, uptr* size, u16* port, Address* address);

} // namespace pax

#endif // PAX_NETWORK_WINDOWS_SOCKET_UDP_HPP
