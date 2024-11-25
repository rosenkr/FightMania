#include "Ichi/Core/window.h"
#include "Ichi/Core/engine.h"
namespace ichi::core
{
    Window::Window()
    {
        window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
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
                // input::Joystick::OnJoystickConnected(e.cdevice);
                break;

            case SDL_CONTROLLERDEVICEREMOVED:
                // input::Joystick::OnJoystickDisconnected(e.cdevice);
                break;
            default:
                break;
            }
        }
        // update input handlers
    }

    void Window::draw()
    {
        // SceneManager.draw
    }

    void Window::update()
    {
        // SceneManager.update
    }

} // namespace ichi::cores