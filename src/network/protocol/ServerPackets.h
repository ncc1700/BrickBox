#ifndef SERVERPACKETS_H_INCLUDED
#define SERVERPACKETS_H_INCLUDED


#include "../Connection.h"
#include "../Packet.h"
#include <memory>

namespace Network {
    namespace ServerPackets {
        int8_t loginSuccessCallback(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet);
        int8_t knownPacks(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet);
        int8_t beginCompression(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet);
        int8_t changeDifficulty(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet);
        int8_t setHeldItem(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet);
        int8_t setTickingState(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet);
        int8_t finishConfig(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet);
        int8_t serverKeepAlive(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet);
        int8_t playerAbilites(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet);
        int8_t updateRecipes(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet);
        int8_t commandsListed(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet);
        int8_t syncPlayerPos(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet);
        int8_t playerInfoUpdate(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet);
        int8_t syncWorldBorder(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet);
        int8_t updateTime(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet);
        int8_t setDefaultSpawnPos(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet);
        int8_t stepTick(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet);
        int8_t setCenterChunk(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet);
        int8_t chunkDataAndUpdateLight(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet);
        int8_t serverData(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet);
        int8_t entityEvent(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet);
        int8_t gameEvent(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet);
    }   
}




















#endif