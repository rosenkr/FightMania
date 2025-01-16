#include "Implementation/match.h"

#include "Ichi/Scene/sceneManager.h"
#include "Implementation/cutsceneHandler.h"

Match::Match(std::shared_ptr<Character> blue, std::shared_ptr<Character> red, TTF_Font *font)
    : core::Component(datatypes::Hitbox(datatypes::Point(0, 0), 384, 224, false)), blueCharacter(std::move(blue)), redCharacter(std::move(red)),
      fight(ichi::graphics::AnimatedSprite(hitbox, graphics::Sprite::Layer::FOREGROUND, {FIGHT_PATH}, fightTime)),
      round1(ichi::graphics::AnimatedSprite(hitbox, graphics::Sprite::Layer::FOREGROUND, {ROUND_1_PATH}, roundTime)),
      round2(ichi::graphics::AnimatedSprite(hitbox, graphics::Sprite::Layer::FOREGROUND, {ROUND_2_PATH}, roundTime)),
      round3(ichi::graphics::AnimatedSprite(hitbox, graphics::Sprite::Layer::FOREGROUND, {ROUND_3_PATH}, roundTime)),
      round4(ichi::graphics::AnimatedSprite(hitbox, graphics::Sprite::Layer::FOREGROUND, {ROUND_4_PATH}, roundTime)),
      round5(ichi::graphics::AnimatedSprite(hitbox, graphics::Sprite::Layer::FOREGROUND, {ROUND_5_PATH}, roundTime)),
      KO(ichi::graphics::AnimatedSprite(hitbox, graphics::Sprite::Layer::FOREGROUND, {KO_PATH}, KOTime)),
      perfect(ichi::graphics::AnimatedSprite(hitbox, graphics::Sprite::Layer::FOREGROUND, {PERFECT_PATH}, perfectTime)),
      blueWins(ichi::graphics::AnimatedSprite(hitbox, graphics::Sprite::Layer::FOREGROUND, {BLUE_WINS_PATH}, blueWinsTime)),
      redWins(ichi::graphics::AnimatedSprite(hitbox, graphics::Sprite::Layer::FOREGROUND, {RED_WINS_PATH}, redWinsTime))
{

    fightSf = loadSoundEffect(SOUND_EFFECT_FIGHT_PATH);
    round1Sf = loadSoundEffect(SOUND_EFFECT_ROUND_1_PATH);
    round2Sf = loadSoundEffect(SOUND_EFFECT_ROUND_2_PATH);
    round3Sf = loadSoundEffect(SOUND_EFFECT_ROUND_3_PATH);
    round4Sf = loadSoundEffect(SOUND_EFFECT_ROUND_4_PATH);
    round5Sf = loadSoundEffect(SOUND_EFFECT_ROUND_5_PATH);
    KOSf = loadSoundEffect(SOUND_EFFECT_KO_PATH);
    perfectSf = loadSoundEffect(SOUND_EFFECT_PERFECT_PATH);
    blueWinsSf = loadSoundEffect(SOUND_EFFECT_BLUE_WINS_PATH);
    redWinsSf = loadSoundEffect(SOUND_EFFECT_RED_WINS_PATH);

    startSet();

    time = std::make_unique<uicomponents::Label>(datatypes::Point(192, 10), "100", font, SDL_Color{255, 255, 0, 255});
}

void Match::draw() const
{
    time.get()->draw();
    blueCharacter.get()->draw();
    redCharacter.get()->draw();
    CutsceneHandler::draw();
}

void Match::update()
{
    if (CutsceneHandler::isPlaying())
    {
        CutsceneHandler::update();
        return;
    }

    if (timeLastUpdated == 0)
        timeLastUpdated = SDL_GetTicks() - 166;

    if (!suddenDeathActive)
    {
        matchTime += SDL_GetTicks() - timeLastUpdated;
        time.get()->updateText(std::to_string((MAX_TIME - matchTime) / 1000));

        timeLastUpdated = SDL_GetTicks();
    }
    else
        time.get()->updateText("OVERTIME!");

    if (!suddenDeathActive && matchTime > MAX_TIME)
    {
        suddenDeathActive = true;
        startSuddenDeath();
        return;
    }

    if (end)
    {
        scene::sceneManager::getActiveScene()->removeComponent(this);
        scene::sceneManager::setActiveScene(1); // local play selection
        return;
    }

    blueCharacter.get()->checkForHit(*redCharacter.get());
    redCharacter.get()->checkForHit(*blueCharacter.get());

    if (blueCharacter.get()->getHitbox().getX() < redCharacter.get()->getHitbox().getX())
    {
        blueCharacter.get()->setDirection(true);
        redCharacter.get()->setDirection(false);
    }
    else
    {
        blueCharacter.get()->setDirection(false);
        redCharacter.get()->setDirection(true);
    }

    if (blueCharacter.get()->getHp() <= 0)
    {
        round++;
        CutsceneHandler::addCutscene(KO, KOSf.get());

        if (redCharacter.get()->getHp() == Character::MAX_HP)
            CutsceneHandler::addCutscene(perfect, perfectSf.get());

        if (redCharacter.get()->addWin())
        {
            CutsceneHandler::addCutscene(redWins, redWinsSf.get());
            end = true;
        }
        else
            startSet();
        return;
    }

    if (redCharacter.get()->getHp() <= 0)
    {
        round++;
        CutsceneHandler::addCutscene(KO, KOSf.get());

        if (blueCharacter.get()->getHp() == Character::MAX_HP)
            CutsceneHandler::addCutscene(perfect, perfectSf.get());

        if (blueCharacter.get()->addWin())
        {
            CutsceneHandler::addCutscene(blueWins, blueWinsSf.get());
            end = true;
        }
        else
            startSet();
        return;
    }

    blueCharacter.get()->update();
    redCharacter.get()->update();
}

void Match::startSuddenDeath()
{
    blueCharacter.get()->setPosition(datatypes::Point(50, 50));
    redCharacter.get()->setPosition(datatypes::Point(300, 50));
    blueCharacter.get()->takeDamage(blueCharacter.get()->getHp() - 1, datatypes::Vector2D(0, 0)); // sets the hp to 1
    redCharacter.get()->takeDamage(redCharacter.get()->getHp() - 1, datatypes::Vector2D(0, 0));
    CutsceneHandler::addCutscene(fight, fightSf.get());
}

void Match::startSet()
{
    round = 1;
    matchTime = 0;
    timeLastUpdated = 0;
    suddenDeathActive = false;
    blueCharacter.get()->setPosition(datatypes::Point(50, 50));
    redCharacter.get()->setPosition(datatypes::Point(300, 50));
    blueCharacter.get()->reset();
    redCharacter.get()->reset();
    switch (round)
    {
    case 1:
        CutsceneHandler::addCutscene(round1, round1Sf.get());
        break;
    case 2:
        CutsceneHandler::addCutscene(round2, round2Sf.get());
        break;
    case 3:
        CutsceneHandler::addCutscene(round3, round3Sf.get());
        break;
    case 4:
        CutsceneHandler::addCutscene(round4, round4Sf.get());
        break;
    case 5:
        CutsceneHandler::addCutscene(round5, round5Sf.get());
        break;

    default:
        break;
    }
    CutsceneHandler::addCutscene(fight, fightSf.get());
}