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

class InitialRenderLoop : public AbstractRenderer {
public:
    explicit InitialRenderLoop(Window& window);
    ~InitialRenderLoop() override = default;
    void loop() override;
private:
    GLuint elem_count;
    TestProgram testProgram;
    VertexArray testVAO;
    Buffer vertexBuffer, indexBuffer;
    RenderableAssets assets;
};


#endif //BRICKBOX_INITIALRENDERLOOP_H