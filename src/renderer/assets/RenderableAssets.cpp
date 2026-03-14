//
// Created by maks on 14.03.2026.
//

#include "RenderableAssets.h"

#include "../AtlasStitcher.h"

RenderableAssets::RenderableAssets() {
    AtlasStitcher stitcher;
    stitcher.addSourceDir("textures/block");
    stitcher.stitch();
    blockAtlas = stitcher.generateResource(blockTextures);
}
