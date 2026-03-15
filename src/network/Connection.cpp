#include "Connection.h"
#include <cerrno>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>


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

    ssize_t Connection::receive(uint8_t* buf, size_t n){
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

    ssize_t Connection::send(const uint8_t* buf, size_t len){
        // 0 is success
        // -1 is we had an error sending a packet
        int sent = 0;
        uint8_t* ubuf = (uint8_t*)buf;
        while(sent < len){
            ssize_t sizeSent = ::send(this->fd, ubuf + sent, 
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

    uint8_t Connection::readByte(){
        uint8_t recv_buffer[2];
        int result = this->receive(recv_buffer, 1);
        return recv_buffer[0];
    }

    ssize_t Connection::writeByte(uint8_t byte){
        return this->send(&byte, 1);
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