#ifndef SCENE_H
#define SCENE_H

#include "Ichi/Core/component.h"

#include <vector>
#include <memory>

namespace ichi::scene
{
    class Scene
    {
    public:
        Scene() {};
        Scene(std::vector<std::unique_ptr<core::Component>>, std::vector<datatypes::Hitbox>);
        void draw() const;
        void update();
        std::vector<datatypes::Hitbox> getCollisionHitboxes() const;
        void addComponent(core::Component *comp);
        void removeComponent(size_t index);

    private:
        std::vector<std::unique_ptr<core::Component>> components;
        std::vector<datatypes::Hitbox> collisionHitboxes;
        bool pausable;
        bool isPaused;
    };
}

#endif
