#include "Ichi/Audio/audioPlayer.h"
#include "SDL2/SDL.h"

namespace ichi::audio
{
    void AudioPlayer::init(int channels)
    {
        if (Mix_Init(MIX_INIT_MP3) == 0)
        {
            ICHI_ERROR("SDL_mixer could not initialize MP3 support! SDL_mixer Error: {}", Mix_GetError());
            return;
        }

        if (SDL_Init(SDL_INIT_AUDIO) < 0)
        {
            ICHI_ERROR("SDL could not initialize audio subsystem! SDL Error: {}", SDL_GetError());
            return;
        }

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, channels, 2048) < 0)
        {
            ICHI_ERROR("SDL_mixer could not initialize! SDL_mixer Error: {}", Mix_GetError());
            return;
        }
        ICHI_INFO("SDL_mixer got initialized")
        setVolume(80);
    }

    void AudioPlayer::play(Mix_Chunk *chunk)
    {
        if (chunk != nullptr)
            Mix_PlayChannel(-1, chunk, 0);
    }

    void AudioPlayer::play(const std::vector<Mix_Chunk *> &soundEffects)
    {
        if (soundEffects.empty())
            return;

        int i = std::rand() % soundEffects.size();
        play(soundEffects.at(i));
    }

    void AudioPlayer::play(Mix_Music *m)
    {
        if (!Mix_PlayingMusic())
            Mix_PlayMusic(m, 0);
    }

} // namespace ichi::audio
