#include "Ichi/engine.h"

// #include "TextureManager.h"

namespace Ichi::Core
{
    Engine *Engine::instance = nullptr;

    bool Engine::init()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            ICHI_ERROR("Error initializing SDL {}", SDL_GetError());
            return false;
        }

        SDL_version version;
        SDL_VERSION(&version);
        ICHI_INFO("SDL {}.{}.{}", (int32_t)version.major, (int32_t)version.minor, (int32_t)version.patch);

        // renderer = SDL_CreateRenderer(window, -1, 0);

        // init managers

        isRunning = true;
        return true;
    }

    void Engine::shutdown()
    {
        ICHI_INFO("Ichi-Engine got shutdown");

        isRunning = false;

        // shutdown Everything exept logmanager

        SDL_DestroyRenderer(renderer);

        SDL_Quit();

        logManager.shutdown();
    }

    void Engine::run()
    {
        logManager.init();

        if (!init())
        {
            shutdown();
            return;
        }

        while (isRunning)
        {
            // call to window
            break;
        }

        shutdown();
    }
} // namespace Ichi::Core
