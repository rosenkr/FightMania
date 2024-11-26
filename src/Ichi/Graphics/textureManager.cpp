#include <SDL2/SDL_image.h>
#include "Ichi/Graphics/textureManager.h"
#include "Ichi/log.h"
namespace ichi::graphics::textureManager
{

    // static in this context means effectively private
    static std::map<Sprite, SDL_Texture *> textureMap;
    static std::map<AnimatedSprite, std::vector<SDL_Texture *>> animatedTextureMap;

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
        {
            SDL_DestroyTexture(texture);
        }
        animatedTextureMap.erase(as);
    }

    // Destroys all sprite and animatedsprite textures and erases both maps
    void shutdown()
    {
        std::map<Sprite, SDL_Texture *>::iterator sIter;
        for (sIter = textureMap.begin(); sIter != textureMap.end(); sIter++)
        {
            SDL_DestroyTexture(sIter->second);
        }
        textureMap.clear();

        std::map<AnimatedSprite, std::vector<SDL_Texture *>>::iterator asIter;
        for (asIter = animatedTextureMap.begin(); asIter != animatedTextureMap.end(); asIter++)
        {
            for (SDL_Texture *texture : asIter->second)
            {
                SDL_DestroyTexture(texture);
            }
        }
        animatedTextureMap.clear();
    }

    void draw(const Sprite &s, int x, int y)
    {
        int w, h, success;
        SDL_QueryTexture(textureMap[s], NULL, NULL, &w, &h); // Assign an images width and height to params
        SDL_Rect srcRect = {0, 0, w, h};                     // Take the whole image.
        SDL_Rect dstRect = {x, y, w, h};
        success = SDL_RenderCopy(core::Engine::getInstance()->getRenderer(), textureMap[s], &srcRect, &dstRect);
        if (success == 0)
        {
            ICHI_INFO("RenderCopy: Successfully drew sprite");
        }
        else
        {
            ICHI_ERROR("RenderCopy: Failed to draw sprite {}", SDL_GetError());
        }
    }

    // Todo: Draw for AnimatedSprite?
}
