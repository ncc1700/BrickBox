//
// Created by maks on 10.03.2026.
//

#ifndef BRICKBOX_GLFWWINDOW_H
#define BRICKBOX_GLFWWINDOW_H
#include <memory>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include "../AbstractRenderer.h"

class Window {
public:
    Window();
    ~Window();
    void loop();
    void setRenderer(std::unique_ptr<AbstractRenderer> &&render_loop);
    glm::vec2 getCursorDelta();
    GLFWwindow *window;
private:
    bool mouseEnabled;
    std::unique_ptr<AbstractRenderer> renderLoop;
    void setGrab(bool grabbing);
    static void keyPressCallback(GLFWwindow* win, int key, int scancode, int action, int mods);
};


#endif //BRICKBOX_GLFWWINDOW_H