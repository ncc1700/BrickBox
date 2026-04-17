
#include "Connection.h"
#include "protocol/MCProtocol.h"
#include "PacketReceiver.h"
#include <cstddef>
#include <memory>
#include <thread>
#include <zlib.h>





namespace Network {
    static std::shared_ptr<PacketReceiver> singleTon = NULL;

    PacketReceiver::PacketReceiver(std::shared_ptr<Connection> con){
        this->con = con;   
        this->isRunning = true;
        this->newThread = std::thread(&PacketReceiver::startThread, this);
    }

    void PacketReceiver::setCompressionThreshold(int amount){
        compressionThreshold = amount;
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
            if(compressionThreshold != -1){
                int pLengthWithData = con->readVarInt();
                // decompress then send
                unsigned long dLength = con->readVarInt();
                // just to get dLengthSize
                Packet testPacket;
                testPacket.writeVarInt(dLength);
                int dLengthSize = testPacket.vec.size();
                int pLength = pLengthWithData - dLengthSize;
                printf("pLengthWithData: %d, pLength: %d, dLength: %lu, dLengthSize: %d\n", pLengthWithData, pLength, dLength, dLengthSize);

                if(dLength == 0){
                    if(pLengthWithData != 0 || pLengthWithData >= dLengthSize){
                        packet.vec.resize(pLength);
                    }
                    ssize_t read = con->receive(packet.vec.data(), pLength);
                    if(pLength > read){
                        continue;
                    }
                    int id = packet.readVarInt();
                    printf("we got an uncompressed packet in a compressed state! Id is 0x%x Size is %d\n", id, pLengthWithData);
                    handleCallback(con, std::make_shared<Packet>(packet), id);  
                } else {
                    Packet packetToHandle;
                    if(pLengthWithData != 0 || pLengthWithData >= dLengthSize){
                        packet.vec.resize(pLength);
                    }
                    ssize_t read = con->receive(packet.vec.data(), pLength);
                    if(pLength > read){
                        printf("???\n");
                        continue;
                    }
                    packetToHandle.vec.resize(dLength);
                    uncompress(packetToHandle.vec.data(), &dLength, packet.vec.data(), pLength);
                    int id = packetToHandle.readVarInt();
                    printf("we got a compressed packet! Id is 0x%x Size is %lu\n", id, dLength);
                    //handleCallback(con, std::make_shared<Packet>(packetToHandle), id);
                }
            } else {
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
                printf("we got an uncompressed packet! Id is 0x%x Size is %d\n", id, packetSize);
                handleCallback(con, std::make_shared<Packet>(packet), id);   
            }   
            
        }
    }
    void PacketReceiver::create(std::shared_ptr<Connection> con){
        singleTon = std::make_shared<PacketReceiver>(con);
    }

    std::shared_ptr<PacketReceiver> PacketReceiver::getInstance() {
        return singleTon;
    }

    void PacketReceiver::setMaxSizeTillCompression(int amount){
        PacketReceiver::getInstance().get()->setCompressionThreshold(amount);
    }
}