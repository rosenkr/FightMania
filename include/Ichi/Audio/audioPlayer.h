#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include "SDL2/SDL_mixer.h"
#include "Ichi/log.h"

#include <vector>

namespace ichi::audio
{
    class AudioPlayer
    {
    public:
        static void init(int channels);
        static void shutdown() { Mix_Quit(); }
        static void setVolume(float f) { Mix_Volume(-1, f * MIX_MAX_VOLUME); } // Max volume is 128
        static void play(Mix_Chunk *);
        static void play(const std::vector<Mix_Chunk *> &);
        static void play(Mix_Music *);

    private:
        AudioPlayer() = default;
        ~AudioPlayer() = default;
    };
} // namespace ichi::audio

#endif