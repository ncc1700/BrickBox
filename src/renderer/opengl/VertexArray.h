//
// Created by maks on 11.03.2026.
//

#ifndef BRICKBOX_VERTEXARRAY_H
#define BRICKBOX_VERTEXARRAY_H
#include <initializer_list>

#include "Resource.h"


class VertexArray : public Resource {
public:
    explicit VertexArray();
    ~VertexArray() override;
    void use() const;
    void add(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer);
private:
    const GLuint id;
};


#endif //BRICKBOX_VERTEXARRAY_H