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
        virtual void shutDown() {};

        const datatypes::Hitbox &getHitbox() const { return hitbox; } 
        Component(const Component &) = delete;
        Component &operator=(const Component &) = delete;

    protected:
        datatypes::Hitbox hitbox;
        Component(datatypes::Hitbox hb) : hitbox(hb) {};
    };
}
#endif
