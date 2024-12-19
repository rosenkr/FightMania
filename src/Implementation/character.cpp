#include "Implementation/character.h"
#include "Ichi/Core/component.h"
#include "Ichi/Graphics/textureManager.h"
#include "Ichi/Core/engine.h"
#include "Ichi/Input/keyboard.h"
#include "Ichi/Input/controllerHandler.h"
#include "Ichi/Scene/sceneManager.h"
#include "Implementation/ground.h"

#include <algorithm>

void Character::applyForce()
{
    // Applies gravity
    velocity += gravity;

    // Applies force to hitbox
    hitbox += velocity;

    checkGroundCollision();

    animation.get()->setX(hitbox.getX());
    animation.get()->setY(hitbox.getY());
}

void Character::handleInput()
{

    if (profile->canTakeAction(Profile::Action::UP))
    {
    }

    if (profile->canTakeAction(Profile::Action::UP))
    {
    }

    if (profile->canTakeAction(Profile::Action::RIGHT))
        velocity.setX(speed);
    else if (profile->canTakeAction(Profile::Action::LEFT))
        velocity.setX(-speed);
    else
        velocity.setX(0);

    if (grounded && profile->canTakeAction(Profile::Action::JUMP))
        velocity.setY(jumpVelocity);

    if (profile->canTakeAction(Profile::Action::LIGHT_ATTACK))
    {
    }

    if (profile->canTakeAction(Profile::Action::HEAVY_ATTACK))
    {
    }

    if (profile->canTakeAction(Profile::Action::BLOCK))
    {
    }
}

void Character::update()
{
    animation.get()->update();
    handleInput();
    applyForce();
}

// currently must handle both raw pointers and shared pointers
void Character::checkGroundCollision()
{
    ichi::scene::Scene *s = ichi::scene::sceneManager::getActiveScene();
    grounded = false; // is not grounded untill proven otherwise

    for (auto &c : s->getCollisionHitboxes())
    {
        if (!(c.get() == hitbox) && c.get().isOverlapping(hitbox + ichi::datatypes::Point(0, 1)))
            grounded = true;

        if (!(c.get() == hitbox) && c.get().isOverlapping(hitbox))
        {
            hitbox.setY(c.get().getY() - hitbox.getHeight());
            velocity.setY(0);
            grounded = true;
            return;
        }
    }
}

void Character::draw() const
{
    animation.get()->draw();
}