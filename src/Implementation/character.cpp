#include "Implementation/character.h"

#include "Ichi/Core/component.h"
#include "Ichi/Core/engine.h"

#include "Ichi/Graphics/textureManager.h"
#include "Ichi/Graphics/sprite.h"

#include "Ichi/Input/keyboard.h"
#include "Ichi/Input/controllerHandler.h"

#include "Ichi/Scene/sceneManager.h"

#include "Ichi/Audio/audioPlayer.h"

#include "Implementation/meleeAttack.h"
#include "Implementation/projectileAttack.h"

#include "Ichi/log.h"

#include <algorithm>

void Character::draw() const
{
    healthBar.get()->draw();

    switch (wins)
    {
    case 0:
        emptyWin1.get()->draw();
        emptyWin2.get()->draw();
        emptyWin3.get()->draw();
        break;
    case 1:
        win1.get()->draw();
        emptyWin2.get()->draw();
        emptyWin3.get()->draw();
        break;
    case 2:
        win1.get()->draw();
        win2.get()->draw();
        emptyWin3.get()->draw();
        break;
    case 3:
        win1.get()->draw();
        win2.get()->draw();
        win3.get()->draw();
        break;

    default:
        break;
    }

    for (const auto &a : attacks)
    {
        if (a.first == currentAttack)
        {
            if (a.second)
                a.second->draw(facingRight);
            else
                ICHI_ERROR("Attack with type {} has a null pointer.", static_cast<int>(a.first));
            continue;
        }

        if (auto ptr = dynamic_cast<ProjectileAttack *>(a.second.get()))
        {
            ptr->draw(facingRight);
        }
    }

    if (currentAttack != AttackType::NONE)
    {
        if (attacks.find(currentAttack) == attacks.end())
        {
            ICHI_ERROR("Invalid current attack: {} not found in attacks map.", static_cast<int>(currentAttack));
        }
        return;
    }

    auto animIt = animations.find(activeState);
    if (animIt != animations.end() && animIt->second)
    {
        animIt->second->draw();
    }
    else
    {
        ICHI_ERROR("Could not find animation for animation state with id: {}", static_cast<int>(activeState));
    }
}

void Character::update()
{
    healthBar.get()->setProcentageFilled(hp / MAX_HP);

    if (attacks.find(currentAttack) != attacks.end() && currentAttack != AttackType::NONE)
        if ((*attacks.find(currentAttack)).second.get()->isDone())
            currentAttack = AttackType::NONE;

    handleInput();
    updateAnimationState();
    applyForce();

    if (animations.find(activeState) == animations.end())
    {
        ICHI_ERROR("Could not find animation for animation state with id: {}", static_cast<int>(activeState));
        return;
    }

    for (auto a : attacks)
    {
        auto pos = (*animations.find(activeState)).second.get()->getHitbox().getPos();

        if (a.first == currentAttack)
        {
            a.second.get()->update(pos, facingRight);
            continue;
        }

        if (auto ptr = dynamic_cast<ProjectileAttack *>(a.second.get()))
            ptr->update(pos, facingRight);
    }

    if (currentAttack != AttackType::NONE)
        return;

    animations.at(activeState).get()->update();
}

void Character::applyForce()
{
    if (currentAttack != AttackType::NONE) // player shouldnt move when attacking
        return;

    // Applies gravity
    velocity.setY(gravity + velocity.getY());

    // Applies force to hitbox
    hitbox += velocity;

    checkGroundCollision();
    checkWallCollision();

    if (animations.find(activeState) != animations.end())
    {
        if (facingRight)
        {
            animations.at(activeState).get()->setX(hitbox.getX() - facingRightDiff.X);
            animations.at(activeState).get()->setY(hitbox.getY() - facingRightDiff.Y);
            return;
        }
        animations.at(activeState).get()->setX(hitbox.getX() - facingLeftDiff.X);
        animations.at(activeState).get()->setY(hitbox.getY() - facingLeftDiff.Y);
    }
    else
        ICHI_ERROR("Could not find animation for animation state with id: {}", static_cast<int>(activeState));
}

void Character::handleInput()
{
    if (currentAttack != AttackType::NONE || stunned)
        return;

    if (profile->canTakeAction(Profile::Action::BLOCK, controllerID))
    {
        velocity.setX(0);
        framesblocking++;
        blocking = true;
        return;
    }
    else
    {
        framesblocking = 0;
        blocking = false;
    }

    if (profile->canTakeAction(Profile::Action::UP, controllerID) || !(profile->canTakeAction(Profile::Action::DOWN, controllerID) || profile->canTakeAction(Profile::Action::RIGHT, controllerID) || profile->canTakeAction(Profile::Action::LEFT, controllerID)))
    {
        direciton = Direction::NEUTRAL;
    }

    if (profile->canTakeAction(Profile::Action::DOWN, controllerID))
    {
        direciton = Direction::DOWN;
        // implement crouch?
    }

    if (profile->canTakeAction(Profile::Action::RIGHT, controllerID))
    {
        direciton = Direction::SIDE;
        if (velocity.getX() < 0)
            velocity += ichi::datatypes::Vector2D(friction, 0);
        velocity.setX(std::clamp(velocity.getX() + acceleration, -MAX_SPEED, MAX_SPEED));
    }
    else if (profile->canTakeAction(Profile::Action::LEFT, controllerID))
    {
        direciton = Direction::SIDE;
        if (velocity.getX() > 0)
            velocity -= ichi::datatypes::Vector2D(friction, 0);
        velocity.setX(std::clamp(velocity.getX() - acceleration, -MAX_SPEED, MAX_SPEED));
    }
    else
    {
        if (velocity.getX() != 0)
        {
            if (velocity.getX() > 0)
                velocity -= ichi::datatypes::Vector2D(friction, 0);
            else
                velocity += ichi::datatypes::Vector2D(friction, 0);

            if ((velocity.getX() > 0 && velocity.getX() < friction) || (velocity.getX() < 0 && velocity.getX() > -friction))
                velocity.setX(0);
        }
    }

    if (grounded && profile->canTakeAction(Profile::Action::JUMP, controllerID))
        velocity.setY(jumpVelocity);

    if (grounded && profile->canTakeAction(Profile::Action::LIGHT_ATTACK, controllerID))
    {
        if (direciton == Direction::NEUTRAL && attacks.find(AttackType::NEUTRAL_LIGHT) != attacks.end())
            currentAttack = AttackType::NEUTRAL_LIGHT;

        if (direciton == Direction::DOWN && attacks.find(AttackType::DOWN_LIGHT) != attacks.end())
            currentAttack = AttackType::DOWN_LIGHT;

        if (direciton == Direction::SIDE && attacks.find(AttackType::SIDE_LIGHT) != attacks.end())
            currentAttack = AttackType::SIDE_LIGHT;
        startAttack();
        return;
    }

    if (grounded && profile->canTakeAction(Profile::Action::HEAVY_ATTACK, controllerID))
    {
        if (direciton == Direction::NEUTRAL && attacks.find(AttackType::NEUTRAL_HEAVY) != attacks.end())
            currentAttack = AttackType::NEUTRAL_HEAVY;

        if (direciton == Direction::DOWN && attacks.find(AttackType::DOWN_HEAVY) != attacks.end())
            currentAttack = AttackType::DOWN_HEAVY;

        if (direciton == Direction::SIDE && attacks.find(AttackType::SIDE_HEAVY) != attacks.end())
            currentAttack = AttackType::SIDE_HEAVY;
        ichi::audio::AudioPlayer::play(swordSwooshSf.get());
        startAttack();
        return;
    }
}

void Character::startAttack()
{
    if (currentAttack == AttackType::NONE)
    {
        ICHI_ERROR("Tried to start a attack with the attackType beeing NONE");
        return;
    }

    if (attacks.find(currentAttack) == attacks.end())
    {
        ICHI_ERROR("Could not find attack with id: {} in map", static_cast<int>(currentAttack));
        return;
    }

    auto attack = (*attacks.find(currentAttack)).second.get();

    if (!attack->canAttack())
    {
        currentAttack = AttackType::NONE;
        return;
    }

    attack->prepareForAttack(facingRight);
    if (auto ptr = dynamic_cast<ProjectileAttack *>(attack))
    {
        if (facingRight)
            ptr->queueAttack(facingRight, hitbox.getPos() + ichi::datatypes::Point(hitbox.getWidth(), 0));
        else
            ptr->queueAttack(facingRight, hitbox.getPos());
    }
}

void Character::updateAnimationState()
{
    if (currentAttack != AttackType::NONE)
        return;

    if (facingRight)
    {
        if (stunned)
        {
            activeState = AnimationState::RIGHT_STUNNED;
            return;
        }

        if (blocking)
        {
            activeState = AnimationState::RIGHT_BLOCKING;
            return;
        }

        if (velocity.getY() < 0 && !grounded)
        {
            activeState = AnimationState::RIGHT_JUMPING;
            return;
        }
        if (velocity.getY() > 0 && !grounded)
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

    if (stunned)
    {
        activeState = AnimationState::LEFT_STUNNED;
        return;
    }

    if (blocking)
    {
        activeState = AnimationState::LEFT_BLOCKING;
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

void Character::setPosition(ichi::datatypes::Point pt)
{
    hitbox.setX(pt.X);
    hitbox.setY(pt.Y);
    for (auto animation : animations)
    {
        animation.second.get()->setX(pt.X);
        animation.second.get()->setY(pt.Y);
    }
}

void Character::reset()
{
    stunned = false;
    velocity = ichi::datatypes::Vector2D(0, 0);
    hp = MAX_HP;
    for (auto pair : attacks)
        pair.second.get()->reset();
}

void Character::checkForHit(Character &other)
{
    for (auto attack : attacks)
    {
        if (dynamic_cast<MeleeAttack *>(attack.second.get()))
            if (currentAttack != attack.first)
                continue;
        if (attack.second.get()->hits(other))
            other.takeDamage(attack.second.get()->getDamage(), attack.second->getForce());
    }
}

void Character::takeDamage(float dmg, ichi::datatypes::Vector2D force)
{
    if (!blocking)
    {
        force.setX(std::abs(force.getX())); // if forces x value is positive then the character is sent to the right
        if (facingRight)                    // if the character is facing to the right it should be sent to the left
            force.setX(-force.getX());
        stunned = true;
        velocity = force;
        hp = std::clamp(hp - dmg, .0f, MAX_HP);
        ichi::audio::AudioPlayer::play(hitSf.get());
        return;
    }

    if (framesblocking <= parryFrameWindow)
    {
        ichi::audio::AudioPlayer::play(parrySf.get());
        return;
    }
    ichi::audio::AudioPlayer::play(blockSf.get());
    hp = std::clamp(hp - (dmg * BLOCK_REDUCE), .0f, MAX_HP);
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
            stunned = false;
            grounded = true;
            return;
        }

        if (c.get()->isOverlapping(hitbox + ichi::datatypes::Point(0, 1)))
        {
            stunned = false;
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
                hitbox.setX(c.get()->getX() - hitbox.getWidth());
            else
                hitbox.setX(c.get()->getX() + c.get()->getWidth());

            velocity.setX(0);
            return;
        }
    }
}