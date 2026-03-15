

#include <atomic>
#include <cstdio>
#include <memory>
#include "../../MCProtocol.h"

namespace Network {
    namespace ServerPackets {
        static std::atomic_bool loginSuccess = false;

        int8_t loginSuccessCallback(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            if(loginSuccess == true){
                // why are we sending this again?
                printf("ERROR: tried sending loginSuccess when its useless!\n");
                return -1;
            }
            printf("Server acknowledged our login\n");
            ClientPackets::loginAcknowledged(con);
            loginSuccess = true;
            return 0;
        }

        
    }
}















