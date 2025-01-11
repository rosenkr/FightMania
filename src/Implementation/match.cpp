#include "Implementation/match.h"

#include "Ichi/Scene/sceneManager.h"
#include "Implementation/cutsceneHandler.h"

Match::Match(std::shared_ptr<Character> blue, std::shared_ptr<Character> red)
    : core::Component(datatypes::Hitbox(datatypes::Point(0, 0), 384, 224, false)), blueCharacter(std::move(blue)), redCharacter(std::move(red)),
      start(ichi::graphics::AnimatedSprite(hitbox, graphics::Sprite::Layer::FOREGROUND, START_PATH, startTime.size(), startTime)),
      KO(ichi::graphics::AnimatedSprite(hitbox, graphics::Sprite::Layer::FOREGROUND, {KO_PATH}, KOTime)),
      perfect(ichi::graphics::AnimatedSprite(hitbox, graphics::Sprite::Layer::FOREGROUND, {PERFECT_PATH}, perfectTime)),
      blueWins(ichi::graphics::AnimatedSprite(hitbox, graphics::Sprite::Layer::FOREGROUND, {BLUE_WINS_PATH}, blueWinsTime)),
      redWins(ichi::graphics::AnimatedSprite(hitbox, graphics::Sprite::Layer::FOREGROUND, {RED_WINS_PATH}, redWinsTime))
{

    startSf = loadSoundEffect(SOUND_EFFECT_START_PATH);
    KOSf = loadSoundEffect(SOUND_EFFECT_KO_PATH);
    perfectSf = loadSoundEffect(SOUND_EFFECT_PERFECT_PATH);
    blueWinsSf = loadSoundEffect(SOUND_EFFECT_BLUE_WINS_PATH);
    redWinsSf = loadSoundEffect(SOUND_EFFECT_RED_WINS_PATH);

    startSet();
    timeStarted = SDL_GetTicks();
}

void Match::draw() const
{
    blueCharacter.get()->draw();
    redCharacter.get()->draw();
    CutsceneHandler::draw();
}

void Match::update()
{
    if (!suddenDeathActive && SDL_GetTicks() - timeStarted > MAX_TIME)
    {
        suddenDeathActive = true;
        startSuddenDeath();
        return;
    }

    if (CutsceneHandler::isPlaying())
    {
        CutsceneHandler::update();
        return;
    }

    if (end)
    {
        scene::sceneManager::getActiveScene()->removeComponent(std::shared_ptr<core::Component>(this));
        scene::sceneManager::setActiveScene(1); // local play selection
        return;
    }

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

        if (redCharacter.get()->getHp() == Character::MAX_HP)
            CutsceneHandler::addCutscene(perfect, perfectSf.get());
        else
            CutsceneHandler::addCutscene(KO, KOSf.get());

        if (redCharacter.get()->addWin())
        {
            CutsceneHandler::addCutscene(redWins, redWinsSf.get());
            end = true;
            return;
        }
        return;
    }

    if (redCharacter.get()->getHp() <= 0)
    {

        if (blueCharacter.get()->getHp() == Character::MAX_HP)
            CutsceneHandler::addCutscene(perfect, perfectSf.get());
        else
            CutsceneHandler::addCutscene(KO, KOSf.get());

        if (blueCharacter.get()->addWin())
        {
            CutsceneHandler::addCutscene(blueWins, blueWinsSf.get());
            end = true;
            return;
        }
        return;
    }

    blueCharacter.get()->update();
    redCharacter.get()->update();
}

void Match::startSuddenDeath()
{
    // blueCharacter.setPos(datatypes::Point(50, 50));
    // redCharacter.setPos(datatypes::Point(300, 50));
    // blueCharacter.setHP(1);
    // redCharacter.setHP(1);
    CutsceneHandler::addCutscene(start, startSf.get());
}

void Match::startSet()
{
    // blueCharacter.setPos(datatypes::Point(50, 50));
    // redCharacter.setPos(datatypes::Point(300, 50));
    // blueCharacter.resetHP();
    // redCharacter.resetHP();
    CutsceneHandler::addCutscene(start, startSf.get());
}