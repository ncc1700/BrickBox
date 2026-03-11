//
// Created by maks on 10.03.2026.
//

#include <epoxy/gl.h>
#include "InitialRenderLoop.h"

#include <iostream>
#include <ostream>

typedef struct {
    float position[2];
    float color[3];
} triangle_vattr;

InitialRenderLoop::InitialRenderLoop(Window& window) : AbstractRenderer(window)
{
    constexpr triangle_vattr points[]= {
        {{0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
        {{1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
        {{-1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
    };
    vertexBuffer.allocate(sizeof(points));
    vertexBuffer.upload(sizeof(points), points);

    testVAO.addArray(vertexBuffer, {
        {testProgram.position, GL_FLOAT, GL_FALSE, VA_STRUCT_MEMBER(triangle_vattr, position)},
        {testProgram.color, GL_FLOAT, GL_FALSE, VA_STRUCT_MEMBER(triangle_vattr, color)}
    });

    testProgram.use();
    testVAO.use();


    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glClearDepth(0.5f);
}

void InitialRenderLoop::loop() {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    vertexBuffer.bind(GL_ARRAY_BUFFER);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
