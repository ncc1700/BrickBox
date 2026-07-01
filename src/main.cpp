#include <BrickBox.h>
#include <network/Packet.h>
#include <network/CSPackets.h>

#include <network/Connection.h>




int main(){
    Network::Connection con;
    Network::ConnectionStatus status = con.connectToServer("127.0.0.1", 25565);
    if(!CON_SUCCESS(status)){
        return -1;
    }
    Network::Packet handshakePacket = Network::CSPackets::handshake(774, "127.0.0.1", 25565);
    con.send((uint8_t*)handshakePacket.returnPacketBuffer(), 
            handshakePacket.returnSizeOfPacket());
    Network::Packet loginPacket = Network::CSPackets::loginStart("BrickBox");
    con.send((uint8_t*)loginPacket.returnPacketBuffer(), 
            loginPacket.returnSizeOfPacket());
    int32_t size = con.readVarInt();
    Network::Packet packet(size);
    con.read(packet.returnPacketBuffer(), size);
    DEBUG_INFO("0x%x\n", packet.readVarInt());
    DEBUG_INFO("returned\n");
    //while(1){continue;}
    return 0;
}
