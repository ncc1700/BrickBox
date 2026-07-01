#ifndef CONNECTION_H_INCLUDED
#define CONNECTION_H_INCLUDED




#include <BrickBox.h>

#define CON_SUCCESS(x) (x == Network::ConnectionStatus::SUCCESS)


namespace Network {
    enum class ConnectionStatus {
        UNKNOWN_FAILURE,
        COULDNT_CREATE_SOCKET,
        COULDNT_CONVERT_IP,
        COULDNT_CONNECT,
        SUCCESS
    };
    class Connection {
        private:
        int sock;
        uint8_t readByte();
        public:
            Connection();
            ConnectionStatus connectToServer(const char* ip, uint16_t port);
            size_t read(uint8_t* buffer, size_t size);
            size_t send(uint8_t* buffer, size_t size);
            int32_t readVarInt();
            ~Connection();
            
    };
}
























#endif
