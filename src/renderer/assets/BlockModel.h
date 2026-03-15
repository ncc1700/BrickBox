//
// Created by maks on 14.03.2026.
//

#ifndef BRICKBOX_BLOCKMODEL_H
#define BRICKBOX_BLOCKMODEL_H

#include "TextureRef.h"
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class BlockModel {
public:
    enum PositionKey {
        thirdperson_righthand, thirdperson_lefthand, firstperson_righthand, firstperson_lefthand, gui, head, ground, fixed, invalid
    };

    struct DisplayPosition {
        //bool specified = false;
        glm::vec3 rotation = {0, 0, 0};
        glm::vec3 translation = {0, 0, 0};
        glm::vec3 scale = {1, 1, 1};
    };

    struct Face {
        // Models can supply custom UVs within a texture
        const TextureRef tex;
        glm::vec3 points[4];
        glm::vec4 uv;
    };


    const bool ambient_occlusion;
    const std::array<DisplayPosition, invalid> display;
    const std::vector<Face> faces;

    BlockModel(bool ambient_occlusion, const std::array<DisplayPosition, invalid> &display, const std::vector<Face> &faces);
};

#endif //BRICKBOX_BLOCKMODEL_H