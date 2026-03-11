#include "../MCProtocol.h"
#include <atomic>
#include <cstdint>
#include <functional>
#include <memory>
#include <unordered_map>
#include "../../Packet.h"
#include "../../PacketSender.h"


namespace Network {

    namespace MCProtocol {
        typedef std::function<int8_t(std::shared_ptr<Connection> con, std::shared_ptr<Packet>)> PacketHandlers;
        std::unordered_map<int, PacketHandlers> callbacks;
        static std::atomic_bool loginSuccess = false;

        static int8_t loginSuccessCallback(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("Server acknowledged our login\n");
            loginAcknowledged(con.get());
            return 0;
        }

        static int8_t serverKeepAlive(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            printf("Server wants to check up on us\n");
            // int id = packet->readU64();
            // Packet p;
            // p.writeVarInt(0x04);
            // p.writeU64(id);
            // PacketSender::send(std::make_shared<Packet>(p));
            PacketSender::send(packet);
            return 0;
        }
        static int8_t knownPacks(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            // for now, just return back whatever they send
            packet->vec[0] = 0x07;
            PacketSender::send(packet);
            return 0;
        }
        static int8_t finishConfig(std::shared_ptr<Connection> con, std::shared_ptr<Packet> packet){
            PacketSender::send(packet);
            return 0;
        }
        int8_t isLoginSuccess(){
            return loginSuccess;
        }
        void registerCallbacks(){
            callbacks[0x2] = loginSuccessCallback;
            callbacks[0x4] = serverKeepAlive;
            callbacks[0xe] = knownPacks;
            callbacks[0x3] = finishConfig;
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