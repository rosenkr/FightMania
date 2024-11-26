#include "Ichi/Core/hitbox.h"

namespace ichi::core
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

namespace std
{
    size_t hash<ichi::core::Hitbox>::operator()(const ichi::core::Hitbox &hitbox) const
    {
        // Hash individual components of the SDL_Rect
        size_t xHash = hash<int>()(hitbox.getX());
        size_t yHash = hash<int>()(hitbox.getY());
        size_t wHash = hash<int>()(hitbox.getWidth());
        size_t hHash = hash<int>()(hitbox.getHeight());

        // Combine the hashes (XOR and bit shifts)
        return xHash ^ (yHash << 1) ^ (wHash << 2) ^ (hHash << 3);
    }
}