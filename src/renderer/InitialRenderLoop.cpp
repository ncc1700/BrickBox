//
// Created by maks on 10.03.2026.
//

#include <epoxy/gl.h>
#include "InitialRenderLoop.h"
#include "AtlasStitcher.h"

#include <iostream>
#include <ostream>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "../assets/BlockModelLoader.h"

typedef struct {
    float position[3];
    unsigned int uv[2];
} triangle_vattr;

InitialRenderLoop::InitialRenderLoop(Window& window) : AbstractRenderer(window)
{

    BlockModelLoader loader(assets.blockTextures);
    BlockModel blockModel = loader.loadModel("minecraft:block/comparator_on_subtract");
    std::cout << "Faces: " << blockModel.faces.size() << std::endl;

    const TextureRef& heavy_core = assets.blockTextures.at("minecraft:block/grass_block_side");
    const Texture& atlas_tex = heavy_core.texture;

    const GLuint indices[] = {2, 1, 0, 0, 3, 2};

    int fv_index = 0;
    int fi_index = 0;
    const auto num_faces = blockModel.faces.size();
    const auto num_verts = num_faces * 4;
    const auto num_elems = num_faces * 6;
    triangle_vattr faceverts[num_verts];
    GLuint faceindices[num_elems];
    for (const auto& face : blockModel.faces) {
        const int fv_base = fv_index;
        for (int i = 0; i < 4; i++) {
            const auto& point = face.points[i];
            auto& vattr = faceverts[fv_index++];
            vattr.position[0] = point.x;
            vattr.position[1] = point.y;
            vattr.position[2] = point.z;
            vattr.uv[0] = (i == 0 || i == 1) ? face.uv.x : face.uv.z;
            vattr.uv[1] = (i == 0 || i == 3) ? face.uv.w : face.uv.y;
        }
        for (int i = 0; i < 6; i++) {
            faceindices[fi_index++] = indices[i] + fv_base;
        }
    }

    vertexBuffer.allocate(sizeof(triangle_vattr) * num_verts);
    vertexBuffer.upload(sizeof(triangle_vattr) * num_verts, faceverts);

    indexBuffer.allocate(sizeof(GLuint) * num_elems);
    indexBuffer.upload(sizeof(GLuint) * num_elems, faceindices);

    testVAO.addArray(vertexBuffer, {
        {testProgram.position, GL_FLOAT, GL_FALSE, VA_STRUCT_MEMBER(triangle_vattr, position)},
        {testProgram.uv, GL_UNSIGNED_INT, GL_FALSE, VA_STRUCT_MEMBER(triangle_vattr, uv)}
    });

    testVAO.setElementBuffer(indexBuffer);

    testProgram.use();
    atlas_tex.setTMU(0);
    glUniform1i(testProgram.sampler.index, 0);

    constexpr glm::vec3 rotate(1.0f, 1.0f, 0.0f);
    glm::mat4x4 transform = glm::identity<glm::mat4x4>();
    //glm::mat4x4 transform = glm::rotate(glm::identity<glm::mat4x4>(), glm::radians(30.0f), rotate);
    //transform = glm::translate(transform, glm::vec3(0.5, 0, -0.5));
    glUniformMatrix4fv(testProgram.transform.index, 1, GL_FALSE, glm::value_ptr(transform));

    testVAO.use();

    elem_count = num_elems;


    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glClearDepth(0.5f);
    glEnable(GL_DEPTH_TEST);
}

void InitialRenderLoop::loop() {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glDrawElements(GL_TRIANGLES, elem_count, GL_UNSIGNED_INT, nullptr);

}
