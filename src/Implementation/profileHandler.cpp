#include "Implementation/profileHandler.h"
#include "Ichi/log.h"

#include <fstream>
#include <algorithm>

using namespace std;

// Profile should be save using following format:
// IS_CONTROLLER(TRUE or FALSE);NAME;UP;DOWN;LEFT;RIGHT;LIGHT_ATTACK;HEAVY_ATTACK;JUMP;BLOCK

bool ProfileHandler::init()
{
    ifstream fstream(PROFILE_PATH);

    if (!fstream.is_open())
    {
        ICHI_ERROR("Could not open file: {}", PROFILE_PATH)
        return false;
    }

    string line;
    while (getline(fstream, line))
        addToVector(split(line, ";"));

    fstream.close();
    return true;
}

void ProfileHandler::saveProfile(vector<string> strings, bool isController)
{
    if (strings.size() != 9)
    {
        ICHI_ERROR("Save Profile Was called with wrong amount of elements in list")
        return;
    }

    for (auto &s : strings)
        transform(s.begin(), s.end(), s.begin(), ::toupper);

    if (profiles.find(strings.at(0)) != profiles.end())
    {
        ICHI_ERROR("Name already exists in list")
        return;
    }

    if (isController)
        for (size_t i = 4; i < strings.size(); i++)
            if (joystickStrings.find(strings.at(i)) == joystickStrings.end() && controllerStrings.find(strings.at(i)) == controllerStrings.end())
            {
                ICHI_ERROR("Could not match arguments to controller for {}", strings.at(0))
                return;
            }

    if (!isController)
        for (size_t i = 1; i < strings.size(); i++)
            if (keyStrings.find(strings.at(i)) == keyStrings.end() && mouseStrings.find(strings.at(i)) == mouseStrings.end())
            {
                ICHI_ERROR("Could not match arguments to Keyboard and mouse for {}", strings.at(0))
                return;
            }

    addToVector(strings, isController);
    updateFile();
}

const Profile *ProfileHandler::getProfile(string name)
{
    transform(name.begin(), name.end(), name.begin(), ::toupper);
    if (profiles.find(name) == profiles.end())
        return nullptr;
    return &profiles.at(name);
}

void ProfileHandler::removeProfile(std::string name)
{
    transform(name.begin(), name.end(), name.begin(), ::toupper);
    if (profiles.find(name) == profiles.end())
    {
        ICHI_ERROR("Name: {} does not exist in profiles", name)
        return;
    }
    profiles.erase(name);
    updateFile();
}

void ProfileHandler::addToVector(string name, bool isController, vector<string> list)
{
    if (isController)
    {
        map<ichi::input::ControllerHandler::ControllerButton, Profile::Action> btnMap;
        map<ichi::input::ControllerHandler::Joystick, Profile::Action> joystickMap;
        int action = static_cast<int>(Profile::Action::LIGHT_ATTACK);
        for (auto key : list)
        {
            if (joystickStrings.find(key) != joystickStrings.end())
                joystickMap[joystickStrings[key]] = static_cast<Profile::Action>(action);
            else
                btnMap[controllerStrings[key]] = static_cast<Profile::Action>(action);
            ++action;
        }

        profiles.emplace(name, Profile(name, btnMap, joystickMap));
        return;
    }

    map<ichi::input::Mouse::MouseButton, Profile::Action> mMap;
    map<ichi::input::Keyboard::Key, Profile::Action> kMap;
    int action = static_cast<int>(Profile::Action::UP);
    for (auto key : list)
    {
        if (mouseStrings.find(key) != mouseStrings.end())
            mMap[mouseStrings[key]] = static_cast<Profile::Action>(action);
        else
            kMap[keyStrings[key]] = static_cast<Profile::Action>(action);
        ++action;
    }
    profiles.emplace(name, Profile(name, mMap, kMap));
}
void ProfileHandler::addToVector(vector<string> list, bool isController)
{
    string name = list[0];
    vector<string> copy(list.begin() + 1, list.end());

    addToVector(name, isController, copy);
}
void ProfileHandler::addToVector(vector<string> list)
{
    bool isController = false;
    if (list[0] == "TRUE")
        isController = true;
    string name = list[1];
    vector<string> copy(list.begin() + 2, list.end());

    addToVector(name, isController, copy);
}

void ProfileHandler::updateFile()
{
    ofstream myfile;
    myfile.open(PROFILE_PATH);

    for (auto profile : profiles)
    {
        if (profile.second.isController())
            myfile << "TRUE";
        else
            myfile << "FALSE";

        myfile << ";" << profile.first;

        for (auto s : profile.second.getKeybinds())
            myfile << ";" << s;
        myfile << endl;
    }

    myfile.close();
}

vector<string>
ProfileHandler::split(const string &s, const string &delimiter)
{
    vector<string> tokens;
    size_t pos = 0;
    string str = s;

    while ((pos = str.find(delimiter)) != string::npos)
    {
        tokens.push_back(str.substr(0, pos));
        str.erase(0, pos + delimiter.length());
    }
    tokens.push_back(str);

    return tokens;
}

// std::string ProfileHandler::PROFILE_PATH = "/home/sasha/Documents/Uni/Course3/projects/fight_mania/resources/Profiles.txt";
std::string ProfileHandler::PROFILE_PATH = "resources/Profiles.txt";
std::map<std::string, Profile> ProfileHandler::profiles;
std::map<std::string, ichi::input::ControllerHandler::Joystick> ProfileHandler::joystickStrings{{"LT", ichi::input::ControllerHandler::Joystick::LeftTrigger}, {"RT", ichi::input::ControllerHandler::Joystick::RightTrigger}};
std::map<std::string, ichi::input::ControllerHandler::ControllerButton> ProfileHandler::controllerStrings{
    {"A", ichi::input::ControllerHandler::ControllerButton::A},
    {"B", ichi::input::ControllerHandler::ControllerButton::B},
    {"X", ichi::input::ControllerHandler::ControllerButton::X},
    {"Y", ichi::input::ControllerHandler::ControllerButton::Y},
    {"LS", ichi::input::ControllerHandler::ControllerButton::LS},
    {"RS", ichi::input::ControllerHandler::ControllerButton::RS},
    {"LB", ichi::input::ControllerHandler::ControllerButton::LB},
    {"RB", ichi::input::ControllerHandler::ControllerButton::RB},
    {"UP", ichi::input::ControllerHandler::ControllerButton::DPAD_Up},
    {"DOWN", ichi::input::ControllerHandler::ControllerButton::DPAD_Down},
    {"LEFT", ichi::input::ControllerHandler::ControllerButton::DPAD_Left},
    {"Right", ichi::input::ControllerHandler::ControllerButton::DPAD_Right},
};
std::map<std::string, ichi::input::Mouse::MouseButton> ProfileHandler::mouseStrings{
    {"LEFT", ichi::input::Mouse::MouseButton::LEFT},
    {"MIDDLE", ichi::input::Mouse::MouseButton::MIDDLE},
    {"RIGHT", ichi::input::Mouse::MouseButton::RIGHT},
    {"X1", ichi::input::Mouse::MouseButton::X1},
    {"X2", ichi::input::Mouse::MouseButton::X2},
};
std::map<std::string, ichi::input::Keyboard::Key> ProfileHandler::keyStrings{
    {"A", ichi::input::Keyboard::Key::ICHIKEY_A},
    {"B", ichi::input::Keyboard::Key::ICHIKEY_B},
    {"C", ichi::input::Keyboard::Key::ICHIKEY_C},
    {"D", ichi::input::Keyboard::Key::ICHIKEY_D},
    {"E", ichi::input::Keyboard::Key::ICHIKEY_E},
    {"F", ichi::input::Keyboard::Key::ICHIKEY_F},
    {"G", ichi::input::Keyboard::Key::ICHIKEY_G},
    {"H", ichi::input::Keyboard::Key::ICHIKEY_H},
    {"I", ichi::input::Keyboard::Key::ICHIKEY_I},
    {"J", ichi::input::Keyboard::Key::ICHIKEY_J},
    {"K", ichi::input::Keyboard::Key::ICHIKEY_K},
    {"L", ichi::input::Keyboard::Key::ICHIKEY_L},
    {"M", ichi::input::Keyboard::Key::ICHIKEY_M},
    {"N", ichi::input::Keyboard::Key::ICHIKEY_N},
    {"O", ichi::input::Keyboard::Key::ICHIKEY_O},
    {"P", ichi::input::Keyboard::Key::ICHIKEY_P},
    {"Q", ichi::input::Keyboard::Key::ICHIKEY_Q},
    {"R", ichi::input::Keyboard::Key::ICHIKEY_R},
    {"S", ichi::input::Keyboard::Key::ICHIKEY_S},
    {"T", ichi::input::Keyboard::Key::ICHIKEY_T},
    {"U", ichi::input::Keyboard::Key::ICHIKEY_U},
    {"V", ichi::input::Keyboard::Key::ICHIKEY_V},
    {"W", ichi::input::Keyboard::Key::ICHIKEY_W},
    {"X", ichi::input::Keyboard::Key::ICHIKEY_X},
    {"Y", ichi::input::Keyboard::Key::ICHIKEY_Y},
    {"Z", ichi::input::Keyboard::Key::ICHIKEY_Z},
    {"1", ichi::input::Keyboard::Key::ICHIKEY_1},
    {"2", ichi::input::Keyboard::Key::ICHIKEY_2},
    {"3", ichi::input::Keyboard::Key::ICHIKEY_3},
    {"4", ichi::input::Keyboard::Key::ICHIKEY_4},
    {"5", ichi::input::Keyboard::Key::ICHIKEY_5},
    {"6", ichi::input::Keyboard::Key::ICHIKEY_6},
    {"7", ichi::input::Keyboard::Key::ICHIKEY_7},
    {"8", ichi::input::Keyboard::Key::ICHIKEY_8},
    {"9", ichi::input::Keyboard::Key::ICHIKEY_9},
    {"0", ichi::input::Keyboard::Key::ICHIKEY_0},
    {"RETURN", ichi::input::Keyboard::Key::ICHIKEY_RETURN},
    {"BACKSPACE", ichi::input::Keyboard::Key::ICHIKEY_BACKSPACE},
    {"TAB", ichi::input::Keyboard::Key::ICHIKEY_TAB},
    {"SPACE", ichi::input::Keyboard::Key::ICHIKEY_SPACE},
    {"MINUS", ichi::input::Keyboard::Key::ICHIKEY_MINUS},
    {"EQUALS", ichi::input::Keyboard::Key::ICHIKEY_EQUALS},
    {"[", ichi::input::Keyboard::Key::ICHIKEY_LEFTBRACKET},
    {"]", ichi::input::Keyboard::Key::ICHIKEY_RIGHTBRACKET},
    {"BACKSLASH", ichi::input::Keyboard::Key::ICHIKEY_BACKSLASH},
    {"NONUSHASH", ichi::input::Keyboard::Key::ICHIKEY_NONUSHASH},
    {"SEMICOLON", ichi::input::Keyboard::Key::ICHIKEY_SEMICOLON},
    {"APOSTROPHE", ichi::input::Keyboard::Key::ICHIKEY_APOSTROPHE},
    {"GRAVE", ichi::input::Keyboard::Key::ICHIKEY_GRAVE},
    {"COMMA", ichi::input::Keyboard::Key::ICHIKEY_COMMA},
    {"PERIOD", ichi::input::Keyboard::Key::ICHIKEY_PERIOD},
    {"SLASH", ichi::input::Keyboard::Key::ICHIKEY_SLASH},
    {"CAPSLOCK", ichi::input::Keyboard::Key::ICHIKEY_CAPSLOCK},
    {"F1", ichi::input::Keyboard::Key::ICHIKEY_F1},
    {"F2", ichi::input::Keyboard::Key::ICHIKEY_F2},
    {"F3", ichi::input::Keyboard::Key::ICHIKEY_F3},
    {"F4", ichi::input::Keyboard::Key::ICHIKEY_F4},
    {"F5", ichi::input::Keyboard::Key::ICHIKEY_F5},
    {"F6", ichi::input::Keyboard::Key::ICHIKEY_F6},
    {"F7", ichi::input::Keyboard::Key::ICHIKEY_F7},
    {"F8", ichi::input::Keyboard::Key::ICHIKEY_F8},
    {"F9", ichi::input::Keyboard::Key::ICHIKEY_F9},
    {"F10", ichi::input::Keyboard::Key::ICHIKEY_F10},
    {"F11", ichi::input::Keyboard::Key::ICHIKEY_F11},
    {"F12", ichi::input::Keyboard::Key::ICHIKEY_F12},
    {"INSERT", ichi::input::Keyboard::Key::ICHIKEY_INSERT},
    {"HOME", ichi::input::Keyboard::Key::ICHIKEY_HOME},
    {"PAGEUP", ichi::input::Keyboard::Key::ICHIKEY_PAGEUP},
    {"DELETE", ichi::input::Keyboard::Key::ICHIKEY_DELETE},
    {"END", ichi::input::Keyboard::Key::ICHIKEY_END},
    {"PAGEDOWN", ichi::input::Keyboard::Key::ICHIKEY_PAGEDOWN},
    {"RIGHT", ichi::input::Keyboard::Key::ICHIKEY_RIGHT},
    {"LEFT", ichi::input::Keyboard::Key::ICHIKEY_LEFT},
    {"DOWN", ichi::input::Keyboard::Key::ICHIKEY_DOWN},
    {"UP", ichi::input::Keyboard::Key::ICHIKEY_UP}};