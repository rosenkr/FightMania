#include "Ichi/Graphics/textureManager.h"

#include "Ichi/Core/engine.h"
#include "Ichi/log.h"

#include "SDL2/SDL_image.h"

namespace ichi::graphics
{
    std::map<std::string, std::unique_ptr<SDL_Texture, SDLTextureDeleter>> TextureManager::textures;

    std::map<std::string, std::unique_ptr<SDL_Texture, SDLTextureDeleter>> TextureManager::textTextures;

 

    SDL_Texture *TextureManager::getTextureFor(const std::string &s)
    {
        auto it = textures.find(s);

        if (it == textures.end())
        {
            ICHI_ERROR("Could not find path in texturemap")
            return nullptr;
        }

        return it->second.get();
    }

    void TextureManager::dropTextureFor(const std::string &s)
    {
        textures.erase(s);
    }

    void TextureManager::addTextureFor(const std::string &str)
    {
        if (textures.find(str) != textures.end())
            return;

        if (auto texture = createTexture(str))
            textures[str] = std::move(texture);
    }

    void TextureManager::addTexturesFor(const std::vector<std::string> &paths)
    {
        for (auto p : paths)
            addTextureFor(p);
    }
    
    void TextureManager::addTextTextureFor(const std::string str, TTF_Font* font, SDL_Color color){
        if (str.empty())
            return;

        if (textTextures.find(str) != textTextures.end())
            return;

        if (auto texture = createTextTexture(str,font,color))
            textTextures.insert({str, std::move(texture)});   
    }

    SDL_Texture* TextureManager::getTextTextureFor(const std::string str, TTF_Font* font, SDL_Color color) {
        if (textTextures.find(str) == textTextures.end())
            return nullptr;
        return textTextures.at(str).get();
    }

    std::unique_ptr<SDL_Texture, SDLTextureDeleter> TextureManager::createTextTexture(const std::string str, TTF_Font* font, SDL_Color color){

        SDL_Surface *surf = TTF_RenderText_Blended(font, str.c_str(), color);

        if (surf == nullptr)
        {

            ICHI_ERROR("Error on getting text texture with text: {} sdlerrror: {}", str, SDL_GetError());
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


    std::unique_ptr<SDL_Texture, SDLTextureDeleter> TextureManager::createTexture(const std::string &path)
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
