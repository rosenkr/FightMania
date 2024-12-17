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
        AnimatedSprite(datatypes::Hitbox hb, Layer l, std::string path, int textureCount, std::map<int, Uint32> frameTime);
        AnimatedSprite(datatypes::Hitbox hb, Layer l, std::vector<std::string> paths, std::map<int, Uint32> frameTime);

        void draw();
        void update();

        bool hasCompleatedALap() { return compleatedALap; }

        bool operator<(const AnimatedSprite &other) const { return paths < other.paths; }

        ~AnimatedSprite() = default;

    private:
        // in milliseconds
        Uint32 lastUpdatedOn = 0;
        std::map<int, Uint32> frameTime;
        std::vector<std::string> paths;

        int currentFrame = 0;
        bool compleatedALap = false;
    };

} // namespace ichi::graphics

#endif // ANIMATED_SPRITE_H
