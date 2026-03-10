#include "Packet.h"
#include <cstdint>
#include <cstring>
#include <netinet/in.h>
#include <sys/types.h>
#include "NetworkTools.h"





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


uint16_t Packet::readU16(){
    uint8_t buffer[3];
    int result = this->receive(buffer, 2);
    return ((uint16_t)buffer[0] << 8) | buffer[1];
}

ssize_t Packet::writeU16(uint16_t num){
    uint16_t numBe = htons(num);
    return this->send((uint8_t*)&numBe, sizeof(numBe));
}

uint32_t Packet::readU32(){
    uint8_t buffer[5];
    int result = this->receive(buffer, 4);
    return ((uint32_t)buffer[0] << 24) 
            | ((uint32_t)buffer[1] << 16)
            | ((uint32_t)buffer[2] << 8)
            | ((uint32_t)buffer[3]);
}

ssize_t Packet::writeU32(uint32_t num){
    uint32_t numBe = htonl(num);
    return this->send((uint8_t*)&numBe, sizeof(numBe));
}

uint64_t Packet::readU64(){
    uint8_t buffer[8];
    int result = this->receive(buffer, 8);
    return ((uint64_t)buffer[0] << 56) 
            | ((uint64_t)buffer[1] << 48)
            | ((uint64_t)buffer[2] << 40)
            | ((uint64_t)buffer[3] << 32)
            | ((uint32_t)buffer[4] << 24) 
            | ((uint32_t)buffer[5] << 16)
            | ((uint32_t)buffer[6] << 8)
            | ((uint32_t)buffer[7]);
}

ssize_t Packet::writeU64(uint64_t num){
    uint64_t numBe = htonll(num);
    return this->send((uint8_t*)&numBe, sizeof(numBe));
}
// not finished
float Packet::readFloat(){
    uint8_t buffer[2];
    int result = this->receive(buffer, 1);
    return buffer[0];
}

ssize_t Packet::writeFloat(float num){
    uint32_t numBits = 0;
    memcpy(&numBits, &num, sizeof(numBits));
    return this->writeU32(numBits);
}

// not finished
double Packet::readDouble(){
    uint8_t buffer[2];
    int result = this->receive(buffer, 1);
    return buffer[0];
}

ssize_t Packet::writeDouble(double num){
    uint64_t numBits = 0;
    memcpy(&numBits, &num, sizeof(numBits));
    return this->writeU64(numBits);
}



// used BareIron as a reference
// thanks to them!!

int Packet::readVarInt(){
    int value = 0;
    int position = 0;
    uint8_t byte = 0;

    while(1){
        int byteInt = this->readByte();
        byte = (uint8_t)byteInt;
        value |= (byte & SEGMENT_BIT) << position;
        if((byte & CONTINUE_BIT) == 0) {
            break;
        }
        position += 7;
        if(position >= 32){
            // something went wrong
            return -1;
        }
    }
    return value;
}

int Packet::sizeVarInt(int value){
    int size = 1;
    while((value & ~SEGMENT_BIT) != 0){
        value >>= 7;
        size++;
    }
    return size;
}

void Packet::writeVarInt(int value){
    while(true){
        if((value & ~SEGMENT_BIT) == 0){
            this->writeByte(value);
            return;
        }
        this->writeByte((value & SEGMENT_BIT) | CONTINUE_BIT);
        value >>= 7;
    }
}

uint8_t* Packet::readBuffer(){
    uint32_t length = this->readVarInt();
    
    uint8_t* buffer = new uint8_t[length];
    ssize_t len = this->receive(buffer, length);
    if(len <= 0){
        delete[] buffer;
        return NULL;
    }
    return buffer;
}

char* Packet::readCStr(){
    uint32_t length = this->readVarInt();
    char* buffer = new char[length + 1];
    ssize_t len = this->receive((uint8_t*)buffer, length);
    if(len == 0){
        delete[] buffer;
        return NULL;
    }
    buffer[len] = '\0';
    return buffer;
}

std::string Packet::readString(){
    char* cstr = this->readCStr();
    std::string str = cstr;
    delete[] cstr;
    return str;
}

void Packet::writeString(std::string str, int maxLength){
    int len = str.length();
    if(len > maxLength){
        len = maxLength;
    }
    this->writeVarInt(len);
    const char* buf = str.c_str();
    for(int i = 0; i < len; i++){
        this->writeByte(buf[i]);
    }
}


// not ideal, pls make better
uint8_t Packet::sendPacket(Connection* connection){
    Packet packetWeSend; 

    packetWeSend.writeVarInt(this->vec.size());
    packetWeSend.vec.insert(packetWeSend.vec.end(), this->vec.begin(), this->vec.end());

    ssize_t size = connection->sendToServer(packetWeSend.vec.data(), packetWeSend.vec.size());
    if(size <= 0){
        return 1;
    }
    return 0;
}


