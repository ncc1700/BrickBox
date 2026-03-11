#ifndef MCPROTOCOL_H_INCLUDED
#define MCPROTOCOL_H_INCLUDED


#include "../Connection.h"
#include "../Packet.h"
#include <memory>
namespace Network {
    namespace MCProtocol {
        void handShake(Connection *con, std::string ip, uint16_t port);
        void loginStart(Connection *con, std::string name, std::string uuid);
        void loginAcknowledged(Connection* con);
        void clientKeepAlive(Connection* con, int64_t id);
        int8_t isLoginSuccess();
        void registerCallbacks();
        int8_t handleCallback(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet, int id);
    }
}




















#endif