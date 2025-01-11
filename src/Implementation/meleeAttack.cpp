#include "Implementation/meleeAttack.h"

#include "Ichi/Core/engine.h"
#include "Ichi/Graphics/textureManager.h"
#include "Ichi/log.h"

MeleeAttack::MeleeAttack(float dmg, std::shared_ptr<ichi::graphics::AnimatedSprite> person, std::shared_ptr<ichi::graphics::AnimatedSprite> hitboxAnimation) : Attack(dmg), animation(person)
{
}

void MeleeAttack::draw() const
{
    animation.get()->draw();
}

void MeleeAttack::update()
{
    animation.get()->update();
}

void MeleeAttack::reset(ichi::datatypes::Point pt)
{
    animation.get()->setX(pt.X);
    animation.get()->setY(pt.Y);
    animation.get()->reset();
}

bool MeleeAttack::hits(Character c)
{
    return hitboxes.at(animation.get()->getCurrentFrame()).isOverlapping(c.getHitbox());
}