#include "Ichi/Core/window.h"
#include "Ichi/Core/engine.h"
#include "Ichi/Input/controllerHandler.h"

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
        /*ICHI_TRACE("Left: {} \t Right: {}\t Middle: {} \t X1: {} \t X2: {}",
                  input::Mouse::buttonIsDown(input::Mouse::MouseButton::LEFT),
                  input::Mouse::buttonIsDown(input::Mouse::MouseButton::RIGHT),
                  input::Mouse::buttonIsDown(input::Mouse::MouseButton::MIDDLE),
                  input::Mouse::buttonIsDown(input::Mouse::MouseButton::X1),
                  input::Mouse::buttonIsDown(input::Mouse::MouseButton::X2));*/
        /*ICHI_TRACE("W: {} \t A: {}\t S: {} \t D: {} \t SPACE: {}",
                  input::Keyboard::keyIsDown(input::Keyboard::Key::ICHIKEY_W),
                  input::Keyboard::keyIsDown(input::Keyboard::Key::ICHIKEY_A),
                  input::Keyboard::keyIsDown(input::Keyboard::Key::ICHIKEY_S),
                  input::Keyboard::keyIsDown(input::Keyboard::Key::ICHIKEY_D),
                  input::Keyboard::keyIsDown(input::Keyboard::Key::ICHIKEY_SPACE));*/
        if (input::ControllerHandler::isControllerAvailable(0) && input::ControllerHandler::buttonIsDown(0, input::ControllerHandler::ControllerButton::Guide) != 0)
            ICHI_TRACE("Left stick x: {}\t y:{} Right stick x: {}\t y:{} \t A:{}\t B:{}\t X:{}\t Y:{}",
                       input::ControllerHandler::getJoystick(0, input::ControllerHandler::Joystick::LeftStickHorizontal),
                       input::ControllerHandler::getJoystick(0, input::ControllerHandler::Joystick::LeftStickVertical),
                       input::ControllerHandler::getJoystick(0, input::ControllerHandler::Joystick::RightStickHorizontal),
                       input::ControllerHandler::getJoystick(0, input::ControllerHandler::Joystick::RightStickVertical),
                       input::ControllerHandler::buttonIsDown(0, input::ControllerHandler::ControllerButton::A),
                       input::ControllerHandler::buttonIsDown(0, input::ControllerHandler::ControllerButton::B),
                       input::ControllerHandler::buttonIsDown(0, input::ControllerHandler::ControllerButton::X),
                       input::ControllerHandler::buttonIsDown(0, input::ControllerHandler::ControllerButton::Y));
        // SceneManager.draw
    }

    void Window::update()
    {
        input::Mouse::update();
        input::Keyboard::update();
        input::ControllerHandler::update();
        // SceneManager.update
    }

} // namespace ichi::cores