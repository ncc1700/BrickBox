
#include "Connection.h"
#include "protocol/MCProtocol.h"
#include "PacketReceiver.h"
#include <chrono>
#include <cstddef>
#include <memory>
#include <queue>
#include <thread>






namespace Network {
    static std::shared_ptr<PacketReceiver> singleTon = NULL;

    PacketReceiver::PacketReceiver(std::shared_ptr<Connection> con){
        this->con = con;   
        this->isRunning = true;
        this->newThread = std::thread(&PacketReceiver::startThread, this);
    }
    PacketReceiver::~PacketReceiver(){
        this->isRunning = false;
        this->con->end();
        if(this->newThread.joinable()){
            this->newThread.join();
        }   
    }
    void PacketReceiver::startThread(){
        while(isRunning){
            Packet packet;
            int packetSize = con->readVarInt();
            if(packetSize == 0){
                continue;
            }
            packet.vec.resize(packetSize);
            ssize_t read = con->receive(packet.vec.data(), packetSize);
            if(packetSize > read){
                continue;
            }
            int id = packet.readVarInt();
            printf("we got a packet! Id is 0x%x Size is %d\n", id, packetSize);
            MCProtocol::handleCallback(con, std::make_shared<Packet>(packet), id);   
        }
    }
    void PacketReceiver::create(std::shared_ptr<Connection> con){
        singleTon = std::make_shared<PacketReceiver>(con);
    }

    std::shared_ptr<PacketReceiver> PacketReceiver::getInstance() {
        return singleTon;
    }
}