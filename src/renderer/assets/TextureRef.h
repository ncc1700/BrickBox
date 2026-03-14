//
// Created by maks on 14.03.2026.
//

#ifndef BRICKBOX_TEXTUREREF_H
#define BRICKBOX_TEXTUREREF_H

class Texture;

struct TextureRef {
    TextureRef(const Texture& texture, const int x, const int y, const int w, const int h) : texture(texture), x(x), y(y), width(w), height(h) {}
    const Texture& texture;
    const unsigned int x, y, width, height;
};


#endif //BRICKBOX_TEXTUREREF_H