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

class Character : public ichi::core::Component
{
public:
    Character(ichi::datatypes::Hitbox &hitbox, std::shared_ptr<ichi::graphics::AnimatedSprite> animation, const Profile *p, std::map<AttackNames, AttackType> attacks)
        : Component(hitbox), hp(100), lives(3), animation(std::move(animation)), profile(p), attacks(attacks) {}

    void spawnAttack(AttackType at) const;

    void handleInput();
    void update();
    void draw() const;

private:
    ichi::datatypes::Point drawPointAttack(AttackType) const;
    float hp;
    int lives;
    const float speed = 1.f;
    float jumpVelocity = -6.9f;

    ichi::datatypes::Vector2D gravity{0, 0.35f};
    ichi::datatypes::Vector2D velocity{0, 0};
    ichi::datatypes::Vector2D direction{-1, 0}; // left
    void setDirection(ichi::datatypes::Vector2D& dir){ direction = dir; }


    bool grounded = false;

    std::shared_ptr<ichi::graphics::AnimatedSprite> animation;

    const Profile *profile;
    std::map<AttackNames, AttackType> attacks;
    void applyForce();
    void checkGroundCollision();
};
#endif