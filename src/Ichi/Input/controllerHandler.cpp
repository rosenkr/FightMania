#include "Ichi/Input/controllerHandler.h"
#include "Ichi/log.h"

#include <algorithm>

#include "SDL2/SDL_events.h"
#include "SDL2/SDL_gamecontroller.h"

namespace ichi::input
{
    std::unordered_map<int, std::unique_ptr<ControllerHandler::Controller>> ControllerHandler::controllers;

    void ControllerHandler::update()
    {
        for (auto it = controllers.begin(); it != controllers.end(); it++)
        {
            Controller *c = it->second.get();

            if (!c || !(c->gameController))
            {
                ICHI_ERROR("Invalid game controller in availableJoysticks map");
                continue;
            }

            std::copy(c->buttons.begin(), c->buttons.end(), c->lastButtons.begin());
            std::copy(c->joystick.begin(), c->joystick.end(), c->lastJoystick.begin());

            for (unsigned int i = 0; i < static_cast<int>(ControllerButton::Count); i++)
                c->buttons[i] = SDL_GameControllerGetButton(c->gameController, static_cast<SDL_GameControllerButton>(i));

            for (unsigned int i = 0; i < static_cast<int>(Joystick::Count); i++)
            {
                auto axis = SDL_GameControllerGetAxis(c->gameController, static_cast<SDL_GameControllerAxis>(i));
                c->joystick[i] = std::clamp(axis / joystickRange, -1.f, 1.f);
            }
        }
    }
    void ControllerHandler::shutdown()
    {
        for (auto it = controllers.begin(); it != controllers.end();)
        {
            Controller *c = it->second.get();
            SDL_GameControllerClose(c->gameController);
            it = controllers.erase(it);
        }
    }

    bool ControllerHandler::isControllerAvailable(int controllerId)
    {
        return controllers.count(controllerId) > 0;
    }

    std::vector<int> ControllerHandler::getActiveControllerIDs()
    {
        std::vector<int> ids;

        for (auto it = controllers.begin(); it != controllers.end(); ++it)
            ids.push_back(it->first);

        return ids;
    }

    bool ControllerHandler::buttonIsDown(int controllerId, ControllerButton button)
    {
        auto it = controllers.find(controllerId);
        if (it != controllers.end())
        {
            return it->second->buttons[static_cast<int>(button)];
        }

        ICHI_ERROR("Controller with id {} is not available!", controllerId);
        return false;
    }

    bool ControllerHandler::buttonIsPressed(int controllerId, ControllerButton button)
    {
        auto it = controllers.find(controllerId);
        if (it != controllers.end())
        {
            return it->second->buttons[static_cast<int>(button)] && !it->second->lastButtons[static_cast<int>(button)];
        }

        ICHI_ERROR("Controller with id {} is not available!", controllerId);
        return false;
    }

    bool ControllerHandler::buttonIsReleased(int controllerId, ControllerButton button)
    {
        auto it = controllers.find(controllerId);
        if (it != controllers.end())
        {
            return !it->second->buttons[static_cast<int>(button)] && it->second->lastButtons[static_cast<int>(button)];
        }

        ICHI_ERROR("Controller with id {} is not available!", controllerId);
        return false;
    }

    float ControllerHandler::getJoystick(int controllerId, Joystick joystick)
    {
        auto it = controllers.find(controllerId);
        if (it != controllers.end())
        {
            float val = it->second->joystick[static_cast<int>(joystick)];
            return abs(val) > deadZone ? val : 0.f;
        }

        ICHI_ERROR("Controller with id {} is not available!", controllerId);
        return 0.f;
    }

    void ControllerHandler::onControllerConnect(SDL_ControllerDeviceEvent &e)
    {
        int deviceIndex = e.which;

        if (!SDL_IsGameController(deviceIndex))
        {
            ICHI_ERROR("Game controller with Device Index {} is not a SDL_GameController", deviceIndex);
            return;
        }

        auto c = std::make_unique<Controller>();
        c->gameController = SDL_GameControllerOpen(deviceIndex);

        if (c->gameController)
        {
            c->index = deviceIndex;

            std::fill(c->buttons.begin(), c->buttons.end(), false);
            std::fill(c->lastButtons.begin(), c->lastButtons.end(), false);
            std::fill(c->joystick.begin(), c->joystick.end(), 0.f);
            std::fill(c->lastJoystick.begin(), c->lastJoystick.end(), 0.f);

            int mapIndex = getNextFreeIndex();

            if (mapIndex == -1)
            {
                ICHI_ERROR("Could not find controller on onConect event")
                return;
            }

            ICHI_TRACE("Joystick connected: mapIndex({}), deviceIndex({})", mapIndex, deviceIndex);

            controllers[mapIndex] = std::move(c);
            return;
        }

        ICHI_ERROR("Error opening game controller with Device Index {}: {}", deviceIndex, SDL_GetError());
    }

    void ControllerHandler::onControllerDisconnect(SDL_ControllerDeviceEvent &e)
    {
        int deviceIndex = e.which;
        for (auto it = controllers.begin(); it != controllers.end(); it++)
        {
            Controller *c = it->second.get();
            if (c->index == deviceIndex)
            {
                ICHI_TRACE("Joystick disconnected: {}", deviceIndex);
                SDL_GameControllerClose(c->gameController);
                controllers.erase(it);
                break;
            }
        }
    }

    bool ControllerHandler::anyControllerIsPressing(ControllerButton button)
    {
        for (auto it = controllers.begin(); it != controllers.end(); it++)
            if (it->second.get() && buttonIsPressed(it->first, button))
                return true;
        return false;
    }

    // negative numbers is left and positive is right
    float ControllerHandler::getTotalLeftStickX()
    {
        float total = 0;
        for (auto it = controllers.begin(); it != controllers.end(); it++)
            if (it->second.get())
                total += getJoystick(it->first, Joystick::LeftStickHorizontal);

        return total;
    }

    // negative numbers are up and positive is down
    float ControllerHandler::getTotalLeftStickY()
    {
        float total = 0;
        for (auto it = controllers.begin(); it != controllers.end(); it++)
            if (it->second.get())
                total += getJoystick(it->first, Joystick::LeftStickVertical);

        return total;
    }

    int ControllerHandler::getNextFreeIndex()
    {
        int ret = -1;

        for (int i = 0; i < SDL_NumJoysticks(); i++)
        {
            if (controllers.count(i) == 0)
            {
                ret = i;
                break;
            }
        }

        return ret;
    }

} // namespace ichi::input
