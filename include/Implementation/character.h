#ifndef CHARACTER_H
#define CHARACTER_H

#include "Ichi/UIComponents/progressBar.h"
#include "Ichi/Graphics/animatedSprite.h"
#include "Ichi/Graphics/sprite.h"
#include "Ichi/DataTypes/hitbox.h"
#include "Ichi/DataTypes/vector2D.h"
#include "Implementation/attack.h"
#include "Implementation/profile.h"

#include <map>
#include <memory>

class Attack;

class Character : public ichi::core::Component
{

    enum class Direction
    {
        NEUTRAL,
        DOWN,
        SIDE,
    };

public:
    enum class AnimationState
    {
        LEFT_IDLE,
        LEFT_WALKING,
        LEFT_JUMPING,
        LEFT_FALLING,
        RIGHT_IDLE,
        RIGHT_WALKING,
        RIGHT_JUMPING,
        RIGHT_FALLING,
    };

    enum class AttackType
    {
        NONE,
        NEUTRAL_LIGHT,
        SIDE_LIGHT,
        DOWN_LIGHT,
        NEUTRAL_HEAVY,
        SIDE_HEAVY,
        DOWN_HEAVY,
    };
    Character(ichi::datatypes::Hitbox &hitbox, std::map<AnimationState, std::shared_ptr<ichi::graphics::AnimatedSprite>> animations, const Profile *p, std::map<AttackType, std::shared_ptr<Attack>> attacks, int id = -1)
        : Component(hitbox), animations(animations), profile(p), controllerID(id), attacks(attacks) {}

    void handleInput();
    void update();
    void draw() const;
    void setDirection(bool facingRight) { this->facingRight = facingRight; }
    bool isFacingRight() const { return facingRight; }

    void setPosition(ichi::datatypes::Point &pt);

    bool addWin() { return ++wins == 3; }

    float getHp() const { return hp; }
    void resetHp() { hp = MAX_HP; }
    void setHp(float newHp) { hp = newHp; }

    inline static const float MAX_HP = 100;

private:
    const float speed = 1.f;
    const float jumpVelocity = -6.9f;
    const float gravity = 0.35f;

    float hp = MAX_HP;
    int wins = 0;

    bool facingRight = true;
    bool grounded = false;
    bool isBlocking = false;

    ichi::datatypes::Vector2D velocity{0, 0};
    Direction direciton = Direction::NEUTRAL;

    AnimationState activeState = AnimationState::LEFT_IDLE;
    std::map<AnimationState, std::shared_ptr<ichi::graphics::AnimatedSprite>> animations;

    const Profile *profile;
    int controllerID;

    AttackType currentAttack = AttackType::NONE;
    std::map<AttackType, std::shared_ptr<Attack>> attacks;

    void updateAnimationState();
    void applyForce();
    void checkWallCollision();
    void checkGroundCollision();
    void startAttack();
};
#endif