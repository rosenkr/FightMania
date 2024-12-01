#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "Ichi/Graphics/sprite.h"

#include <vector>
#include <map>

namespace ichi::graphics
{
    class AnimatedSprite : public Sprite
    {
    public:
        AnimatedSprite(core::Hitbox hb, Layer l, std::string path, int textureCount, std::map<int, Uint32> frameTime);
        AnimatedSprite(core::Hitbox hb, Layer l, std::vector<std::string> paths, std::map<int, Uint32> frameTime) : Sprite(hb, l), frameTime(frameTime), paths(paths) {}

        void draw();
        void update();

        bool operator<(const AnimatedSprite &other) const { return layer < other.layer; }

        ~AnimatedSprite()
        {
            // temp
            for (auto t : textures)
                SDL_DestroyTexture(t);
        }

    private:
        // in milliseconds
        Uint32 lastUpdatedOn = 0;
        std::map<int, Uint32> frameTime;

        int currentFrame = 0;

        // temp
        std::vector<SDL_Texture *> textures;
        std::vector<std::string> paths;
    };

} // namespace ichi::graphics

#endif // ANIMATED_SPRITE_H
