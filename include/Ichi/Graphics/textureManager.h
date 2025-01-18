#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "Ichi/Graphics/sprite.h"
#include "Ichi/Graphics/animatedSprite.h"

#include "SDL2/SDL_ttf.h"

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
        static SDL_Texture *getTextureFor(const std::string &s);
        static SDL_Texture* getTextTextureFor(const std::string str, TTF_Font* font, SDL_Color color);
        static void dropTextureFor(const std::string &s);
        
        static void addTextureFor(const std::string &path);
        static void addTexturesFor(const std::vector<std::string> &paths);

        // Texture for text
        static void addTextTextureFor(const std::string, TTF_Font*, SDL_Color);
        //static void dropTextTextureFor(const std::string, TTF_Font*, SDL_Color);
        
        // Perhaps for progress bar too

        static void shutDown() {
            textures.clear();
        }

    private:
        static std::unique_ptr<SDL_Texture, SDLTextureDeleter> createTexture(const std::string &path);

        static std::unique_ptr<SDL_Texture, SDLTextureDeleter> createTextTexture(const std::string, TTF_Font*, SDL_Color);


        static std::map<std::string, std::unique_ptr<SDL_Texture, SDLTextureDeleter>> textures;

        static std::map<std::string, std::unique_ptr<SDL_Texture, SDLTextureDeleter>> textTextures;
        TextureManager() = default;
        ~TextureManager() = default;
    };

} // namespace ichi::graphics

#endif