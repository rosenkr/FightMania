#ifndef SPRITE_H
#define SPRITE_H

#include "Ichi/Core/hitbox.h"
#include "Ichi/Graphics/textureManager.h"

#include <string>
#include <unordered_map>

namespace ichi::graphics
{
    class Sprite
    {
    public:
        enum class Layer
        {
            BACKGROUND,
            MIDGROUND,
            FOREGROUND,
            DETAILS,
            EFFECTS,
            COLOR_ADJUSTMENT,
            UICOMPONENT,
        };

        Layer getLayer() const { return layer; }
        const core::Hitbox &getHitbox() const { return hitbox; }

        void draw();
        Sprite(core::Hitbox, Layer, std::string);
        bool operator==(const Sprite &other) const;

    protected:
        Layer layer;
        core::Hitbox hitbox;
    };
}

namespace std
{
    template <>
    struct hash<ichi::graphics::Sprite>
    {
        size_t operator()(const ichi::graphics::Sprite &sprite) const;
    };
}
#endif