#include "Ichi/Scene/scene.h"

#include "Ichi/Graphics/animatedSprite.h"
#include "Ichi/UIComponents/pane.h"
#include "Ichi/log.h"

namespace ichi::scene
{
    Scene::Scene(std::shared_ptr<graphics::Sprite> background, std::vector<std::shared_ptr<core::Component>> components, bool pausable)
        : background(std::move(background)), components(std::move(components)), pausable(pausable), paused(false)
    {
    }

    void Scene::draw() const
    {
        background->draw();
        for (const auto &comp : components)
            comp->draw();
    }

    void Scene::update()
    {
        background->update();
        for (const auto &comp : components)
            comp->update();
    }

    core::Component *Scene::getComponent(datatypes::Point p) const
    {
        core::Component *component = nullptr;

        for (auto c : components)
        {
            if (c.get()->getHitbox().getPos() == p)
                return c.get();
            if (auto ptr = std::dynamic_pointer_cast<uicomponents::Pane>(c))
                for (auto uic : ptr.get()->getUIComponents())
                    if (uic.first == p)
                        return uic.second.get();
        }

        return component;
    }

    // Returns a vector of immutable Hitbox references to all tangible hitboxes of all components of this Scene.
    std::vector<std::reference_wrapper<const datatypes::Hitbox>> Scene::getCollisionHitboxes() const
    {
        std::vector<std::reference_wrapper<const datatypes::Hitbox>> vec;

        for (const auto &component : components)
            if (component.get()->getHitbox().getIsTangible())
                vec.push_back(component->getHitbox()); // Direct access using shared_ptr

        return vec;
    }

    void Scene::addComponent(std::shared_ptr<core::Component> component)
    {
        components.push_back(component);
    }

    void Scene::removeComponent(size_t index)
    {
        if (index < 0 || index >= components.size())
        {
            ICHI_ERROR("Index error when removing component at index");
            return;
        }
        components.erase(components.begin() + index);
    }

    void Scene::removeComponent(const std::shared_ptr<core::Component> &c)
    {
        auto it = std::find(components.begin(), components.end(), c);

        if (it != components.end())
            components.erase(it); // Remove the shared_ptr directly
        else
            ICHI_ERROR("Could not remove component from list");
    }

    void Scene::setPaused(bool paused)
    {
        if (pausable)
            this->paused = paused;
    }
}
