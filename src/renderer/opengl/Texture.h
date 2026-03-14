//
// Created by maks on 11.03.2026.
//

#ifndef BRICKBOX_TEXTURE_H
#define BRICKBOX_TEXTURE_H
#include "Resource.h"

class Texture : public Resource {
public:
    explicit Texture(GLsizei width, GLsizei height, GLint internalformat);
    Texture(Texture&& other) noexcept = default;
    ~Texture() override;
    void upload(GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels) const;
    void setTMU(unsigned tmu_id) const;
private:
    const GLuint id;
    void bind(bool force = false) const;
};

#endif //BRICKBOX_TEXTURE_H