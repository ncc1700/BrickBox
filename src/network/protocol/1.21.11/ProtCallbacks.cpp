#include "../MCProtocol.h"
#include <cstdint>
#include <functional>
#include <memory>
#include <unordered_map>
#include "../../Packet.h"


namespace Network {

    typedef std::function<int8_t(std::shared_ptr<Connection> con, std::shared_ptr<Packet>)> PacketHandlers;
    std::unordered_map<int, PacketHandlers> callbacks;
    
    void registerCallbacks(){
        // very messy =(
        callbacks[0x02] = ServerPackets::loginSuccessCallback;
        callbacks[0x4] = ServerPackets::serverKeepAlive;
        callbacks[0xE] = ServerPackets::knownPacks;
        callbacks[0x3] = ServerPackets::finishConfig;
        callbacks[0x0A] = ServerPackets::changeDifficulty;
        callbacks[0x3E] = ServerPackets::playerAbilites;
        callbacks[0x67] = ServerPackets::setHeldItem; // SIX SEVEEEEEN
        callbacks[0x83] = ServerPackets::updateRecipes;
        callbacks[0x22] = ServerPackets::entityEvent;
        callbacks[0x10] = ServerPackets::commandsListed;
        callbacks[0x46] = ServerPackets::syncPlayerPos;
        callbacks[0x54] = ServerPackets::serverData;
        callbacks[0x44] = ServerPackets::playerInfoUpdate;
        callbacks[0x2A] = ServerPackets::syncWorldBorder;
        callbacks[0x6F] = ServerPackets::updateTime;
        callbacks[0x5F] = ServerPackets::setDefaultSpawnPos;
        callbacks[0x26] = ServerPackets::gameEvent;
        callbacks[0x7D] = ServerPackets::setTickingState;
        callbacks[0x7E] = ServerPackets::stepTick;
        callbacks[0x5C] = ServerPackets::setCenterChunk;
        callbacks[0x2C] = ServerPackets::chunkDataAndUpdateLight;
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