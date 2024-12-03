#include "Ichi/Scene/scene.h"
#include "Ichi/log.h"

namespace ichi::scene
{
    Scene::Scene(std::vector<std::unique_ptr<core::Component>> components = {}, std::vector<datatypes::Hitbox> hitboxes = {}) : components(std::move(components)), collisionHitboxes(hitboxes) {}
    void Scene::draw() const
    {
        for (const auto &up_c : components)
            up_c->draw();
    }

    void Scene::update()
    {
        for (const auto &up_c : components)
            up_c->update();
    }

    std::vector<datatypes::Hitbox> Scene::getCollisionHitboxes() const
    {
        return collisionHitboxes;
    }

    // Impl usage: ConcreteComponent comp; Scene::addComponent(&comp);
    void Scene::addComponent(core::Component *comp)
    {
        if (!comp)
        {
            ICHI_ERROR("Null pointer passed to addComponent");
            return;
        }
        components.push_back(std::unique_ptr<core::Component>(comp));
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
}
