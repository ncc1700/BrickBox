#ifndef PACKET_H_INCLUDED
#define PACKET_H_INCLUDED




#include "Connection.h"
#include <cstdint>
#include <stdint.h>
#include <string>
#include <vector>
#include <sys/types.h>

#define SEGMENT_BIT 0x7F
#define CONTINUE_BIT 0x80


class Packet {
    private:
        uint64_t tracker = 0;
    public:
        std::vector<uint8_t> vec;
        uint8_t readByte();
        ssize_t writeByte(uint8_t byte);
        ssize_t receive(uint8_t* buf, size_t n);
        ssize_t send(const uint8_t* buf, size_t len);
        uint16_t readU16();
        ssize_t writeU16(uint16_t num);
        uint32_t readU32();
        ssize_t writeU32(uint32_t num);
        uint64_t readU64();
        ssize_t writeU64(uint64_t num);
        float readFloat();
        ssize_t writeFloat(float num);
        double readDouble();
        ssize_t writeDouble(double num);
        int readVarInt();
        int sizeVarInt(int value);
        void writeVarInt(int value);
        uint8_t* readBuffer();
        char* readCStr();
        std::string readString(); // <---- USE THIS, NOT READCSTR
        void writeString(std::string str, int maxLength);
        uint8_t sendPacket(Connection* connection);
};




#endif