#ifndef ABSTRACTFORMAT_H_INCLUDED
#define ABSTRACTFORMAT_H_INCLUDED








#include <cstdint>
#include <string>
#include <sys/types.h>
#include <vector>

namespace Network {
    class AbstractFormat {
        public:
            virtual uint8_t readByte() = 0;
            virtual ssize_t writeByte(uint8_t byte) = 0;
            virtual ssize_t receive(uint8_t* buf, size_t n) = 0;
            virtual ssize_t send(const uint8_t* buf, size_t len) = 0;
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
            int64_t readVarLong();
            void writeVarInt(int value);
            void writeVarLong(int64_t value);;
            uint8_t* readBuffer();
            char* readCStr();
            std::string readString(); // <---- USE THIS, NOT READCSTR
            void writeString(std::string str, int maxLength);
            static int sizeVarInt(int value);

    };
}
























#endif