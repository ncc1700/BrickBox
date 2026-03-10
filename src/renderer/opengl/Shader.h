//
// Created by maks on 10.03.2026.
//

#ifndef BRICKBOX_SHADER_H
#define BRICKBOX_SHADER_H
#include "Resource.h"
#include <string>



class Shader : public Resource {
public:
    explicit Shader(GLuint type, const char* file_name);
    explicit Shader(GLuint type, std::string const &source, const char* debug_name);
    ~Shader() override;
    [[nodiscard]] GLuint getId() const;
private:
    const GLuint id;
    bool ready = false;
    std::string error;
};


#endif //BRICKBOX_SHADER_H