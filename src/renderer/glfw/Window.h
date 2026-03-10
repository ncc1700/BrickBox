//
// Created by maks on 10.03.2026.
//

#ifndef BRICKBOX_GLFWWINDOW_H
#define BRICKBOX_GLFWWINDOW_H
#include <memory>
#include <GLFW/glfw3.h>
#include "../AbstractRenderer.h"

class Window {
public:
    Window();
    ~Window();
    void loop();
    void setRenderer(std::unique_ptr<AbstractRenderer> &&render_loop);
private:
    std::unique_ptr<AbstractRenderer> renderLoop;
    GLFWwindow *window;
};


#endif //BRICKBOX_GLFWWINDOW_H