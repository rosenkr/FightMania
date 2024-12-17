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
          std::vector<core::Component*> components = {}, 
          bool pausable = true
        );

        Scene(graphics::Sprite* background, 
          std::vector<std::shared_ptr<core::Component>> components = {}, 
          bool pausable = true);
        
        ~Scene(){
            for (auto p : components)
                if (auto rawPtr = std::get_if<core::Component*>(&p)) {
                    delete *rawPtr;  // if raw pointer, delete
                }
            components.clear();
            delete background;
            background = nullptr;
        }

        virtual void draw() const;
        virtual void update();
        std::vector<std::reference_wrapper<const datatypes::Hitbox>> getCollisionHitboxes() const;
        void addComponent(core::Component *comp);
        void addComponent(std::shared_ptr<core::Component> component);
        void removeComponent(size_t index);
        void setPaused(bool paused);
        bool isPaused() const { return paused; }
        bool isPausable() const { return pausable; }
        const std::vector<std::variant<core::Component*, std::shared_ptr<core::Component>>>& getComponents() const { return components; }

    protected:
        graphics::Sprite *background;
        std::vector<std::variant<core::Component*, std::shared_ptr<core::Component>>> components;
        bool pausable;
        bool paused;
    };
}

#endif
