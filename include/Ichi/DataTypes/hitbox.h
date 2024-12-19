#ifndef HITBOX_H
#define HITBOX_H
#include "Ichi/DataTypes/point.h"
#include "Ichi/DataTypes/vector2D.h"

#include <SDL2/SDL.h>
#include <functional>

namespace ichi::datatypes
{
    class Hitbox
    {
    public:
        Hitbox(Point p, int w, int h, bool tangible) : rect(SDL_Rect{p.X, p.Y, w, h}), isTangible(tangible) {};

        const SDL_Rect *getSDLRect() const { return &rect; }
        int getWidth() const { return rect.w; }
        int getHeight() const { return rect.h; }
        Point getPos() const { return Point(rect.x, rect.y); }
        int getX() const { return rect.x; }
        int getY() const { return rect.y; }
        bool getIsTangible() const { return isTangible; }

        bool pointIsInRect(Point p) const { return (rect.x <= p.X && p.X <= rect.x + rect.w) &&
                                                   (rect.y <= p.Y && p.Y <= rect.y + rect.h); }
        bool isOverlapping(const Hitbox &other) const;
        bool operator==(const Hitbox &other) const { return other.getWidth() == getWidth() && other.getHeight() == getHeight() && other.getX() == getX() && other.getY() == getY(); }
        bool operator!=(const Hitbox &other) const { return !(other == *this); }

        friend Hitbox operator+(Hitbox lhs, const Point &rhs)
        {
            lhs += rhs;
            return lhs;
        }

        Hitbox &operator+=(const Point &p)
        {
            rect = {rect.x + p.X, rect.y + p.Y, rect.w, rect.h};
            return *this;
        }

        Hitbox &operator-=(const Point &p)
        {
            rect = {rect.x - p.X, rect.y - p.Y, rect.w, rect.h};
            return *this;
        }

        Hitbox &operator+=(const Vector2D &vec)
        {
            rect = {rect.x + static_cast<int>(std::round(vec.getX())), rect.y + static_cast<int>(std::round(vec.getY())), rect.w, rect.h};
            return *this;
        }

        Hitbox &operator-=(const Vector2D &vec)
        {
            rect = {rect.x - static_cast<int>(std::round(vec.getX())), rect.y - static_cast<int>(std::round(vec.getY())), rect.w, rect.h};
            return *this;
        }

        void setX(int newX) { rect.x = newX; }
        void setY(int newY) { rect.y = newY; }

    private:
        SDL_Rect rect;
        bool isTangible = false;
    };
}
#endif