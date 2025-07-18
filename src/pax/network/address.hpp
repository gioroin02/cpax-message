#ifndef PAX_NETWORK_ADDRESS_HPP
#define PAX_NETWORK_ADDRESS_HPP

#include "address_ip.hpp"

namespace pax {

//
// Types
//

enum Address_Kind
{
    ADDRESS_KIND_NONE,
    ADDRESS_KIND_IP4,
    ADDRESS_KIND_IP6,
};

struct Address
{
    Address_Kind kind = ADDRESS_KIND_NONE;

    union
    {
        Address_IP4 ip4;
        Address_IP6 ip6;
    };
};

//
// Procs
//

/* Address*/

Address
address_any(Address_Kind kind);

b32
address_is_equal(Address self, Address value);

/* Address parsing */

b32
address_from_str8(str8 self, Address_Kind kind, Address* value);

} // namespace pax

#endif // PAX_NETWORK_ADDRESS_HPP
