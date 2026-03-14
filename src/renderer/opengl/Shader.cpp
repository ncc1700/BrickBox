//
// Created by maks on 10.03.2026.
//

#include <epoxy/gl.h>

#include "Shader.h"

#include <cmath>
#include <iostream>

#include "../../Filesystem.h"

static std::string readShaderFromFile(const char* file_name) {
    if (auto shaderContent = Filesystem::readAsString(file_name); shaderContent.has_value()) return shaderContent.value();
    return "";
}

Shader::Shader(const GLuint type, const char *file_name) : Shader (type, readShaderFromFile(file_name), file_name) {}

Shader::Shader(const GLuint type, std::string const &source, const char* debug_name) : id(glCreateShader(type)){
    if (id == 0 || source.empty()) return;
    const char* shaderSource_c = source.c_str();
    glShaderSource(id, 1, &shaderSource_c, nullptr);
    glCompileShader(id);
    GLint status = GL_FALSE;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        GLchar log[length + 1];
        log[0] = 0;
        glGetShaderInfoLog(id, length, &length, log);
        error = std::move(std::string(log));
        std::cout << "Failed to compile shader " << debug_name << ": " << std::endl << log << std::endl;
    }else {
        std::cout << "Successfully compiled shader " << debug_name << std::endl;
        ready = true;
    }
}

GLuint Shader::getId() const {
    if (!ready) return 0;
    return id;
}

Shader::~Shader() {
    if (id != 0) glDeleteShader(id);
}
