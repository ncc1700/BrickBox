//
// Created by maks on 14.03.2026.
//

#ifndef BRICKBOX_BLOCKMODEL_H
#define BRICKBOX_BLOCKMODEL_H

#include <nlohmann/json_fwd.hpp>

class BlockModel {
public:
    BlockModel(const std::string &name);
    ~BlockModel();

};

#endif //BRICKBOX_BLOCKMODEL_H