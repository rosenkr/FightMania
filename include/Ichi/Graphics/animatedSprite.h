#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Ichi/Graphics/sprite.h"
#include "Ichi/Core/hitbox.h"

#include <map>
#include <string>
#include <vector>

namespace ichi::graphics
{
    class AnimatedSprite : public graphics::Sprite
    {
    public:
        AnimatedSprite(core::Hitbox hb, graphics::Sprite::Layer layer, std::vector<std::string> strings, std::vector<Uint32> floats);

        void update();
        void draw();
        const SDL_Texture &getFrame(int frame);

    private:
        // in milliseconds
        std::map<int, Uint32> frameTime;
        Uint32 lastUpdated;
        int currentFrame = 0;
        int frameCount;
    };
}
#endif