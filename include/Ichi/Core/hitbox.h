#ifndef HITBOX_H
#define HITBOX_H
#include <SDL2/SDL.h>
#include "point.h"

namespace ichi::core
{
    class Hitbox
    {
    public:
        Hitbox(Point p, int w, int h, bool tangible) : rect(SDL_Rect{p.X, p.Y, w, h}), isTangible(tangible) {};

        const SDL_Rect *toSdlRect() const { return &rect; }
        int getWidth() const { return rect.w; }
        int getHeight() const { return rect.h; }
        int getX() const { return rect.x; }
        int getY() const { return rect.y; }

        bool isOverlapping(const Hitbox &other) const;

    private:
        SDL_Rect rect;
        bool isTangible = false;
    };
}
#endif