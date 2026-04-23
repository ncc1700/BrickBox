


#include "network/Connection.h"
#include "network/Packet.h"
#include "network/PacketReceiver.h"
#include "network/PacketSender.h"
#include "network/protocol/MCProtocol.h"
#include <chrono>
#include <memory>
#include <thread>

int main(){
    std::shared_ptr<Network::Connection> con = std::make_shared<Network::Connection>();

    con->connectToServer("0.0.0.0", 25565);
    Network::registerCallbacks();
    Network::PacketSender::create(con);
    Network::PacketReceiver::create(con);
    Network::ClientPackets::handShake(con, "127.0.0.1", 48472);
    Network::ClientPackets::loginStart(con, "BrickBox", "123e4567-e89b-12d3-a456-426614174000");    
    
    // the rest is done via the callbacks
    while(1){
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        continue;
    }
    //Network::MCProtocol::RegistryData(&con);
    // uint64_t h = con.readVarInt();
    // printf("something: %d\n", h);
}