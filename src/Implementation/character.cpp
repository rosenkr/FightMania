#include "Implementation/character.h"
#include "Ichi/Core/component.h"
#include "Ichi/Graphics/textureManager.h"
#include "Ichi/Core/engine.h"
#include "Ichi/Input/keyboard.h"
#include "Ichi/Input/controllerHandler.h"
#include "Ichi/Scene/sceneManager.h"
#include "Implementation/ground.h"
#include "Ichi/Graphics/sprite.h"
#include "Implementation/attack.h"

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

    // if key press 'H', spawnAttack(attacks[FIREBALL])



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

void Character::spawnAttack(AttackType at) const {
    /*if(direction == LEFT) {

    }*/
    /*
        first: switch case on character direction.
        if left, set attackvelocity x negative. on right, set attackvelocity x positive
    */

    ichi::datatypes::Hitbox fireballHitbox(ichi::datatypes::Point(???, ???), at.getWidth(), at.getHeight(), true);
    std::shared_ptr<ichi::graphics::AnimatedSprite> fireballAnimation = std::make_shared<ichi::graphics::AnimatedSprite>(
    fireballHitbox, ichi::graphics::Sprite::Layer::FOREGROUND, attacks.at(FIREBALL).getPaths(), std::map<int, Uint32>{{0, 200}, {1, 200}, {2, 200}, {3, 200}});
    std::shared_ptr<Attack> fbAttack = std::make_shared<Attack>(fireballHitbox, fireballAnimation); // create attack
    // add attack to components
    ichi::scene::sceneManager::getActiveScene()->addComponent(fbAttack);
    // not removing attack ever though
}