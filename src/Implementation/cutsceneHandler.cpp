#include "Implementation/cutsceneHandler.h"

std::queue<std::pair<ichi::graphics::AnimatedSprite, Mix_Chunk *>> CutsceneHandler::queue = {};

void CutsceneHandler::update()
{
    if (queue.empty())
        return;

    if (queue.front().first.hasCompleatedALap())
    {
        queue.pop();
        return;
    }

    queue.front().first.update();

    if (!queue.front().second)
        return;

    ichi::audio::AudioPlayer::play(queue.front().second);
    queue.front().second = nullptr;
}

void CutsceneHandler::draw()
{
    if (queue.empty())
        return;
    auto as = queue.front().first;
    as.draw();
}

void CutsceneHandler::addCutscene(ichi::graphics::AnimatedSprite as, Mix_Chunk *chunk)
{
    queue.push(std::pair<ichi::graphics::AnimatedSprite, Mix_Chunk *>(as, chunk));
}