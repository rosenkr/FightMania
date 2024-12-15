#include "Implementation/profile.h"

std::stack<Profile::Action> Profile::getActions(int controller)
{
    std::stack<Action> actions;

    if (usingController)
    {
        for (auto pair : controllerButtons)
            if (ichi::input::ControllerHandler::buttonIsDown(controller, pair.first))
                actions.push(pair.second);

        if (joystick.find(ichi::input::ControllerHandler::Joystick::LeftTrigger) != joystick.end() && ichi::input::ControllerHandler::getJoystick(controller, ichi::input::ControllerHandler::Joystick::LeftTrigger) > 0)
            actions.push(joystick[ichi::input::ControllerHandler::Joystick::LeftTrigger]);

        if (joystick.find(ichi::input::ControllerHandler::Joystick::RightTrigger) != joystick.end() && ichi::input::ControllerHandler::getJoystick(controller, ichi::input::ControllerHandler::Joystick::RightTrigger) > 0)
            actions.push(joystick[ichi::input::ControllerHandler::Joystick::RightTrigger]);

        if (ichi::input::ControllerHandler::getJoystick(controller, ichi::input::ControllerHandler::Joystick::LeftStickVertical) > 0)
            actions.push(Action::DOWN);
        if (ichi::input::ControllerHandler::getJoystick(controller, ichi::input::ControllerHandler::Joystick::LeftStickVertical) < 0)
            actions.push(Action::DOWN);
        if (ichi::input::ControllerHandler::getJoystick(controller, ichi::input::ControllerHandler::Joystick::LeftStickHorizontal) > 0)
            actions.push(Action::RIGHT);
        if (ichi::input::ControllerHandler::getJoystick(controller, ichi::input::ControllerHandler::Joystick::LeftStickHorizontal) < 0)
            actions.push(Action::LEFT);

        return actions;
    }

    for (auto pair : keyboardKeys)
        if (ichi::input::Keyboard::keyIsDown(pair.first))
            actions.push(pair.second);

    for (auto pair : mouseButtons)
        if (ichi::input::Mouse::buttonIsDown(pair.first))
            actions.push(pair.second);

    return actions;
}