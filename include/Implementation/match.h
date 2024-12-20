#ifndef MATCH_H
#define MATCH_H

#include "Ichi/Core/component.h"
#include "Ichi/Graphics/textureManager.h"
#include "Ichi/Audio/audioPlayer.h"
#include "Implementation/character.h"

using namespace ichi;

class Match : public ichi::core::Component
{
public:
    struct MixChunkDeleter
    {
        void operator()(Mix_Chunk *chunk) const
        {
            if (chunk)
                Mix_FreeChunk(chunk);
        }
    };
    Match(std::shared_ptr<Character> blue, std::shared_ptr<Character> red)
        : core::Component(datatypes::Hitbox(datatypes::Point(0, 0), 384, 224, false)), blueCharacter(std::move(blue)), redCharacter(std::move(red)),
          start(ichi::graphics::AnimatedSprite(hitbox, graphics::Sprite::Layer::FOREGROUND, START_PATH, startTime.size(), startTime)),
          KO(ichi::graphics::AnimatedSprite(hitbox, graphics::Sprite::Layer::FOREGROUND, {KO_PATH}, KOTime)),
          perfect(ichi::graphics::AnimatedSprite(hitbox, graphics::Sprite::Layer::FOREGROUND, {PERFECT_PATH}, perfectTime)),
          blueWins(ichi::graphics::AnimatedSprite(hitbox, graphics::Sprite::Layer::FOREGROUND, {BLUE_WINS_PATH}, blueWinsTime)),
          redWins(ichi::graphics::AnimatedSprite(hitbox, graphics::Sprite::Layer::FOREGROUND, {RED_WINS_PATH}, redWinsTime))
    {
        startSet();
        timeStarted = SDL_GetTicks();

        startSf = loadSoundEffect(SOUND_EFFECT_START_PATH);
        KOSf = loadSoundEffect(SOUND_EFFECT_KO_PATH);
        perfectSf = loadSoundEffect(SOUND_EFFECT_PERFECT_PATH);
        blueWinsSf = loadSoundEffect(SOUND_EFFECT_BLUE_WINS_PATH);
        redWinsSf = loadSoundEffect(SOUND_EFFECT_RED_WINS_PATH);
    }

    void draw() const;
    void update();
    void startSet();
    void startSuddenDeath();

private:
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

    const std::string SOUND_EFFECT_START_PATH = "resources/sounds/ChestOpening.wav";
    const std::string SOUND_EFFECT_KO_PATH = "resources/sounds/ChestOpening.wav";
    const std::string SOUND_EFFECT_PERFECT_PATH = "resources/sounds/ChestOpening.wav";
    const std::string SOUND_EFFECT_BLUE_WINS_PATH = "resources/sounds/ChestOpening.wav";
    const std::string SOUND_EFFECT_RED_WINS_PATH = "resources/sounds/ChestOpening.wav";

    std::unique_ptr<Mix_Chunk, MixChunkDeleter> startSf;
    std::unique_ptr<Mix_Chunk, MixChunkDeleter> KOSf;
    std::unique_ptr<Mix_Chunk, MixChunkDeleter> perfectSf;
    std::unique_ptr<Mix_Chunk, MixChunkDeleter> blueWinsSf;
    std::unique_ptr<Mix_Chunk, MixChunkDeleter> redWinsSf;

    const std::string START_PATH = "resources/images/CutScenes/StartCutscene";
    const std::string KO_PATH = "resources/images/CutScenes/KO.png";
    const std::string PERFECT_PATH = "resources/images/CutScenes/Perfect.png";
    const std::string BLUE_WINS_PATH = "resources/images/CutScenes/BlueWins.png";
    const std::string RED_WINS_PATH = "resources/images/CutScenes/RedWins.png";

    std::map<int, Uint32> startTime = {{0, 1000}, {1, 1000}, {2, 1000}, {3, 500}};
    std::map<int, Uint32> KOTime = {{0, 1000}};
    std::map<int, Uint32> perfectTime = {{0, 1000}};
    std::map<int, Uint32> blueWinsTime = {{0, 1000}};
    std::map<int, Uint32> redWinsTime = {{0, 1000}};

    // in milli sec
    const Uint32 MAX_TIME = 300 * 1000;
    Uint32 timeStarted = 0;

    bool suddenDeathActive = false;
    bool end = false;

    std::shared_ptr<Character> blueCharacter;
    std::shared_ptr<Character> redCharacter;

    ichi::graphics::AnimatedSprite start;
    ichi::graphics::AnimatedSprite KO;
    ichi::graphics::AnimatedSprite perfect;
    ichi::graphics::AnimatedSprite blueWins;
    ichi::graphics::AnimatedSprite redWins;
};

#endif // MATCH_H
