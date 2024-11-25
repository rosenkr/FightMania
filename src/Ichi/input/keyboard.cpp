#include "Ichi/Input/keyboard.h"
#include <algorithm>
#include "SDL2/SDL_keyboard.h"

namespace ichi::input
{
    std::array<bool, Keyboard::KeyCount> Keyboard::keys;
    std::array<bool, Keyboard::KeyCount> Keyboard::lastKeys;

    void Keyboard::init()
    {
        std::fill(keys.begin(), keys.end(), false);
        std::fill(lastKeys.begin(), lastKeys.end(), false);
    }

    void Keyboard::update()
    {
        lastKeys = keys;
        const Uint8 *state = SDL_GetKeyboardState(nullptr);
        for (int i = static_cast<int>(Keyboard::Key::ICHIKEY_FIRST); i < KeyCount; i++)
            keys[i] = state[i];
    }

    bool Keyboard::keyIsDown(Key key)
    {
        return keys[static_cast<int>(key)];
    }

    bool Keyboard::keyIsPressed(Key key)
    {
        return keys[static_cast<int>(key)] && !lastKeys[static_cast<int>(key)];
    }

    bool Keyboard::keyIsReleased(Key key)
    {
        return !keys[static_cast<int>(key)] && lastKeys[static_cast<int>(key)];
    }

} // namespace ichi::input
