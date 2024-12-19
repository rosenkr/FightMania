#include "Ichi/DataTypes/hitbox.h"

namespace ichi::datatypes
{
    // Basically check minx to the others maxx, and same for y, symmetrically
    bool Hitbox::isOverlapping(const Hitbox &other) const
    {
        return SDL_HasIntersection(getSDLRect(), other.getSDLRect());
    }
}