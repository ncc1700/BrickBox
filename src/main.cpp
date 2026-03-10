


#include "network/Connection.h"
#include "network/protocol/MCProtocol.h"

int main(){
    Connection con;
    con.connectToServer("0.0.0.0", 25565);

    MCProtocol::HandShake(&con, "127.0.0.1", 48472);
    MCProtocol::LoginStart(&con, "Test", "123e4567-e89b-12d3-a456-426614174000");    
    MCProtocol::LoginSuccess(&con);
    // uint64_t h = con.readVarInt();
    // printf("something: %d\n", h);
}