#ifndef HITBOX_H
#define HITBOX_H
#include "Ichi/DataTypes/point.h"

#include <SDL2/SDL.h>
#include <functional>

namespace ichi::datatypes
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
        bool operator==(const Hitbox &other) const { return other.getWidth() == getWidth() && other.getHeight() == getHeight() && other.getX() == getX() && other.getY() == getY(); }
        bool operator!=(const Hitbox &other) const { return !(other == *this); }

    private:
        SDL_Rect rect;
        bool isTangible = false;
    };
}
#endif