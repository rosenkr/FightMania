#ifndef MELEE_ATTACK_H
#define MELEE_ATTACK_H

#include "Ichi/Graphics/animatedSprite.h"

#include "Implementation/attack.h"

#include <map>

class MeleeAttack : public Attack
{
public:
    MeleeAttack(float dmg, Uint32 cooldown, std::shared_ptr<ichi::graphics::AnimatedSprite> leftPerson, std::shared_ptr<ichi::graphics::AnimatedSprite> rightPerson, std::map<int, ichi::datatypes::Hitbox> hitboxes);
    ~MeleeAttack() = default;

    void draw(bool) const override;
    void update(ichi::datatypes::Point, bool) override;
    void reset() override;
    bool hits(const Character &c) override;
    bool isDone() override { return left.get()->hasCompleatedALap() || right.get()->hasCompleatedALap(); }

private:
    std::shared_ptr<ichi::graphics::AnimatedSprite> left;
    std::shared_ptr<ichi::graphics::AnimatedSprite> right;
    std::map<int, ichi::datatypes::Hitbox> hitboxes;
    bool hasHit = false;
};

#endif