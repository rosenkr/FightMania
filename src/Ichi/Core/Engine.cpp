#include "Ichi/Core/engine.h"

#include "Ichi/log.h"
#include "Ichi/Input/mouse.h"
#include "Ichi/Input/keyboard.h"
#include "Ichi/Input/controllerHandler.h"
#include "Ichi/Audio/audioPlayer.h"
#include "Ichi/Graphics/textureManager.h"

#include "SDL2/SDL_ttf.h"

namespace ichi::core
{
    // singleton
    Engine *Engine::instance = nullptr;

    bool Engine::init()
    {
        logManager.init();

        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            ICHI_ERROR("Error initializing SDL {}", SDL_GetError());
            return false;
        }

        SDL_version version;
        SDL_VERSION(&version);
        ICHI_INFO("SDL {}.{}.{}", (int32_t)version.major, (int32_t)version.minor, (int32_t)version.patch);

        if (TTF_Init() != 0)
        {
            ICHI_ERROR("Error initializing TTF {}", SDL_GetError());
            return false;
        }

        // init std::rand
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        // init managers
        ichi::input::Mouse::init();
        ichi::input::Keyboard::init();
        ichi::audio::AudioPlayer::init(2);

        isRunning = true;

        return true;
    }

    void Engine::run()
    {
        while (isRunning)
        {
            Uint32 frameStart = SDL_GetTicks();

            window.handleEvents();
            window.update();
            window.draw();

            Uint32 frameTime = SDL_GetTicks() - frameStart;
            if (1000 / FPS > frameTime)
                SDL_Delay((1000 / FPS) - frameTime);
        }

        shutdown();
    }

    void Engine::shutdown()
    {
        ICHI_INFO("Ichi-Engine got shutdown");

        isRunning = false;

        // shutdown Everything exept logmanager
        ichi::input::ControllerHandler::shutdown();
        ichi::audio::AudioPlayer::shutdown();

        SDL_Quit();

        logManager.shutdown();
    }

} // namespace ichi::core
