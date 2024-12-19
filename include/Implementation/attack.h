#ifndef ATTACK_H
#define ATTACK_H
#include "Ichi/Core/component.h"
#include "Ichi/Graphics/sprite.h"
#include "Ichi/DataTypes/vector2D.h"
#include "Ichi/DataTypes/hitbox.h"
/*
enum class AttackType { 
    ICE,
    FIRE
};*/

// Every attack has a direction which is a vector for example left attack is (-1, 0) direction
class Attack : public ichi::core::Component{
    public:
        Attack(ichi::datatypes::Hitbox hb, ichi::datatypes::Vector2D direction, float dmg, float speed): Component(hb), direction(direction), dmg(dmg), speed(speed) {}
        void update();
        void draw() const;
    private:
        ichi::datatypes::Vector2D direction;
        float dmg;
        float speed;
};

#endif