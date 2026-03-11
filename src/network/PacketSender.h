#ifndef PACKETSENDER_H_INCLUDED
#define PACKETSENDER_H_INCLUDED







#include "Connection.h"
#include "Packet.h"
#include <atomic>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

namespace Network {
    class PacketSender {
        private:
            std::shared_ptr<Connection> con;
            std::queue<std::shared_ptr<Packet>> packetQueue;
            std::thread newThread;
            std::mutex mutex;
            std::atomic_bool isRunning;
            void startThread();
        public:
            //static std::shared_ptr<PacketSender> singleTon;
            PacketSender(std::shared_ptr<Connection> con);
            void sendPacket(std::shared_ptr<Packet>);
            ~PacketSender();
            static void create(std::shared_ptr<Connection> con); 
            static std::shared_ptr<PacketSender> getInstance(); 
            static void send(std::shared_ptr<Packet>);
    };

}







#endif