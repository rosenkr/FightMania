#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <vector>
#include <map>
#include "Ichi/DataTypes/hitbox.h"

#include <string>

namespace ichi::graphics
{
    class AnimatedSprite
    {
    public:

        enum class Layer
        {
            BACKGROUND = 0,
            MIDGROUND = 1,
            FOREGROUND = 2,
            DETAILS = 3,
            EFFECTS = 4,
            COLOR_ADJUSTMENT = 5,
            UICOMPONENT = 6,
        };
        AnimatedSprite(datatypes::Hitbox hb, Layer l, std::string path, int textureCount, std::map<int, unsigned int> frameTime);
        AnimatedSprite(datatypes::Hitbox hb, Layer l, std::vector<std::string> paths, std::map<int, unsigned int> frameTime);

        int getCurrentFrame() const { return currentFrame; }
        int getFrameCount() { return (int)frameTime.size(); }

        void draw() const;
        void update();
        void reset()
        {
            currentFrame = 0;
            compleatedALap = false;
            lastUpdatedOn = 0;
        }

        void compleateLap() { compleatedALap = true; }
        bool hasCompleatedALap() { return compleatedALap; }

        bool operator<(const AnimatedSprite &other) const { return paths < other.paths; }

        AnimatedSprite(const AnimatedSprite &as) : hitbox(as.hitbox), layer(as.layer), frameTime(as.frameTime), paths(as.paths) {}
        AnimatedSprite &operator=(const AnimatedSprite &other)
        {
            if (this == &other)
                return *this;

            this->frameTime = other.frameTime;
            this->paths = other.paths;
            this->lastUpdatedOn = other.lastUpdatedOn;
            this->currentFrame = other.currentFrame;
            this->compleatedALap = other.compleatedALap;

            return *this;
        }

        int getHeight() const { return hitbox.getHeight(); }
        int getWidth() const { return hitbox.getWidth(); }
        const datatypes::Hitbox &getHitbox() const {return hitbox;}
        void setX(int i);
        void setY(int i);
        int getX() const { return hitbox.getX(); };
        int getY() const { return hitbox.getY(); };
        ~AnimatedSprite() = default;

    private:
        // in milliseconds
        datatypes::Hitbox hitbox;
        Layer layer;
        unsigned int lastUpdatedOn = 0;
        std::map<int, unsigned int> frameTime;
        std::vector<std::string> paths;

        int currentFrame = 0;
        bool compleatedALap = false;
    };

} // namespace ichi::graphics

#endif // ANIMATED_SPRITE_H
