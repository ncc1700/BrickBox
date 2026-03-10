#ifndef MCPROTOCOL_H_INCLUDED
#define PROTOCOL_H_INCLUDED


#include "../Connection.h"


namespace MCProtocol {
    void HandShake(Connection *con, std::string ip, uint16_t port);
    void LoginStart(Connection *con, std::string name, std::string uuid);
    uint8_t LoginSuccess(Connection* con);
}























#endif