//
// Created by maks on 10.03.2026.
//

#ifndef BRICKBOX_PROGRAM_H
#define BRICKBOX_PROGRAM_H

#include <tuple>

#include "Resource.h"
#include "Shader.h"


class Program : public Resource {
public:
    explicit Program(const char* debug_name, std::initializer_list<Shader> shaders);
    ~Program() override;
    [[nodiscard]] GLuint getId() const;
    GLint getUniformLocation(const char* name) const;
    GLint getAttributeLocation(const char* name) const;
    void use() const;
private:
    const GLuint id;
    bool ready = false;
    std::string error;
};


#endif //BRICKBOX_PROGRAM_H