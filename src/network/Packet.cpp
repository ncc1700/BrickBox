
#include <network/Packet.hpp>

namespace Network {


    Packet::Packet(size_t initialCapacity){
        CreateByteStream(&this->stream, initialCapacity);
        this->shouldFree = true;
    }
    Packet::Packet(uint8_t* buffer, size_t sizeOfBuffer, bool shouldFree){
        CreateByteStreamEx(&this->stream, buffer, sizeOfBuffer);
        this->shouldFree = shouldFree;
    }
    uint8_t Packet::readByte(){
        return stream.ReadByte(&this->stream);
    }
    size_t Packet::writeByte(uint8_t byte){
        stream.WriteByte(&this->stream, byte);
        return 0; // will implement this
    }
    uint16_t Packet::readU16(){
        return ReadU16(&this->stream);
    }
    size_t Packet::writeU16(uint16_t num){
        return WriteU16(&this->stream, num);
    }
    uint32_t Packet::readU32(){
        return ReadU32(&this->stream);
    }
    size_t Packet::writeU32(uint32_t num){
        return WriteU32(&this->stream, num);
    }
    uint64_t Packet::readU64(){
        return ReadU64(&this->stream);
    }
    size_t Packet::writeU64(uint64_t num){
        return WriteU64(&this->stream, num);
    }
    size_t Packet::writeFloat(float num){
        return WriteFloat(&this->stream, num);
    }
    size_t Packet::writeDouble(double num){
        return WriteDouble(&this->stream, num);
    }
    int Packet::readVarInt(){
        return ReadVarInt(&this->stream);
    }
    int64_t Packet::readVarLong(){
        return ReadVarLong(&this->stream);
    }
    size_t Packet::writeVarInt(int value){
        WriteVarInt(&this->stream, value);
        return 0;
    }
    size_t Packet::writeVarIntFront(int value){
        WriteVarIntFront(&this->stream, value);
        return 0;
    }
    size_t Packet::writeVarLong(int64_t value){
        WriteVarLong(&this->stream, value);
        return 0;
    }
    // needs to be freed
    uint8_t* Packet::readBuffer(){
        return ReadBuffer(&this->stream); 
    }
    std::string Packet::readStr(){
        char* string = ReadCStr(&this->stream);
        std::string copiedString = string;
        DEFAULT_FREE(string);
        return copiedString;
    }
    size_t Packet::writeStr(std::string str, int maxLength){
        WriteCStr(&this->stream, str.c_str(), maxLength);
        return 0;
    }
    const ByteStream* Packet::returnByteStream(){
        return &this->stream;
    }
    Packet::~Packet(){
        if(this->shouldFree){
            DestroyByteStream(&this->stream);
        }
    }
        

}



