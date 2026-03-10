//
// Created by maks on 10.03.2026.
//

#ifndef BRICKBOX_BUFFER_H
#define BRICKBOX_BUFFER_H
#include "Resource.h"


class Buffer : public Resource {
public:
    explicit Buffer();
    ~Buffer() override;
    void allocate(GLsizei size, GLenum usage = GL_STATIC_DRAW) const;
    void bind(GLenum target) const;
    void upload(GLsizei size, const GLvoid* data) const;
private:
    void bindCopyWrite() const;
    const GLuint id;
};


#endif //BRICKBOX_BUFFER_H