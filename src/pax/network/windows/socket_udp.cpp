#ifndef PAX_NETWORK_WINDOWS_SOCKET_UDP_CPP
#define PAX_NETWORK_WINDOWS_SOCKET_UDP_CPP

#include "socket_udp.hpp"

#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOMINMAX

#include <winsock2.h>
#include <ws2tcpip.h>

namespace pax {

#define SOCK4_SIZE pax_size_of(Sock4)
#define SOCK6_SIZE pax_size_of(Sock6)
#define SOCK_SIZE  pax_size_of(Sock_Storage)

#define SOCK(self) pax_cast(Sock_Address*, self)

#define SOCK4(self)      pax_cast(Sock4*, self)
#define SOCK4_PORT(self) pax_cast(u16*, &SOCK4(self)->sin_port)
#define SOCK4_ADDR(self) pax_cast(u8*, &SOCK4(self)->sin_addr.s_addr)

#define SOCK6(self)      pax_cast(Sock6*, self)
#define SOCK6_PORT(self) pax_cast(u16*, &SOCK6(self)->sin6_port)
#define SOCK6_ADDR(self) pax_cast(u8*, SOCK6(self)->sin6_addr.s6_addr)

using Sock_Address = struct sockaddr;
using Sock_Storage = struct sockaddr_storage;
using Sock4        = struct sockaddr_in;
using Sock6        = struct sockaddr_in6;

struct Windows_Socket_UDP
{
    SOCKET       handle  = INVALID_SOCKET;
    Sock_Storage address = {};
};

Windows_Socket_UDP*
windows_socket_udp_create(Arena* arena, Address_Kind kind)
{
    uptr offset = arena_offset(arena);
    uptr family = 0;

    switch (kind) {
        case ADDRESS_KIND_IP4: { family = AF_INET;  } break;
        case ADDRESS_KIND_IP6: { family = AF_INET6; } break;

        default: return 0;
    }

    Windows_Socket_UDP* result = arena_reserve_one<Windows_Socket_UDP>(arena);

    if (result != 0) {
        result->handle  = socket(family, SOCK_DGRAM, 0);
        result->address = {};

        if (result->handle != INVALID_SOCKET)
            return result;

        arena_rewind(arena, offset);
    }

    return 0;
}

void
windows_socket_udp_destroy(Windows_Socket_UDP* self)
{
    if (self == 0) return;

    if (self->handle != INVALID_SOCKET)
        closesocket(self->handle);

    self->handle  = INVALID_SOCKET;
    self->address = {};
}

Address
windows_socket_udp_get_address(Windows_Socket_UDP* self)
{
    Address result = {};

    switch (self->address.ss_family) {
        case AF_INET: {
            mem8_copy(result.ip4.memory, SOCK4_ADDR(&self->address),
                ADDRESS_IP4_GROUPS);

            result.kind = ADDRESS_KIND_IP4;
        } break;

        case AF_INET6: {
            mem16_copy(result.ip6.memory, SOCK6_ADDR(&self->address),
                ADDRESS_IP6_GROUPS);

            result.kind = ADDRESS_KIND_IP6;
        } break;

        default: break;
    }

    return result;
}

u16
windows_socket_udp_get_port(Windows_Socket_UDP* self)
{
    u16 port = 0;

    switch (self->address.ss_family) {
        case AF_INET:  {
            port = *SOCK4_PORT(&self->address);
        } break;

        case AF_INET6: {
            port = *SOCK6_PORT(&self->address);
        } break;

        default: break;
    }

    return u16_host_from_net(port);
}

b32
windows_socket_udp_bind(Windows_Socket_UDP* self, u16 port, Address address)
{
    Sock_Storage storage = {};
    i32          payload = 0;

    switch (address.kind) {
        case ADDRESS_KIND_IP4: {
            port = u16_net_from_host(port);

            mem16_copy(SOCK4_PORT(&storage), &port, 1);

            mem8_copy(SOCK4_ADDR(&storage), address.ip4.memory,
                ADDRESS_IP4_GROUPS);

            storage.ss_family = AF_INET;
            payload           = SOCK4_SIZE;
        } break;

        case ADDRESS_KIND_IP6: {
            port = u16_net_from_host(port);

            mem16_copy(SOCK6_PORT(&storage), &port, 1);

            mem16_copy(SOCK6_ADDR(&storage), address.ip6.memory,
                ADDRESS_IP6_GROUPS);

            storage.ss_family = AF_INET6;
            payload           = SOCK6_SIZE;
        } break;

        default: return 0;
    }

    if (bind(self->handle, SOCK(&storage), payload) == SOCKET_ERROR)
        return 0;

    self->address = storage;

    return 1;
}

b32
windows_socket_udp_listen(Windows_Socket_UDP* self)
{
    if (listen(self->handle, SOMAXCONN) == SOCKET_ERROR)
        return 0;

    return 1;
}

b32
windows_socket_udp_connect(Windows_Socket_UDP* self, u16 port, Address address)
{
    Sock_Storage storage = {};
    i32          payload = 0;

    switch (address.kind) {
        case ADDRESS_KIND_IP4: {
            port = u16_net_from_host(port);

            mem16_copy(SOCK4_PORT(&storage), &port, 1);

            mem8_copy(SOCK4_ADDR(&storage), address.ip4.memory,
                ADDRESS_IP4_GROUPS);

            storage.ss_family = AF_INET;
            payload           = SOCK4_SIZE;
        } break;

        case ADDRESS_KIND_IP6: {
            port = u16_net_from_host(port);

            mem16_copy(SOCK6_PORT(&storage), &port, 1);

            mem16_copy(SOCK6_ADDR(&storage), address.ip6.memory,
                ADDRESS_IP6_GROUPS);

            storage.ss_family = AF_INET6;
            payload           = SOCK6_SIZE;
        } break;

        default: return 0;
    }

    if (connect(self->handle, SOCK(&storage), payload) == SOCKET_ERROR)
        return 0;

    return 1;
}

Windows_Socket_UDP*
windows_socket_udp_accept(Windows_Socket_UDP* self, Arena* arena)
{
    uptr offset = arena_offset(arena);

    Windows_Socket_UDP* result = arena_reserve_one<Windows_Socket_UDP>(arena);

    if (result != 0) {
        Sock_Storage storage = {};
        i32          payload = SOCK_SIZE;

        result->handle  = accept(self->handle, SOCK(&storage), &payload);
        result->address = storage;

        if (result->handle != INVALID_SOCKET)
            return result;

        arena_rewind(arena, offset);
    }

    return 0;
}

b32
windows_socket_udp_write(Windows_Socket_UDP* self, buf8* buffer)
{
    u8*  memory = buffer->memory + buffer->head;
    uptr length = buffer->size;

    b32 state = 0;

    if (buffer->head > buffer->tail) {
        memory = buffer->memory + buffer->head;
        length = buffer->length - buffer->head;

        state = windows_socket_udp_write_mem8(self, memory, length);

        if (state != 0) {
            buffer->size -= length;
            buffer->head  = (buffer->head + length) % buffer->length;
        } else
            return 0;

        memory = buffer->memory + buffer->head;
        length = buffer->size;
   }

    if (length != 0) {
        state = windows_socket_udp_write_mem8(self, memory, length);

        if (state != 0) {
            buffer->size = 0;
            buffer->head = 0;
            buffer->tail = 0;
        }
    }

    return state;
}

b32
windows_socket_udp_write_to(Windows_Socket_UDP* self, buf8* buffer, u16 port, Address address)
{
    u8*  memory = buffer->memory + buffer->head;
    uptr length = buffer->size;

    b32 state = 0;

    if (buffer->head > buffer->tail) {
        memory = buffer->memory + buffer->head;
        length = buffer->length - buffer->head;

        state = windows_socket_udp_write_mem8_to(self, memory, length, port, address);

        if (state != 0) {
            buffer->size -= length;
            buffer->head  = (buffer->head + length) % buffer->length;
        } else
            return 0;

        memory = buffer->memory + buffer->head;
        length = buffer->size;
   }

    if (length != 0) {
        state = windows_socket_udp_write_mem8_to(self, memory, length, port, address);

        if (state != 0) {
            buffer->size = 0;
            buffer->head = 0;
            buffer->tail = 0;
        }
    }

    return state;
}

b32
windows_socket_udp_write_mem8(Windows_Socket_UDP* self, u8* memory, uptr length)
{
    uptr result = 0;
    uptr temp   = 0;

    for (uptr i = 0; i < length; i += temp) {
        i8* mem = pax_cast(i8*, memory + i);
        i32 len = pax_cast(i32, length - i);

        temp = send(self->handle, mem, len, 0);

        if (temp == 0) return 0;
    }

    return 1;
}

b32
windows_socket_udp_write_mem8_to(Windows_Socket_UDP* self, u8* memory, uptr length, u16 port, Address address)
{
    Sock_Storage storage = {};
    i32          payload = 0;

    switch (address.kind) {
        case ADDRESS_KIND_IP4: {
            port = u16_net_from_host(port);

            mem16_copy(SOCK4_PORT(&storage), &port, 1);

            mem8_copy(SOCK4_ADDR(&storage), address.ip4.memory,
                ADDRESS_IP4_GROUPS);

            storage.ss_family = AF_INET;
            payload           = SOCK4_SIZE;
        } break;

        case ADDRESS_KIND_IP6: {
            port = u16_net_from_host(port);

            mem16_copy(SOCK6_PORT(&storage), &port, 1);

            mem16_copy(SOCK6_ADDR(&storage), address.ip6.memory,
                ADDRESS_IP6_GROUPS);

            storage.ss_family = AF_INET6;
            payload           = SOCK6_SIZE;
        } break;

        default: return 0;
    }

    uptr result = 0;
    uptr temp   = 0;

    for (uptr i = 0; i < length; i += temp) {
        i8* mem = pax_cast(i8*, memory + i);
        i32 len = pax_cast(i32, length - i);

        temp = sendto(self->handle, mem, len, 0, SOCK(&storage), payload);

        if (temp == 0) return 0;
    }

    return 1;
}

b32
windows_socket_udp_read(Windows_Socket_UDP* self, buf8* buffer)
{
    u8*  memory = buffer->memory + buffer->tail;
    uptr length = buffer->length - buffer->size;

    b32  state = 0;
    uptr size  = 0;

    if (buffer->head < buffer->tail) {
        memory = buffer->memory + buffer->tail;
        length = buffer->length - buffer->tail;

        state = windows_socket_udp_read_mem8(self, memory, length, &size);

        if (state != 0) {
            buffer->size += size;
            buffer->tail  = (buffer->tail + size) % buffer->length;
        } else
            return 0;

        if (size < length) return 1;

        memory = buffer->memory + buffer->tail;
        length = buffer->length - buffer->size;
    }

    if (length != 0) {
        state = windows_socket_udp_read_mem8(self, memory, length, &size);

        if (state != 0) {
            buffer->size += size;
            buffer->tail  = (buffer->tail + size) % buffer->length;
        }
    }

    return 1;
}

b32
windows_socket_udp_read_from(Windows_Socket_UDP* self, buf8* buffer, u16* port, Address* address)
{
    u8*  memory = buffer->memory + buffer->tail;
    uptr length = buffer->length - buffer->size;

    b32  state = 0;
    uptr size  = 0;

    if (buffer->head > buffer->tail) buf8_normalize(buffer);

    if (length != 0) {
        state = windows_socket_udp_read_mem8_from(self, memory, length, &size, port, address);

        if (state != 0) {
            buffer->size += size;
            buffer->tail  = (buffer->tail + size) % buffer->length;
        }
    }

    return 1;
}

b32
windows_socket_udp_read_mem8(Windows_Socket_UDP* self, u8* memory, uptr length, uptr* size)
{
    i8* mem = pax_cast(i8*, memory);
    i32 len = pax_cast(i32, length);

    uptr result = recv(self->handle, mem, len, 0);

    if (result <= length) {
        if (size != 0)
            *size = result;

        return 1;
    }

    return 0;
}

b32
windows_socket_udp_read_mem8_from(Windows_Socket_UDP* self, u8* memory, uptr length, uptr* size, u16* port, Address* address)
{
    Sock_Storage storage = {};
    i32          payload = SOCK_SIZE;

    i8* mem = pax_cast(i8*, memory);
    i32 len = pax_cast(i32, length);

    uptr result = recvfrom(self->handle, mem, len, 0, SOCK(&storage), &payload);

    if (result > length) return 0;

    switch (storage.ss_family) {
        case AF_INET: {
            if (port != 0)
                mem_copy_host_from_net(port, SOCK4_PORT(&storage), U16_SIZE);

            if (address != 0) {
                address->kind = ADDRESS_KIND_IP4;

                mem8_copy(address->ip4.memory, SOCK4_ADDR(&storage),
                    ADDRESS_IP4_GROUPS);
            }
        } break;

        case AF_INET6: {
            if (port != 0)
                mem_copy_host_from_net(port, SOCK6_PORT(&storage), U16_SIZE);

            if (address != 0) {
                address->kind = ADDRESS_KIND_IP6;

                mem16_copy(address->ip6.memory, SOCK6_ADDR(&storage),
                    ADDRESS_IP6_GROUPS);
            }
        } break;

        default: return 0;
    }

    if (size != 0) *size = result;

    return 1;
}

} // namespace pax

#endif // PAX_NETWORK_WINDOWS_SOCKET_UDP_CPP
