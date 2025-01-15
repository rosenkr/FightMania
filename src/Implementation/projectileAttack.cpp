#include "Implementation/projectileAttack.h"
#include "Ichi/Core/window.h"
#include "Ichi/log.h"

void ProjectileAttack::update(ichi::datatypes::Point pt, bool isFacingRight)
{
    if (!isFacingRight && !leftCharacterAnimation.get()->hasCompleatedALap())
    {
        leftCharacterAnimation.get()->setX(pt.X);
        leftCharacterAnimation.get()->setY(pt.Y);
        leftCharacterAnimation.get()->update();
    }

    if (isFacingRight && !rightCharacterAnimation.get()->hasCompleatedALap())
    {
        rightCharacterAnimation.get()->setX(pt.X);
        rightCharacterAnimation.get()->setY(pt.Y);
        rightCharacterAnimation.get()->update();
    }

    for (auto it = projectiles.begin(); it != projectiles.end();)
    {
        it->moveInDirectionWithSpeed();
        if (it->getHitbox().getX() < 0 || it->getHitbox().getX() > WINDOW_WIDTH)
            it = projectiles.erase(it);
        else
            ++it; // Increment only if no element was erased
    }
}

void ProjectileAttack::draw(bool isFacingRight) const
{
    if (!isFacingRight && !leftCharacterAnimation.get()->hasCompleatedALap())
        leftCharacterAnimation.get()->draw();

    if (isFacingRight && !rightCharacterAnimation.get()->hasCompleatedALap())
        rightCharacterAnimation.get()->draw();

    for (auto p : projectiles)
        p.draw();
}

void ProjectileAttack::reset()
{
    leftCharacterAnimation.get()->reset();
    rightCharacterAnimation.get()->reset();
}

void ProjectileAttack::spawnProjectile(bool isGoingRight, ichi::datatypes::Point p)
{
    lastUsed = SDL_GetTicks();
    if (isGoingRight)
        projectiles.push_back(Projectile(rightProjectileAnimation, speed, p + ichi::datatypes::Point{60, 0}));
    else
        projectiles.push_back(Projectile(leftProjectileAnimation, -speed, p - ichi::datatypes::Point{60, 0}));
}

bool ProjectileAttack::hits(const Character &c)
{
    for (size_t i = 0; i < projectiles.size(); i++)
    {
        if (projectiles.at(i).isOverlapping(c.getHitbox())) // Should be pixel detection for the future
        {
            projectiles.erase(projectiles.begin() + i);
            return true;
        }
    }
    return false;
}