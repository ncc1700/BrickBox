//
// Created by maks on 14.03.2026.
//

#include <nlohmann/json.hpp>

#include "BlockModel.h"

#include <iostream>

#include "../../Filesystem.h"

BlockModel::BlockModel(bool ambient_occlusion, const std::array<DisplayPosition, invalid> &display, const std::vector<Face> &faces)
    : ambient_occlusion(ambient_occlusion), faces(faces), display(display) {}

