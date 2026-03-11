//
// Created by maks on 10.03.2026.
//

#ifndef BRICKBOX_RESOURCE_H
#define BRICKBOX_RESOURCE_H

#define DEBUG_RESOURCE_ALLOCATION

#ifdef DEBUG_RESOURCE_ALLOCATION
#include <GLFW/glfw3.h>
#endif

class Resource {
public:
    Resource();
    Resource(Resource const& other) = delete;
    Resource(Resource &&other) = delete;
    virtual ~Resource();
#ifdef DEBUG_RESOURCE_ALLOCATION
private:
    GLFWwindow* window;
#endif
};

#endif //BRICKBOX_RESOURCE_H