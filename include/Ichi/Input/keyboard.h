#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <array>

namespace ichi::input
{
    class Keyboard
    {

    public:
        // Adapted from SDL - see SDL_BUTTON_LEFT
        enum class Key
        {
            ICHIKEY_FIRST = 4,
            ICHIKEY_A = ICHIKEY_FIRST,
            ICHIKEY_B = 5,
            ICHIKEY_C = 6,
            ICHIKEY_D = 7,
            ICHIKEY_E = 8,
            ICHIKEY_F = 9,
            ICHIKEY_G = 10,
            ICHIKEY_H = 11,
            ICHIKEY_I = 12,
            ICHIKEY_J = 13,
            ICHIKEY_K = 14,
            ICHIKEY_L = 15,
            ICHIKEY_M = 16,
            ICHIKEY_N = 17,
            ICHIKEY_O = 18,
            ICHIKEY_P = 19,
            ICHIKEY_Q = 20,
            ICHIKEY_R = 21,
            ICHIKEY_S = 22,
            ICHIKEY_T = 23,
            ICHIKEY_U = 24,
            ICHIKEY_V = 25,
            ICHIKEY_W = 26,
            ICHIKEY_X = 27,
            ICHIKEY_Y = 28,
            ICHIKEY_Z = 29,
            ICHIKEY_1 = 30,
            ICHIKEY_2 = 31,
            ICHIKEY_3 = 32,
            ICHIKEY_4 = 33,
            ICHIKEY_5 = 34,
            ICHIKEY_6 = 35,
            ICHIKEY_7 = 36,
            ICHIKEY_8 = 37,
            ICHIKEY_9 = 38,
            ICHIKEY_0 = 39,
            ICHIKEY_RETURN = 40,
            ICHIKEY_ESCAPE = 41,
            ICHIKEY_BACKSPACE = 42,
            ICHIKEY_TAB = 43,
            ICHIKEY_SPACE = 44,
            ICHIKEY_MINUS = 45,
            ICHIKEY_EQUALS = 46,
            ICHIKEY_LEFTBRACKET = 47,
            ICHIKEY_RIGHTBRACKET = 48,
            ICHIKEY_BACKSLASH = 49,
            ICHIKEY_NONUSHASH = 50,
            ICHIKEY_SEMICOLON = 51,
            ICHIKEY_APOSTROPHE = 52,
            ICHIKEY_GRAVE = 53,
            ICHIKEY_COMMA = 54,
            ICHIKEY_PERIOD = 55,
            ICHIKEY_SLASH = 56,
            ICHIKEY_CAPSLOCK = 57,
            ICHIKEY_F1 = 58,
            ICHIKEY_F2 = 59,
            ICHIKEY_F3 = 60,
            ICHIKEY_F4 = 61,
            ICHIKEY_F5 = 62,
            ICHIKEY_F6 = 63,
            ICHIKEY_F7 = 64,
            ICHIKEY_F8 = 65,
            ICHIKEY_F9 = 66,
            ICHIKEY_F10 = 67,
            ICHIKEY_F11 = 68,
            ICHIKEY_F12 = 69,
            ICHIKEY_PRINTSCREEN = 70,
            ICHIKEY_SCROLLLOCK = 71,
            ICHIKEY_PAUSE = 72,
            ICHIKEY_INSERT = 73,
            ICHIKEY_HOME = 74,
            ICHIKEY_PAGEUP = 75,
            ICHIKEY_DELETE = 76,
            ICHIKEY_END = 77,
            ICHIKEY_PAGEDOWN = 78,
            ICHIKEY_RIGHT = 79,
            ICHIKEY_LEFT = 80,
            ICHIKEY_DOWN = 81,
            ICHIKEY_UP = 82,
            ICHIKEY_NUMLOCKCLEAR = 83,
            ICHIKEY_KP_DIVIDE = 84,
            ICHIKEY_KP_MULTIPLY = 85,
            ICHIKEY_KP_MINUS = 86,
            ICHIKEY_KP_PLUS = 87,
            ICHIKEY_KP_ENTER = 88,
            ICHIKEY_KP_1 = 89,
            ICHIKEY_KP_2 = 90,
            ICHIKEY_KP_3 = 91,
            ICHIKEY_KP_4 = 92,
            ICHIKEY_KP_5 = 93,
            ICHIKEY_KP_6 = 94,
            ICHIKEY_KP_7 = 95,
            ICHIKEY_KP_8 = 96,
            ICHIKEY_KP_9 = 97,
            ICHIKEY_KP_0 = 98,
            ICHIKEY_KP_PERIOD = 99,
            ICHIKEY_NONUSBACKSLASH = 100,
            ICHIKEY_APPLICATION = 101,
            ICHIKEY_POWER = 102,
            ICHIKEY_KP_EQUALS = 103,
            ICHIKEY_F13 = 104,
            ICHIKEY_F14 = 105,
            ICHIKEY_F15 = 106,
            ICHIKEY_F16 = 107,
            ICHIKEY_F17 = 108,
            ICHIKEY_F18 = 109,
            ICHIKEY_F19 = 110,
            ICHIKEY_F20 = 111,
            ICHIKEY_F21 = 112,
            ICHIKEY_F22 = 113,
            ICHIKEY_F23 = 114,
            ICHIKEY_F24 = 115,
            ICHIKEY_EXECUTE = 116,
            ICHIKEY_HELP = 117,
            ICHIKEY_MENU = 118,
            ICHIKEY_SELECT = 119,
            ICHIKEY_STOP = 120,
            ICHIKEY_AGAIN = 121,
            ICHIKEY_UNDO = 122,
            ICHIKEY_CUT = 123,
            ICHIKEY_COPY = 124,
            ICHIKEY_PASTE = 125,
            ICHIKEY_FIND = 126,
            ICHIKEY_MUTE = 127,
            ICHIKEY_VOLUMEUP = 128,
            ICHIKEY_VOLUMEDOWN = 129,
            ICHIKEY_KP_COMMA = 133,
            ICHIKEY_KP_EQUALSAS400 = 134,
            ICHIKEY_INTERNATIONAL1 = 135,
            ICHIKEY_INTERNATIONAL2 = 136,
            ICHIKEY_INTERNATIONAL3 = 137,
            ICHIKEY_INTERNATIONAL4 = 138,
            ICHIKEY_INTERNATIONAL5 = 139,
            ICHIKEY_INTERNATIONAL6 = 140,
            ICHIKEY_INTERNATIONAL7 = 141,
            ICHIKEY_INTERNATIONAL8 = 142,
            ICHIKEY_INTERNATIONAL9 = 143,
            ICHIKEY_LANG1 = 144,
            ICHIKEY_LANG2 = 145,
            ICHIKEY_LANG3 = 146,
            ICHIKEY_LANG4 = 147,
            ICHIKEY_LANG5 = 148,
            ICHIKEY_LANG6 = 149,
            ICHIKEY_LANG7 = 150,
            ICHIKEY_LANG8 = 151,
            ICHIKEY_LANG9 = 152,
            ICHIKEY_ALTERASE = 153,
            ICHIKEY_SYSREQ = 154,
            ICHIKEY_CANCEL = 155,
            ICHIKEY_CLEAR = 156,
            ICHIKEY_PRIOR = 157,
            ICHIKEY_RETURN2 = 158,
            ICHIKEY_SEPARATOR = 159,
            ICHIKEY_OUT = 160,
            ICHIKEY_OPER = 161,
            ICHIKEY_CLEARAGAIN = 162,
            ICHIKEY_CRSEL = 163,
            ICHIKEY_EXSEL = 164,
            ICHIKEY_KP_00 = 176,
            ICHIKEY_KP_000 = 177,
            ICHIKEY_THOUSANDSSEPARATOR = 178,
            ICHIKEY_DECIMALSEPARATOR = 179,
            ICHIKEY_CURRENCYUNIT = 180,
            ICHIKEY_CURRENCYSUBUNIT = 181,
            ICHIKEY_KP_LEFTPAREN = 182,
            ICHIKEY_KP_RIGHTPAREN = 183,
            ICHIKEY_KP_LEFTBRACE = 184,
            ICHIKEY_KP_RIGHTBRACE = 185,
            ICHIKEY_KP_TAB = 186,
            ICHIKEY_KP_BACKSPACE = 187,
            ICHIKEY_KP_A = 188,
            ICHIKEY_KP_B = 189,
            ICHIKEY_KP_C = 190,
            ICHIKEY_KP_D = 191,
            ICHIKEY_KP_E = 192,
            ICHIKEY_KP_F = 193,
            ICHIKEY_KP_XOR = 194,
            ICHIKEY_KP_POWER = 195,
            ICHIKEY_KP_PERCENT = 196,
            ICHIKEY_KP_LESS = 197,
            ICHIKEY_KP_GREATER = 198,
            ICHIKEY_KP_AMPERSAND = 199,
            ICHIKEY_KP_DBLAMPERSAND = 200,
            ICHIKEY_KP_VERTICALBAR = 201,
            ICHIKEY_KP_DBLVERTICALBAR = 202,
            ICHIKEY_KP_COLON = 203,
            ICHIKEY_KP_HASH = 204,
            ICHIKEY_KP_SPACE = 205,
            ICHIKEY_KP_AT = 206,
            ICHIKEY_KP_EXCLAM = 207,
            ICHIKEY_KP_MEMSTORE = 208,
            ICHIKEY_KP_MEMRECALL = 209,
            ICHIKEY_KP_MEMCLEAR = 210,
            ICHIKEY_KP_MEMADD = 211,
            ICHIKEY_KP_MEMSUBTRACT = 212,
            ICHIKEY_KP_MEMMULTIPLY = 213,
            ICHIKEY_KP_MEMDIVIDE = 214,
            ICHIKEY_KP_PLUSMINUS = 215,
            ICHIKEY_KP_CLEAR = 216,
            ICHIKEY_KP_CLEARENTRY = 217,
            ICHIKEY_KP_BINARY = 218,
            ICHIKEY_KP_OCTAL = 219,
            ICHIKEY_KP_DECIMAL = 220,
            ICHIKEY_KP_HEXADECIMAL = 221,
            ICHIKEY_LCTRL = 224,
            ICHIKEY_LSHIFT = 225,
            ICHIKEY_LALT = 226,
            ICHIKEY_LGUI = 227,
            ICHIKEY_RCTRL = 228,
            ICHIKEY_RSHIFT = 229,
            ICHIKEY_RALT = 230,
            ICHIKEY_RGUI = 231,
            ICHIKEY_MODE = 257,
            ICHIKEY_AUDIONEXT = 258,
            ICHIKEY_AUDIOPREV = 259,
            ICHIKEY_AUDIOSTOP = 260,
            ICHIKEY_AUDIOPLAY = 261,
            ICHIKEY_AUDIOMUTE = 262,
            ICHIKEY_MEDIASELECT = 263,
            ICHIKEY_WWW = 264,
            ICHIKEY_MAIL = 265,
            ICHIKEY_CALCULATOR = 266,
            ICHIKEY_COMPUTER = 267,
            ICHIKEY_AC_SEARCH = 268,
            ICHIKEY_AC_HOME = 269,
            ICHIKEY_AC_BACK = 270,
            ICHIKEY_AC_FORWARD = 271,
            ICHIKEY_AC_STOP = 272,
            ICHIKEY_AC_REFRESH = 273,
            ICHIKEY_AC_BOOKMARKS = 274,
            ICHIKEY_BRIGHTNESSDOWN = 275,
            ICHIKEY_BRIGHTNESSUP = 276,
            ICHIKEY_DISPLAYSWITCH = 277,
            ICHIKEY_KBDILLUMTOGGLE = 278,
            ICHIKEY_KBDILLUMDOWN = 279,
            ICHIKEY_KBDILLUMUP = 280,
            ICHIKEY_EJECT = 281,
            ICHIKEY_SLEEP = 282,
            ICHIKEY_APP1 = 283,
            ICHIKEY_APP2 = 284,
            ICHIKEY_AUDIOREWIND = 285,
            ICHIKEY_AUDIOFASTFORWARD = 286,
            LAST = ICHIKEY_AUDIOFASTFORWARD
        };

        static void init();
        static void update();

        static bool keyIsDown(Key key);
        static bool keyIsPressed(Key key);
        static bool keyIsReleased(Key key);

    private:
        constexpr static const int KeyCount = 287; // SDL supports up to index 286 - see SDL_NUM_SCANCODES

        static std::array<bool, KeyCount> keys;
        static std::array<bool, KeyCount> lastKeys;

        Keyboard() = default;
        ~Keyboard() = default;
    };

} // namespace ichi::input

#endif // KEYBOARD_H