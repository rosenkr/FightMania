#include "Implementation/profile.h"
#include "Implementation/profileHandler.h"

bool Profile::canTakeAction(Action a, int controller) const
{
    if (controller == -1 || !usingController)
    {
        for (auto pair : mouseButtons)
            if (pair.second == a && ichi::input::Mouse::buttonIsDown(pair.first))
                return true;
        for (auto pair : keyboardKeys)
            if (pair.second == a && ichi::input::Keyboard::keyIsDown(pair.first))
                return true;
        return false;
    }

    for (auto pair : controllerButtons)
        if (pair.second == a && ichi::input::ControllerHandler::buttonIsDown(controller, pair.first))
            return true;

    for (auto pair : joystick)
        if (pair.second == a && ichi::input::ControllerHandler::getJoystick(controller, pair.first) > 0)
            return true;

    if (a == Action::DOWN && ichi::input::ControllerHandler::getJoystick(controller, ichi::input::ControllerHandler::Joystick::LeftStickVertical) > 0)
        return true;
    if (a == Action::UP && ichi::input::ControllerHandler::getJoystick(controller, ichi::input::ControllerHandler::Joystick::LeftStickVertical) < 0)
        return true;
    if (a == Action::RIGHT && ichi::input::ControllerHandler::getJoystick(controller, ichi::input::ControllerHandler::Joystick::LeftStickHorizontal) > 0)
        return true;
    if (a == Action::LEFT && ichi::input::ControllerHandler::getJoystick(controller, ichi::input::ControllerHandler::Joystick::LeftStickHorizontal) < 0)
        return true;

    return false;
}

const std::vector<std::string> Profile::getKeybinds() const
{
    std::vector<std::string> actions;

    if (usingController)
    {
        actions.push_back("joystick");
        actions.push_back("joystick");
        actions.push_back("joystick");
        actions.push_back("joystick");
    }

    for (int i = static_cast<int>(Action::UP); i <= static_cast<int>(Action::END); i++)
    {
        for (auto c : controllerButtons)
            if (c.second == static_cast<Action>(i))
            {
                actions.push_back(ProfileHandler::getString(c.first));
                break;
            }

        for (auto c : keyboardKeys)
            if (c.second == static_cast<Action>(i))
            {
                actions.push_back(ProfileHandler::getString(c.first));
                break;
            }

        for (auto c : mouseButtons)
            if (c.second == static_cast<Action>(i))
            {
                actions.push_back(ProfileHandler::getString(c.first));
                break;
            }

        for (auto c : joystick)
            if (c.second == static_cast<Action>(i))
            {
                actions.push_back(ProfileHandler::getString(c.first));
                break;
            }
    }
    return actions;
}