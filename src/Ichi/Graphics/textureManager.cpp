#include <SDL2/SDL_image.h>
#include "Ichi/Graphics/textureManager.h"
#include "Ichi/log.h"
namespace ichi::graphics::textureManager
{

    // static in this context means effectively private
    static std::unordered_map<Sprite, SDL_Texture *> textureMap;
    static std::unordered_map<AnimatedSprite, std::vector<SDL_Texture *>> animatedTextureMap;

    // Creates texture from image file, adds it to map, returns true on success
    bool addTextureFor(const Sprite &s, const std::string &filePath)
    {
        SDL_Surface *surf = IMG_Load(filePath.c_str());

        if (surf == nullptr)
        {
            ICHI_ERROR("Failed to load image file:\n {}", SDL_GetError());
            return false;
        }

        SDL_Texture *texture = SDL_CreateTextureFromSurface(core::Engine::getInstance()->getRenderer(), surf);

        if (texture == nullptr)
        {
            ICHI_ERROR("Failed to create texture for sprite:\n {}", SDL_GetError());
            return false;
        }

        SDL_FreeSurface(surf);
        textureMap[s] = texture;

        return true;
    }

    bool addTextureFor(const AnimatedSprite &as, const std::string &filePath)
    {
        SDL_Surface *surf = IMG_Load(filePath.c_str());

        if (surf == nullptr)
        {
            ICHI_ERROR("Failed to load image file:\n {}", SDL_GetError());
            return false;
        }

        SDL_Texture *texture = SDL_CreateTextureFromSurface(core::Engine::getInstance()->getRenderer(), surf);

        if (texture == nullptr)
        {
            ICHI_ERROR("Failed to create texture for animatedSprite:\n {}", SDL_GetError());
            return false;
        }

        SDL_FreeSurface(surf);
        animatedTextureMap[as].push_back(texture);

        return true;
    }

    // Destroys texture and removes sprite entry from the map
    void dropTextureFor(const Sprite &s)
    {
        SDL_DestroyTexture(textureMap[s]);

        textureMap.erase(s);
    }

    // Destroys all textures associated with animated sprite
    void dropTexturesFor(const AnimatedSprite &as)
    {
        for (SDL_Texture *texture : animatedTextureMap[as])
            SDL_DestroyTexture(texture);

        animatedTextureMap.erase(as);
    }

    // Destroys all sprite and animatedsprite textures and erases both maps
    void shutdown()
    {
        for (auto sIter = textureMap.begin(); sIter != textureMap.end(); sIter++)
            dropTextureFor(sIter->first);

        for (auto asIter = animatedTextureMap.begin(); asIter != animatedTextureMap.end(); asIter++)
            dropTexturesFor(asIter->first);
    }

    SDL_Texture *getTextureFor(const Sprite &s)
    {
        return textureMap.at(s);
    }

    std::vector<SDL_Texture *> getTexturesFor(const AnimatedSprite &s)
    {
        return animatedTextureMap[s];
    }
}
