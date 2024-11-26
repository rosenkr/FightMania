#ifndef HITBOX_H
#define HITBOX_H
#include <SDL2/SDL.h>
#include "point.h"

namespace ichi::core {
    class Hitbox {
        public:
            Hitbox(Point p, int w, int h){ rect.x = p.X; rect.y = p.Y; rect.w = w; rect.h = h;}
            int getWidth() const { return rect.w; }
            int getHeight() const { return rect.h; };
            int getX() const { return rect.x; }
            int getY() const { return rect.y; }
            void setTangible(bool t) { isTangible = t; }
            bool isOverlapping(const Hitbox& other) const;
        private:
            SDL_Rect rect;
            bool isTangible = false;
    };
}
#endif