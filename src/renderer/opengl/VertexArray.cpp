//
// Created by maks on 11.03.2026.
//

#include <epoxy/gl.h>
#include "VertexArray.h"

static GLuint current_vertex_array = 0;

static GLuint allocVertexArray() {
    GLuint id = 0;
    glGenVertexArrays(1, &id);
    return id;
}

VertexArray::VertexArray() : id(allocVertexArray()) {
    if (id == 0) return;
}

void VertexArray::addArray(const Buffer &buffer, const std::initializer_list<Member> &members) const {
    if (id != current_vertex_array) use();
    buffer.bind(GL_ARRAY_BUFFER);
    for (const auto& member : members) {
        glEnableVertexAttribArray(member.index);
        glVertexAttribPointer(member.index, member.size, member.type, member.normalized, member.stride, member.pointer);
    }
}

void VertexArray::setElementBuffer(const Buffer &buffer) const {
    if (id != current_vertex_array) use();
    buffer.bind(GL_ELEMENT_ARRAY_BUFFER);
}

void VertexArray::use() const {
    if (id != current_vertex_array) {
        glBindVertexArray(id);
        current_vertex_array = id;
    }
}

VertexArray::~VertexArray() {
    if (id != 0) {
        if (id == current_vertex_array) {
            current_vertex_array = 0;
            glBindVertexArray(0);
        }
        glDeleteVertexArrays(1, &id);
    }
}
