#ifndef WINDOW_H
#define WINDOW_H

#include "SDL2/SDL.h"

#define WINDOW_WIDTH 384
#define WINDOW_HEIGHT 224
#define WINDOW_NAME "Fight-Mania"

// temp
#include "Ichi/Graphics/sprite.h"

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

        SDL_Renderer *getRenderer() const { return renderer; }

    private:
        SDL_Window *window;
        SDL_Renderer *renderer;

        // temp
        graphics::Sprite s = graphics::Sprite(Hitbox(Point(0, 0), WINDOW_WIDTH, WINDOW_HEIGHT, false), graphics::Sprite::Layer::BACKGROUND, "resources/images/Dojo.png");
    };

} // namespace ichi::core

#endif