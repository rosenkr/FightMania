#ifndef PROJECTILE_ATTACK_H
#define PROJECTILE_ATTACK_H

#include "Implementation/attack.h"
#include "Ichi/Graphics/animatedSprite.h"

#include <memory>

class Projectile
{
public:
    Projectile(std::shared_ptr<ichi::graphics::AnimatedSprite> animation, float speed, ichi::datatypes::Point pos) : speed(speed)
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
    std::shared_ptr<ichi::graphics::AnimatedSprite> animation;
    float speed;
};

class ProjectileAttack : public Attack
{
public:
    ProjectileAttack(std::shared_ptr<ichi::graphics::AnimatedSprite> animation, float speed, float dmg, Uint32 cooldownTime) : Attack(dmg), animation(std::move(animation)), speed(speed), cooldownTime(cooldownTime) {}

    void update();
    void draw() const;

    void spawnProjectile(bool isGoingRight, ichi::datatypes::Point p);
    float getDamage() { return damage; }
    bool hits(Character c);

private:
    std::vector<Projectile> projectiles;
    std::shared_ptr<ichi::graphics::AnimatedSprite> animation;
    float speed;
    Uint32 cooldownTime;
    Uint32 lastSpawned = 0;
};

#endif
