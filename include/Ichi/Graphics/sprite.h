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

        Sprite(datatypes::Hitbox, Layer, std::string);
        Sprite(datatypes::Hitbox h, Layer l) : hitbox(h), layer(l) {}

        void draw();

        bool operator<(const Sprite &other) const { return layer < other.layer; }

        ~Sprite() = default;

    protected:
        datatypes::Hitbox hitbox;
        Layer layer;
    };
}

#endif