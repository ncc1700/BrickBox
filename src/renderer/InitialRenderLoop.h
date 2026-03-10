//
// Created by maks on 10.03.2026.
//

#ifndef BRICKBOX_INITIALRENDERLOOP_H
#define BRICKBOX_INITIALRENDERLOOP_H
#include "AbstractRenderer.h"
#include "opengl/Buffer.h"
#include "opengl/Program.h"
#include "opengl/VertexArray.h"

class InitialRenderLoop : public AbstractRenderer {
public:
    explicit InitialRenderLoop(Window& window);
    ~InitialRenderLoop() override = default;
    void loop() override;
private:
    Program testProgram;
    VertexArray testVAO;
    Buffer vertexBuffer;
    GLuint va_position;
};


#endif //BRICKBOX_INITIALRENDERLOOP_H