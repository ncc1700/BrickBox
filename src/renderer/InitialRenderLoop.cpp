//
// Created by maks on 10.03.2026.
//

#include <epoxy/gl.h>
#include "InitialRenderLoop.h"
#include "AtlasStitcher.h"

#include <iostream>
#include <ostream>

typedef struct {
    float position[2];
    unsigned int uv[2];
} triangle_vattr;

InitialRenderLoop::InitialRenderLoop(Window& window) : AbstractRenderer(window)
{

    const TextureRef& heavy_core = assets.blockTextures.at("grass_block_side");
    const Texture& atlas_tex = heavy_core.texture;

    const unsigned int uv_top_left[2] = {heavy_core.x, heavy_core.y};
    const unsigned int uv_top_right[2] = {heavy_core.x + heavy_core.width, heavy_core.y};
    const unsigned int uv_bottom_left[2] = {heavy_core.x, heavy_core.y + heavy_core.height};
    const unsigned int uv_bottom_right[2] = {heavy_core.x + heavy_core.width, heavy_core.y + heavy_core.height};

    std::cout << heavy_core.x << " " << heavy_core.y << std::endl;

    const triangle_vattr points[]= {
        {{-1.0f, 1.0f}, {uv_top_left[0], uv_top_left[1]}},
        {{1.0f, 1.0f}, {uv_top_right[0], uv_top_right[1]}},
        {{1.0f, -1.0f}, {uv_bottom_right[0], uv_bottom_right[1]}},
        {{1.0f, -1.0f}, {uv_bottom_right[0], uv_bottom_right[1]}},
        {{-1.0f, -1.0f}, {uv_bottom_left[0], uv_bottom_left[1]}},
        {{-1.0f, 1.0f}, {uv_top_left[0], uv_top_left[1]}},
    };
    vertexBuffer.allocate(sizeof(points));
    vertexBuffer.upload(sizeof(points), points);

    testVAO.addArray(vertexBuffer, {
        {testProgram.position, GL_FLOAT, GL_FALSE, VA_STRUCT_MEMBER(triangle_vattr, position)},
        {testProgram.uv, GL_UNSIGNED_INT, GL_FALSE, VA_STRUCT_MEMBER(triangle_vattr, uv)}
    });

    testProgram.use();
    atlas_tex.setTMU(0);
    glUniform1i(testProgram.sampler.index, 0);

    testVAO.use();


    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glClearDepth(0.5f);
}

void InitialRenderLoop::loop() {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    vertexBuffer.bind(GL_ARRAY_BUFFER);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
