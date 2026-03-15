#include <cstdio>
#include <memory>
#include "../../MCProtocol.h"
#include "../../../PacketSender.h"

namespace Network {
    namespace ServerPackets {

        int8_t knownPacks(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            // for now, just return back whatever they send
            packet->vec[0] = 0x07;
            PacketSender::send(packet);
            return 0;
        }

        int8_t changeDifficulty(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("STUB: %s", __FUNCTION__);
            // make server happy
            int difficulty = packet->readByte();
            ClientPackets::changeDifficulty(con, difficulty);
            return 0;
        }

        int8_t setHeldItem(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("STUB: %s\n", __FUNCTION__);
            return 0;
        }

        int8_t setTickingState(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("STUB: %s\n", __FUNCTION__);
            return 0;
        }
        

        int8_t finishConfig(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            PacketSender::send(packet);
            return 0;
        }
        
    }
}
