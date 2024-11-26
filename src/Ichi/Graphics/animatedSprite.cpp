#include "Ichi/Graphics/animatedSprite.h"
#include "animatedSprite.h"
#include "SDL2/SDL_timer.h"

namespace ichi::graphics
{

    AnimatedSprite::AnimatedSprite(core::Hitbox hb, graphics::Sprite::Layer layer, std::vector<std::string> strings, std::vector<Uint32> floats) : Sprite(hb, layer, "")
    {
        frameCount = strings.size();

        for (int i = 0; i < frameCount; i++)
        {
            textureManager::addTextureFor(this, strings.at(i));
            frameTime[i] = floats.at(i);
        }
    }

    void AnimatedSprite::update()
    {
        Uint32 ticks = SDL_GetTicks(); // update to take account for paus
        if (lastUpdated + frameTime[currentFrame] > ticks)
            return;

        if (++currentFrame > frameCount - 1)
            currentFrame = 0;

        lastUpdated = ticks;
    }

    void AnimatedSprite::draw()
    {
        SDL_Rect rect{currentFrame * hitbox.getWidth(), 0, hitbox.getWidth(), hitbox.getHeight()};
        SDL_RenderCopy(core::Engine::getInstance()->getRenderer(), textureManager::getTextureFor(*this), &rect, hitbox.toSdlRect());
    }

    const SDL_Texture &AnimatedSprite::getFrame(int frame)
    {
        return *textureManager::getTexturesFor(*this).at(frame);
    }

} // namespace ichi::graphics