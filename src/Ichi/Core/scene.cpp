#include "Ichi/Core/scene.h"
namespace ichi::core {
    Scene::Scene(std::vector<std::unique_ptr<Component>> components, std::vector<Hitbox> hitboxes) : components(components), collisionHitboxes(hitboxes) {}
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
}