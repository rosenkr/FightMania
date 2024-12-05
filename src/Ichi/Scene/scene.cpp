#include "Ichi/Scene/scene.h"
#include "Ichi/log.h"

namespace ichi::scene
{
<<<<<<< HEAD
    Scene::Scene(std::vector<std::unique_ptr<core::Component>> components): components(std::move(components)){ }
=======
    Scene::Scene(std::vector<core::Component *> components = {}) : components(std::move(components)) {}
>>>>>>> 98f295f1fa4cec20d57bb39c5d9e456588d0fb61

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

    // Returns a vector of immutable Hitbox references to all hitboxes of all components of this Scene.
    std::vector<std::reference_wrapper<const datatypes::Hitbox>> Scene::getCollisionHitboxes() const
    {
        std::vector<std::reference_wrapper<const datatypes::Hitbox>> vec;

<<<<<<< HEAD
        for (const auto& component : components)
            if(component.get()->getHitbox().getIsTangible())
                vec.push_back(component.get()->getHitbox());
=======
        for (const auto &component : components)
        {
            vec.push_back(component->getHitbox());
        }
>>>>>>> 98f295f1fa4cec20d57bb39c5d9e456588d0fb61
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

    void Scene::setPaused(bool paused) { 
        if(pausable){ 
            isPaused = paused;
        }
    }
}
