#include "Implementation/profile.h"
#include "Ichi/Input/controllerHandler.h"
#include "Ichi/Input/mouse.h"
#include "Ichi/Input/keyboard.h"

#include <vector>
#include <map>

class ProfileHandler
{
public:
    static bool init();
    static void saveProfile(std::vector<std::string>, bool);
    static const Profile *getProfile(std::string name);
    static void removeProfile(std::string name);

private:
    static std::string PROFILE_PATH;

    static std::map<std::string, Profile> profiles;

    static bool updateVector();
    static void addToVector(std::vector<std::string>);
    static std::vector<std::string> split(const std::string &s, const std::string &delimiter);

    static std::map<std::string, ichi::input::ControllerHandler::Joystick> joystickStrings;
    static std::map<std::string, ichi::input::ControllerHandler::ControllerButton> controllerStrings;
    static std::map<std::string, ichi::input::Mouse::MouseButton> mouseStrings;
    static std::map<std::string, ichi::input::Keyboard::Key> keyStrings;

    ProfileHandler() = delete;
    ~ProfileHandler() = delete;
};