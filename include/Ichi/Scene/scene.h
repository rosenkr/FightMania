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
        Scene(std::shared_ptr<graphics::Sprite> background, std::vector<std::shared_ptr<core::Component>> components = {}, bool pausable = true);

        virtual void draw() const;
        virtual void update();

        std::vector<std::reference_wrapper<const datatypes::Hitbox>> getCollisionHitboxes() const;
        const std::vector<std::shared_ptr<core::Component>> &getComponents() const { return components; }
        bool isPaused() const { return paused; }
        bool isPausable() const { return pausable; }

        void setPaused(bool paused);

        void addComponent(std::shared_ptr<core::Component> component);
        void removeComponent(size_t index);
        void removeComponent(const std::shared_ptr<core::Component> &c);

        ~Scene() = default;

    protected:
        std::shared_ptr<graphics::Sprite> background;
        std::vector<std::shared_ptr<core::Component>> components;
        bool pausable;
        bool paused;
    };
}

#endif
