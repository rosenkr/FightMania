#include "Ichi/Core/window.h"

#include "Ichi/Core/engine.h"
#include "Ichi/Input/controllerHandler.h"
#include "Ichi/Input/mouse.h"
#include "Ichi/Input/keyboard.h"
#include "Ichi/Scene/sceneManager.h"

namespace ichi::core
{

    Window::Window()
    {
        SDL_CreateWindowAndRenderer(WINDOW_WIDTH + SCALE, WINDOW_HEIGHT * SCALE, 0, &window, &renderer);
        SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
    }

    Window::~Window()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        renderer = nullptr;
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

        input::Mouse::update();
        input::Keyboard::update();
        input::ControllerHandler::update();
    }

    void Window::draw()
    {
        SDL_RenderClear(Engine::getInstance()->getRenderer());

        scene::sceneManager::draw();

        SDL_RenderPresent(Engine::getInstance()->getRenderer());
    }

    void Window::update()
    {
        scene::sceneManager::update();
    }

} // namespace ichi::core