#include <network/CSPackets.h>
#include <string.h>


namespace Network {
    namespace CSPackets {
        Packet handshake(int32_t protocol, const char* ip, uint16_t port){
            Packet packet;
            size_t ipLength = strlen(ip);
            if(ipLength >= 255) ipLength = 255;
            size_t size = Packet::sizeVarInt(0x00) + Packet::sizeVarInt(protocol) + 
                            Packet::sizeVarInt(ipLength) + ipLength + sizeof(uint16_t) + Packet::sizeVarInt(2);
            packet.writeVarInt(size);
            packet.writeVarInt(0x00);
            packet.writeVarInt(protocol);
            packet.writeString(ip, 255);
            packet.writeU16(port);
            packet.writeVarInt(2);
            return packet;
        }
        Packet loginStart(const char* username){
            Packet packet;
            size_t nameLength = strlen(username);
            if(nameLength >= 16) nameLength = 16;
            size_t size = Packet::sizeVarInt(0x00) + Packet::sizeVarInt(nameLength) + nameLength + sizeof(uint64_t) + sizeof(uint64_t);
            packet.writeVarInt(size);
            packet.writeVarInt(0x00);
            packet.writeString(username, 16);
            packet.writeU64(0);
            packet.writeU64(0);
            return packet;
        }
        // Packet acknowledgeLogin(){
        // }
        // Packet configSuccess(){
        // }
    }
}

