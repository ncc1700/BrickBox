//
// Created by maks on 14.03.2026.
//

#ifndef BRICKBOX_BLOCKMODELLOADER_H
#define BRICKBOX_BLOCKMODELLOADER_H
#include <unordered_map>
#include <nlohmann/json.hpp>

#include "../renderer/assets/BlockModel.h"
#include "../renderer/assets/BlockModel.h"

class BlockModelLoader {
public:
    BlockModelLoader(const std::unordered_map<std::string, const TextureRef> &textures);
    BlockModel loadModel(const std::string& name);
private:
    // Incomplete block model data.
    struct Intermediate {
        bool ambientocclusion = true;
        nlohmann::json display[BlockModel::PositionKey::invalid];
        std::unordered_map<std::string, std::string> textures;
        nlohmann::json elements;
    };

    // Second stage model data: positions are deserialized, textures are resolved
    // to TextureRefs.
    struct PreResolved {
        std::array<BlockModel::DisplayPosition, BlockModel::PositionKey::invalid> display;
        std::unordered_map<std::string, const TextureRef> textures;
        std::vector<BlockModel::Face> faces;
    };

    std::unordered_map<std::string,Intermediate> intermediates;
    const std::unordered_map<std::string, const TextureRef> blockTextures;

    Intermediate loadIntermediate(const std::string &name, bool topLevel);
    const TextureRef& resolveTexture(const Intermediate &intermediate, const std::string& texture);
    const TextureRef& resolveTexture(const PreResolved &pre_resolved, const std::string& texture) const;
    const TextureRef& resolveGlobalTexture(const std::string& texture) const;
    void resolveTextures(const Intermediate &intermediate, PreResolved& pre_resolved);

    void loadElement(PreResolved& pre_resolved, const nlohmann::json &elemen) const;
    void loadFace(PreResolved &pre_resolved, const nlohmann::json &faces, const std::string &name,
        std::tuple<const glm::vec3&,const glm::vec3&,const glm::vec3&,const glm::vec3&> points) const;

    static void deserializePosition(const nlohmann::json &positionJson, BlockModel::DisplayPosition &display);
};


#endif //BRICKBOX_BLOCKMODELLOADER_H