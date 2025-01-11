#ifndef ATTACK_H
#define ATTACK_H

#include "Implementation/character.h"
#include "Ichi/DataTypes/point.h"

class Character; // Forward delcalration

class Attack
{
public:
    virtual void draw() const = 0;
    virtual void update() = 0;
    virtual void reset(ichi::datatypes::Point) = 0;
    virtual bool hits(Character c) = 0;
    virtual bool isDone() = 0;

protected:
    Attack(float dmg) : damage(dmg) {}
    ~Attack() = default;

    float damage;
};

#endif // ATTACK_H
