#ifndef PACKET_H_INCLUDED
#define PACKET_H_INCLUDED




#include "AbstractFormat.h"
#include "Connection.h"
#include <cstdint>
#include <stdint.h>
#include <string>
#include <vector>
#include <sys/types.h>

#define SEGMENT_BIT 0x7F
#define CONTINUE_BIT 0x80

namespace Network {
    class Packet : public AbstractFormat {
        private:
            uint64_t tracker = 0;
        public:
            uint64_t getTracker();
            void setTracker(uint64_t value);
            std::vector<uint8_t> vec;
            uint8_t readByte();
            ssize_t writeByte(uint8_t byte);
            ssize_t receive(uint8_t* buf, size_t n);
            ssize_t send(const uint8_t* buf, size_t len);
            uint8_t sendPacket(Connection* connection);
            uint8_t sendCompressedPacket(int threshold, Connection* connection);
    };
}

#endif