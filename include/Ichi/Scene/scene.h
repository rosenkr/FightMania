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
        Scene(std::vector<core::Component *>);
        ~Scene()
        {
            for (auto p : components)
                delete p;
            components.clear();
        }

        virtual void draw() const;
        virtual void update();
        std::vector<std::reference_wrapper<const datatypes::Hitbox>> getCollisionHitboxes() const;
        void addComponent(core::Component *comp);
        void removeComponent(size_t index);
        void setPaused(bool paused);
        bool isPaused() const { return paused; }
        bool isPausable() const { return pausable; }

    protected:
        std::vector<core::Component *> components;
        bool pausable;
        bool paused;
    };
}

#endif
