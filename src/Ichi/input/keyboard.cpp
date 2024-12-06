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
        std::copy(keys.begin(), keys.end(), lastKeys.begin());

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

    const std::map<Keyboard::Key, std::string> Keyboard::capsStringRepresentation = {
        {Key::ICHIKEY_A, "A"},
        {Key::ICHIKEY_B, "B"},
        {Key::ICHIKEY_C, "C"},
        {Key::ICHIKEY_D, "D"},
        {Key::ICHIKEY_E, "E"},
        {Key::ICHIKEY_F, "F"},
        {Key::ICHIKEY_G, "G"},
        {Key::ICHIKEY_H, "H"},
        {Key::ICHIKEY_I, "I"},
        {Key::ICHIKEY_J, "J"},
        {Key::ICHIKEY_K, "K"},
        {Key::ICHIKEY_L, "L"},
        {Key::ICHIKEY_M, "M"},
        {Key::ICHIKEY_N, "N"},
        {Key::ICHIKEY_O, "O"},
        {Key::ICHIKEY_P, "P"},
        {Key::ICHIKEY_Q, "Q"},
        {Key::ICHIKEY_R, "R"},
        {Key::ICHIKEY_S, "S"},
        {Key::ICHIKEY_T, "T"},
        {Key::ICHIKEY_U, "U"},
        {Key::ICHIKEY_V, "V"},
        {Key::ICHIKEY_W, "W"},
        {Key::ICHIKEY_X, "X"},
        {Key::ICHIKEY_Y, "Y"},
        {Key::ICHIKEY_Z, "Z"},
        {Key::ICHIKEY_1, "!"},
        {Key::ICHIKEY_2, "\""},
        {Key::ICHIKEY_3, "#"},
        {Key::ICHIKEY_4, "¤"},
        {Key::ICHIKEY_5, "%"},
        {Key::ICHIKEY_6, "&"},
        {Key::ICHIKEY_7, "/"},
        {Key::ICHIKEY_8, "("},
        {Key::ICHIKEY_9, ")"},
        {Key::ICHIKEY_0, "="},
        {Key::ICHIKEY_RETURN, ""},
        {Key::ICHIKEY_ESCAPE, ""},
        {Key::ICHIKEY_BACKSPACE, ""},
        {Key::ICHIKEY_TAB, "\t"},
        {Key::ICHIKEY_SPACE, " "},
        {Key::ICHIKEY_MINUS, "-"},
        {Key::ICHIKEY_EQUALS, "="},
        {Key::ICHIKEY_LEFTBRACKET, "["},
        {Key::ICHIKEY_RIGHTBRACKET, "]"},
        {Key::ICHIKEY_BACKSLASH, "\\"},
        {Key::ICHIKEY_NONUSHASH, "¨"},
        {Key::ICHIKEY_SEMICOLON, ";"},
        {Key::ICHIKEY_APOSTROPHE, "'"},
        {Key::ICHIKEY_GRAVE, "`"},
        {Key::ICHIKEY_COMMA, ","},
        {Key::ICHIKEY_PERIOD, "."},
        {Key::ICHIKEY_SLASH, "/"}};

    const std::map<Keyboard::Key, std::string> Keyboard::lowerStringRepresentation = {
        {Key::ICHIKEY_A, "a"},
        {Key::ICHIKEY_B, "b"},
        {Key::ICHIKEY_C, "c"},
        {Key::ICHIKEY_D, "d"},
        {Key::ICHIKEY_E, "e"},
        {Key::ICHIKEY_F, "f"},
        {Key::ICHIKEY_G, "g"},
        {Key::ICHIKEY_H, "h"},
        {Key::ICHIKEY_I, "i"},
        {Key::ICHIKEY_J, "j"},
        {Key::ICHIKEY_K, "k"},
        {Key::ICHIKEY_L, "l"},
        {Key::ICHIKEY_M, "m"},
        {Key::ICHIKEY_N, "n"},
        {Key::ICHIKEY_O, "o"},
        {Key::ICHIKEY_P, "p"},
        {Key::ICHIKEY_Q, "q"},
        {Key::ICHIKEY_R, "r"},
        {Key::ICHIKEY_S, "s"},
        {Key::ICHIKEY_T, "t"},
        {Key::ICHIKEY_U, "u"},
        {Key::ICHIKEY_V, "v"},
        {Key::ICHIKEY_W, "w"},
        {Key::ICHIKEY_X, "x"},
        {Key::ICHIKEY_Y, "y"},
        {Key::ICHIKEY_Z, "z"},
        {Key::ICHIKEY_1, "1"},
        {Key::ICHIKEY_2, "2"},
        {Key::ICHIKEY_3, "3"},
        {Key::ICHIKEY_4, "4"},
        {Key::ICHIKEY_5, "5"},
        {Key::ICHIKEY_6, "6"},
        {Key::ICHIKEY_7, "7"},
        {Key::ICHIKEY_8, "8"},
        {Key::ICHIKEY_9, "9"},
        {Key::ICHIKEY_0, "0"},
        {Key::ICHIKEY_RETURN, ""},
        {Key::ICHIKEY_ESCAPE, ""},
        {Key::ICHIKEY_BACKSPACE, ""},
        {Key::ICHIKEY_TAB, "\t"},
        {Key::ICHIKEY_SPACE, " "},
        {Key::ICHIKEY_MINUS, "-"},
        {Key::ICHIKEY_EQUALS, "="},
        {Key::ICHIKEY_LEFTBRACKET, "["},
        {Key::ICHIKEY_RIGHTBRACKET, "]"},
        {Key::ICHIKEY_BACKSLASH, "\\"},
        {Key::ICHIKEY_NONUSHASH, "¨"},
        {Key::ICHIKEY_SEMICOLON, ";"},
        {Key::ICHIKEY_APOSTROPHE, "'"},
        {Key::ICHIKEY_GRAVE, "`"},
        {Key::ICHIKEY_COMMA, ","},
        {Key::ICHIKEY_PERIOD, "."},
        {Key::ICHIKEY_SLASH, "/"}};

} // namespace ichi::input
