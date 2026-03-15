

#include <cstdio>
#include <memory>
#include "../../MCProtocol.h"

namespace Network {
    namespace ServerPackets {
        // MOTD
        int8_t serverData(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("STUB: %s\n", __FUNCTION__);
            return 0;
        }
    }
}

