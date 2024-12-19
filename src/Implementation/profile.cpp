#include "Implementation/profile.h"
#include "Implementation/profileHandler.h"

std::vector<Profile::Action> Profile::getActions(int controller) const
{
    std::vector<Action> actions;

    if (usingController)
    {
        for (auto pair : controllerButtons)
            if (ichi::input::ControllerHandler::buttonIsDown(controller, pair.first))
                actions.push_back(pair.second);

        if (joystick.find(ichi::input::ControllerHandler::Joystick::LeftTrigger) != joystick.end() && ichi::input::ControllerHandler::getJoystick(controller, ichi::input::ControllerHandler::Joystick::LeftTrigger) > 0)
            actions.push_back(joystick.at(ichi::input::ControllerHandler::Joystick::LeftTrigger));

        if (joystick.find(ichi::input::ControllerHandler::Joystick::RightTrigger) != joystick.end() && ichi::input::ControllerHandler::getJoystick(controller, ichi::input::ControllerHandler::Joystick::RightTrigger) > 0)
            actions.push_back(joystick.at(ichi::input::ControllerHandler::Joystick::LeftTrigger));

        if (ichi::input::ControllerHandler::getJoystick(controller, ichi::input::ControllerHandler::Joystick::LeftStickVertical) > 0)
            actions.push_back(Action::DOWN);
        if (ichi::input::ControllerHandler::getJoystick(controller, ichi::input::ControllerHandler::Joystick::LeftStickVertical) < 0)
            actions.push_back(Action::DOWN);
        if (ichi::input::ControllerHandler::getJoystick(controller, ichi::input::ControllerHandler::Joystick::LeftStickHorizontal) > 0)
            actions.push_back(Action::RIGHT);
        if (ichi::input::ControllerHandler::getJoystick(controller, ichi::input::ControllerHandler::Joystick::LeftStickHorizontal) < 0)
            actions.push_back(Action::LEFT);

        return actions;
    }

    for (auto pair : keyboardKeys)
        if (ichi::input::Keyboard::keyIsDown(pair.first))
            actions.push_back(pair.second);

    for (auto pair : mouseButtons)
        if (ichi::input::Mouse::buttonIsDown(pair.first))
            actions.push_back(pair.second);

    return actions;
}

const std::vector<std::string> Profile::getKeybinds() const
{
    std::vector<std::string> actions;

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