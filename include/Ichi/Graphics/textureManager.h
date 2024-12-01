#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "Ichi/Graphics/sprite.h"
#include "Ichi/Graphics/animatedSprite.h"

#include <map>
#include <memory>
#include <vector>

namespace ichi::graphics
{
    struct SDLTextureDeleter
    {
        void operator()(SDL_Texture *texture) const
        {
            if (texture)
                SDL_DestroyTexture(texture);
        }
    };

    class TextureManager
    {
    public:
        static SDL_Texture *getTextureFor(const Sprite &s);
        static void dropTextureFor(const Sprite &s);
        static void addTextureFor(const Sprite &s, const std::string &path);

        static SDL_Texture *getTextureFor(const AnimatedSprite &as, int index);
        static void dropTexturesFor(const AnimatedSprite &as);
        static void addTexturesFor(const AnimatedSprite &as, const std::vector<std::string> &paths);

    private:
        static std::unique_ptr<SDL_Texture, SDLTextureDeleter> getTexture(const std::string &path);

        static std::map<Sprite, std::unique_ptr<SDL_Texture, SDLTextureDeleter>> spriteMap;
        static std::map<AnimatedSprite, std::map<int, std::unique_ptr<SDL_Texture, SDLTextureDeleter>>> animatedSpriteMap;

        TextureManager() = default;
        ~TextureManager() = default;
    };

} // namespace ichi::graphics

#endif