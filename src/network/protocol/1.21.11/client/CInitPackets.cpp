#include <memory>
#include <sys/types.h>
#include "../../../PacketSender.h"
#include "../../ClientPackets.h"


namespace Network {
    namespace ClientPackets {
        // initial packets for logging in
        void handShake(std::shared_ptr<Connection> con, std::string ip, uint16_t port){
            printf("handshake\n");
            Packet packet;
            packet.writeVarInt(0x00);
            packet.writeVarInt(774);
            packet.writeString(ip, 255);
            packet.writeU16(port);
            packet.writeVarInt(2);
            PacketSender::send(std::make_shared<Packet>(packet));
        }
        void loginStart(std::shared_ptr<Connection> con, std::string name, std::string uuid){
            printf("login start\n");
            Packet packet;
            packet.writeVarInt(0x00);
            packet.writeString(name, 16);
            packet.writeU64(0);
            packet.writeU64(0);
            PacketSender::send(std::make_shared<Packet>(packet));
        }
        void loginAcknowledged(std::shared_ptr<Connection> con){
            printf("login acknowledged\n");
            Packet packet;
            packet.writeVarInt(0x03);
            PacketSender::send(std::make_shared<Packet>(packet));
        }

        void playerLoaded(std::shared_ptr<Connection> con){
            printf("sending that initialization is successful and we can play!\n");
            Packet packet;
            packet.writeVarInt(0x2B);
            PacketSender::send(std::make_shared<Packet>(packet));
        }
    }


}