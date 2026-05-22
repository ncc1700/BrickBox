#ifndef MINECRAFTCLIENT_HPP_INCLUDED
#define MINECRAFTCLIENT_HPP_INCLUDED


#include <brickboxNet.h>
#include <string>
#include <network/Packet.hpp>
namespace Network {
    class MinecraftClient {
        private:
            BrickBoxClient client;
        public:
            MinecraftClient(std::string ip, uint16_t port);
            void start();
            void sendPacketToServer(Packet* packet);
            template <typename T> void registerCallback(T callback){
                if constexpr(std::is_same_v<T, OnConnect>) {
                    this->client.onConnect = callback;
                } else if constexpr(std::is_same_v<T, OnRead>){
                    this->client.onRead = callback;
                } else if constexpr(std::is_same_v<T, OnWrite>){
                    this->client.onWrite = callback;
                } else {
                    DEBUG_FAIL("Unknown type??\n");
                }
            }
            ~MinecraftClient();
    };
}















#endif