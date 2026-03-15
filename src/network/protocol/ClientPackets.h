#ifndef CLIENTPACKETS_H_INCLUDED
#define CLIENTPACKETS_H_INCLUDED


#include "../Connection.h"
#include "../Packet.h"
#include <memory>

namespace Network {
    namespace ClientPackets {
        void handShake(std::shared_ptr<Connection> con, std::string ip, uint16_t port);
        void loginStart(std::shared_ptr<Connection> con, std::string name, std::string uuid);
        void loginAcknowledged(std::shared_ptr<Connection> con);
        void keepAlive(std::shared_ptr<Connection> con, int64_t id);
        void playerLoaded(std::shared_ptr<Connection> con);
        void syncPlayerPos(std::shared_ptr<Connection> con, int64_t id);
        void changeDifficulty(std::shared_ptr<Connection> con, int difficulty);
    }
}




















#endif