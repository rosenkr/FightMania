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
        Window();
        ~Window();

        void handleEvents();
        void draw();
        void update();

    private:
        SDL_Window *window;
    };

} // namespace ichi::core

#endif