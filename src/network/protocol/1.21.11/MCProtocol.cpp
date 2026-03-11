#include "../MCProtocol.h"
#include "../../Packet.h"
#include <memory>
#include <sys/types.h>
#include "../../PacketSender.h"



namespace Network {
    namespace MCProtocol {
        // initial packets for logging in
        void handShake(Connection *con, std::string ip, uint16_t port){
            printf("handshake\n");
            Packet packet;
            packet.writeVarInt(0x00);
            packet.writeVarInt(774);
            packet.writeString(ip, 255);
            packet.writeU16(port);
            packet.writeVarInt(2);
            PacketSender::send(std::make_shared<Packet>(packet));
        }
        void loginStart(Connection *con, std::string name, std::string uuid){
            printf("login start\n");
            Packet packet;
            packet.writeVarInt(0x00);
            packet.writeString(name, 16);
            packet.writeU64(0);
            packet.writeU64(0);
            PacketSender::send(std::make_shared<Packet>(packet));
        }
        void loginAcknowledged(Connection* con){
            printf("login acknowledged\n");
            Packet packet;
            packet.writeVarInt(0x03);
            PacketSender::send(std::make_shared<Packet>(packet));
        }
    }


}