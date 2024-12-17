#ifndef MATCH_H
#define MATCH_H

#include "Ichi/Core/component.h"
#include "Ichi/Graphics/textureManager.h"
#include "Ichi/Audio/audioPlayer.h"

using namespace ichi;

class Match : public ichi::core::Component
{
public:
    Match(/*Character blue, Character red*/)
        : core::Component(datatypes::Hitbox(datatypes::Point(0, 0), 384, 224, false)),
          start(ichi::graphics::AnimatedSprite(hitbox, graphics::Sprite::Layer::FOREGROUND, START_PATH, startTime.size(), startTime)),
          KO(ichi::graphics::AnimatedSprite(hitbox, graphics::Sprite::Layer::FOREGROUND, KO_PATH, KOTime.size(), KOTime)),
          perfect(ichi::graphics::AnimatedSprite(hitbox, graphics::Sprite::Layer::FOREGROUND, START_PATH, perfectTime.size(), perfectTime)),
          blueWins(ichi::graphics::AnimatedSprite(hitbox, graphics::Sprite::Layer::FOREGROUND, START_PATH, blueWinsTime.size(), blueWinsTime)),
          redWins(ichi::graphics::AnimatedSprite(hitbox, graphics::Sprite::Layer::FOREGROUND, START_PATH, redWinsTime.size(), redWinsTime))
    /* , blueCharacter(std::move(blue)), redCharacter(std::move(red))*/
    {
        startSet();
        timeStarted = SDL_GetTicks();

        startSf = Mix_LoadWAV(SOUND_EFFECT_START_PATH);
        KOSf = Mix_LoadWAV(SOUND_EFFECT_KO_PATH);
        perfectSf = Mix_LoadWAV(SOUND_EFFECT_PERFECT_PATH);
        blueWinsSf = Mix_LoadWAV(SOUND_EFFECT_BLUE_WINS_PATH);
        redWinsSf = Mix_LoadWAV(SOUND_EFFECT_RED_WINS_PATH);

        if (!startSf || !KOSf || !perfectSf || !blueWinsSf || !redWinsSf)
            ICHI_ERROR("Could not init all sound effects: {}", SDL_GetError());
    }

    ~Match()
    {
        Mix_FreeChunk(startSf);
        Mix_FreeChunk(KOSf);
        Mix_FreeChunk(perfectSf);
        Mix_FreeChunk(blueWinsSf);
        Mix_FreeChunk(redWinsSf);

        startSf = nullptr;
        KOSf = nullptr;
        perfectSf = nullptr;
        blueWinsSf = nullptr;
        redWinsSf = nullptr;
    };

    void draw() const;
    void update();
    void startSet();
    void startSuddenDeath();

private:
    const char *SOUND_EFFECT_START_PATH = "";
    const char *SOUND_EFFECT_KO_PATH = "";
    const char *SOUND_EFFECT_PERFECT_PATH = "";
    const char *SOUND_EFFECT_BLUE_WINS_PATH = "";
    const char *SOUND_EFFECT_RED_WINS_PATH = "";

    Mix_Chunk *startSf;
    Mix_Chunk *KOSf;
    Mix_Chunk *perfectSf;
    Mix_Chunk *blueWinsSf;
    Mix_Chunk *redWinsSf;

    const std::string START_PATH = "";
    const std::string KO_PATH = "";
    const std::string PERFECT_PATH = "";
    const std::string BLUE_WINS_PATH = "";
    const std::string RED_WINS_PATH = "";

    std::map<int, Uint32> startTime = {{1, 1000}};
    std::map<int, Uint32> KOTime = {{1, 1000}};
    std::map<int, Uint32> perfectTime = {{1, 1000}};
    std::map<int, Uint32> blueWinsTime = {{1, 1000}};
    std::map<int, Uint32> redWinsTime = {{1, 1000}};

    // in milli sec
    const Uint32 MAX_TIME = 300 * 1000;
    Uint32 timeStarted = 0;

    bool suddenDeathActive = false;
    bool end = false;

    // Character blueCharacter;
    // Character redCharacter;

    ichi::graphics::AnimatedSprite start;
    ichi::graphics::AnimatedSprite KO;
    ichi::graphics::AnimatedSprite perfect;
    ichi::graphics::AnimatedSprite blueWins;
    ichi::graphics::AnimatedSprite redWins;
};

#endif // MATCH_H
