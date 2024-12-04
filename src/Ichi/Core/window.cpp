#include "Ichi/Core/window.h"

#include "Ichi/Core/engine.h"
#include "Ichi/Input/controllerHandler.h"
#include "Ichi/Input/mouse.h"
#include "Ichi/Input/keyboard.h"

namespace ichi::core
{

    Window::Window()
    {
        SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
    }

    Window::~Window()
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    void Window::handleEvents()
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_QUIT:
                Engine::getInstance()->quit();
                break;

            case SDL_CONTROLLERDEVICEADDED:
                input::ControllerHandler::onControllerConnect(e.cdevice);
                break;

            case SDL_CONTROLLERDEVICEREMOVED:
                input::ControllerHandler::onControllerDisconnect(e.cdevice);
                break;
            default:
                break;
            }
        }
        // update input handlers
    }

    void Window::draw()
    {
        SDL_RenderClear(Engine::getInstance()->getRenderer());

        // SceneManager.draw

        SDL_RenderPresent(Engine::getInstance()->getRenderer());
    }

    void Window::update()
    {
        input::Mouse::update();
        input::Keyboard::update();
        input::ControllerHandler::update();
        // SceneManager.update
    }

} // namespace ichi::core