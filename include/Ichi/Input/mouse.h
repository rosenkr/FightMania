#ifndef MOUSE_H
#define MOUSE_H

#include <array>

namespace ichi::input
{
    class Mouse
    {

    public:
        // Adapted from SDL - see SDL_BUTTON_LEFT
        enum class MouseButton
        {
            FIRST = 1,
            LEFT = FIRST,
            MIDDLE = 2,
            RIGHT = 3,
            X1 = 4,
            X2 = 5,
            LAST = 5

        };

        static void init();
        static void update();

        static bool buttonIsDown(MouseButton button);
        static bool buttonIsPressed(MouseButton button);
        static bool buttonIsReleased(MouseButton button);

        inline static int getX() { return x; }
        inline static int getY() { return y; }

    private:
        constexpr static const int ButtonCount = 5; // SDL supports up to 5 mouse buttons - see SDL_BUTTON_LEFT

        static int x;
        static int y;
        static int lastX;
        static int lastY;

        static std::array<bool, ButtonCount> buttons;
        static std::array<bool, ButtonCount> lastButtons;

        Mouse() = default;
        ~Mouse() = default;
    };
} // namespace ichi::input

#endif