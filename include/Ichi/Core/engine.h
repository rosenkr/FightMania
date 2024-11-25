#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include "Ichi/log.h"
#include "Ichi/Managers/logManager.h"
#include "Ichi/Core/window.h"

namespace ichi::core
{
    class Engine
    {
    public:
        // Singleton instance
        static Engine *getInstance() { return instance = (instance != nullptr) ? instance : new Engine(); }
        SDL_Renderer *getRenderer() const { return renderer; };
        void quit() { isRunning = false; }
        void run();

    private:
        Window window;
        SDL_Renderer *renderer;
        ichi::managers::LogManager logManager;
        bool isRunning = true;

        static Engine *instance;

        bool init();
        void shutdown();

        Engine() = default;
        ~Engine() = default;
    };
}
#endif