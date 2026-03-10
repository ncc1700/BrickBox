//
// Created by maks on 10.03.2026.
//

#include "Resource.h"

#include <iostream>
#include <ostream>
#include <stdexcept>

Resource::Resource() {
#ifdef DEBUG_RESOURCE_ALLOCATION
    window = glfwGetCurrentContext();
    if (window == nullptr) {
        std::cout << "Attempted to allocate OpenGL resource from wrong thread" << std::endl;
        std::terminate();
    }
#endif
}

Resource::~Resource() {
#ifdef DEBUG_RESOURCE_ALLOCATION
    if (glfwGetCurrentContext() != window) {
        std::cout << "Attempted to deallocate resource on the wrong thread" << std::endl;
        std::terminate();
    }
#endif
}
