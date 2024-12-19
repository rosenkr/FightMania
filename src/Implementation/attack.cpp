#include "Implementation/attack.h"

void Attack::update() {
    // move depending on speed

    animation.get()->update();
}
void Attack::draw() const {
    // draw the animations

    animation.get()->draw();
}