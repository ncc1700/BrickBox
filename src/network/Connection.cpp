#include <network/Connection.h>
#ifndef _WIN32
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#endif





namespace Network {
    Connection::Connection(){
        this->sock = -1;
    }
    ConnectionStatus Connection::connectToServer(const char* ip, uint16_t port){
        this->sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        if(this->sock == -1){
            DEBUG_FAIL("socket creation failed\n");
            return ConnectionStatus::COULDNT_CREATE_SOCKET;
        }
        struct sockaddr_in sa = {.sin_family = AF_INET, .sin_port = htons(port)};
        int result = inet_pton(AF_INET, ip, &sa.sin_addr);
        if(result != 1){
            DEBUG_FAIL("couldn't convert IP address to binary form, %d\n", result);
            close(this->sock);
            this->sock = -1;
            return ConnectionStatus::COULDNT_CONVERT_IP;
        }
        result = connect(this->sock, (struct sockaddr*)&sa, sizeof(sa));
        if(result == -1){
            DEBUG_FAIL("couldn't connect!\n");
            close(this->sock);
            this->sock = -1;
            return ConnectionStatus::COULDNT_CONNECT;
        }
        return ConnectionStatus::SUCCESS;
    }
    size_t Connection::read(uint8_t* buffer, size_t size){
        size_t readFrom = 0;
        do {
            ssize_t s = recv(this->sock, buffer, (size - readFrom), 0);
            if(s == -1){
                DEBUG_FAIL("an error has occured: ");
                perror("");
                return -1;
            }
            readFrom += s;
        } while(readFrom < size);
        return readFrom;
    }
    size_t Connection::send(uint8_t* buffer, size_t size){
        size_t sent = 0;
        do {
            ssize_t s = write(this->sock, buffer, (size - sent));
            if(s == -1){
                DEBUG_FAIL("an error has occured: ");
                perror("");
                return -1;
            }
            sent += s;
        } while(sent < size);
        return sent;
    }

    uint8_t Connection::readByte(){
        uint8_t buffer[1];
        this->read(buffer, 1);
        return buffer[0];
    }

    int32_t Connection::readVarInt(){
        int32_t value = 0;
        int32_t position = 0;
        while(true){
            uint8_t byte = this->readByte();
            value |= (((byte & SEGMENT_BIT)) << position);
            if((byte & CONTINUE_BIT) == 0){
                
                break;
            }
            position += 7;
            if(position >= 32){
                DEBUG_FAIL("position overflow\n");
                break;
            }
        }
        return value;
    }
    Connection::~Connection(){
        if(this->sock != -1){
            close(this->sock);
        }
    }



}
