#include "Implementation/match.h"

#include "Ichi/Scene/sceneManager.h"
#include "Implementation/cutsceneHandler.h"

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

    /*if (blueCharacter.get()->getHp() <= 0)
    {

        if (redCharacter.get()->etHp() == Character::MAX_HP)
            CutsceneHandler::addCutscene(perfect, perfectSf);
        else
            CutsceneHandler::addCutscene(KO, KOSf);

        if (redCharacter.get()->addWin())
        {
            CutsceneHandler::addCutscene(redWins, redWinsSf);
            end = true;
            return;
        }
        return;
    }

    if (redCharacter.get()->getHp() <= 0)
    {

        if (blueCharacter.get()->getHp() == Character::MAX_HP)
            CutsceneHandler::addCutscene(perfect, perfectSf);
        else
            CutsceneHandler::addCutscene(KO, KOSf);

        if (blueCharacter.get()->addWin())
        {
            CutsceneHandler::addCutscene(blueWins, blueWinsSf);
            end = true;
            return;
        }
        return;
    }*/

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