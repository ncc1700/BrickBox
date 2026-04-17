#include "Packet.h"
#include <cstdint>
#include <cstring>
#include <netinet/in.h>
#include <sys/types.h>

namespace Network {
    uint64_t Packet::getTracker(){
        return this->tracker;
    }
    void Packet::setTracker(uint64_t value){
        this->tracker = value;
    }
    // could do a uint8_t but i want to have errors
    uint8_t Packet::readByte(){
        if(this->tracker >= vec.size()){
            return 0; // we should kick the client here
        }
        this->tracker++;
        return vec[this->tracker - 1];
    }

    ssize_t Packet::writeByte(uint8_t byte){
        vec.push_back(byte);
        return 1;
    }

    ssize_t Packet::receive(uint8_t* buf, size_t n){
        for(size_t i = 0; i < n; i++){
            buf[i] = readByte();
        }
        return n;
    }

    ssize_t Packet::send(const uint8_t* buf, size_t len){
        for(size_t i = 0; i < len; i++){
            writeByte(buf[i]);
        }
        return len;
    }

    // not ideal, pls make better
    uint8_t Packet::sendPacket(Connection* connection){
        // Packet dummyPacket;
        // dummyPacket.writeVarInt(this->vec.size());
        Packet packetWeSend; 
        packetWeSend.writeVarInt(this->vec.size());

        packetWeSend.vec.insert(packetWeSend.vec.end(), this->vec.begin(), this->vec.end());
        
        ssize_t size = connection->send(packetWeSend.vec.data(), packetWeSend.vec.size());
        if(size <= 0){
            return 1;
        }
        return 0;
    }

    uint8_t Packet::sendCompressedPacket(int threshold, Connection* connection){
        Packet dummyPacket;
        dummyPacket.writeVarInt(0);
        Packet packetWeSend; 
        packetWeSend.writeVarInt(this->vec.size() + dummyPacket.vec.size());
        packetWeSend.writeVarInt(0);
        
        packetWeSend.vec.insert(packetWeSend.vec.end(), this->vec.begin(), this->vec.end());
        
        ssize_t size = connection->send(packetWeSend.vec.data(), packetWeSend.vec.size());
        if(size <= 0){
            return 1;
        }
        return 0;
    }


}