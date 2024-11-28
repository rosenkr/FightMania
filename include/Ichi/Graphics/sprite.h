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

        Layer getLayer() const { return layer; }
        const core::Hitbox &getHitbox() const { return hitbox; }

        Sprite(core::Hitbox, Layer, std::string);

        void draw();

        bool operator<(const Sprite &other) const;

        ~Sprite()
        {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }

    private:
        core::Hitbox hitbox;
        Layer layer;
        // temp
        SDL_Texture *texture;
        std::string path;
    };
}

#endif