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
#include "Ichi/log.h"

#include <algorithm>

void Character::applyForce()
{
    // Applies gravity
    velocity.setY(gravity + velocity.getY());

    // Applies force to hitbox
    hitbox += velocity;

    checkGroundCollision();

    animation.get()->setX(hitbox.getX());
    animation.get()->setY(hitbox.getY());
}
void Character::handleInput()
{
    if (profile->canTakeAction(Profile::Action::RIGHT))
    {
        direciton = Direction::SIDE;
        velocity.setX(speed);
    }
    else if (profile->canTakeAction(Profile::Action::LEFT))
    {
        direciton = Direction::SIDE;
        velocity.setX(-speed);
    }
    else
    {
        direciton = Direction::NEUTRAL;
        velocity.setX(0);
    }

    if (profile->canTakeAction(Profile::Action::UP))
    {
        direciton = Direction::NEUTRAL;
    }

    if (profile->canTakeAction(Profile::Action::DOWN))
    {
        direciton = Direction::DOWN;
        // implement crouch
    }

    if (grounded && profile->canTakeAction(Profile::Action::JUMP))
        velocity.setY(jumpVelocity);

    if (profile->canTakeAction(Profile::Action::LIGHT_ATTACK))
    {
        if (direciton == Direction::NEUTRAL && attacks.find(AttackType::NEUTRAL_LIGHT) != attacks.end())
        {
            if (auto ptr = dynamic_cast<ProjectileAttack *>(attacks.at(AttackType::NEUTRAL_LIGHT).get()))
                ptr->spawnProjectile(facingRight, hitbox.getPos()); // The projectile should go the same way the character is facing
        }
        if (direciton == Direction::SIDE && attacks.find(AttackType::SIDE_LIGHT) != attacks.end())
        {
            if (auto ptr = dynamic_cast<ProjectileAttack *>(attacks.at(AttackType::SIDE_LIGHT).get()))
                ptr->spawnProjectile(facingRight, hitbox.getPos()); // The projectile should go the same way the character is facing
        }
        if (direciton == Direction::DOWN && attacks.find(AttackType::DOWN_LIGHT) != attacks.end())
        {
            if (auto ptr = dynamic_cast<ProjectileAttack *>(attacks.at(AttackType::DOWN_LIGHT).get()))
                ptr->spawnProjectile(facingRight, hitbox.getPos()); // The projectile should go the same way the character is facing
        }
    }

    if (profile->canTakeAction(Profile::Action::HEAVY_ATTACK))
    {
        if (direciton == Direction::NEUTRAL && attacks.find(AttackType::NEUTRAL_HEAVY) != attacks.end())
        {
            if (auto ptr = dynamic_cast<ProjectileAttack *>(attacks.at(AttackType::NEUTRAL_HEAVY).get()))
                ptr->spawnProjectile(facingRight, hitbox.getPos()); // The projectile should go the same way the character is facing
        }
        if (direciton == Direction::SIDE && attacks.find(AttackType::SIDE_HEAVY) != attacks.end())
        {
            if (auto ptr = dynamic_cast<ProjectileAttack *>(attacks.at(AttackType::SIDE_HEAVY).get()))
                ptr->spawnProjectile(facingRight, hitbox.getPos()); // The projectile should go the same way the character is facing
        }
        if (direciton == Direction::DOWN && attacks.find(AttackType::DOWN_HEAVY) != attacks.end())
        {
            if (auto ptr = dynamic_cast<ProjectileAttack *>(attacks.at(AttackType::DOWN_HEAVY).get()))
                ptr->spawnProjectile(facingRight, hitbox.getPos()); // The projectile should go the same way the character is facing
        }
    }

    if (profile->canTakeAction(Profile::Action::BLOCK))
        isBlocking = true;
    else
        isBlocking = false;
}

void Character::update()
{
    animation.get()->update();
    handleInput();
    applyForce();

    for (auto a : attacks)
        a.second.get()->update();
}

void Character::checkGroundCollision()
{
    ichi::scene::Scene *s = ichi::scene::sceneManager::getActiveScene();
    grounded = false;                  // is not grounded untill proven otherwise
    for (auto &c : s->getComponents()) // for every component
    {
        if (auto g = dynamic_cast<Ground *>(c.get()))
        { // if component is Ground
            if (!(g->getHitbox() == hitbox) && g->getHitbox().isOverlapping(hitbox + ichi::datatypes::Point(0, 1)))
                grounded = true;

            if (!(g->getHitbox() == hitbox) && g->getHitbox().isOverlapping(hitbox))
            {
                hitbox.setY(g->getHitbox().getY() - hitbox.getHeight());
                velocity.setY(0);
                grounded = true;
                return;
            }
        }
    }
}

void Character::draw() const
{
    animation.get()->draw();
    for (auto a : attacks)
        a.second.get()->draw();
}