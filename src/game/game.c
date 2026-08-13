#include <game/game.h>



// NOT THREAD SAFE, TODO: MAKE IT THREAD SAFE!!!!!!!!!!

static boolean isGameRunning = TRUE;





void GameEnd(){
    isGameRunning = FALSE;
}

boolean GameIsRunning(){
    return isGameRunning;
}

