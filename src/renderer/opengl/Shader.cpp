//
// Created by maks on 10.03.2026.
//

#include <epoxy/gl.h>

#include "Shader.h"

#include <cmath>
#include <iostream>
#include <filesystem>
#include <cstdio>
#include <cstring>

// TODO move this somewhere else
static std::string readShaderFromFile(const char* file_name) {
    FILE *fp = fopen(file_name, "r");
    if (!fp) {
        std::cout << "Failed to open " << file_name << ": " << strerror(errno) << std::endl;
        return "";
    }
    fseek(fp, 0, SEEK_END);
    const size_t length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    std::string shaderContent;
    shaderContent.resize(length);
    if (fread(shaderContent.data(), sizeof(char), length, fp) != length) {
        std::cout << "Failed to read " << file_name << ": " << strerror(errno) << std::endl;
        fclose(fp);
        return "";
    }
    fclose(fp);
    return shaderContent;
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
