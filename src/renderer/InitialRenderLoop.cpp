//
// Created by maks on 10.03.2026.
//

#include <epoxy/gl.h>
#include "InitialRenderLoop.h"

#include <iostream>
#include <ostream>

typedef struct {
    float position[2];
} triangle_vattr;

InitialRenderLoop::InitialRenderLoop(Window& window) : AbstractRenderer(window),
                                                       testProgram("test", {
                                                                       Shader(GL_VERTEX_SHADER, "test.vert"),
                                                                       Shader(GL_FRAGMENT_SHADER, "test.frag")
                                                       })
{
    constexpr triangle_vattr points[]= {
        {0.0f, 1.0f},
        {1.0f, 0.0f},
        {-1.0f, 0.0f},
    };
    vertexBuffer.allocate(sizeof(points));
    vertexBuffer.upload(sizeof(points), points);
    va_position = testProgram.getAttributeLocation("position");
    std::cout << va_position << std::endl;

    testProgram.use();
    vertexBuffer.bind(GL_ARRAY_BUFFER);
    testVAO.use();
    testVAO.add(va_position, 2, GL_FLOAT, GL_FALSE, sizeof(triangle_vattr), nullptr);


    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glClearDepth(0.5f);
}

void InitialRenderLoop::loop() {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    vertexBuffer.bind(GL_ARRAY_BUFFER);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
