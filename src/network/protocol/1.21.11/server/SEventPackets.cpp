#include <atomic>
#include <cstdio>
#include <memory>
#include "../../MCProtocol.h"

namespace Network {
    namespace ServerPackets {
        int8_t entityEvent(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("STUB: %s\n", __FUNCTION__);
            return 0;
        }
        
        int8_t gameEvent(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("STUB: %s\n", __FUNCTION__);
            return 0;
        }
    }
}

