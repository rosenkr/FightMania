#ifndef PROFILE_HANDLER_H
#define PROFILE_HANDLER_H

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
    static std::vector<std::string> getNames()
    {
        std::vector<std::string> strings;
        for (const auto &p : profiles)
            strings.push_back(p.first);

        return strings;
    }

    static std::string getString(ichi::input::ControllerHandler::Joystick js)
    {
        for (auto pair : joystickStrings)
            if (pair.second == js)
                return pair.first;
        return "";
    }
    static std::string getString(ichi::input::ControllerHandler::ControllerButton c)
    {
        for (auto pair : controllerStrings)
            if (pair.second == c)
                return pair.first;
        return "";
    }
    static std::string getString(ichi::input::Keyboard::Key k)
    {
        for (auto pair : keyStrings)
            if (pair.second == k)
                return pair.first;
        return "";
    }
    static std::string getString(ichi::input::Mouse::MouseButton btn)
    {
        for (auto pair : mouseStrings)
            if (pair.second == btn)
                return pair.first;
        return "";
    }

private:
    static std::string PROFILE_PATH;

    static std::map<std::string, Profile> profiles;

    static void addToVector(std::vector<std::string>);
    static void addToVector(std::vector<std::string>, bool);
    static void addToVector(std::string, bool, std::vector<std::string>);
    static void updateFile();
    static std::vector<std::string> split(const std::string &s, const std::string &delimiter);

    static std::map<std::string, ichi::input::ControllerHandler::Joystick> joystickStrings;
    static std::map<std::string, ichi::input::ControllerHandler::ControllerButton> controllerStrings;
    static std::map<std::string, ichi::input::Mouse::MouseButton> mouseStrings;
    static std::map<std::string, ichi::input::Keyboard::Key> keyStrings;

    ProfileHandler() = delete;
    ~ProfileHandler() = delete;
};

#endif