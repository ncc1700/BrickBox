#ifndef MCPROTOCOL_H_INCLUDED
#define MCPROTOCOL_H_INCLUDED


#include "../Connection.h"
#include "../Packet.h"
#include <memory>
#include "ClientPackets.h"
#include "ServerPackets.h"
namespace Network {
    void registerCallbacks();
    int8_t handleCallback(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet, int id);
}




















#endif