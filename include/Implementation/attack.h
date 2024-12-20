#ifndef ATTACK_H
#define ATTACK_H
#include "Ichi/Core/component.h"
#include "Ichi/Graphics/sprite.h"
#include "Ichi/DataTypes/vector2D.h"
#include "Ichi/DataTypes/hitbox.h"
#include "Ichi/Graphics/animatedSprite.h"
#include "Ichi/log.h"
#include <memory>

class Attack : public ichi::core::Component, public std::enable_shared_from_this<Attack>{
    public:
        Attack(ichi::datatypes::Hitbox hb, std::shared_ptr<ichi::graphics::AnimatedSprite> animation, ichi::datatypes::Vector2D direction, float dmg, float speed): Component(hb), animation(std::move(animation)), direction(direction), dmg(dmg), speed(speed) {}
        ichi::datatypes::Vector2D getDirection() const { return direction; }
        void update();
        void draw() const;
        void moveInDirectionWithSpeed();
    private:
        std::shared_ptr<ichi::graphics::AnimatedSprite> animation;
        ichi::datatypes::Vector2D direction; 
        float dmg;
        float speed;

};


// cant have animation because animations need hitbox which is only relevant for actual attacks on the screen
class AttackType{
    public:
        AttackType(std::vector<std::string> paths, int width, int height): paths(paths), width(width), height(height) {}
        std::vector<std::string> getPaths() const { return paths; }
        int getWidth() const { return width; }
        int getHeight() const { return height; }
    private:
        std::vector<std::string> paths;
        int width;
        int height;
};

enum AttackNames { FIREBALL = 0 };
#endif

