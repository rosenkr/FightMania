#ifndef COMPONENT_H
#define COMPONENT_H

#include "Ichi/DataTypes/hitbox.h"

namespace ichi::core
{
    class Component
    {
    public:
        virtual void update() = 0;
        virtual void draw() const = 0;
        virtual void handleinput() {};
        virtual ~Component() = default;

        const datatypes::Hitbox &getHitbox() const { return hitbox; } // Getter in case we want to draw textures based on hitbox size

        // Prefer newer idiom of public + delete over making these private
        Component(const Component &) = delete;
        Component &operator=(const Component &) = delete;

    protected:
        datatypes::Hitbox hitbox;
        Component(datatypes::Hitbox hb) : hitbox(hb) {};
    };
}
#endif
