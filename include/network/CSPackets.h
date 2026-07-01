#ifndef CSPACKETS_H_INCLUDED
#define CSPACKETS_H_INCLUDED





#include <BrickBox.h>
#include <network/Packet.h>

namespace Network {
    namespace CSPackets {
        Packet handshake(int32_t protocol, const char* ip, uint16_t port);
        Packet loginStart(const char* username);
        Packet acknowledgeLogin();
        Packet configSuccess();
    }
}






#endif
