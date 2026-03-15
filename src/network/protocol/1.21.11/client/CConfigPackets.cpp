#include <memory>
#include <sys/types.h>
#include "../../../PacketSender.h"
#include "../../ClientPackets.h"


namespace Network {
    namespace ClientPackets {
        // configuration packets the client can send

        // 0 = peaceful, 1 = easy, 2 = normal, 3 = hard
        void changeDifficulty(std::shared_ptr<Connection> con, int difficulty){
            Packet packet;
            packet.writeVarInt(0x03);
            packet.writeByte(difficulty);
            PacketSender::send(std::make_shared<Packet>(packet));
        }

 
    }


}