//
// Created by maks on 10.03.2026.
//

#include "GLFWLifecycle.h"

#include <iostream>

static void glfwErrorCalllback(int errorCode, const char* description) {
    std::cout << "[GLFW error" << errorCode << "] " << description << std::endl;
}

GLFWLifecycle::GLFWLifecycle() {
#ifdef __linux__
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
#endif
    glfwSetErrorCallback(glfwErrorCalllback);
    if (!glfwInit()) throw std::runtime_error("GLFW initialization failed");
}

GLFWLifecycle::~GLFWLifecycle() {
    glfwTerminate();
}
