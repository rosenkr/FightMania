#ifndef SPRITE_H
#define SPRITE_H

#include "Ichi/DataTypes/hitbox.h"

#include <string>

namespace ichi::graphics
{
    class Sprite
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

        Sprite(datatypes::Hitbox &, Layer, std::string);

        void draw() const;
        virtual void update() {};

        int getHeight() const { return hitbox.getHeight(); }
        int getWidth() const { return hitbox.getWidth(); }

        bool operator<(const Sprite &other) const { return path < other.path; }

        virtual ~Sprite() = default;

        const datatypes::Hitbox &getHitbox() const;

        void setX(int i);
        void setY(int i);
        int getX() const { return hitbox.getX(); };
        int getY() const { return hitbox.getY(); };

    protected:
        Sprite(datatypes::Hitbox h, Layer l) : hitbox(h), layer(l)
        {
        }
        datatypes::Hitbox &hitbox;
        Layer layer;
        std::string path;
    };
}

#endif