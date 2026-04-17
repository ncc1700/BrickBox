#include "Connection.h"
#include "PacketSender.h"
#include <chrono>
#include <cstddef>
#include <memory>
#include <queue>
#include <sys/types.h>
#include <thread>






namespace Network {
    static std::shared_ptr<PacketSender> singleTon = NULL;

    PacketSender::PacketSender(std::shared_ptr<Connection> con){
        this->con = con;   
        this->isRunning = true;
        this->newThread = std::thread(&PacketSender::startThread, this);
    }
    PacketSender::~PacketSender(){
        this->isRunning = false;
        if(this->newThread.joinable()){
            this->newThread.join();
        }   
    }
    void PacketSender::sendPacket(std::shared_ptr<Packet> packet){
        this->mutex.lock();
        this->packetQueue.push(packet);
        this->mutex.unlock();
    }

    void PacketSender::setCompressionThreshold(int amount){
        compressionThreshold = amount;
    }
    
    void PacketSender::startThread(){
        while(isRunning){
            this->mutex.lock();
            if(this->packetQueue.empty() == true){
                this->mutex.unlock();
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                continue;
            }
            printf("sending a packet! (queue line: %ld)\n", this->packetQueue.size());
            int vecSize = this->packetQueue.front()->vec.size();
            if(compressionThreshold != -1){
                printf("sending COMPRESSED packet\n");
                this->packetQueue.front()->sendCompressedPacket(compressionThreshold, this->con.get());
            } else {
                printf("sending UNCOMPRESSED packet\n");
                this->packetQueue.front()->sendPacket(this->con.get());
            }
            this->packetQueue.pop();
            this->mutex.unlock();
        }
    }

    // static functions
    void PacketSender::create(std::shared_ptr<Connection> con){
        singleTon = std::make_shared<PacketSender>(con);
    }

    std::shared_ptr<PacketSender> PacketSender::getInstance() {
        return singleTon;
    }

    void PacketSender::send(std::shared_ptr<Packet> packet){
        PacketSender::getInstance().get()->sendPacket(packet);
    }
    
    void PacketSender::setMaxSizeTillCompression(int amount){
        PacketSender::getInstance().get()->setCompressionThreshold(amount);
    }
}