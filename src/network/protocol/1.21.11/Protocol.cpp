#include "../MCProtocol.h"
#include <atomic>
#include <sys/types.h>



namespace Network {
    std::atomic_bool loginSuccessBool = false;

    void loginSuccess(){
        loginSuccessBool = true;
    }
    bool isLoginSuccess(){
        return loginSuccessBool;
    }

}