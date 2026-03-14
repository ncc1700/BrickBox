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
}

Window::~Window() {
    renderLoop.reset();
    glfwDestroyWindow(window);
}

void Window::setRenderer(std::unique_ptr<AbstractRenderer> &&render_loop) {
    renderLoop = std::move(render_loop);
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


