#ifndef SCENE_LOADER_H
#define SCENE_LOADER_H

#include "Ichi/UIComponents/label.h"
#include "Ichi/UIComponents/textbox.h"
#include "Ichi/UIComponents/slidebar.h"
#include "Ichi/UIComponents/dropDownMenu.h"
#include "Ichi/UIComponents/button.h"
#include "Ichi/UIComponents/checkbox.h"
#include "Ichi/UIComponents/pane.h"

#include "Ichi/Scene/sceneManager.h"
#include "Ichi/Scene/popUpMenu.h"
#include "Ichi/Scene/scene.h"

#include "Implementation/character.h"

#include <memory>

using namespace ichi;

class SceneLoader
{
public:
    enum class SceneName
    {
        MAIN,
        LOCAL_PLAY_CHARACTER_SELECTION,
        TRAINING_CHARACTER_SELECTION,
        PROFILE_EDITOR,
        SETTINGS,
        DOJO,
        CYBER_PUNK,
    };

    static bool init();

private:
    // const std::string TEMP = "/home/sasha/Documents/Uni/Course3/projects/fight_mania/";
    inline static const std::string TEMP = "";

    inline static const std::string FONT_PATH = TEMP + "resources/fonts/PRSTART.TTF";

    inline static const std::string POP_UP_MENU_PATH = TEMP + "resources/images/PopUpMenu/PopUpMenu.png";
    inline static const std::string TRANSPARENT_BLACK_PATH = TEMP + "resources/images/PopUpMenu/TransparantBlack.png";

    inline static const std::string BAR_PATH = TEMP + "resources/images/UIComponents/Bar.png";
    inline static const std::string BUTTON_PATH = TEMP + "resources/images/UIComponents/Button.png";
    inline static const std::string CHECKBOX_PATH = TEMP + "resources/images/UIComponents/Checkbox.png";
    inline static const std::string CHECKED_CHECKBOX_PATH = TEMP + "resources/images/UIComponents/CheckedCheckbox.png";
    inline static const std::string COLOR_GREEN_PATH = TEMP + "resources/images/UIComponents/colorGreen.png";
    inline static const std::string DROP_DOWN_MENU_PATH = TEMP + "resources/images/UIComponents/DropDownMenu.png";
    inline static const std::string FOCUSED_DROP_DOWN_MENU_PATH = TEMP + "resources/images/UIComponents/FocusedDropDownMenu.png";
    inline static const std::string FOCUSED_BUTTON_PATH = TEMP + "resources/images/UIComponents/FocusedButton.png";
    inline static const std::string FOCUSED_SLIDER_PATH = TEMP + "resources/images/UIComponents/FocusedSlider.png";
    inline static const std::string FOCUSED_TEXTBOX_PATH = TEMP + "resources/images/UIComponents/FocusedTextbox.png";
    inline static const std::string HEART_PATH = TEMP + "resources/images/UIComponents/Heart.png";
    inline static const std::string ITEM_PATH = TEMP + "resources/images/UIComponents/Item.png";
    inline static const std::string PROGRESS_BAR_PATH = TEMP + "resources/images/UIComponents/ProgressBar.png";
    inline static const std::string SLIDER_PATH = TEMP + "resources/images/UIComponents/Slider.png";
    inline static const std::string TEXTBOX_PATH = TEMP + "resources/images/UIComponents/Textbox.png";
    inline static const std::string FOCUSED_RETURN_BTN_PATH = TEMP + "resources/images/UIComponents/FocusedReturnBtn.png";
    inline static const std::string RETURN_BTN_PATH = TEMP + "resources/images/UIComponents/ReturnBtn.png";
    inline static const std::string ROBOT_PATH0 = TEMP + "resources/images/RobotAnimations/0.png";
    inline static const std::string ROBOT_PATH1 = TEMP + "resources/images/RobotAnimations/1.png";
    inline static const std::string ROBOT_PATH2 = TEMP + "resources/images/RobotAnimations/2.png";
    inline static const std::string ROBOT_PATH3 = TEMP + "resources/images/RobotAnimations/3.png";
    inline static const std::string FB_PATH0 = TEMP + "resources/images/Attacks/0.png";
    inline static const std::string FB_PATH1 = TEMP + "resources/images/Attacks/1.png";
    inline static const std::string FB_PATH2 = TEMP + "resources/images/Attacks/2.png";
    inline static const std::string FB_PATH3 = TEMP + "resources/images/Attacks/3.png";

    inline static const std::string DARK_BLUE_SCREEN_PATH = TEMP + "resources/images/BackGrounds/DarkBlueScreen.png";
    inline static const std::string CHARACTER_SELECTION_PATH = TEMP + "resources/images/BackGrounds/CharcterSelection.png";
    inline static const std::string TRAINING_SELECTION_PATH = TEMP + "resources/images/BackGrounds/CharcterSelectionTraining.png";
    inline static const std::string DOJO_PATH = TEMP + "resources/images/BackGrounds/Dojo.png";
    inline static const std::string CP_PATH = TEMP + "resources/images/BackGrounds/Cyberpunk.png";

    // Character names
    inline static const std::string ROBOT = "ROBOT";

    inline static const graphics::Sprite::Layer UI_LAYER = graphics::Sprite::Layer::UICOMPONENT;
    inline static const graphics::Sprite::Layer BACKGROUND_LAYER = ichi::graphics::Sprite::Layer::BACKGROUND;
    inline static const graphics::Sprite::Layer FOREGROUND_LAYER = ichi::graphics::Sprite::Layer::FOREGROUND;

    static datatypes::Hitbox window;
    static datatypes::Hitbox hbName;

    static datatypes::Hitbox blueProfileDropdownHB;
    static datatypes::Hitbox blueCharacterDropdownHB;
    static datatypes::Hitbox redProfileDropdownHB;
    static datatypes::Hitbox redCharacterDropdownHB;

    inline static const SDL_Color black{0, 0, 0, 255};
    inline static const SDL_Color white{255, 255, 255, 255};

    static TTF_Font *font;

    static void changeSceneToMain();
    static void changeSceneToLocalPlayCharacterSelection();
    static void changeSceneToTrainingCharacterSelection();
    static void changeSceneToProfileEditor();
    static void changeSceneToSettings();
    static void changeSceneToDojo();

    static void quitGame();
    static void resetTextboxes();
    static void importProfile();
    static void removeProfile();
    static void saveProfile();

    static std::shared_ptr<ichi::uicomponents::Button> createButton(ichi::datatypes::Hitbox &, const std::string &, const std::string &, const std::string &, const std::function<void()> &);
    static std::shared_ptr<uicomponents::DropDownMenu> createMenu(datatypes::Hitbox &, const std::vector<std::string> &, const std::string &, const std::string &, const std::string &);
    static std::shared_ptr<uicomponents::Textbox> createTextbox(datatypes::Hitbox &, const std::string &, const std::string &, int);
    static std::shared_ptr<uicomponents::SlideBar> createSlideBar(datatypes::Hitbox &, const std::string &, int, int, const std::string &, const std::string &, std::function<void(float)>);
    static std::shared_ptr<Character> createRobot(const Profile *p, datatypes::Hitbox &hb);

    static void createPopUpMenu();
    static void createMainMenu();
    static void createLocalPlayMenu();
    static void createTrainingMenu();
    static void createProfileEditorMenu();
    static void createSettingMenu();
    static void createDojo();

    SceneLoader() = delete;
    ~SceneLoader() { TTF_CloseFont(font); }
};

#endif // SCENE_LOADER_H
