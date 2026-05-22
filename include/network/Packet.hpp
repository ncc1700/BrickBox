#ifndef PACKET_HPP_INCLUDED
#define PACKET_HPP_INCLUDED


#include <brickboxNet.h>
#include <string>
namespace Network {


    class Packet {
        private:
            ByteStream stream;
            bool shouldFree = true;
        public:
            Packet(size_t initialSize);
            Packet(uint8_t* buffer, size_t sizeOfBuffer, bool shouldFree);
            uint8_t readByte();
            size_t writeByte(uint8_t byte);
            uint16_t readU16();
            size_t writeU16(uint16_t num);
            uint32_t readU32();
            size_t writeU32(uint32_t num);
            uint64_t readU64();
            size_t writeU64(uint64_t num);
            //float readFloat();
            size_t writeFloat(float num);
            //double readDouble();
            size_t writeDouble(double num);
            int readVarInt();
            int64_t readVarLong();
            size_t writeVarInt(int value);
            size_t writeVarIntFront(int value);
            size_t writeVarLong(int64_t value);
            uint8_t* readBuffer();
            std::string readStr();
            size_t writeStr(std::string str, int maxLength);
            const ByteStream* returnByteStream();
            ~Packet();
    };

}




















#endif