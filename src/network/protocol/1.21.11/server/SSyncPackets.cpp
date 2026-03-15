#include <cstdio>
#include <memory>
#include "../../ClientPackets.h"
#include "../../../PacketSender.h"

namespace Network {
    namespace ServerPackets {

        int8_t serverKeepAlive(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("Server wants to check up on us\n");
            PacketSender::send(packet);
            return 0;
        }

        int8_t playerAbilites(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("STUB: %s\n", __FUNCTION__);
            return 0;
        }

        int8_t updateRecipes(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("STUB: %s\n", __FUNCTION__);
            return 0;
        }

        int8_t commandsListed(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("STUB: %s\n", __FUNCTION__);
            return 0;
        }

        int8_t syncPlayerPos(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("Syncing player position\n");
            // do some syncing here artdev/jojo.....
            printf("synced, sending confirmation to server\n");
            int teleportId = packet->readVarInt();
            ClientPackets::syncPlayerPos(con, teleportId);
            // you can then do another packet if yall want with extra info
            // https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Player_Position_and_Rotation
            // ill just skip it for times sake
            return 0;
        }
        int8_t playerInfoUpdate(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("STUB: %s\n", __FUNCTION__);
            return 0;
        }

        int8_t syncWorldBorder(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("STUB: %s\n", __FUNCTION__);
            return 0;
        }

        int8_t updateTime(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("STUB: %s\n", __FUNCTION__);
            return 0;
        }

        int8_t setDefaultSpawnPos(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("STUB: %s\n", __FUNCTION__);
            return 0;
        }
        
        int8_t stepTick(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("STUB: %s\n", __FUNCTION__);
            return 0;
        }

        int8_t setCenterChunk(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("STUB: %s\n", __FUNCTION__);
            printf("center chunk x: %d, center chunk y: %d\n", packet->readVarInt(), packet->readVarInt());
            return 0;
        }

        int8_t chunkDataAndUpdateLight(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("for artdev, chunkdata and light\n");
            // inital parsing
            printf("chunk x: %d, chunk z: %d\n", packet->readU32(), packet->readU32());
            // ok heres ya data, you can see whats sent via
            // https://minecraft.wiki/w/Java_Edition_protocol/Packets#Chunk_Data_and_Update_Light

            // finally we send the final packet of the basic initialization
            // of the minecraft JE client
            ClientPackets::playerLoaded(con);
            return 0;
        }
    }
}
