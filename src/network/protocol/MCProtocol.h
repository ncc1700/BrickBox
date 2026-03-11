#ifndef MCPROTOCOL_H_INCLUDED
#define MCPROTOCOL_H_INCLUDED


#include "../Connection.h"
#include "../Packet.h"
#include <memory>
namespace Network {
    namespace MCProtocol {
        void HandShake(Connection *con, std::string ip, uint16_t port);
        void LoginStart(Connection *con, std::string name, std::string uuid);
        uint8_t LoginSuccess(Connection* con);
        void LoginAcknowledged(Connection* con);
        uint8_t RegistryData(Connection* con);
        int8_t isLoginSuccess();
        void registerCallbacks();
        int8_t handleCallback(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet, int id);
    }
}




















#endif