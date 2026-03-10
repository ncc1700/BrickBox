#include "../MCProtocol.h"
#include "../../Packet.h"
#include <string_view>
#include <sys/types.h>


namespace MCProtocol {
    void HandShake(Connection *con, std::string ip, uint16_t port){
        Packet packet;
        packet.writeVarInt(0x00);
        packet.writeVarInt(774);
        packet.writeString(ip, 255);
        packet.writeU16(port);
        packet.writeVarInt(2);
        packet.sendPacket(con);
    }
    void LoginStart(Connection *con, std::string name, std::string uuid){
        Packet packet;
        packet.writeVarInt(0x00);
        packet.writeString(name, 16);
        packet.writeU64(0);
        packet.writeU64(0);
        packet.sendPacket(con);
    }
    uint8_t LoginSuccess(Connection* con){
        // 0 is success
        // 1 is that we couldn't read all of them
        Packet packet;
        int packetSize = con->readVarInt();
        packet.vec.resize(packetSize);
        ssize_t read = con->receive(packet.vec.data(), packetSize);
        if(packetSize > read){
            return 1;
        }
        int protocol = packet.readVarInt();
        if(protocol == 0x03){
            printf("Server acknowledged our login\n");
        } 
        return 0;
    }
}


