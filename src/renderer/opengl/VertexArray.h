//
// Created by maks on 11.03.2026.
//

#ifndef BRICKBOX_VERTEXARRAY_H
#define BRICKBOX_VERTEXARRAY_H
#include <initializer_list>

#include "Resource.h"
#include "Buffer.h"
#include "Program.h"

class VertexArray : public Resource {
public:
    struct Member {
        Member(const Program::Attribute attrib, const GLenum type, const GLboolean normalized, const GLsizei stride, const void* pointer) :
            index(attrib.index), size(attrib.size), type(type), normalized(normalized), stride(stride), pointer(pointer) {}
        const GLuint index;
        const GLint size;
        const GLenum type;
        const GLboolean normalized;
        const GLsizei stride;
        const void* pointer;
    };

#define OFFSET_VP(STRUCT, MEMBER) reinterpret_cast<const void*>(offsetof(STRUCT, MEMBER))
#define VA_STRUCT_MEMBER(STRUCT, MEMBER) sizeof(STRUCT), OFFSET_VP(STRUCT, MEMBER)

    explicit VertexArray();
    ~VertexArray() override;
    void use() const;
    void addArray(const Buffer &buffer, const std::initializer_list<Member> &members) const;
    void setElementBuffer(const Buffer& buffer) const;
private:
    const GLuint id;
};


#endif //BRICKBOX_VERTEXARRAY_H