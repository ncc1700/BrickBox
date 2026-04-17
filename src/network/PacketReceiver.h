#ifndef PACKETRECEIVER_H_INCLUDED
#define PACKETRECEIVER_H_INCLUDED







#include "Connection.h"
#include "Packet.h"
#include <atomic>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

namespace Network {
    class PacketReceiver {
        private:
            std::shared_ptr<Connection> con;
            std::queue<std::shared_ptr<Packet>> packetQueue;
            std::thread newThread;
            std::mutex mutex;
            std::atomic_bool isRunning;
            int compressionThreshold = -1;;
            void startThread();
        public:
            PacketReceiver(std::shared_ptr<Connection> con);
            void setCompressionThreshold(int amount);
            ~PacketReceiver();
            static void create(std::shared_ptr<Connection> con); 
            static std::shared_ptr<PacketReceiver> getInstance(); 
            static void setMaxSizeTillCompression(int amount);;
    };

}







#endif