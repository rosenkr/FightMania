#ifndef SCENE_H
#define SCENE_H

#include "Ichi/Core/component.h"
#include "Ichi/Graphics/sprite.h"

#include <vector>
#include <memory>

namespace ichi::scene
{
    class Scene
    {
    public:
        Scene(graphics::Sprite *, std::vector<core::Component *>, bool);
        ~Scene()
        {
            for (auto p : components)
                delete p;
            components.clear();
            delete background;
            background = nullptr;
        }

        virtual void draw() const;
        virtual void update();
        std::vector<std::reference_wrapper<const datatypes::Hitbox>> getCollisionHitboxes() const;
        void addComponent(core::Component *comp);
        void removeComponent(size_t index);
        const std::vector<core::Component *> &getComponents() { return components; }
        void setPaused(bool paused);
        bool isPaused() const { return paused; }
        bool isPausable() const { return pausable; }

    protected:
        graphics::Sprite *background;
        std::vector<core::Component *> components;
        bool pausable;
        bool paused;
    };
}

#endif
