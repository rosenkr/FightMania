#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <map>
#include <string>
#include <vector>
#include "Ichi/Core/engine.h"
#include "Ichi/Core/sprite.h"
#include "Ichi/Core/animatedSprite.h"

namespace ichi::core::textureManager { 
    bool addTextureFor(const Sprite& s, const std::string& filePath);
    bool addTextureFor(const AnimatedSprite& as, const std::string& filePath);
    void dropTextureFor(const Sprite& s);
    void dropTexturesFor(const AnimatedSprite& as);
    SDL_Texture getTextureFor(const Sprite& s);
    SDL_Texture getTextureFor(const AnimatedSprite& s);
    void shutdown(); // Clear all textures
    void draw(const Sprite& s, int x, int y);
    //void draw(const AnimatedSprite& s, int x, int y);
}
#endif