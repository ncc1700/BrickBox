//
// Created by maks on 10.03.2026.
//

#include <epoxy/gl.h>
#include <iostream>
#include "Program.h"

#include <math.h>

Program::Program(const char *debug_name, const std::initializer_list<Shader> shaders) : id(glCreateProgram()) {
    if (id == 0) return;
    for (auto& shader : shaders) {
        const GLuint shader_id = shader.getId();
        if (shader_id == 0) {
            std::cout << "Not initializing " << debug_name << " because one of the shaders didn't compile";
            return;
        }
        glAttachShader(id, shader_id);
    }
    glLinkProgram(id);
    GLint status = GL_FALSE;
    glGetProgramiv(id, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint length = 0;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
        GLchar log[length + 1];
        log[0] = 0;
        glGetProgramInfoLog(id, length, &length, log);
        std::cout << "Failed to link program " << debug_name << ": " << std::endl << log << std::endl;
    }else {
        std::cout << "Successfully linked program " << debug_name << std::endl;
        ready = true;
    }
}

GLuint Program::getId() const {
    return id;
}

GLint Program::getUniformLocation(const char *name) const {
    if (!ready) return -1;
    return glGetUniformLocation(id, name);
}

GLint Program::getAttributeLocation(const char * name) const {
    if (!ready) return -1;
    return glGetAttribLocation(id, name);
}

void Program::use() const {
    glUseProgram(id);
}

Program::Attribute Program::getAttribute(const char *name, const GLint size) const {
    return {getAttributeLocation(name), size};
}

Program::~Program() {
    if (id != 0) glDeleteProgram(id);
}
