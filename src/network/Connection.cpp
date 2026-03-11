#include "Connection.h"
#include <cerrno>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include "NetworkTools.h"


namespace Network {

    Connection::Connection(){
        this->fd = -1;
    }

    uint8_t Connection::connectToServer(std::string ip, uint16_t port){
        // 0 is success
        // 1 is it can't create a socket
        // 2 is it can't connect

        this->fd = socket(AF_INET, SOCK_STREAM, 0);
        if(fd == -1){
            perror("Couldn't create socket");
            return 1;
        }
        struct sockaddr_in sa = {
            .sin_family = AF_INET,
            .sin_port = htons(port)
        };
        inet_pton(AF_INET, 
                ip.c_str(), &sa.sin_addr);
        
        int result = connect(this->fd, 
                    (struct sockaddr*)&sa, sizeof(sa));
        if(result == -1){
            perror("Couldn't connect to server");
            return 2;
        }
        return 0;
    }

    ssize_t Connection::receive(void* buf, size_t n){
        // 0 is success
        // -1 is we had an error receiving a packet
        int received = 0;
        uint8_t* ubuf = (uint8_t*)buf;
        while(received < n){
            size_t sizeReceived = recv(this->fd, 
                                        ubuf + received, 
                                        n - received, 0);
            if(sizeReceived < 0){
                if(errno == EAGAIN || errno == EWOULDBLOCK)
                    continue;
                perror("Couldn't receive packet");
                return -1;
            } else if(sizeReceived == 0){
                return received;
            }

            received += sizeReceived;
        }
        
        return received;
    }   

    ssize_t Connection::sendToServer(const void* buf, size_t len){
        // 0 is success
        // -1 is we had an error sending a packet
        int sent = 0;
        uint8_t* ubuf = (uint8_t*)buf;
        while(sent < len){
            ssize_t sizeSent = send(this->fd, ubuf + sent, 
                                len - sent, 0);
            if(sizeSent == 0){
                perror("returned nothing");
                return -1;
            } else if(sizeSent > 0){
                sent += sizeSent;
            } else {
                if(errno != EAGAIN && errno != EWOULDBLOCK){
                    perror("Couldn't send packet");
                    return -1;
                }
            }
        }
        
        return sent;
    }

    // could do a uint8_t but i want to have errors
    uint8_t Connection::readByte(){
        char recv_buffer[2];
        int result = this->receive(recv_buffer, 1);
        return recv_buffer[0];
    }

    ssize_t Connection::writeByte(uint8_t byte){
        return this->sendToServer(&byte, 1);
    }

    uint16_t Connection::readU16(){
        char recv_buffer[3];
        int result = this->receive(recv_buffer, 2);
        return ((uint16_t)recv_buffer[0] << 8) | recv_buffer[1];
    }

    ssize_t Connection::writeU16(uint16_t num){
        uint16_t numBe = htons(num);
        return this->sendToServer(&numBe, sizeof(numBe));
    }

    uint32_t Connection::readU32(){
        char recv_buffer[5];
        int result = this->receive(recv_buffer, 4);
        return ((uint32_t)recv_buffer[0] << 24) 
                | ((uint32_t)recv_buffer[1] << 16)
                | ((uint32_t)recv_buffer[2] << 8)
                | ((uint32_t)recv_buffer[3]);
    }

    ssize_t Connection::writeU32(uint32_t num){
        uint32_t numBe = htonl(num);
        return this->sendToServer(&numBe, sizeof(numBe));
    }

    uint64_t Connection::readU64(){
        char recv_buffer[8];
        int result = this->receive(recv_buffer, 8);
        return ((uint64_t)recv_buffer[0] << 56) 
                | ((uint64_t)recv_buffer[1] << 48)
                | ((uint64_t)recv_buffer[2] << 40)
                | ((uint64_t)recv_buffer[3] << 32)
                | ((uint64_t)recv_buffer[4] << 24) 
                | ((uint64_t)recv_buffer[5] << 16)
                | ((uint64_t)recv_buffer[6] << 8)
                | ((uint64_t)recv_buffer[7]);
    }

    ssize_t Connection::writeU64(uint64_t num){
        uint64_t numBe = htonll(num);
        return this->sendToServer(&numBe, sizeof(numBe));
    }
    // not finished
    float Connection::readFloat(){
        char recv_buffer[2];
        int result = this->receive(recv_buffer, 1);
        return recv_buffer[0];
    }

    ssize_t Connection::writeFloat(float num){
        uint32_t numBits = 0;
        memcpy(&numBits, &num, sizeof(numBits));
        return this->writeU32(numBits);
    }
    // not finished
    double Connection::readDouble(){
        char recv_buffer[2];
        int result = this->receive(recv_buffer, 1);
        return recv_buffer[0];
    }

    ssize_t Connection::writeDouble(double num){
        uint64_t numBits = 0;
        memcpy(&numBits, &num, sizeof(numBits));
        return this->writeU64(numBits);
    }



    // BareIron helped me with these ones
    // thanks to them!!

    int Connection::readVarInt(){
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

    int Connection::sizeVarInt(int value){
        int size = 1;
        while((value & ~SEGMENT_BIT) != 0){
            value >>= 7;
            size++;
        }
        return size;
    }

    void Connection::writeVarInt(int value){
        while(true){
            if((value & ~SEGMENT_BIT) == 0){
                this->writeByte(value);
                return;
            }
            this->writeByte((value & SEGMENT_BIT) | CONTINUE_BIT);
            value >>= 7;
        }
    }

    void Connection::writeVarLong(int64_t value){
        while(true){
            if((value & ~SEGMENT_BIT) == 0){
                this->writeByte(value);
                return;
            }
            this->writeByte((value & SEGMENT_BIT) | CONTINUE_BIT);
            value >>= 7;
        }
    }
    char* Connection::readBuffer(){
        uint32_t length = this->readVarInt();
        
        char* buffer = new char[length];
        ssize_t len = this->receive((void*)buffer, length);
        if(len <= 0){
            delete[] buffer;
            return NULL;
        }
        return buffer;
    }

    char* Connection::readCStr(){
        uint32_t length = this->readVarInt();
        char* buffer = new char[length + 1];
        ssize_t len = this->receive((void*)buffer, length);
        if(len == 0){
            delete[] buffer;
            return NULL;
        }
        buffer[len] = '\0';
        return buffer;
    }

    std::string Connection::readString(){
        char* cstr = this->readCStr();
        std::string str = cstr;
        delete[] cstr;
        return str;
    }

    void Connection::end(){
        shutdown(fd, SHUT_RDWR);
    }

    Connection::~Connection(){
        if(this->fd != -1){
            close(this->fd);
        }
    }

}