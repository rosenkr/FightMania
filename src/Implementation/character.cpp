#include "Implementation/character.h"
#include "Ichi/Core/component.h"
#include "Ichi/Graphics/textureManager.h"
#include "Ichi/Core/engine.h"
#include "Ichi/Input/keyboard.h"
#include "Ichi/Input/controllerHandler.h"
#include "Ichi/Scene/sceneManager.h"
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
    checkWallCollision();

    if (animations.find(activeState) != animations.end())
    {
        animations.at(activeState).get()->setX(hitbox.getX());
        animations.at(activeState).get()->setY(hitbox.getY());
    }
    else
        ICHI_ERROR("Could not find animation for animation state with id: {}", static_cast<int>(activeState));
}

void Character::handleInput()
{
    if (profile->canTakeAction(Profile::Action::UP, controllerID))
    {
        direciton = Direction::NEUTRAL;
    }

    if (profile->canTakeAction(Profile::Action::DOWN, controllerID))
    {
        direciton = Direction::DOWN;
        // implement crouch
    }

    if (profile->canTakeAction(Profile::Action::RIGHT, controllerID))
    {
        direciton = Direction::SIDE;
        velocity.setX(speed);
    }
    else if (profile->canTakeAction(Profile::Action::LEFT, controllerID))
    {
        direciton = Direction::SIDE;
        velocity.setX(-speed);
    }
    else
    {
        direciton = Direction::NEUTRAL;
        velocity.setX(0);
    }

    if (grounded && profile->canTakeAction(Profile::Action::JUMP, controllerID))
        velocity.setY(jumpVelocity);

    if (profile->canTakeAction(Profile::Action::LIGHT_ATTACK, controllerID))
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

    if (profile->canTakeAction(Profile::Action::HEAVY_ATTACK, controllerID))
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

    if (profile->canTakeAction(Profile::Action::BLOCK, controllerID))
        isBlocking = true;
    else
        isBlocking = false;
}

void Character::update()
{
    handleInput();
    applyForce();
    updateAnimationState();

    if (animations.find(activeState) != animations.end())
        animations.at(activeState).get()->update();
    else
        ICHI_ERROR("Could not find animation for animation state with id: {}", static_cast<int>(activeState));

    for (auto a : attacks)
        a.second.get()->update();
}

void Character::draw() const
{
    if (animations.find(activeState) != animations.end())
        animations.at(activeState).get()->draw();
    else
        ICHI_ERROR("Could not find animation for animation state with id: {}", static_cast<int>(activeState));
    for (auto a : attacks)
        a.second.get()->draw();
}

void Character::updateAnimationState()
{
    if (facingRight)
    {
        if (velocity.getY() < 0)
        {
            activeState = AnimationState::RIGHT_JUMPING;
            return;
        }
        if (velocity.getY() > 0)
        {
            activeState = AnimationState::RIGHT_FALLING;
            return;
        }

        if (velocity.getX() != 0)
        {
            activeState = AnimationState::RIGHT_WALKING;
            return;
        }
        activeState = AnimationState::RIGHT_IDLE;
        return;
    }

    if (velocity.getY() < 0 && !grounded)
    {
        activeState = AnimationState::LEFT_JUMPING;
        return;
    }
    if (velocity.getY() > 0 && !grounded)
    {
        activeState = AnimationState::LEFT_FALLING;
        return;
    }

    if (velocity.getX() != 0)
    {
        activeState = AnimationState::LEFT_WALKING;
        return;
    }
    activeState = AnimationState::LEFT_IDLE;
}

void Character::checkGroundCollision()
{
    ichi::scene::Scene *s = ichi::scene::sceneManager::getActiveScene();
    grounded = false; // is not grounded untill proven otherwise
    for (auto &c : s->getCollisionHitboxes())
    {
        if (c.get()->getY() < hitbox.getY() || *c.get() == hitbox)
            continue;

        if (c.get()->isOverlapping(hitbox))
        {
            hitbox.setY(c.get()->getY() - hitbox.getHeight());
            velocity.setY(0);
            grounded = true;
            return;
        }

        if (c.get()->isOverlapping(hitbox + ichi::datatypes::Point(0, 1)))
        {
            grounded = true;
            return;
        }
    }
}

void Character::checkWallCollision()
{
    ichi::scene::Scene *s = ichi::scene::sceneManager::getActiveScene();
    for (auto &c : s->getCollisionHitboxes())
    {
        if (c.get()->getY() > hitbox.getY() || *c.get() == hitbox)
            continue;

        if (c.get()->isOverlapping(hitbox))
        {
            if (hitbox.getX() < c.get()->getX())
                hitbox.setX(c.get()->getX() - hitbox.getHeight());
            else
                hitbox.setX(c.get()->getX() + c.get()->getWidth());

            velocity.setX(0);
            return;
        }
    }
}