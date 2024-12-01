#include "Ichi/Graphics/animatedSprite.h"

// temp
#include "Ichi/log.h"
#include "Ichi/Core/engine.h"

namespace ichi::graphics
{
    AnimatedSprite::AnimatedSprite(core::Hitbox hb, Layer l, std::string path, int textureCount, std::map<int, Uint32> frameTime) : Sprite(hb, l), frameTime(frameTime)
    {
        for (int i = 0; i < textureCount; i++)
        {
            paths.push_back(path.substr(0, path.find('.')) + std::to_string(i) + path.substr(path.find('.'), std::string::npos));
        }
    }

    void AnimatedSprite::update()
    {
        if (lastUpdatedOn + frameTime[currentFrame] > SDL_GetTicks())
            return;

        if (++currentFrame > (int)frameTime.size() - 1)
            currentFrame = 0;

        lastUpdatedOn = SDL_GetTicks();
    }

    void AnimatedSprite::draw()
    {
        if (textures.empty())
            for (auto s : paths)
            {
                SDL_Surface *surf = IMG_Load(s.c_str());

                if (surf == nullptr)
                {

                    ICHI_ERROR("Could not open image: {}", s);
                    return;
                }

                SDL_Texture *texture = SDL_CreateTextureFromSurface(core::Engine::getInstance()->getRenderer(), surf);

                SDL_FreeSurface(surf);

                if (texture == nullptr)
                {
                    ICHI_ERROR("Could not create texture for sprite: {}", SDL_GetError());
                    return;
                }

                textures.push_back(texture);
            }

        SDL_RenderCopy(core::Engine::getInstance()->getRenderer(), textures[currentFrame], NULL, hitbox.toSdlRect());
    }
} // namespace ichi::graphics
