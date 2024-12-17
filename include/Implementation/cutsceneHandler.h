#ifndef CUTSCENE_HANDLER_H
#define CUTSCENE_HANDLER_H

#include "Ichi/Graphics/animatedSprite.h"
#include "Ichi/Audio/audioPlayer.h"

#include <queue>
#include <utility>

class CutsceneHandler
{
public:
    static void update();
    static void draw();
    static void addCutscene(ichi::graphics::AnimatedSprite as, Mix_Chunk *chunk = nullptr);
    static bool isPlaying() { return queue.size() > 0; }

private:
    static std::queue<std::pair<ichi::graphics::AnimatedSprite, Mix_Chunk *>> queue;
    CutsceneHandler() = delete;
    ~CutsceneHandler() = delete;
};

#endif // CUTSCENE_HANDLER_H
