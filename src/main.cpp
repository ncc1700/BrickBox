
#include <stdio.h>

#include "renderer/glfw/GLFWLifecycle.h"
#include "renderer/glfw/Window.h"

GLFWLifecycle lifecycle;

int main(){
    Window window;
    window.loop();
}