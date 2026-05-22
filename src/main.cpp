#include <brickboxNet.h>
#include <network/Packet.hpp>
#include <network/MinecraftClient.hpp>

void CallbackOnConnect(BrickBoxClient* clientData, void* connection, ConnectionResult result){
    Network::MinecraftClient* client = (Network::MinecraftClient*)clientData->data;
    if(result == CONNECTION_SUCCESS){
       
        DEBUG_INFO("SUCCESS!\n");

        Network::Packet packet1(1);
        packet1.writeVarInt(0x00);
        packet1.writeVarInt(774);
        packet1.writeStr("127.0.0.1", 255);
        packet1.writeU16(25565);
        packet1.writeVarInt(2);
        client->sendPacketToServer(&packet1);
       
        Network::Packet packet2(1);
        packet2.writeVarInt(0x00);
        packet2.writeStr("m", 16);
        packet2.writeU64(0);
        packet2.writeU64(0);
        client->sendPacketToServer(&packet2);
    } else DEBUG_INFO("FAIL\n");
}

void CallbackOnRead(BrickBoxClient* clientData, bool readSuccess, const void* buffer, size_t size){
    if(buffer == NULL) return;
    Network::MinecraftClient* client = (Network::MinecraftClient*)clientData->data;
    if(readSuccess == false){
        DEBUG_FAIL("failed to fully read packet");
        return;
    }
    Network::Packet packet((uint8_t*)buffer, size, false);
    //DEBUG_INFO("")
    int sizeOfPacket = packet.readVarInt();
    int id = packet.readVarInt();
    DEBUG_INFO("id is 0x%x, size is %d\n", ((uint8_t*)buffer)[0], sizeOfPacket);
}

int main(){
    Network::MinecraftClient client("127.0.0.1", 25565);
    client.registerCallback<OnConnect>(CallbackOnConnect);
    client.registerCallback<OnRead>(CallbackOnRead);
    client.start();
   // while(1){continue;}
    return 0;
}

