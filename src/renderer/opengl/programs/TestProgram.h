//
// Created by maks on 11.03.2026.
//

#ifndef BRICKBOX_TESTPROGRAM_H
#define BRICKBOX_TESTPROGRAM_H
#include "../Program.h"


class TestProgram : public Program {
public:
    TestProgram() : Program("TestProgram", {
        Shader(GL_VERTEX_SHADER, "test.vert"),
        Shader(GL_FRAGMENT_SHADER, "test.frag")
    }) {};
    Attribute position = getAttribute("position", 3);
    Attribute uv = getAttribute("uv", 2);
    Uniform sampler = getUniform("tex_sampler");
    Uniform transform = getUniform("transform");

};


#endif //BRICKBOX_TESTPROGRAM_H