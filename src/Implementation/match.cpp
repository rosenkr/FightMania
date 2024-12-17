#include "Implementation/match.h"

#include "Ichi/Scene/sceneManager.h"
#include "Implementation/cutsceneHandler.h"

void Match::draw() const
{
    // blueCharacter.draw();
    // redCharacter.draw();
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
        scene::sceneManager::getActiveScene()->removeComponent(this);
        scene::sceneManager::setActiveScene(1); // local play selection
        return;
    }

    /*

    if(blueCharacter.getHp() <= 0){

        if (redCharacter.getHp() == Character::MAX_HP)
            CutsceneHandler::addCutscene(perfect, perfectSf);
        else
            CutsceneHandler::addCutscene(KO, KOSf);

        if (redCharacter.addWin()){
            CutsceneHandler::addCutscene(redWins, redWinsSf);
            end = true;
            return;
        }
        return;
    }

    if(redCharacter.getHp() <= 0){

        if (blueCharacter.getHp() == Character::MAX_HP)
            CutsceneHandler::addCutscene(perfect, perfectSf);
        else
            CutsceneHandler::addCutscene(KO, KOSf);

        if (blueCharacter.addWin()){
            CutsceneHandler::addCutscene(blueWins, blueWinsSf);
            end = true;
            return;
        }
        return;
    }

    blueCharacter.update();
    redCharacter.update();
    */
}

void Match::startSuddenDeath()
{
    // blueCharacter.setPos(datatypes::Point(50, 50));
    // redCharacter.setPos(datatypes::Point(300, 50));
    // blueCharacter.setHP(1);
    // redCharacter.setHP(1);
    CutsceneHandler::addCutscene(start, startSf);
}

void Match::startSet()
{
    // blueCharacter.setPos(datatypes::Point(50, 50));
    // redCharacter.setPos(datatypes::Point(300, 50));
    // blueCharacter.resetHP();
    // redCharacter.resetHP();
    CutsceneHandler::addCutscene(start, startSf);
}