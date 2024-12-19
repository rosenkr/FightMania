#ifndef ATTACK_H
#define ATTACK_H
#include "Ichi/Core/component.h"
#include "Ichi/Graphics/sprite.h"
#include "Ichi/DataTypes/vector2D.h"
#include "Ichi/DataTypes/hitbox.h"
#include "Ichi/Graphics/animatedSprite.h"
#include <memory>

class Attack : public ichi::core::Component{
    public:
        Attack(ichi::datatypes::Hitbox hb, std::shared_ptr<ichi::graphics::AnimatedSprite> animation): Component(hb), animation(animation){}
        void update();
        void draw() const;
    private:
        std::shared_ptr<ichi::graphics::AnimatedSprite> animation;

};


// cant have animation because animations need hitbox which is only relevant for actual attacks on the screen
class AttackType{
    public:
        AttackType(std::vector<std::string> paths, float dmg, float speed, int width, int height): paths(paths), dmg(dmg), speed(speed), width(width), height(height) {}
        std::vector<std::string> getPaths() const { return paths; }
        float getDmg() const { return dmg; }
        float getSpeed() const { return speed; }
        int getWidth() const { return width; }
        int getHeight() const { return height; }
    private:
        std::vector<std::string> paths;
        float dmg;
        float speed;
        int width;
        int height;
};

enum AttackNames { FIREBALL = 0 };
#endif

