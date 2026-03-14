//
// Created by maks on 11.03.2026.
//

#include "AtlasStitcher.h"

#include <iostream>
#include <rectpack2D/finders_interface.h>
#include <stb/stb_image.h>

#include <utility>

#include "../Filesystem.h"


static GLint max_side = 8192;

static bool str_ends_with(const std::string &str1, const std::string &str2) {
    const auto str2_len = str2.size();
    const std::string str1_tail = str1.substr(str1.size() - str2_len, str2_len);
    return str1_tail == str2;
}

AtlasStitcher::Rect::Rect(const rect_type &rect_, std::string name) : rect(rect_), path(std::move(name)) {}

auto &AtlasStitcher::Rect::get_rect() {
    return rect;
}

static unsigned int round_pow2(unsigned int v) {
    // compute the next highest power of 2 of 32-bit v
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

void AtlasStitcher::addSourceDir(const std::string &dir) {
    Filesystem::iterateFilePaths(dir, [this](const std::string &file_path) {
        if (!str_ends_with(file_path, ".png")) return;
        int w, h, c;
        if (stbi_info(file_path.c_str(), &w, &h, &c)) {
            stitch_entries.emplace_front(rect_type(0, 0, w, h), file_path);
            //std::cout << "Added " << w << "x" << h << " at " << file_path << " to stitch queue" << std::endl;
        } else {
            std::cout << "Not including "<< file_path << " because stbi_info failed" << std::endl;
        }
    });
}

void AtlasStitcher::stitch() {
    bool aborted = false;

    const auto report_successful = [](rect_type&) {
        return rectpack2D::callback_result::CONTINUE_PACKING;
    };

    const auto report_unsuccessful = [&aborted](rect_type&) {
        aborted = true;
        return rectpack2D::callback_result::ABORT_PACKING;
    };

    size = rectpack2D::find_best_packing<spaces_type>(
        stitch_entries,
        rectpack2D::make_finder_input(max_side, -4, report_successful, report_unsuccessful, rectpack2D::flipping_option::DISABLED)
    );

    successful = !aborted;
    if (successful) {
        size.w = static_cast<int>(round_pow2(size.w));
        size.h = static_cast<int>(round_pow2(size.h));
        std::cout << "Stitched " << size.w << "x" << size.h << " atlas" << std::endl;
    }
}

std::unique_ptr<Texture> AtlasStitcher::generateResource(std::unordered_map<std::string, TextureRef> &refs) {
    if (!successful || (size.w == 0 || size.h == 0)) {
        std::cout << "Did not generate atlas resource: nothing to generate" << std::endl;
    }
    auto atlas = std::make_unique<Texture>(size.w, size.h, GL_RGBA8);
    for (auto& entry : stitch_entries) {
        int x, y, c;
        void* tex_content = stbi_load(entry.path.c_str(), &x, &y, &c, 4);
        if (tex_content == nullptr) {
            std::cout << "Failed to load texture " << entry.path << std::endl;
            continue;
        }
        const auto& rect = entry.get_rect();
        if (x != rect.w || y != rect.h) {
            std::cout << "Texture " << entry.path << " doesn't have the same size" << std::endl;
            continue;
        }
        atlas->upload(rect.x, rect.y, rect.w, rect.h, GL_RGBA, GL_UNSIGNED_BYTE, tex_content);
        free(tex_content);
        const auto atlas_key = Filesystem::removeExtension(Filesystem::fileName(entry.path));
        refs.emplace(atlas_key, TextureRef(*atlas, rect.x, rect.y, rect.w, rect.h));
        //std::cout << "Loaded " << atlas_key << std::endl;
    }
    return std::move(atlas);
}
