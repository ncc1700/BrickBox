#include <cstdint>
#include <memory>
#include <sys/types.h>
#include "../../../PacketSender.h"
#include "../../ClientPackets.h"


namespace Network {
    namespace ClientPackets {
        // sync packets the client can send back to the server

        // doesn't work, don't use
        void keepAlive(std::shared_ptr<Connection>  con, int64_t id){
            printf("sending that we are alive\n");
            Packet packet;
            packet.writeVarInt(0x04);
            packet.writeU64(id);
            PacketSender::send(std::make_shared<Packet>(packet));
        }
        
        void syncPlayerPos(std::shared_ptr<Connection>  con, int64_t id){
            Packet packet;
            packet.writeVarInt(0x00);
            packet.writeVarInt(id);
            PacketSender::send(std::make_shared<Packet>(packet));
        }

 
    }


}