#include "Ichi/Graphics/animatedSprite.h"
#include "Ichi/Core/engine.h"
#include "Ichi/Graphics/textureManager.h"
#include "Ichi/log.h"

namespace ichi::graphics
{
    AnimatedSprite::AnimatedSprite(datatypes::Hitbox& hb, Layer l, std::string path, int textureCount, std::map<int, Uint32> frameTime) : Sprite(hb, l), frameTime(frameTime)
    {
        std::vector<std::string> paths;
        for (int i = 0; i < textureCount; i++)
            paths.push_back(path + std::to_string(i) + ".png");

        TextureManager::addTexturesFor(*this, paths);

        this->paths = paths;
    }
    AnimatedSprite::AnimatedSprite(datatypes::Hitbox& hb, Layer l, std::vector<std::string> paths, std::map<int, Uint32> frameTime) : Sprite(hb, l), frameTime(frameTime), paths(paths)
    {
        TextureManager::addTexturesFor(*this, paths);
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
        SDL_Renderer* renderer = core::Engine::getInstance()->getRenderer();
        SDL_Texture* texture = TextureManager::getTextureFor(*this, currentFrame);
        const SDL_Rect* rect = hitbox.getSDLRect();

        if (SDL_RenderCopy(renderer, texture, NULL, rect) != 0) {
            ICHI_INFO("SDL_RenderCopy failed: {}", SDL_GetError());
        }
    }
} // namespace ichi::graphics
