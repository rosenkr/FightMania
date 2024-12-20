#ifndef ENGINE_H
#define ENGINE_H

#define FPS 60

#include <SDL2/SDL.h>
#include "Ichi/Core/window.h"
#include "Ichi/Managers/logManager.h"

namespace ichi::core
{
    class Engine
    {
    public:
        // Singleton instance
        static Engine *getInstance() { return instance = (instance != nullptr) ? instance : new Engine(); }
        SDL_Renderer *getRenderer() const { return window.getRenderer(); }
        void quit() { isRunning = false; }
        void run();
        bool init();
        void shutdown();

    private:
        Window window;
        ichi::managers::LogManager logManager;
        bool isRunning = true;

        static Engine *instance;

        Engine() = default;
        ~Engine() = default;
    };
}
#endif