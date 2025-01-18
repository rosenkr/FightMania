#ifndef CHARACTER_H
#define CHARACTER_H

#include "Ichi/UIComponents/progressBar.h"
#include "Ichi/Graphics/animatedSprite.h"
#include "Ichi/Graphics/sprite.h"
#include "Ichi/DataTypes/hitbox.h"
#include "Ichi/DataTypes/vector2D.h"

#include "Implementation/attack.h"
#include "Implementation/profile.h"
#include "Ichi/log.h"
#include "Constants.h"

#include "SDL2/SDL_mixer.h"

#include <map>
#include <memory>
#include <algorithm>

class Attack;

class Character : public ichi::core::Component
{
    struct MixChunkDeleter
    {
        void operator()(Mix_Chunk *chunk) const
        {
            if (chunk)
                Mix_FreeChunk(chunk);
        }
    };
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
        LEFT_BLOCKING,
        LEFT_STUNNED,
        RIGHT_IDLE,
        RIGHT_WALKING,
        RIGHT_JUMPING,
        RIGHT_FALLING,
        RIGHT_BLOCKING,
        RIGHT_STUNNED,
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
        // footStepsSf.push_back(loadSoundEffect(SOUND_EFFECT_FOOT_STEPS_0_PATH));
        // footStepsSf.push_back(loadSoundEffect(SOUND_EFFECT_FOOT_STEPS_1_PATH));
        // footStepsSf.push_back(loadSoundEffect(SOUND_EFFECT_FOOT_STEPS_2_PATH));
        // footStepsSf.push_back(loadSoundEffect(SOUND_EFFECT_FOOT_STEPS_3_PATH));
        swordSwooshSf = loadSoundEffect(SOUND_EFFECT_SWORD_SWOOSH_PATH);
        hitSf = loadSoundEffect(SOUND_EFFECT_HIT_PATH);
        blockSf = loadSoundEffect(SOUND_EFFECT_BLOCK_PATH);
        parrySf = loadSoundEffect(SOUND_EFFECT_PARRY_PATH);

        ichi::datatypes::Hitbox hb(ichi::datatypes::Point(10, 10), 70, 10, false);
        if (!facingRight)
            hb.setX(384 - 70 - 10);

        ichi::graphics::Sprite s(hb, ichi::graphics::Sprite::Layer::UICOMPONENT, PROGRESS_BAR_PATH);
        ichi::graphics::Sprite colorGreen(hb, ichi::graphics::Sprite::Layer::UICOMPONENT, COLOR_GREEN_PATH);
        healthBar = std::make_unique<ichi::uicomponents::ProgressBar>(hb, s, colorGreen, !facingRight);

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
    bool isBlocking() const { return blocking; }

    void setPosition(ichi::datatypes::Point pt);

    bool addWin() { return ++wins == 3; }

    void checkForHit(Character &);

    void takeDamage(float dmg, ichi::datatypes::Vector2D force);
    float getHp() const { return hp; }
    void reset();
    void shutDown() override
    {
        if (swordSwooshSf)
        {
            auto rawPtr = swordSwooshSf.release();
            swordSwooshSf.get_deleter()(rawPtr);
        }
        if (blockSf)
        {
            auto rawPtr = blockSf.release();
            blockSf.get_deleter()(rawPtr);
        }
        if (hitSf)
        {
            auto rawPtr = hitSf.release();
            hitSf.get_deleter()(rawPtr);
        }
        if (parrySf)
        {
            auto rawPtr = parrySf.release();
            parrySf.get_deleter()(rawPtr);
        }
        /*std::vector<std::unique_ptr<Mix_Chunk, MixChunkDeleter>> footStepsSf;
std::unique_ptr<Mix_Chunk, MixChunkDeleter> swordSwooshSf;
std::unique_ptr<Mix_Chunk, MixChunkDeleter> hitSf;
std::unique_ptr<Mix_Chunk, MixChunkDeleter> blockSf;
std::unique_ptr<Mix_Chunk, MixChunkDeleter> parrySf;*/
    }
    inline static const float MAX_HP = 100;

private:
    const std::string COLOR_GREEN_PATH = constants::gResPath + "images/UIComponents/colorGreen.png";
    const std::string PROGRESS_BAR_PATH = constants::gResPath + "images/UIComponents/ProgressBar.png";

    const std::string WIN_PATH = constants::gResPath + "images/UIComponents/Win.png";
    const std::string EMPTY_WIN_PATH = constants::gResPath + "images/UIComponents/EmptyWin.png";

    const float MAX_SPEED = 2.f;
    const float acceleration = 0.3f;
    const float friction = 0.5f;
    const float jumpVelocity = -6.0f;
    const float gravity = 0.37f;

    const float BLOCK_REDUCE = 1 - 0.8f;
    const int parryFrameWindow = 50;
    int framesblocking = 0;

    ichi::datatypes::Point facingRightDiff{32, 10};
    ichi::datatypes::Point facingLeftDiff{100, 10};

    float hp = MAX_HP;
    int wins = 0;

    bool facingRight;
    bool grounded = false;
    bool blocking = false;
    bool stunned = false;

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

    const std::string SOUND_EFFECT_FOOT_STEPS_0_PATH = constants::gResPath + "sounds/footSteps0.wav";
    const std::string SOUND_EFFECT_FOOT_STEPS_1_PATH = constants::gResPath + "sounds/footSteps1.wav";
    const std::string SOUND_EFFECT_FOOT_STEPS_2_PATH = constants::gResPath + "sounds/footSteps2.wav";
    const std::string SOUND_EFFECT_FOOT_STEPS_3_PATH = constants::gResPath + "sounds/footSteps3.wav";
    const std::string SOUND_EFFECT_PARRY_PATH = constants::gResPath + "sounds/parry.wav";
    const std::string SOUND_EFFECT_BLOCK_PATH = constants::gResPath + "sounds/block.wav";
    const std::string SOUND_EFFECT_HIT_PATH = constants::gResPath + "sounds/hit.wav";
    const std::string SOUND_EFFECT_SWORD_SWOOSH_PATH = constants::gResPath + "sounds/swordSwoosh.wav";

    // std::vector<std::unique_ptr<Mix_Chunk, MixChunkDeleter>> footStepsSf;
    std::unique_ptr<Mix_Chunk, MixChunkDeleter> swordSwooshSf;
    std::unique_ptr<Mix_Chunk, MixChunkDeleter> hitSf;
    std::unique_ptr<Mix_Chunk, MixChunkDeleter> blockSf;
    std::unique_ptr<Mix_Chunk, MixChunkDeleter> parrySf;

    std::unique_ptr<Mix_Chunk, MixChunkDeleter> loadSoundEffect(const std::string &path)
    {
        Mix_Chunk *chunk = Mix_LoadWAV(path.c_str());
        if (!chunk)
        {
            ICHI_ERROR("Could not load sound effect: {}", SDL_GetError());
            return nullptr;
        }
        return std::unique_ptr<Mix_Chunk, MixChunkDeleter>(chunk);
    }
};
#endif