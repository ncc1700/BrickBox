#ifndef CHANNEL_H_INCLUDED
#define CHANNEL_H_INCLUDED



#include <BrickBox.h>
#include <queue>
#include <mutex>

// wanted to create a seperate file but idk how =(
namespace Core {
    template <class T>
    class Channel {
        private:
        std::queue<T> queue;
        std::mutex queueMutex;
        public:
        Channel(){}
        bool hasEvent(){
            queueMutex.lock();
            bool result = this->queue.empty();
            queueMutex.unlock();
            return !result;
        }
        void push(T item){
            queueMutex.lock();
            this->queue.push(item);
            queueMutex.unlock();
        }
        T pop(){
            queueMutex.lock();
            T item = this->queue.front();
            this->queue.pop();
            queueMutex.unlock();
            return item;
        }
        ~Channel(){}
    };
}
















#endif
