#include "Implementation/meleeAttack.h"

#include "Ichi/Core/engine.h"
#include "Ichi/Graphics/textureManager.h"
#include "Ichi/log.h"

MeleeAttack::MeleeAttack(float dmg, Uint32 cooldown, std::shared_ptr<ichi::graphics::AnimatedSprite> leftPerson, std::shared_ptr<ichi::graphics::AnimatedSprite> rightPerson)
    : Attack(dmg, cooldown), left(leftPerson), right(rightPerson) {}

void MeleeAttack::draw(bool isRight) const
{
    if (isRight)
        right.get()->draw();
    else
        left.get()->draw();
}

void MeleeAttack::update(ichi::datatypes::Point pt, bool isFacingRight)
{
    if (isFacingRight)
    {
        right.get()->setX(pt.X);
        right.get()->setY(pt.Y);
        right.get()->update();
        return;
    }
    left.get()->setX(pt.X);
    left.get()->setY(pt.Y);
    left.get()->update();
}

void MeleeAttack::reset()
{
    lastUsed = SDL_GetTicks();
    left.get()->reset();
    right.get()->reset();
}

bool MeleeAttack::hits(const Character &c)
{
    auto it = hitboxes.find(left.get()->getCurrentFrame());
    if (it == hitboxes.end())
        return false;
    if (c.isFacingRight())
        return (*it).second.isOverlapping(c.getHitbox());
    return (*it).second.isOverlapping(c.getHitbox());
}