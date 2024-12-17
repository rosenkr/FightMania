#include "Ichi/Scene/scene.h"

#include "Ichi/Graphics/animatedSprite.h"
#include "Ichi/log.h"

namespace ichi::scene
{
    Scene::Scene(graphics::Sprite *background, std::vector<core::Component *> components = {}, bool pausable = true) : background(std::move(background)), components(std::move(components)), pausable(pausable), paused(false) {}

    void Scene::draw() const
    {
        background->draw();
        for (const auto &up_c : components)
            up_c->draw();
    }

    void Scene::update()
    {
        background->update();
        for (const auto &up_c : components)
            up_c->update();
    }

    // Returns a vector of immutable Hitbox references to all hitboxes of all components of this Scene.
    std::vector<std::reference_wrapper<const datatypes::Hitbox>> Scene::getCollisionHitboxes() const
    {
        std::vector<std::reference_wrapper<const datatypes::Hitbox>> vec;

        for (const auto &component : components)
        {
            vec.push_back(component->getHitbox());
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

    void Scene::removeComponent(size_t index)
    {
        if (index < 0 || index >= components.size())
        {
            ICHI_ERROR("Index error when removing component at index");
            return;
        }

        delete components.at(index);
        components.at(index) = nullptr;
        components.erase(components.begin() + index);
    }

    void Scene::removeComponent(core::Component *c)
    {
        if (std::find(components.begin(), components.end(), c) == components.end())
        {
            ICHI_ERROR("Could not remove component from list");
            return;
        }
        delete c;
        c = nullptr;
        components.erase(std::remove(components.begin(), components.end(), c), components.end());
    }

    void Scene::setPaused(bool paused)
    {
        if (pausable)
            this->paused = paused;
    }
}
