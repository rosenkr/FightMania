#include "Ichi/Scene/scene.h"

#include "Ichi/Graphics/animatedSprite.h"
#include "Ichi/log.h"

namespace ichi::scene
{
    Scene::Scene(
        graphics::Sprite* background,
        std::vector<core::Component*> components,
        bool pausable
    )
        : background(background), pausable(pausable), paused(false)
    {
        for (auto* comp : components) {
            this->components.push_back(comp);  // Add raw pointer directly
        }
    }

    // Constructor to handle smart pointers
    Scene::Scene(
        graphics::Sprite* background,
        std::vector<std::shared_ptr<core::Component>> components,
        bool pausable
    )
        : background(std::move(background)), pausable(pausable), paused(false)
    {
        // Convert smart pointers into std::variant<core::Component*, std::shared_ptr<core::Component>>
        for (auto& comp : components) {
            this->components.push_back(comp); // Add shared_ptr directly
        }
    }

    void Scene::draw() const
    {
        background->draw();
        for (const auto &up_c : components)
        {
            if (auto rawPtr = std::get_if<core::Component *>(&up_c))
            {
                (*rawPtr)->draw(); 
            }
            else if (auto sharedPtr = std::get_if<std::shared_ptr<core::Component>>(&up_c))
            {
                sharedPtr->get()->draw();  
            }
        }
    }

    void Scene::update()
    {
        background->update();
        for (const auto &up_c : components)
        {
            if (auto rawPtr = std::get_if<core::Component *>(&up_c))
            {
                (*rawPtr)->update();
            }
            else if (auto sharedPtr = std::get_if<std::shared_ptr<core::Component>>(&up_c))
            {
                sharedPtr->get()->update();
            }
        }
    }

    // Returns a vector of immutable Hitbox references to all hitboxes of all components of this Scene.
    std::vector<std::reference_wrapper<const datatypes::Hitbox>> Scene::getCollisionHitboxes() const
    {
        std::vector<std::reference_wrapper<const datatypes::Hitbox>> vec;

        for (const auto &component : components)
        {
            if (auto rawPtr = std::get_if<core::Component *>(&component))
            {
                vec.push_back((*rawPtr)->getHitbox());
            }
            else if (auto sharedPtr = std::get_if<std::shared_ptr<core::Component>>(&component))
            {
                vec.push_back(sharedPtr->get()->getHitbox());
            }
        }

        return vec;
    }

    // Impl usage: ConcreteComponent comp; Scene::addComponent(&comp);
    void Scene::addComponent(core::Component *comp)
    {
        if (!comp)
        {
            ICHI_ERROR("Null pointer passed to addComponent");
            return;
        }
        components.push_back(std::move(comp));
    }

    void Scene::addComponent(std::shared_ptr<core::Component> component) {
        components.push_back(component);
    }


    // The unique pointer will automatically delete the Component object!
    void Scene::removeComponent(size_t index)
    {
        if (index < 0 || index >= components.size())
        {
            ICHI_ERROR("Index error when removing component at index");
            return;
        }
        components.erase(components.begin() + index);
    }

    void Scene::setPaused(bool paused)
    {
        if (pausable)
            this->paused = paused;
    }
}
