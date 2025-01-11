#ifndef MELEE_ATTACK_H
#define MELEE_ATTACK_H

#include "Ichi/Graphics/animatedSprite.h"

#include "Implementation/attack.h"

#include <map>

class MeleeAttack : public Attack
{
public:
    MeleeAttack(float dmg, std::shared_ptr<ichi::graphics::AnimatedSprite> person, std::shared_ptr<ichi::graphics::AnimatedSprite> hitboxAnimation);
    ~MeleeAttack() = default;

    void draw() const override;
    void update() override;
    void reset(ichi::datatypes::Point) override;
    bool hits(Character c) override;
    bool isDone() override { return animation.get()->hasCompleatedALap(); }

private:
    std::shared_ptr<ichi::graphics::AnimatedSprite> animation;
    std::map<int, ichi::datatypes::Hitbox> hitboxes;
    std::vector<ichi::datatypes::Point> getNonTransparentPixels(SDL_Surface *surface);
};

#endif