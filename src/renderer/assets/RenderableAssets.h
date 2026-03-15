//
// Created by maks on 14.03.2026.
//

#ifndef BRICKBOX_RENDERABLEASSETS_H
#define BRICKBOX_RENDERABLEASSETS_H

#include <list>
#include <unordered_map>
#include <memory>
#include <string>

#include "../opengl/Texture.h"
#include "TextureRef.h"

class RenderableAssets : public Resource {
public:
    RenderableAssets();
    std::unique_ptr<Texture> blockAtlas;
    std::unordered_map<std::string, const TextureRef> blockTextures;
private:
};


#endif //BRICKBOX_RENDERABLEASSETS_H