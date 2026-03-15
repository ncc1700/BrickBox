//
// Created by maks on 11.03.2026.
//

#ifndef BRICKBOX_ATLASSTITCHER_H
#define BRICKBOX_ATLASSTITCHER_H
#include <list>
#include <string>
#include <memory>
#include <rectpack2D/finders_interface.h>

#include "assets/RenderableAssets.h"

class AtlasStitcher {
public:
    // Add all textures based on an incomplete namespaced path (for example, minecraft:block/)
    void addResources(const std::string& path);
    void stitch();
    std::unique_ptr<Texture> generateResource(std::unordered_map<std::string, const TextureRef> &refs);
private:
    using spaces_type = rectpack2D::empty_spaces<false>;
    using rect_type = rectpack2D::output_rect_t<spaces_type>;

    class Rect {
        rect_type rect;
    public:
        const std::string path;
        const std::string name;
        Rect(const rect_type& rect_, std::string path, std::string name);
        auto& get_rect();
    };

    rectpack2D::rect_wh size;
    bool successful = false;
    std::list<Rect> stitch_entries;
};


#endif //BRICKBOX_ATLASSTITCHER_H