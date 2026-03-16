//
// Created by maks on 14.03.2026.
//

#include "BlockModelLoader.h"
#include "../Filesystem.h"
#include <iostream>

#include <glm/mat4x4.hpp>

#include "glm/ext/matrix_transform.hpp"

BlockModelLoader::BlockModelLoader(const std::unordered_map<std::string, const TextureRef> &textures) : blockTextures(textures) {}

BlockModel BlockModelLoader::loadModel(const std::string& name) {
    const Intermediate intermediate = loadIntermediate(name,true);
    PreResolved pre_resolved;
    resolveTextures(intermediate, pre_resolved);
    for (int i = 0; i < BlockModel::PositionKey::invalid; ++i) {
        const auto& displayJson = intermediate.display[i];
        if (displayJson.empty()) continue;
        deserializePosition(displayJson, pre_resolved.display[i]);
    }
    for (const auto& element : intermediate.elements) {
        loadElement(pre_resolved, element);
    }
    return BlockModel(intermediate.ambientocclusion, pre_resolved.display, pre_resolved.faces);
}

static glm::mat4x4 setupRotate(const nlohmann::json &rotate) {
    if (!rotate.contains("angle")) return glm::identity<glm::mat4x4>();
    const float angle = rotate["angle"];
    if (angle == 0.0f) return glm::identity<glm::mat4x4>();
    glm::vec3 origin = {0, 0, 0};
    if (rotate.contains("origin")) {
        const auto& originj = rotate["origin"];
        origin[0] = originj[0];
        origin[1] = originj[1];
        origin[2] = originj[2];
    }
    glm::vec3 axisv = {0, 0, 0};
    const std::string axis = rotate["axis"];
    if (axis == "x") axisv.x = 1.0f;
    if (axis == "y") axisv.y = 1.0f;
    if (axis == "z") axisv.z = 1.0f;

    // TODO implement rescale
    auto rotation = glm::identity<glm::mat4x4>();
    rotation = glm::translate(rotation, origin);
    rotation = glm::rotate(rotation, glm::radians(angle), axisv);
    rotation = glm::translate(rotation, -origin);
    return rotation;
}

void BlockModelLoader::loadFace(PreResolved &pre_resolved, const nlohmann::json &faces, const std::string &name,
                                const std::array<glm::vec3, 4> &points, const glm::vec4& uv_default) const {
    if (!faces.contains(name)) return;
    const nlohmann::json &facej = faces[name];
    const std::string &texture = facej["texture"];

    glm::vec4 uv(uv_default);
    if (facej.contains("uv")) {
        const auto& uvj = facej["uv"];
        uv.x = uvj[0];
        uv.y = uvj[1];
        uv.z = uvj[2];
        uv.w = uvj[3];
    }
    uv /= glm::vec4(16);


    std::array<unsigned char, 4> pointSwizzle = {0, 1, 2, 3};

    if (facej.contains("rotation")) {
        switch (const unsigned int rotation = facej["rotation"]) {
            case 0: break;
            case 90: pointSwizzle = {1, 2, 3, 0}; break;
            case 180: {
                std::swap(uv.y, uv.w);
                std::swap(uv.x, uv.z);
            } break;
            case 270: pointSwizzle = {3, 0, 1, 2}; break;
            default:
                throw std::invalid_argument("Unknown UV rotation: " + std::to_string(rotation));
        }
    }


    const TextureRef texture_ref = resolveTexture(pre_resolved, texture);
    uv.x = texture_ref.x + (uv.x * texture_ref.width);
    uv.y = texture_ref.y + (uv.y * texture_ref.height);
    uv.z = texture_ref.x + (uv.z * texture_ref.width);
    uv.w = texture_ref.y + (uv.w * texture_ref.height);


    pre_resolved.faces.emplace_back(BlockModel::Face{
        .tex = texture_ref,
        .points = {
            points[pointSwizzle[0]], points[pointSwizzle[1]], points[pointSwizzle[2]], points[pointSwizzle[3]],
        },
        .uv = uv
    });
}

void BlockModelLoader::loadElement(PreResolved &pre_resolved, const nlohmann::json &element) const {
    const auto& from = element["from"];
    const auto& to = element["to"];

    const glm::vec3 fromv = {from[0], from[1], from[2]};
    const glm::vec3 tov = {to[0], to[1], to[2]};

    const glm::mat4 el_transform = element.contains("rotation") ? setupRotate(element["rotation"]) : glm::identity<glm::mat4x4>();

    const glm::vec3 point1 = xyz((el_transform * glm::vec4{fromv.x, tov.y, fromv.z, 1.0f}));
    const glm::vec3 point2 = xyz((el_transform * glm::vec4{fromv.x, tov.y, tov.z, 1.0f}));
    const glm::vec3 point3 = xyz((el_transform * glm::vec4{tov.x, tov.y, tov.z, 1.0f}));
    const glm::vec3 point4 = xyz((el_transform * glm::vec4{tov.x, tov.y, fromv.z, 1.0f}));
    const glm::vec3 point5 = xyz((el_transform * glm::vec4{fromv.x, fromv.y, fromv.z, 1.0f}));
    const glm::vec3 point6 = xyz((el_transform * glm::vec4{fromv.x, fromv.y, tov.z, 1.0f}));
    const glm::vec3 point7 = xyz((el_transform * glm::vec4{tov.x, fromv.y, tov.z, 1.0f}));
    const glm::vec3 point8 = xyz((el_transform * glm::vec4{tov.x, fromv.y, fromv.z, 1.0f}));


    const glm::vec4 def_uv_tb = {fromv.x, fromv.z, tov.x, tov.z};
    const glm::vec4 def_uv_sn = {fromv.x, fromv.y, tov.x, tov.y};
    const glm::vec4 def_uv_we = {fromv.x, fromv.y, tov.x, tov.y};

    const auto& faces = element["faces"];

    std::vector<BlockModel::Face> facesv;
    facesv.reserve(6);

    loadFace(pre_resolved, faces, "up", { point2, point1, point4, point3 }, def_uv_tb);
    loadFace(pre_resolved, faces, "down", { point5, point6, point7, point8 }, def_uv_tb);
    loadFace(pre_resolved, faces, "south", { point6, point2, point3, point7 }, def_uv_sn);
    loadFace(pre_resolved, faces, "north", { point8, point4, point1, point5 }, def_uv_sn);
    loadFace(pre_resolved, faces, "west", { point5, point1, point2, point6 }, def_uv_we);
    loadFace(pre_resolved, faces, "east", { point7, point3, point4, point8 }, def_uv_we);

    facesv.shrink_to_fit();
}

static BlockModel::PositionKey fromString(const std::string &str) {
    if (str == "thirdperson_righthand") return BlockModel::PositionKey::thirdperson_righthand;
    if (str == "thirdperson_lefthand") return BlockModel::PositionKey::thirdperson_lefthand;
    if (str == "firstperson_righthand") return BlockModel::PositionKey::firstperson_righthand;
    if (str == "firstperson_lefthand") return BlockModel::PositionKey::firstperson_lefthand;
    if (str == "gui") return BlockModel::PositionKey::gui;
    if (str == "head") return BlockModel::PositionKey::head;
    if (str == "fixed") return BlockModel::PositionKey::fixed;
    return BlockModel::PositionKey::invalid;
}



BlockModelLoader::Intermediate BlockModelLoader::loadIntermediate(const std::string &name, bool topLevel) {
    {
        // Try to find a cached copy of the intermediate before attempting to load a new one
        if (const auto cache_iter = intermediates.find(name); cache_iter != intermediates.end()) {
            std::cout << "Cache hit: " << name << std::endl;
            return cache_iter->second;
        }
    }

    const std::string& path = Filesystem::fromNamespacedPath(name, Filesystem::AssetTypes.MODEL);
    std::cout << "Load: " << name << std::endl;

    nlohmann::json model_json = Filesystem::readAsJson(path);
    Intermediate base = model_json.contains("parent") ? loadIntermediate(model_json["parent"], false) : Intermediate();

    std::cout << "Now processing " << name << std::endl;
    if (model_json.contains("ambientocclusion")) base.ambientocclusion = model_json["ambientocclusion"];
    if (model_json.contains("display")) {
        const auto display = model_json["display"];
        for (auto it = display.begin(); it != display.end(); ++it) {
            const auto posKey = fromString(it.key());
            if (posKey == BlockModel::invalid) continue;
            std::cout << "Override display: " << posKey << std::endl;
            base.display[posKey] = it.value();
        }
    }
    if (model_json.contains("textures")) {
        const auto textures = model_json["textures"];
        for (auto it = textures.begin(); it != textures.end(); ++it) {
            const auto& key = it.key();
            std::cout << "Override texture: " << key << std::endl;
            base.textures[key] = it.value();
        }
    }
    if (model_json.contains("elements")) {
        std::cout << "Override elements" << std::endl;
        base.elements = model_json["elements"];
    }

    // Don't cache top level models, because the caching system is only intended to boost parent resolution time
    if (!topLevel) intermediates[name] = base;
    return base;
}

void BlockModelLoader::resolveTextures(const Intermediate &intermediate, PreResolved &pre_resolved) {
    for (const auto&[name, texid] : intermediate.textures) {

        pre_resolved.textures.emplace(name, resolveTexture(intermediate, texid));
    }
}

const TextureRef &BlockModelLoader::resolveGlobalTexture(const std::string &texture) const {
    const auto& bt_iter = blockTextures.find(Filesystem::defaultify(texture));
    if (bt_iter == blockTextures.end()) throw std::runtime_error("Unknown texture "+texture);
    return bt_iter->second;
}

const TextureRef &BlockModelLoader::resolveTexture(const PreResolved &pre_resolved, const std::string &texture) const {
    if (texture.empty()) throw std::invalid_argument("Attempted to resolve an empty texture ID");
    if (texture[0] == '#') {
        const auto& iter = pre_resolved.textures.find(texture.substr(1));
        if (iter == pre_resolved.textures.end()) throw std::invalid_argument("Texture ID ref " + texture +  " is not present in model textures");
        return iter->second;
    }
    return resolveGlobalTexture(texture);
}

const TextureRef &BlockModelLoader::resolveTexture(const Intermediate &intermediate, const std::string& texture) {
    if (texture.empty()) throw std::invalid_argument("Attempted to resolve an empty texture ID");
    if (texture[0] == '#') {
        const auto& iter = intermediate.textures.find(texture.substr(1));
        if (iter == intermediate.textures.end()) throw std::invalid_argument("Texture ID ref " + texture +  " is not present in model textures");
        return resolveTexture(intermediate, iter->second);
    }
    return resolveGlobalTexture(texture);
}

void BlockModelLoader::deserializePosition(const nlohmann::json &positionJson, BlockModel::DisplayPosition &display) {
    const auto& rotation = positionJson["rotation"];
    const auto& translation = positionJson["translation"];
    const auto& scale = positionJson["scale"];
    display.rotation[0] = rotation[0];
    display.rotation[1] = rotation[1];
    display.rotation[2] = rotation[2];

    display.translation[0] = translation[0];
    display.translation[1] = translation[1];
    display.translation[2] = translation[2];

    display.scale[0] = scale[0];
    display.scale[1] = scale[1];
    display.scale[2] = scale[2];
}
