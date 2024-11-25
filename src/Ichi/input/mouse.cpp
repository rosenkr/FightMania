#include "Ichi/Input/mouse.h"
#include "SDL2/SDL.h"
#include "Ichi/log.h"
#include <algorithm>

namespace ichi::input
{
    int Mouse::x = 0;
    int Mouse::lastX = 0;
    int Mouse::y = 0;
    int Mouse::lastY = 0;

    std::array<bool, Mouse::ButtonCount> Mouse::buttons;
    std::array<bool, Mouse::ButtonCount> Mouse::lastButtons;

    void Mouse::init()
    {
        std::fill(buttons.begin(), buttons.end(), false);
        std::fill(lastButtons.begin(), lastButtons.end(), false);
    }

    void Mouse::update()
    {
        lastX = x;
        lastY = y;
        lastButtons = buttons;

        Uint32 state = SDL_GetMouseState(&x, &y);
        for (int i = 0; i <= Mouse::ButtonCount; i++)
        {
            buttons[i] = state & SDL_BUTTON(i + 1);
        }
    }

    bool Mouse::buttonIsDown(MouseButton button)
    {
        return buttons[static_cast<int>(button) - 1];
    }

    bool Mouse::buttonIsPressed(MouseButton button)
    {
        return buttons[static_cast<int>(button) - 1] && !lastButtons[static_cast<int>(button) - 1];
    }

    bool Mouse::buttonIsReleased(MouseButton button)
    {
        return !buttons[static_cast<int>(button) - 1] && lastButtons[static_cast<int>(button) - 1];
    }

} // namespace ichi::input
