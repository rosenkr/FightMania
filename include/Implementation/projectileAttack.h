#ifndef PROJECTILE_ATTACK_H
#define PROJECTILE_ATTACK_H

#include "Implementation/attack.h"
#include "Ichi/Graphics/animatedSprite.h"

#include <memory>

typedef std::shared_ptr<ichi::graphics::AnimatedSprite> AnimatedSprite;

class Projectile
{
public:
    Projectile(AnimatedSprite animation, float speed, ichi::datatypes::Point pos) : speed(speed)
    {
        this->animation = std::make_shared<ichi::graphics::AnimatedSprite>(*animation.get());
        this->animation.get()->setX(pos.X);
        this->animation.get()->setY(pos.Y);
    }
    void draw() const { animation.get()->draw(); }
    void moveInDirectionWithSpeed()
    {
        animation.get()->setX(animation.get()->getX() + speed);
        animation.get()->update();
    }
    bool isOverlapping(ichi::datatypes::Hitbox hb) const { return hb.isOverlapping(animation.get()->getHitbox()); }
    const ichi::datatypes::Hitbox &getHitbox() { return animation.get()->getHitbox(); }

private:
    AnimatedSprite animation;
    float speed;
};

class ProjectileAttack : public Attack
{
public:
    ProjectileAttack(AnimatedSprite paLeft, AnimatedSprite paRight, AnimatedSprite caLeft, AnimatedSprite caRight, float speed, float dmg, Uint32 cooldownTime)
        : Attack(dmg, cooldownTime), leftProjectileAnimation(paLeft), rightProjectileAnimation(paRight), leftCharacterAnimation(caLeft), rightCharacterAnimation(caRight), speed(speed)
    {
        caLeft.get()->compleateLap(); // to avoid the characters to be animated the first time
        caRight.get()->compleateLap();
    }

    void draw(bool) const override;
    void update(ichi::datatypes::Point, bool) override;
    void reset() override;
    bool isDone() override { return leftCharacterAnimation.get()->hasCompleatedALap() || rightCharacterAnimation.get()->hasCompleatedALap(); }

    void spawnProjectile(bool isGoingRight, ichi::datatypes::Point p);
    float getDamage() { return damage; }
    bool hits(const Character &c);

private:
    std::vector<Projectile> projectiles;
    AnimatedSprite leftProjectileAnimation;
    AnimatedSprite rightProjectileAnimation;
    AnimatedSprite leftCharacterAnimation;
    AnimatedSprite rightCharacterAnimation;
    float speed;
};

#endif
