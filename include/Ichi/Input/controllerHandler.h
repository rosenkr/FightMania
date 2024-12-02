#ifndef CONTROLLER_HANDLER_H
#define CONTROLLER_HANDLER_H

#include <array>
#include <unordered_map>
#include <memory>

struct SDL_ControllerDeviceEvent;
typedef struct _SDL_GameController SDL_GameController;

namespace ichi::input
{
    class ControllerHandler
    {
    public:
        // Adapted from SDL - see SDL_GameControllerAxis
        enum class Joystick
        {
            LeftStickHorizontal,
            LeftStickVertical,
            RightStickHorizontal,
            RightStickVertical,
            LeftTrigger,
            RightTrigger,
            Count
        };

        // Adapted from SDL - see SDL_GameControllerButton
        enum class ControllerButton
        {
            A,
            B,
            X,
            Y,
            Back,
            Guide, // home button on playstation controller
            Start,
            LS,
            RS,
            LB, // Left Bumper
            RB, // Right Bumper
            DPAD_Up,
            DPAD_Down,
            DPAD_Left,
            DPAD_Right,
            Count
        };

        static void update();
        static void shutdown();

        static bool isControllerAvailable(int controllerId);

        static bool buttonIsDown(int controllerId, ControllerButton button);
        static bool buttonIsPressed(int controllerId, ControllerButton button);
        static bool buttonIsReleased(int controllerId, ControllerButton button);

        static float getJoystick(int controllerId, Joystick joystick);

        static void onControllerConnect(SDL_ControllerDeviceEvent &e);
        static void onControllerDisconnect(SDL_ControllerDeviceEvent &e);

    private:
        struct Controller
        {
            int index = -1;
            SDL_GameController *gameController = nullptr;

            std::array<bool, (int)ControllerButton::Count> buttons;
            std::array<bool, (int)ControllerButton::Count> lastButtons;
            std::array<float, (int)Joystick::Count> joystick;
            std::array<float, (int)Joystick::Count> lastJoystick;
        };
        // SDL ranges joysticks from -32768 to 32767
        static constexpr float joystickRange = 32767.f;

        static constexpr float deadZone = 0.2f;

        static std::unordered_map<int, std::unique_ptr<Controller>> controllers;

        static int getNextFreeIndex();

        ControllerHandler() = default;
        ~ControllerHandler() = default;
    };

} // namespace ichi::input

#endif