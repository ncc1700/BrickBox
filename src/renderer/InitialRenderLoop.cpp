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
#include "glfw/Window.h"
#include <glm/gtc/matrix_transform.hpp>

typedef struct {
    float position[3];
    unsigned int uv[2];
} triangle_vattr;

InitialRenderLoop::InitialRenderLoop(Window& window) : AbstractRenderer(window), translate(1.0f), rotate(1.0f), scale(1.0f), projection(1.0f)
{
    projection = glm::perspective(45.0f, 1.0f, 0.01f, 0.95f);
    scale = glm::scale(scale, glm::vec3(0.007f));
    translate = glm::translate(translate, glm::vec3(0.0f, 0.0f, -64.0f));


    BlockModelLoader loader(assets.blockTextures);
    BlockModel blockModel = loader.loadModel("minecraft:block/composter");
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

    glUniformMatrix4fv(testProgram.projection.index, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(testProgram.transform.index, 1, GL_FALSE, glm::value_ptr(scale * translate));

    //glm::mat4 ident = glm::identity<glm::mat4>();
    //glUniformMatrix4fv(testProgram.transform.index, 1, GL_FALSE, glm::value_ptr(ident));

    testVAO.use();

    elem_count = num_elems;


    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void InitialRenderLoop::move(const glm::vec3 &dir) {
    translate = glm::translate(translate, xyz(glm::inverse(rotate) * glm::vec4(dir.x, dir.y, dir.z, 1.0f)));
}

void InitialRenderLoop::loop() {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    const glm::vec2 mousevec = parent.getCursorDelta();
    bool mat_update = false;
    if (mousevec.x != 0.0f || mousevec.y != 0.0f) {
        angleX += mousevec.y / 1000.0f;
        angleZ += mousevec.x / 1000.0f;
        const glm::mat4 rotate_x = glm::rotate(glm::identity<glm::mat4>(), angleX, glm::vec3{1.0f, 0.0f, 0.0f});
        rotate = glm::rotate(rotate_x, angleZ, glm::vec3{0.0f, 1.0f, 0.0f});

        mat_update = true;
    }
    if (glfwGetKey(parent.window, GLFW_KEY_W) == GLFW_PRESS) {
        move({0.0f, 0.0f, 0.5f});
        mat_update = true;
    }

    if (glfwGetKey(parent.window, GLFW_KEY_S) == GLFW_PRESS) {
        move({0.0f, 0.0f, -0.5f});
        mat_update = true;
    }

    if (glfwGetKey(parent.window, GLFW_KEY_A) == GLFW_PRESS) {
        move({0.5f, 0.0f, 0.0f});
        mat_update = true;
    }

    if (glfwGetKey(parent.window, GLFW_KEY_D) == GLFW_PRESS) {
        move({-0.5f, 0.0f, 0.0f});
        mat_update = true;
    }

    if (mat_update) {
        glm::mat4 final =  scale * rotate * translate;
        glUniformMatrix4fv(testProgram.transform.index, 1, GL_FALSE, glm::value_ptr(final));
    }

    glDrawElements(GL_TRIANGLES, elem_count, GL_UNSIGNED_INT, nullptr);

}
