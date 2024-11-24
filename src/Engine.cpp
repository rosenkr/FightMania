#include "Engine.h"
#include "TextureManager.h"

namespace ichi {
    Engine* Engine::instance = nullptr;

    // TODO: add logging success/failure checks on renderer/window with spdlog, change to bool return type for use by run()?
    void Engine::init() {
        SDL_Init(SDL_INIT_EVERYTHING);
        window = SDL_CreateWindow("Fighters", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
        renderer = SDL_CreateRenderer(window, -1, 0);
        isRunning = true;
    }

    void Engine::shutdown() {
        TextureManager::shutdown();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    // TODO: add run impl
    void run() { }
}
