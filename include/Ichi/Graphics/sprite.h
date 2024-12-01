#ifndef SPRITE_H
#define SPRITE_H

#include "Ichi/Core/hitbox.h"

#include <string>

// temp
#include "SDL2/SDL_image.h"

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

        Sprite(core::Hitbox, Layer, std::string);
        Sprite(core::Hitbox h, Layer l) : hitbox(h), layer(l) {}

        void draw();

        bool operator<(const Sprite &other) const { return layer < other.layer; }

        ~Sprite() = default;

    protected:
        core::Hitbox hitbox;
        Layer layer;
    };
}

#endif