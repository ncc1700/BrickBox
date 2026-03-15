#ifndef CONNECTION_H_INCLUDED
#define CONNECTION_H_INCLUDED







#include "AbstractFormat.h"
#include <cstddef>
#include <cstdint>
#include <string>
#include <sys/types.h>

namespace Network {
    #define SEGMENT_BIT 0x7F
    #define CONTINUE_BIT 0x80

    class Connection : public AbstractFormat {
        private:
            int fd;
        public:
            Connection();
            uint8_t connectToServer(std::string ip, uint16_t port);
            ssize_t receive(uint8_t* buf, size_t n);
            ssize_t send(const uint8_t* buf, size_t len);
            uint8_t readByte();
            ssize_t writeByte(uint8_t byte);
            void end();
            ~Connection();
    };
}




#endif