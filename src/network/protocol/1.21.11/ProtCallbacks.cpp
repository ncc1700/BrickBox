#include "../MCProtocol.h"
#include <atomic>
#include <cstdint>
#include <functional>
#include <memory>
#include <unordered_map>
#include "../../Packet.h"
#include "../../PacketSender.h"


namespace Network {

    namespace MCProtocol {
        typedef std::function<int8_t(std::shared_ptr<Connection> con, std::shared_ptr<Packet>)> PacketHandlers;
        std::unordered_map<int, PacketHandlers> callbacks;
        static std::atomic_bool loginSuccess = false;

        static int8_t loginSuccessCallback(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            if(loginSuccess == true){
                // why are we sending this again?
                printf("ERROR: tried sending loginSuccess when its useless!\n");
                return -1;
            }
            printf("Server acknowledged our login\n");
            loginAcknowledged(con.get());
            loginSuccess = true;
            return 0;
        }

        static int8_t serverKeepAlive(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("Server wants to check up on us\n");
            PacketSender::send(packet);
            return 0;
        }
        static int8_t knownPacks(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            // for now, just return back whatever they send
            packet->vec[0] = 0x07;
            PacketSender::send(packet);
            return 0;
        }
        static int8_t finishConfig(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            PacketSender::send(packet);
            return 0;
        }
        int8_t isLoginSuccess(){
            return loginSuccess;
        }
        static int8_t changeDifficulty(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("STUB: %s", __FUNCTION__);
            // make server happy
            int difficulty = packet->readByte();
            Packet sentPacket;
            sentPacket.writeVarInt(0x03);
            sentPacket.writeByte(difficulty);
            PacketSender::send(std::make_shared<Packet>(sentPacket));
            return 0;
        }
        static int8_t playerAbilites(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("STUB: %s\n", __FUNCTION__);
            return 0;
        }
        static int8_t setHeldItem(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("STUB: %s\n", __FUNCTION__);
            return 0;
        }
        static int8_t updateRecipes(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("STUB: %s\n", __FUNCTION__);
            return 0;
        }
        static int8_t entityEvent(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("STUB: %s\n", __FUNCTION__);
            return 0;
        }
        static int8_t commandsListed(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("STUB: %s\n", __FUNCTION__);
            return 0;
        }
        static int8_t syncPlayerPos(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("Syncing player position\n");
            // do some syncing here artdev/jojo.....
            printf("synced, sending confirmation to server\n");
            int teleportId = packet->readVarInt();
            Packet sentPacket;
            sentPacket.writeVarInt(0x00);
            sentPacket.writeVarInt(teleportId);
            PacketSender::send(std::make_shared<Packet>(sentPacket));
            // you can then do another packet if yall want with extra info
            // https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Player_Position_and_Rotation
            // ill just skip it for times sake
            return 0;
        }
        static int8_t serverData(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("STUB: %s\n", __FUNCTION__);
            return 0;
        }
        static int8_t playerInfoUpdate(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("STUB: %s\n", __FUNCTION__);
            return 0;
        }
        static int8_t initWorldBorder(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("STUB: %s\n", __FUNCTION__);
            return 0;
        }
        static int8_t updateTime(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("STUB: %s\n", __FUNCTION__);
            return 0;
        }
        static int8_t setDefaultSpawnPos(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("STUB: %s\n", __FUNCTION__);
            return 0;
        }
        static int8_t gameEvent(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("STUB: %s\n", __FUNCTION__);
            return 0;
        }
        static int8_t setTickingState(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("STUB: %s\n", __FUNCTION__);
            return 0;
        }
        static int8_t stepTick(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("STUB: %s\n", __FUNCTION__);
            return 0;
        }
        static int8_t setCenterChunk(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("STUB: %s\n", __FUNCTION__);
            return 0;
        }
        static int8_t chunkDataAndUpdateLight(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("for artdev, chunkdata and light\n");
            // ok heres ya data, you can see whats sent via
            // https://minecraft.wiki/w/Java_Edition_protocol/Packets#Chunk_Data_and_Update_Light

            // finally we send the final packet of the basic initialization
            // of the minecraft JE client
            Packet loadedPacket;
            loadedPacket.writeVarInt(0x2B);
            PacketSender::send(std::make_shared<Packet>(loadedPacket));
            return 0;
        }
        void registerCallbacks(){
            // very messy =(
            callbacks[0x02] = loginSuccessCallback;
            callbacks[0x4] = serverKeepAlive;
            callbacks[0xE] = knownPacks;
            callbacks[0x3] = finishConfig;
            callbacks[0x0A] = changeDifficulty;
            callbacks[0x3E] = playerAbilites;
            callbacks[0x67] = setHeldItem; // SIX SEVEEEEEN
            callbacks[0x83] = updateRecipes;
            callbacks[0x22] = entityEvent;
            callbacks[0x10] = commandsListed;
            callbacks[0x46] = syncPlayerPos;
            callbacks[0x54] = serverData;
            callbacks[0x44] = playerInfoUpdate;
            callbacks[0x2A] = initWorldBorder;
            callbacks[0x6F] = updateTime;
            callbacks[0x5F] = setDefaultSpawnPos;
            callbacks[0x26] = gameEvent;
            callbacks[0x7D] = setTickingState;
            callbacks[0x7E] = stepTick;
            callbacks[0x5C] = setCenterChunk;
            callbacks[0x2C] = chunkDataAndUpdateLight;
        }   

        int8_t handleCallback(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet, int id){
            if(callbacks.count(id) == 0){
                printf("invalid packet\n");
                // we could kick the client here, or not
                return -1;
            }
            return callbacks[id](con, packet);
        }

        
    }
}