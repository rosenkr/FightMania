#ifndef SCENE_H
#define SCENE_H

#include "Ichi/Core/component.h"
#include "Ichi/Graphics/sprite.h"

#include <vector>
#include <memory>
#include <variant>

namespace ichi::scene
{
    class Scene
    {
    public:
        Scene(graphics::Sprite* background, 
          std::vector<std::shared_ptr<core::Component>> components = {}, 
          bool pausable = true);
        
        ~Scene(){
            components.clear();
            delete background;
            background = nullptr;
        }

        virtual void draw() const;
        virtual void update();
        std::vector<std::reference_wrapper<const datatypes::Hitbox>> getCollisionHitboxes() const;
        void addComponent(std::shared_ptr<core::Component> component);
        void removeComponent(size_t index);
        void removeComponent(const std::shared_ptr<core::Component>& c);
        void setPaused(bool paused);
        bool isPaused() const { return paused; }
        bool isPausable() const { return pausable; }
        const std::vector<std::shared_ptr<core::Component>>& getComponents() const { return components; }

    protected:
        graphics::Sprite *background;
        std::vector<std::shared_ptr<core::Component>> components;
        bool pausable;
        bool paused;
    };
}

#endif
