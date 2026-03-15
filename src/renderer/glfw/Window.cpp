//
// Created by maks on 10.03.2026.
//


#include <iostream>
#include "Window.h"

#include "../InitialRenderLoop.h"


Window::Window() {
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    window = glfwCreateWindow(1024, 1024, "BrickBox", nullptr, nullptr);
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, keyPressCallback);
}

Window::~Window() {
    renderLoop.reset();
    glfwDestroyWindow(window);
}

void Window::setRenderer(std::unique_ptr<AbstractRenderer> &&render_loop) {
    renderLoop = std::move(render_loop);
}


void Window::keyPressCallback(GLFWwindow *win, const int key, int scancode, const int action, int mods) {
    auto* _this = static_cast<Window*>(glfwGetWindowUserPointer(win));
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) _this->setGrab(false);
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) _this->setGrab(true);
}

void Window::setGrab(const bool grabbing) {
    if (grabbing) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPos(window, 0, 0);
        mouseEnabled = true;
    }else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        mouseEnabled = false;
    }
}

glm::vec2 Window::getCursorDelta() {
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
        setGrab(false);
    }
    if (!mouseEnabled) return {0.0f, 0.0f};
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    glfwSetCursorPos(window, 0.0, 0.0);
    return {x, y};
}

void Window::loop() {
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    setRenderer(std::make_unique<InitialRenderLoop>(*this));
    while (true) {
        if (glfwWindowShouldClose(window)) break;
        if (renderLoop != nullptr) renderLoop->loop();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}


