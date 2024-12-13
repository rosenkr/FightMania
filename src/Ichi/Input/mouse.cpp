#include "Ichi/Input/mouse.h"
#include "Ichi/Core/engine.h"
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
        std::copy(buttons.begin(), buttons.end(), lastButtons.begin());

        Uint32 state = SDL_GetMouseState(&x, &y);

        // Setting x and y to logical points
        float fx, fy;
        SDL_RenderWindowToLogical(core::Engine::getInstance()->getRenderer(), x, y, &fx, &fy);

        x = static_cast<int>(fx);
        y = static_cast<int>(fy);

        for (int i = 0; i < Mouse::ButtonCount; i++)
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
