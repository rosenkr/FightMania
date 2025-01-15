#include "Implementation/meleeAttack.h"

#include "Ichi/Core/engine.h"
#include "Ichi/Graphics/textureManager.h"
#include "Ichi/log.h"

MeleeAttack::MeleeAttack(float dmg, Uint32 cooldown, std::shared_ptr<ichi::graphics::AnimatedSprite> leftPerson, std::shared_ptr<ichi::graphics::AnimatedSprite> rightPerson, std::map<int, ichi::datatypes::Hitbox> hitboxes)
    : Attack(dmg, cooldown), left(leftPerson), right(rightPerson), hitboxes(hitboxes)
{
    right->compleateLap();
    left->compleateLap();
}

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
    right->compleateLap();
    left->compleateLap();
}

void MeleeAttack::prepareForAttack(bool isFacingRight)
{
    hasHit = false;
    lastUsed = SDL_GetTicks();
    right.get()->reset();
    left.get()->reset();
}

bool MeleeAttack::hits(const Character &c)
{
    if (hasHit)
        return false;
    if (c.isFacingRight()) // if the opponent is facing right the user is facing left
    {
        auto it = hitboxes.find(left.get()->getCurrentFrame());
        if (it == hitboxes.end())
            return false;
        auto hb = (*it).second;
        hb.setX(left.get()->getHitbox().getPos().X + hb.getX());
        hb.setY(left.get()->getHitbox().getPos().Y + hb.getY());
        if (c.getHitbox().isOverlapping(hb))
            hasHit = true;
        return c.getHitbox().isOverlapping(hb);
    }
    auto it = hitboxes.find(right.get()->getCurrentFrame());
    if (it == hitboxes.end())
        return false;
    auto hb = (*it).second;

    hb.setX(180 - (hb.getX() + hb.getWidth()));

    hb.setX(right.get()->getHitbox().getPos().X + hb.getX());
    hb.setY(right.get()->getHitbox().getPos().Y + hb.getY());
    if (c.getHitbox().isOverlapping(hb))
        hasHit = true;
    return c.getHitbox().isOverlapping(hb);
}