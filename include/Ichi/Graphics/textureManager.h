#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <unordered_map>
#include <string>
#include <vector>
#include "Ichi/Core/engine.h"
#include "Ichi/Graphics/sprite.h"
#include "Ichi/Graphics/animatedSprite.h"

namespace ichi::graphics::textureManager
{
    bool addTextureFor(const Sprite &s, const std::string &filePath);
    bool addTextureFor(const AnimatedSprite &as, const std::string &filePath);
    void dropTextureFor(const Sprite &s);
    void dropTexturesFor(const AnimatedSprite &as);
    SDL_Texture *getTextureFor(const Sprite &s);
    std::vector<SDL_Texture *> getTexturesFor(const AnimatedSprite &s);
    void shutdown(); // Clear all textures
}
#endif