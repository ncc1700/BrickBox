#include <network/MinecraftClient.hpp>
#include <type_traits>




namespace Network {
    MinecraftClient::MinecraftClient(std::string ip, uint16_t port){
        CreateBrickBoxClient(&this->client, ip.c_str(), port);
        this->client.data = (void*)this;
    }
    void MinecraftClient::start(){
        StartBrickBoxClient(&this->client);
    }

    void MinecraftClient::sendPacketToServer(Packet* packet){
        packet->writeVarIntFront(packet->returnByteStream()->storage.used);
        DEBUG_INFO("%d\n", packet->returnByteStream()->storage.used);
        WriteDataToServer(&this->client, packet->returnByteStream()->storage.buffer, packet->returnByteStream()->storage.used);
    }
    
    MinecraftClient::~MinecraftClient(){
         DestroyBrickBoxClient(&this->client);
    }
}