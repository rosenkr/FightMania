#include "Ichi/Core/scene.h"
#include "Ichi/log.h"
namespace ichi::core {
    Scene::Scene(std::vector<std::unique_ptr<Component>> components = {}, std::vector<Hitbox> hitboxes = {}) : components(std::move(components)), collisionHitboxes(hitboxes) {}
    void Scene::draw() const {
        for(const std::unique_ptr<Component>& up_c : components) {
            up_c->draw();
        }
    }
    
    void Scene::update() {
        for(const std::unique_ptr<Component>& up_c : components) {
            up_c->update();
        }        
    }

    std::vector<Hitbox> Scene::getCollisionHitboxes() const {
        return collisionHitboxes;
    }

    // Impl usage: ConcreteComponent comp; Scene::addComponent(&comp);
    void Scene::addComponent(Component* comp) {
        if (comp) { 
            components.push_back(std::unique_ptr<Component>(comp));
        } else {
            ICHI_ERROR("Null pointer passed to addComponent");
        }
    }

    // The unique pointer will automatically delete the Component object!
    void Scene::removeComponent(size_t index) {
        if(index >= 0 && index < components.size()) {
            components.erase(components.begin()+index);
        } else {
            ICHI_ERROR("Index error when removing component at index");
        }
    }   
}
