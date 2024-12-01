#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include <memory>
#include "Ichi/Core/component.h"
namespace ichi::core {
    class Scene {
        public:
            Scene(std::vector<std::unique_ptr<Component>>, std::vector<Hitbox>);
            void draw() const;
            void update();
            std::vector<Hitbox> getCollisionHitboxes() const;
            
        private:
            std::vector<std::unique_ptr<Component>> components;
            std::vector<Hitbox> collisionHitboxes;
            bool pausable;
            bool isPaused;
    };
}

#endif