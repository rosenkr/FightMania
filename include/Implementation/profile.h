#include "Ichi/Input/controllerHandler.h"
#include "Ichi/Input/mouse.h"
#include "Ichi/Input/keyboard.h"

#include <string>
#include <map>
#include <stack>

class Profile
{
public:
    // Move enum to character
    enum class Action
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        LIGHT_ATTACK,
        HEAVY_ATTACK,
        JUMP,
        BLOCK,
    };

    Profile(std::string name, std::map<ichi::input::ControllerHandler::ControllerButton, Action> cbtns, std::map<ichi::input::ControllerHandler::Joystick, Action> joystick)
        : name(name), controllerButtons(cbtns), joystick(joystick), usingController(true) {}

    Profile(std::string name, std::map<ichi::input::Mouse::MouseButton, Action> mbtns, std::map<ichi::input::Keyboard::Key, Action> keys)
        : name(name), mouseButtons(mbtns), keyboardKeys(keys), usingController(false) {}

    ~Profile() {}

    std::string getName() const { return name; }

    std::stack<Action> getActions(int controller);

private:
    std::string name;
    std::map<ichi::input::ControllerHandler::ControllerButton, Action> controllerButtons;
    std::map<ichi::input::ControllerHandler::Joystick, Action> joystick;
    std::map<ichi::input::Mouse::MouseButton, Action> mouseButtons;
    std::map<ichi::input::Keyboard::Key, Action> keyboardKeys;
    bool usingController;
};