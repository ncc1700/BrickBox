#ifndef PACKET_H_INCLUDED
#define PACKET_H_INCLUDED




#include <BrickBox.h>
#include <vector>
#include <string>
namespace Network { 
    class Packet {
    private:
        std::vector<uint8_t> vec;
        size_t readIndex = 0;
    public:
        Packet();
        Packet(size_t initialSize);
        size_t returnSizeOfPacket();
        uint8_t* returnPacketBuffer();
        void resizePacket(size_t size);
        uint8_t readByte();
        void writeByte(uint8_t byte);
        uint16_t readU16();
        void writeU16(uint16_t byte);
        uint32_t readU32();
        void writeU32(uint32_t byte);
        uint64_t readU64();
        void writeU64(uint64_t byte);
        int32_t readVarInt();
        void writeVarInt(int32_t value);
        static int32_t sizeVarInt(int32_t value);
        int64_t readVarLong();
        void writeVarLong(int64_t value);
        std::string readString();
        void writeString(std::string str, size_t maxLength);
        ~Packet();
    };
}










#endif
