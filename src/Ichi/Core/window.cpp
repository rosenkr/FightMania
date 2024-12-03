#include "Ichi/Core/window.h"
#include "Ichi/Core/engine.h"
#include "Ichi/Input/controllerHandler.h"

// temp
#include "Ichi/Graphics/sprite.h"
#include "Ichi/Graphics/animatedSprite.h"
#include "Ichi/Audio/audioPlayer.h"
#include "Ichi/UIComponents/label.h"

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

    // temp
    graphics::Sprite s = graphics::Sprite(datatypes::Hitbox(datatypes::Point(0, 0), WINDOW_WIDTH, WINDOW_HEIGHT, false), graphics::Sprite::Layer::BACKGROUND, "resources/images/Dojo.png");
    graphics::AnimatedSprite as = graphics::AnimatedSprite(
        datatypes::Hitbox(datatypes::Point(0, 0), 100, 120, false),
        graphics::Sprite::Layer::BACKGROUND,
        "resources/images/Robot animations/RobotWalk", 4,
        {{0, 166}, {1, 166}, {2, 166}, {3, 166}});

    void Window::draw()
    {
        SDL_RenderClear(Engine::getInstance()->getRenderer());

        s.draw();
        as.draw();

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

        auto f = TTF_OpenFont("resources/fonts/PRSTART.TTF", 20);
        uicomponents::Label lbl = uicomponents::Label(datatypes::Hitbox(datatypes::Point(0, 0), WINDOW_WIDTH, 50, false), "Fight - Mania", f, {255, 255, 255});

        lbl.draw();

        // SceneManager.draw

        SDL_RenderPresent(Engine::getInstance()->getRenderer());
    }

    void Window::update()
    {
        /*audio::AudioPlayer::play(Mix_LoadMUS("resources/music/UnderTale.wav"));

        if (input::Keyboard::keyIsDown(input::Keyboard::Key::ICHIKEY_W) || input::Keyboard::keyIsDown(input::Keyboard::Key::ICHIKEY_A) || input::Keyboard::keyIsDown(input::Keyboard::Key::ICHIKEY_S) || input::Keyboard::keyIsDown(input::Keyboard::Key::ICHIKEY_D))
        {
            audio::AudioPlayer::play({
                Mix_LoadWAV("resources/sounds/StoneStep1.wav"),
                Mix_LoadWAV("resources/sounds/StoneStep2.wav"),
                Mix_LoadWAV("resources/sounds/StoneStep3.wav"),
                Mix_LoadWAV("resources/sounds/StoneStep4.wav"),
            });
        }

        if (input::Keyboard::keyIsDown(input::Keyboard::Key::ICHIKEY_SPACE))
        {
            audio::AudioPlayer::play(Mix_LoadWAV("resources/sounds/ChestOpening.wav"));
        }*/

        as.update();
        input::Mouse::update();
        input::Keyboard::update();
        input::ControllerHandler::update();
        // SceneManager.update
    }

} // namespace ichi::core