//
// Created by maks on 14.03.2026.
//

#include <nlohmann/json.hpp>

#include "BlockModel.h"

#include "../Filesystem.h"

BlockModel::BlockModel(const std::string &name) {
    nlohmann::json model_json = Filesystem::readAsJson("models/block/" + name + ".json");
}
