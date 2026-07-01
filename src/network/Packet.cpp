#include <network/Packet.h>


// pretty unoptimized but eh
namespace Network {
   
    Packet::Packet(){
        this->readIndex = 0;
    }
    Packet::Packet(size_t initialSize){
        //this->Packet();
        this->readIndex = 0;
        this->vec.resize(initialSize);
    }
    size_t Packet::returnSizeOfPacket(){
        return this->vec.size();
    }
    uint8_t* Packet::returnPacketBuffer(){
        return &vec[0];
    }
    void Packet::resizePacket(size_t size){
        this->vec.resize(size);
    }
    uint8_t Packet::readByte(){
        size_t size = this->vec.size();
        if(readIndex >= size){
            DEBUG_FAIL("vector overflow\n");
            return 0;
        }
        uint8_t byte = this->vec[readIndex];
        readIndex++;
        return byte;
    }
    void Packet::writeByte(uint8_t byte){
        this->vec.push_back(byte);
    }
    uint16_t Packet::readU16(){
        uint16_t firstByte = this->readByte();
        uint16_t secondByte = this->readByte();
        return (firstByte << 8) | secondByte;
    }
    void Packet::writeU16(uint16_t byte){
        uint8_t firstByte = (byte >> 8);
        uint8_t secondByte = (byte & 0xFF);
        this->writeByte(firstByte);
        this->writeByte(secondByte);
    }
    uint32_t Packet::readU32(){
        uint32_t firstU16 = this->readU16();
        uint32_t secondU16 = this->readU16();
        return (firstU16 << 16) | secondU16;
    }
    void Packet::writeU32(uint32_t byte){
        uint16_t firstU16 = (byte >> 16);
        uint16_t secondU16 = (byte & 0xFFFF);
        this->writeU16(firstU16);
        this->writeU16(secondU16);
    }
    uint64_t Packet::readU64(){
        uint64_t firstU32 = this->readU32();
        uint64_t secondU32 = this->readU32();
        return (firstU32 << 32) | secondU32;
    }
    void Packet::writeU64(uint64_t byte){
        uint32_t firstU32 = (byte >> 32);
        uint32_t secondU32 = (byte & 0xFFFFFFFF);
        this->writeU32(firstU32);
        this->writeU32(secondU32);
    }

    int32_t Packet::readVarInt(){
        int32_t value = 0;
        int32_t position = 0;
        while(true){
            uint8_t byte = this->readByte();
            value |= (((byte & SEGMENT_BIT)) << position);
            if((byte & CONTINUE_BIT) == 0){
                
                break;
            }
            position += 7;
            if(position >= 32){
                DEBUG_FAIL("position overflow\n");
                break;
            }
        }
        return value;
    }
    void Packet::writeVarInt(int32_t value){
        int32_t valueC = value;
        while(true){
            if((valueC & ~SEGMENT_BIT) == 0){
                this->writeByte(valueC);
                break;
            }
            this->writeByte((uint8_t)(valueC & SEGMENT_BIT) | CONTINUE_BIT);
            valueC >>= 7;
        }
    }
    int32_t Packet::sizeVarInt(int32_t value){
        int32_t size = 1;
        while((value & ~SEGMENT_BIT) != 0){
            value >>= 7;
            size++;
        }
        return size;
    }

    int64_t Packet::readVarLong(){
        int64_t value = 0;
        int64_t position = 0;
        while(true){
            uint8_t byte = this->readByte();
            value |= (((byte & SEGMENT_BIT)) << position);
            if((byte & CONTINUE_BIT) == 0){
                break;
            }
            position += 7;
            if(position >= 64){
                DEBUG_FAIL("position overflow\n");
                break;
            }
        }
        return value;
    }

    void Packet::writeVarLong(int64_t value){
        int64_t valueC = value;
        while(true){
            if((valueC & ~SEGMENT_BIT) == 0){
                this->writeByte(valueC);
                break;
            }
            this->writeByte((uint8_t)(valueC & SEGMENT_BIT) | CONTINUE_BIT);
            valueC >>= 7;
        }
    }

    std::string Packet::readString(){
        return "";
    }

    void Packet::writeString(std::string str, size_t maxLength){
        size_t length = str.length();
        if(length >= maxLength) length = maxLength;
        this->writeVarInt(length);
        for(size_t i = 0; i < length; i++){
            this->writeByte((uint8_t)str[i]);
        }
    }    
    
    Packet::~Packet(){
    
    }
}
