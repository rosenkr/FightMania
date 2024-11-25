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
        /*ICHI_INFO("Left: {} \t Right: {}\t Middle: {} \t X1: {} \t X2: {}",
                  input::Mouse::buttonIsDown(input::Mouse::MouseButton::LEFT),
                  input::Mouse::buttonIsDown(input::Mouse::MouseButton::RIGHT),
                  input::Mouse::buttonIsDown(input::Mouse::MouseButton::MIDDLE),
                  input::Mouse::buttonIsDown(input::Mouse::MouseButton::X1),
                  input::Mouse::buttonIsDown(input::Mouse::MouseButton::X2));*/
        ICHI_INFO("W: {} \t A: {}\t S: {} \t D: {} \t SPACE: {}",
                  input::Keyboard::keyIsDown(input::Keyboard::Key::ICHIKEY_W),
                  input::Keyboard::keyIsDown(input::Keyboard::Key::ICHIKEY_A),
                  input::Keyboard::keyIsDown(input::Keyboard::Key::ICHIKEY_S),
                  input::Keyboard::keyIsDown(input::Keyboard::Key::ICHIKEY_D),
                  input::Keyboard::keyIsDown(input::Keyboard::Key::ICHIKEY_SPACE));
        // SceneManager.draw
    }

    void Window::update()
    {
        input::Mouse::update();
        input::Keyboard::update();
        // SceneManager.update
    }

} // namespace ichi::cores