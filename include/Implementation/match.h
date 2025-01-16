#ifndef MATCH_H
#define MATCH_H

#include "Ichi/Core/component.h"
#include "Ichi/Graphics/textureManager.h"
#include "Ichi/Audio/audioPlayer.h"
#include "Ichi/UIComponents/label.h"
#include "Implementation/character.h"

#include "Constants.h"

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
    Match(std::shared_ptr<Character> blue, std::shared_ptr<Character> red, TTF_Font *font);

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

    const std::string SOUND_EFFECT_FIGHT_PATH = constants::gResPath + "sounds/fight.wav";
    const std::string SOUND_EFFECT_KO_PATH = constants::gResPath + "sounds/KO.wav";
    const std::string SOUND_EFFECT_PERFECT_PATH = constants::gResPath + "sounds/perfect.wav";
    const std::string SOUND_EFFECT_BLUE_WINS_PATH = constants::gResPath + "sounds/blueWins.wav";
    const std::string SOUND_EFFECT_RED_WINS_PATH = constants::gResPath + "sounds/redWins.wav";

    const std::string SOUND_EFFECT_ROUND_1_PATH = constants::gResPath + "sounds/roundOne.wav";
    const std::string SOUND_EFFECT_ROUND_2_PATH = constants::gResPath + "sounds/roundTwo.wav";
    const std::string SOUND_EFFECT_ROUND_3_PATH = constants::gResPath + "sounds/roundThree.wav";
    const std::string SOUND_EFFECT_ROUND_4_PATH = constants::gResPath + "sounds/roundFour.wav";
    const std::string SOUND_EFFECT_ROUND_5_PATH = constants::gResPath + "sounds/roundFive.wav";

    std::unique_ptr<Mix_Chunk, MixChunkDeleter> fightSf;
    std::unique_ptr<Mix_Chunk, MixChunkDeleter> round1Sf;
    std::unique_ptr<Mix_Chunk, MixChunkDeleter> round2Sf;
    std::unique_ptr<Mix_Chunk, MixChunkDeleter> round3Sf;
    std::unique_ptr<Mix_Chunk, MixChunkDeleter> round4Sf;
    std::unique_ptr<Mix_Chunk, MixChunkDeleter> round5Sf;
    std::unique_ptr<Mix_Chunk, MixChunkDeleter> KOSf;
    std::unique_ptr<Mix_Chunk, MixChunkDeleter> perfectSf;
    std::unique_ptr<Mix_Chunk, MixChunkDeleter> blueWinsSf;
    std::unique_ptr<Mix_Chunk, MixChunkDeleter> redWinsSf;

    const std::string FIGHT_PATH = constants::gResPath + "images/CutScenes/Fight.png";

    const std::string ROUND_1_PATH = constants::gResPath + "images/CutScenes/RoundOne.png";
    const std::string ROUND_2_PATH = constants::gResPath + "images/CutScenes/RoundTwo.png";
    const std::string ROUND_3_PATH = constants::gResPath + "images/CutScenes/RoundThree.png";
    const std::string ROUND_4_PATH = constants::gResPath + "images/CutScenes/RoundFour.png";
    const std::string ROUND_5_PATH = constants::gResPath + "images/CutScenes/RoundFive.png";

    const std::string KO_PATH = constants::gResPath + "images/CutScenes/KO.png";
    const std::string PERFECT_PATH = constants::gResPath + "images/CutScenes/Perfect.png";
    const std::string BLUE_WINS_PATH = constants::gResPath + "images/CutScenes/BlueWins.png";
    const std::string RED_WINS_PATH = constants::gResPath + "images/CutScenes/RedWins.png";

    std::map<int, Uint32> fightTime = {{0, 2000}};
    std::map<int, Uint32> roundTime = {{0, 2500}};
    std::map<int, Uint32> KOTime = {{0, 3000}};
    std::map<int, Uint32> perfectTime = {{0, 2000}};
    std::map<int, Uint32> blueWinsTime = {{0, 4000}};
    std::map<int, Uint32> redWinsTime = {{0, 4000}};

    // in milli sec
    const Uint32 MAX_TIME = 100 * 1000;
    Uint32 matchTime = 0;
    Uint32 timeLastUpdated = 0;

    bool suddenDeathActive = false;
    bool end = false;

    int round = 1;

    std::shared_ptr<Character> blueCharacter;
    std::shared_ptr<Character> redCharacter;

    ichi::graphics::AnimatedSprite fight;
    ichi::graphics::AnimatedSprite round1;
    ichi::graphics::AnimatedSprite round2;
    ichi::graphics::AnimatedSprite round3;
    ichi::graphics::AnimatedSprite round4;
    ichi::graphics::AnimatedSprite round5;
    ichi::graphics::AnimatedSprite KO;
    ichi::graphics::AnimatedSprite perfect;
    ichi::graphics::AnimatedSprite blueWins;
    ichi::graphics::AnimatedSprite redWins;

    std::unique_ptr<ichi::uicomponents::Label> time;
};

#endif // MATCH_H
