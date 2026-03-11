#include "../MCProtocol.h"
#include <atomic>
#include <cstdint>
#include <functional>
#include <memory>
#include <unordered_map>
#include "../../Packet.h"


namespace Network {

    namespace MCProtocol {
        typedef std::function<uint8_t(std::shared_ptr<Connection> con, std::shared_ptr<Packet>)> PacketHandlers;
        std::unordered_map<int, PacketHandlers> callbacks;
        static std::atomic_bool loginSuccess = false;
        static int8_t loginSuccessCallback(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("Server acknowledged our login\n");
            Network::MCProtocol::LoginAcknowledged(con.get());
            return 0;
        }
        int8_t isLoginSuccess(){
            return loginSuccess;
        }
        void registerCallbacks(){
            callbacks[0x2] = loginSuccessCallback;
        }

        int8_t handleCallback(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet, int id){
            if(callbacks.count(id) == 0){
                printf("invalid packet\n");
                // we could kick the client here, or not
                return -1;
            }
            return callbacks[id](con, packet);
        }

        
    }
}