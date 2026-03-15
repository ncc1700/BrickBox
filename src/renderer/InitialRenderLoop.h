//
// Created by maks on 10.03.2026.
//

#ifndef BRICKBOX_INITIALRENDERLOOP_H
#define BRICKBOX_INITIALRENDERLOOP_H
#include "AbstractRenderer.h"
#include "assets/RenderableAssets.h"
#include "opengl/Buffer.h"
#include "opengl/programs/TestProgram.h"
#include "opengl/VertexArray.h"
#include <glm/mat4x4.hpp>

class InitialRenderLoop : public AbstractRenderer {
public:
    explicit InitialRenderLoop(Window& window);
    ~InitialRenderLoop() override = default;
    void loop() override;
private:
    void move(const glm::vec3 &dir);
    float angleX = 0, angleZ = 0;
    GLuint elem_count;
    TestProgram testProgram;
    VertexArray testVAO;
    Buffer vertexBuffer, indexBuffer;
    glm::mat4 translate, rotate, scale,projection;
    RenderableAssets assets;
};


#endif //BRICKBOX_INITIALRENDERLOOP_H