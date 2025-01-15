#ifndef CHARACTER_H
#define CHARACTER_H

#include "Ichi/UIComponents/progressBar.h"
#include "Ichi/Graphics/animatedSprite.h"
#include "Ichi/Graphics/sprite.h"
#include "Ichi/DataTypes/hitbox.h"
#include "Ichi/DataTypes/vector2D.h"

#include "Implementation/attack.h"
#include "Implementation/profile.h"
#include "Constants.h"

#include <map>
#include <memory>
#include <algorithm>

class Attack;

class Character : public ichi::core::Component
{

    enum class Direction
    {
        NEUTRAL,
        DOWN,
        SIDE,
    };

public:
    enum class AnimationState
    {
        LEFT_IDLE,
        LEFT_WALKING,
        LEFT_JUMPING,
        LEFT_FALLING,
        RIGHT_IDLE,
        RIGHT_WALKING,
        RIGHT_JUMPING,
        RIGHT_FALLING,
    };

    enum class AttackType
    {
        NONE,
        NEUTRAL_LIGHT,
        SIDE_LIGHT,
        DOWN_LIGHT,
        NEUTRAL_HEAVY,
        SIDE_HEAVY,
        DOWN_HEAVY,
    };
    Character(ichi::datatypes::Hitbox &hitbox, std::map<AnimationState, std::shared_ptr<ichi::graphics::AnimatedSprite>> animations,
              const Profile *p, std::map<AttackType, std::shared_ptr<Attack>> attacks, bool facingRight, int id = -1)
        : Component(hitbox), facingRight(facingRight), animations(animations), profile(p), controllerID(id), attacks(attacks)
    {
        ichi::datatypes::Hitbox hb(ichi::datatypes::Point(10, 10), 70, 10, false);
        if (!facingRight)
            hb.setX(384 - 70 - 10);

        ichi::graphics::Sprite s(hb, ichi::graphics::Sprite::Layer::UICOMPONENT, PROGRESS_BAR_PATH);
        healthBar = std::make_unique<ichi::uicomponents::ProgressBar>(hb, s, COLOR_GREEN_PATH, !facingRight);

        ichi::datatypes::Hitbox winHb(ichi::datatypes::Point(hb.getX() + hb.getWidth() - 8, 20), 8, 8, false);
        if (facingRight)
        {
            win1 = std::make_unique<ichi::graphics::Sprite>(winHb, ichi::graphics::Sprite::Layer::UICOMPONENT, WIN_PATH);
            emptyWin1 = std::make_unique<ichi::graphics::Sprite>(winHb, ichi::graphics::Sprite::Layer::UICOMPONENT, EMPTY_WIN_PATH);

            winHb -= ichi::datatypes::Point(20, 0);

            win2 = std::make_unique<ichi::graphics::Sprite>(winHb, ichi::graphics::Sprite::Layer::UICOMPONENT, WIN_PATH);
            emptyWin2 = std::make_unique<ichi::graphics::Sprite>(winHb, ichi::graphics::Sprite::Layer::UICOMPONENT, EMPTY_WIN_PATH);

            winHb -= ichi::datatypes::Point(20, 0);

            win3 = std::make_unique<ichi::graphics::Sprite>(winHb, ichi::graphics::Sprite::Layer::UICOMPONENT, WIN_PATH);
            emptyWin3 = std::make_unique<ichi::graphics::Sprite>(winHb, ichi::graphics::Sprite::Layer::UICOMPONENT, EMPTY_WIN_PATH);
            return;
        }
        winHb.setX(hb.getX());

        win1 = std::make_unique<ichi::graphics::Sprite>(winHb, ichi::graphics::Sprite::Layer::UICOMPONENT, WIN_PATH);
        emptyWin1 = std::make_unique<ichi::graphics::Sprite>(winHb, ichi::graphics::Sprite::Layer::UICOMPONENT, EMPTY_WIN_PATH);

        winHb += ichi::datatypes::Point(20, 0);

        win2 = std::make_unique<ichi::graphics::Sprite>(winHb, ichi::graphics::Sprite::Layer::UICOMPONENT, WIN_PATH);
        emptyWin2 = std::make_unique<ichi::graphics::Sprite>(winHb, ichi::graphics::Sprite::Layer::UICOMPONENT, EMPTY_WIN_PATH);

        winHb += ichi::datatypes::Point(20, 0);

        win3 = std::make_unique<ichi::graphics::Sprite>(winHb, ichi::graphics::Sprite::Layer::UICOMPONENT, WIN_PATH);
        emptyWin3 = std::make_unique<ichi::graphics::Sprite>(winHb, ichi::graphics::Sprite::Layer::UICOMPONENT, EMPTY_WIN_PATH);
    }

    void handleInput();
    void update();
    void draw() const;

    void setDirection(bool facingRight) { this->facingRight = facingRight; }
    bool isFacingRight() const { return facingRight; }

    void setPosition(ichi::datatypes::Point pt);

    bool addWin() { return ++wins == 3; }

    void checkForHit(Character &);

    float getHp() const { return hp; }
    void resetHp() { hp = MAX_HP; }
    void takeDamage(float dmg) { hp = std::clamp(hp - dmg, .0f, MAX_HP); }

    inline static const float MAX_HP = 100;

private:
    const std::string COLOR_GREEN_PATH = constants::gResPath + "images/UIComponents/colorGreen.png";
    const std::string PROGRESS_BAR_PATH = constants::gResPath + "images/UIComponents/ProgressBar.png";

    const std::string WIN_PATH = constants::gResPath + "images/UIComponents/Win.png";
    const std::string EMPTY_WIN_PATH = constants::gResPath + "images/UIComponents/EmptyWin.png";

    const float speed = 1.f;
    const float jumpVelocity = -6.9f;
    const float gravity = 0.35f;

    ichi::datatypes::Point facingRightDiff{32, 10};
    ichi::datatypes::Point facingLeftDiff{100, 10};

    float hp = MAX_HP;
    int wins = 0;

    bool facingRight;
    bool grounded = false;
    bool isBlocking = false;

    ichi::datatypes::Vector2D velocity{0, 0};
    Direction direciton = Direction::NEUTRAL;

    AnimationState activeState = AnimationState::LEFT_IDLE;
    std::map<AnimationState, std::shared_ptr<ichi::graphics::AnimatedSprite>> animations;

    const Profile *profile;
    int controllerID;

    AttackType currentAttack = AttackType::NONE;
    std::map<AttackType, std::shared_ptr<Attack>> attacks;

    std::unique_ptr<ichi::graphics::Sprite> win1;
    std::unique_ptr<ichi::graphics::Sprite> emptyWin1;
    std::unique_ptr<ichi::graphics::Sprite> win2;
    std::unique_ptr<ichi::graphics::Sprite> emptyWin2;
    std::unique_ptr<ichi::graphics::Sprite> win3;
    std::unique_ptr<ichi::graphics::Sprite> emptyWin3;
    std::unique_ptr<ichi::uicomponents::ProgressBar> healthBar;

    void updateAnimationState();
    void applyForce();
    void checkWallCollision();
    void checkGroundCollision();
    void startAttack();
};
#endif