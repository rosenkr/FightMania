#include "Ichi/DataTypes/hitbox.h"

namespace ichi::datatypes
{
    // Basically check minx to the others maxx, and same for y, symmetrically
    bool Hitbox::isOverlapping(const Hitbox &other) const
    {
        int otherMaxX = other.getX() + other.getWidth();
        int otherMaxY = other.getY() + other.getHeight();
        int thisMaxX = rect.x + rect.w;
        int thisMaxY = rect.y + rect.h;
        return rect.x < otherMaxX && other.getX() < thisMaxX && rect.y < otherMaxY && other.getY() < thisMaxY;
    }
}