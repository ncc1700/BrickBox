//
// Created by maks on 11.03.2026.
//

#include <epoxy/gl.h>
#include "VertexArray.h"

static GLuint allocVertexArray() {
    GLuint id = 0;
    glGenVertexArrays(1, &id);
    return id;
}

VertexArray::VertexArray() : id(allocVertexArray()) {
    if (id == 0) return;
    glBindVertexArray(id);
}

void VertexArray::add(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer) {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void VertexArray::use() const {
    glBindVertexArray(id);
}

VertexArray::~VertexArray() {
    if (id != 0) glDeleteVertexArrays(1, &id);
}
