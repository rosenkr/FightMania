#ifndef CHARACTER_H
#define CHARACTER_H
#include "Ichi/Core/component.h"
#include "Ichi/Graphics/animatedSprite.h"
#include "Ichi/Graphics/sprite.h"
#include "Ichi/UIComponents/progressBar.h"
#include "Ichi/DataTypes/hitbox.h"
#include "Ichi/DataTypes/vector2D.h"

#include <map>
#include <memory>

class Character : public ichi::core::Component
{
public:
    Character(
        ichi::datatypes::Hitbox &hitbox,
        float hp, float ms, int lives,
        std::shared_ptr<ichi::graphics::AnimatedSprite> animation,
        bool grounded,
        ichi::Vector2D velocity = ichi::Vector2D()) : Component(hitbox), hp(hp), ms(ms), lives(lives), animation(std::move(animation)), grounded(grounded), velocity(velocity) {}

    bool collidesWith(const Component &other) const;
    void handleInput();
    void update();
    void draw() const;

private:
    float hp;
    float ms;
    float jumpVelocity = -60.0f;
    int lives;
    std::shared_ptr<ichi::graphics::AnimatedSprite> animation;
    bool grounded = false;
    Uint32 jumpTime = 0;
    void applyGravity();
    ichi::Vector2D &velocity;
    Uint32 fallTime = 0;
    bool checkGroundCollision();
    float calculateVerticalPositionKinematic(float dt, float v, float g, int y);
};
#endif