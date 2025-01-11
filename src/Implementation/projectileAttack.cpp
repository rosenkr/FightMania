#include "Implementation/projectileAttack.h"
#include "Ichi/Core/window.h"
#include "Ichi/log.h"

void ProjectileAttack::update()
{
    if (!characterAnimation.get()->hasCompleatedALap())
        characterAnimation.get()->update();
    for (auto it = projectiles.begin(); it != projectiles.end();)
    {
        it->moveInDirectionWithSpeed();
        if (it->getHitbox().getX() < 0 || it->getHitbox().getX() > WINDOW_WIDTH)
            it = projectiles.erase(it);
        else
            ++it; // Increment only if no element was erased
    }
}

void ProjectileAttack::draw() const
{
    if (!characterAnimation.get()->hasCompleatedALap())
        characterAnimation.get()->draw();
    for (auto p : projectiles)
        p.draw();
}

void ProjectileAttack::reset(ichi::datatypes::Point pt)
{
    characterAnimation.get()->setX(pt.X);
    characterAnimation.get()->setY(pt.Y);
    characterAnimation.get()->reset();
}

void ProjectileAttack::spawnProjectile(bool isGoingRight, ichi::datatypes::Point p)
{
    if (SDL_GetTicks() < lastSpawned + cooldownTime)
        return;

    characterAnimation.get()->setX(p.X);
    characterAnimation.get()->setY(p.Y);

    if (isGoingRight)
        projectiles.push_back(Projectile(projectileAnimation, speed, p));
    else
        projectiles.push_back(Projectile(projectileAnimation, -speed, p));
    lastSpawned = SDL_GetTicks();
}

bool ProjectileAttack::hits(Character c)
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