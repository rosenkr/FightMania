#ifndef CHARACTER_H
#define CHARACTER_H

#include "Ichi/UIComponents/progressBar.h"
#include "Ichi/Graphics/animatedSprite.h"
#include "Ichi/Graphics/sprite.h"
#include "Ichi/DataTypes/hitbox.h"
#include "Ichi/DataTypes/vector2D.h"
#include "Implementation/projectileAttack.h"
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
        LEFT_ATTACKING,
        RIGHT_IDLE,
        RIGHT_WALKING,
        RIGHT_JUMPING,
        RIGHT_FALLING,
        RIGHT_ATTACKING,
    };

    enum class AttackType
    {
        NEUTRAL_LIGHT,
        SIDE_LIGHT,
        DOWN_LIGHT,
        NEUTRAL_HEAVY,
        SIDE_HEAVY,
        DOWN_HEAVY,
    };
    Character(ichi::datatypes::Hitbox &hitbox, std::map<AnimationState, std::shared_ptr<ichi::graphics::AnimatedSprite>> animations, const Profile *p, std::map<AttackType, std::shared_ptr<Attack>> attacks, int id = -1)
        : Component(hitbox), hp(100), lives(3), animations(animations), profile(p), controllerID(id), attacks(attacks) {}

    void handleInput();
    void update();
    void draw() const;
    void setDirection(bool facingRight) { this->facingRight = facingRight; }

private:
    const float speed = 1.f;
    const float jumpVelocity = -6.9f;
    const float gravity = 0.35f;

    float hp;
    int lives;

    bool facingRight = true;
    bool grounded = false;
    bool isBlocking = false;

    ichi::datatypes::Vector2D velocity{0, 0};
    Direction direciton = Direction::NEUTRAL;

    AnimationState activeState = AnimationState::LEFT_IDLE;
    std::map<AnimationState, std::shared_ptr<ichi::graphics::AnimatedSprite>> animations;

    const Profile *profile;
    int controllerID;

    std::map<AttackType, std::shared_ptr<Attack>> attacks;

    void updateAnimationState();
    void applyForce();
    void checkWallCollision();
    void checkGroundCollision();
};
#endif