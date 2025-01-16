#ifndef ATTACK_H
#define ATTACK_H

#include "Implementation/character.h"
#include "Ichi/DataTypes/point.h"

class Character; // Forward delcalration

class Attack
{
public:
    virtual void draw(bool) const = 0;
    virtual void update(ichi::datatypes::Point, bool) = 0;
    virtual void reset() = 0;
    virtual void prepareForAttack(bool) = 0;
    virtual bool hits(const Character &c) = 0;
    virtual bool isDone() = 0;
    bool canAttack() { return SDL_GetTicks() > lastUsed + cooldownTime; }
    float getDamage() { return damage; }
    ichi::datatypes::Vector2D getForce() { return force; }

protected:
    Attack(float dmg, ichi::datatypes::Vector2D force, Uint32 cooldown) : damage(dmg), force(force), cooldownTime(cooldown) {}
    ~Attack() = default;

    float damage;
    ichi::datatypes::Vector2D force;
    Uint32 cooldownTime;
    Uint32 lastUsed = 0;
};

#endif // ATTACK_H
