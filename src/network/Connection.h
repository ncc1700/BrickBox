#ifndef CONNECTION_H_INCLUDED
#define CONNECTION_H_INCLUDED







#include <cstddef>
#include <cstdint>
#include <string>
#include <sys/types.h>

#define SEGMENT_BIT 0x7F
#define CONTINUE_BIT 0x80

class Connection {
    private:
        int fd;
    public:
        Connection();
        uint8_t connectToServer(std::string ip, uint16_t port);
        ssize_t receive(void* buf, size_t n);
        ssize_t sendToServer(const void* buf, size_t len);
        uint8_t readByte();
        ssize_t writeByte(uint8_t byte);
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
        char* readBuffer();
        char* readCStr();
        std::string readString(); // <---- USE THIS
        ~Connection();
};
















#endif