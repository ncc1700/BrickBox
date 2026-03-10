//
// Created by maks on 10.03.2026.
//

#include <epoxy/gl.h>
#include "Buffer.h"

#include <iterator>

static GLuint copyWriteTarget = 0;

static GLuint allocateBuffer() {
    GLuint buffer = 0;
    glGenBuffers(1, &buffer);
    return buffer;
}

Buffer::Buffer() : id(allocateBuffer()) {}
Buffer::~Buffer() {
    if (id != 0) glDeleteBuffers(1, &id);
}

void Buffer::bindCopyWrite() const {
    if (copyWriteTarget != id) {
        glBindBuffer(GL_COPY_WRITE_BUFFER, id);
        copyWriteTarget = id;
    }
}

void Buffer::allocate(const GLsizei size, const GLenum usage) const {
    bindCopyWrite();
    glBufferData(GL_COPY_WRITE_BUFFER, size, nullptr, usage);
}

void Buffer::bind(const GLenum target) const {
    if (target == GL_COPY_WRITE_BUFFER && copyWriteTarget == id) return;
    glBindBuffer(target, id);
}

void Buffer::upload(const GLsizei size, const GLvoid* data) const {
    bindCopyWrite();
    glBufferSubData(GL_COPY_WRITE_BUFFER, 0, size, data);
}
