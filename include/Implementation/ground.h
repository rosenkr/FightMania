#ifndef GROUND_H
#define GROUND_H
#include "Ichi/Core/component.h"

class Ground : public ichi::core::Component{
    public:
        Ground(ichi::datatypes::Hitbox& hitbox) : Component(hitbox){}
        void update();
        void draw() const;
    private:
}; 

#endif