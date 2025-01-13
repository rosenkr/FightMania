#include "Implementation/match.h"

#include "Ichi/Scene/sceneManager.h"
#include "Implementation/cutsceneHandler.h"

Match::Match(std::shared_ptr<Character> blue, std::shared_ptr<Character> red, TTF_Font *font)
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

    time = std::make_unique<uicomponents::Label>(datatypes::Point(192, 10), "test", font, SDL_Color{255, 255, 0, 255});
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
    time.get()->updateText(std::to_string((MAX_TIME - SDL_GetTicks() + timeStarted) / 1000));

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

        if (redCharacter.get()->getHp() == Character::MAX_HP)
            CutsceneHandler::addCutscene(perfect, perfectSf.get());
        else
            CutsceneHandler::addCutscene(KO, KOSf.get());

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

        if (blueCharacter.get()->getHp() == Character::MAX_HP)
            CutsceneHandler::addCutscene(perfect, perfectSf.get());
        else
            CutsceneHandler::addCutscene(KO, KOSf.get());

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
    blueCharacter.get()->takeDamage(blueCharacter.get()->getHp() - 1); // sets the hp to 1
    redCharacter.get()->takeDamage(redCharacter.get()->getHp() - 1);
    CutsceneHandler::addCutscene(start, startSf.get());
}

void Match::startSet()
{
    blueCharacter.get()->setPosition(datatypes::Point(50, 50));
    redCharacter.get()->setPosition(datatypes::Point(300, 50));
    blueCharacter.get()->resetHp();
    redCharacter.get()->resetHp();
    timeStarted = SDL_GetTicks();
    CutsceneHandler::addCutscene(start, startSf.get());
}