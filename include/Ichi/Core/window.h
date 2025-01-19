#ifndef WINDOW_H
#define WINDOW_H

#include "SDL2/SDL.h"

#define WINDOW_WIDTH 384
#define WINDOW_HEIGHT 224
#define WINDOW_NAME "Fight-Mania"

namespace ichi::core
{
    class Window
    {
    public:
        Window() = default;
        ~Window() = default;

        void init();
        void handleEvents();
        void draw();
        void update();
        void shutDown();

        SDL_Renderer *getRenderer() const { return renderer; }


    private:
        const int SCALE = 3;
        SDL_Window *window = nullptr;
        SDL_Renderer *renderer = nullptr;
    };

} // namespace ichi::core

#endif