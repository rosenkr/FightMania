#include "Ichi/Graphics/animatedSprite.h"
#include "Ichi/Core/engine.h"
#include "Ichi/Graphics/textureManager.h"

namespace ichi::graphics
{
    AnimatedSprite::AnimatedSprite(datatypes::Hitbox hb, Layer l, std::string path, int textureCount, std::map<int, Uint32> frameTime) : Sprite(hb, l), frameTime(frameTime)
    {
        std::vector<std::string> paths;
        for (int i = 0; i < textureCount; i++)
            paths.push_back(path + std::to_string(i) + ".png");

        TextureManager::addTexturesFor(*this, paths);

        this->paths = paths;
    }
    AnimatedSprite::AnimatedSprite(datatypes::Hitbox hb, Layer l, std::vector<std::string> paths, std::map<int, Uint32> frameTime) : Sprite(hb, l), frameTime(frameTime), paths(paths)
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
        SDL_RenderCopy(core::Engine::getInstance()->getRenderer(), TextureManager::getTextureFor(*this, currentFrame), NULL, hitbox.getSDLRect());
    }
} // namespace ichi::graphics
