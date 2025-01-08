#include "Ichi/Graphics/textureManager.h"

#include "Ichi/Core/engine.h"
#include "Ichi/log.h"

#include "SDL2/SDL_image.h"

namespace ichi::graphics
{
    std::map<Sprite, std::unique_ptr<SDL_Texture, SDLTextureDeleter>> TextureManager::spriteMap;
    std::map<AnimatedSprite, std::map<int, std::unique_ptr<SDL_Texture, SDLTextureDeleter>>> TextureManager::animatedSpriteMap;

    SDL_Texture *TextureManager::getTextureFor(const Sprite &s)
    {
        auto it = spriteMap.find(s);

        if (it == spriteMap.end())
        {
            ICHI_ERROR("Could not find sprite in texturemap")
            return nullptr;
        }

        return it->second.get();
    }

    void TextureManager::dropTextureFor(const Sprite &s)
    {
        spriteMap.erase(s);
    }

    void TextureManager::addTextureFor(const Sprite &s, const std::string &str)
    {
        if (auto texture = getTexture(str))
            spriteMap[s] = std::move(texture);
    }

    SDL_Texture *TextureManager::getTextureFor(const AnimatedSprite &as, int index)
    {
        auto it = animatedSpriteMap.find(as);

        if (it == animatedSpriteMap.end())
        {
            ICHI_ERROR("Could not find animated sprite in texturemap")
            return nullptr;
        }

        if (it->second[index].get() == nullptr)
            ICHI_ERROR("Could not find frame {} in animatedTexturemap", index)

        return it->second[index].get();
    }

    void TextureManager::dropTexturesFor(const AnimatedSprite &as)
    {
        animatedSpriteMap.erase(as);
    }

    void TextureManager::addTexturesFor(const AnimatedSprite &as, const std::vector<std::string> &paths)
    {
        std::map<int, std::unique_ptr<SDL_Texture, SDLTextureDeleter>> map;

        int i = 0;
        for (auto path : paths)
        {
            if (auto texture = getTexture(path))
            {
                map[i++] = std::move(texture);
            }
            else
                ICHI_ERROR("Failed to add path {} with index: {}", path, i - 1)
        }

        animatedSpriteMap[as] = std::move(map);
    }

    std::unique_ptr<SDL_Texture, SDLTextureDeleter> TextureManager::getTexture(const std::string &path)
    {

        SDL_Surface *surf = IMG_Load(path.c_str());

        if (surf == nullptr)
        {

            ICHI_ERROR("Could not open image: {}", path);
            return nullptr;
        }
        SDL_Texture *texture = SDL_CreateTextureFromSurface(core::Engine::getInstance()->getRenderer(), surf);

        SDL_FreeSurface(surf);

        if (texture == nullptr)
        {
            ICHI_ERROR("Could not create texture for sprite: {}", SDL_GetError());
            return nullptr;
        }

        return std::unique_ptr<SDL_Texture, SDLTextureDeleter>(texture);
    }
} // namespace ichi::graphics
