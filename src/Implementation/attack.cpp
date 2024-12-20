#include "Implementation/attack.h"
#include "Ichi/log.h"
#include "Ichi/Scene/sceneManager.h"
void Attack::update() {
    // move depending on speed
    // TODO: if collides with tangible component or goes out of bound of map, should destroy the attack
    moveInDirectionWithSpeed();
    animation.get()->update();
    if(hitbox.getX() < 0 || hitbox.getX() > 1000) { // temp, should be > window width
        ichi::scene::sceneManager::getActiveScene()->removeComponent(shared_from_this());
    }
}
void Attack::draw() const {
    // draw the animations
    animation.get()->draw();
    ICHI_INFO("Attacks animation hitbox: x: {}, y: {} ", animation->getHitbox().getX(), animation->getHitbox().getY());
}

void Attack::moveInDirectionWithSpeed() { 
    hitbox += direction * speed; 
    ICHI_INFO("Attacks hitbox updated: x: {}, y: {}", hitbox.getX(), hitbox.getY());

    if (animation) 
    {
        ICHI_DEBUG("Animation exists. Updating coordinates.");
        animation->setX(hitbox.getX()); 
        animation->setY(hitbox.getY()); 
        animation->update(); 
    }
    else
    {
        ICHI_ERROR("Animation pointer is null!"); 
    }
}