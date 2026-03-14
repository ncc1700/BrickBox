//
// Created by maks on 11.03.2026.
//

#include <epoxy/gl.h>
#include "Texture.h"

static GLuint bound_texture = 0;

static GLuint allocateTexture() {
    GLuint id = 0;
    glGenTextures(1, &id);
    return id;
}

Texture::Texture(const GLsizei width, const GLsizei height, const GLint internalformat) : id(allocateTexture()) {
    if (id == 0) return;
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, nullptr);
    bound_texture = id;
}

void Texture::upload(const GLint xoffset, const GLint yoffset, const GLsizei width, const GLsizei height, const GLenum format, const GLenum type, const void *pixels) const {
    bind();
    glTexSubImage2D(GL_TEXTURE_2D, 0, xoffset, yoffset, width, height, format, type, pixels);
}

void Texture::setTMU(const unsigned tmu_id) const {
    glActiveTexture(GL_TEXTURE0 + tmu_id);
    bind(true);
}

void Texture::bind(const bool force) const {
    if (id != bound_texture || force) {
        glBindTexture(GL_TEXTURE_2D, id);
        bound_texture = id;
    }
}

Texture::~Texture() {
    if (id != 0) glDeleteTextures(1, &id);
}
