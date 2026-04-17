

#include <atomic>
#include <cstdio>
#include <memory>
#include "../../MCProtocol.h"
#include "../Protocol.h"
namespace Network {
    namespace ServerPackets {

        int8_t loginSuccessCallback(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            if(isLoginSuccess() == true){
                // why are we sending this again?
                printf("ERROR: tried sending loginSuccess when its useless!\n");
                return -1;
            }
            printf("Server acknowledged our login\n");
            ClientPackets::loginAcknowledged(con);
            loginSuccess();
            return 0;
        }

        
    }
}















