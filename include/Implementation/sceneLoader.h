#ifndef SCENE_LOADER_H
#define SCENE_LOADER_H

#include "Constants.h"

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

#include "Ichi/log.h"

#include "SDL2/SDL_mixer.h"

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

    struct MixMusicDeleter
    {
        void operator()(Mix_Music *music) const
        {
            if (music)
                Mix_FreeMusic(music);
        }
    };

    static void shutdown()
    {
        if (font)
        {
            TTF_CloseFont(font);
            font = nullptr;
        }
    }
    static bool init();

private:
    inline static const std::string FONT_PATH = constants::gResPath + "fonts/PRSTART.TTF";

    inline static const std::string POP_UP_MENU_PATH = constants::gResPath + "images/PopUpMenu/PopUpMenu.png";
    inline static const std::string TRANSPARENT_BLACK_PATH = constants::gResPath + "images/PopUpMenu/TransparantBlack.png";

    inline static const std::string BAR_PATH = constants::gResPath + "images/UIComponents/Bar.png";
    inline static const std::string BUTTON_PATH = constants::gResPath + "images/UIComponents/Button.png";
    inline static const std::string CHECKBOX_PATH = constants::gResPath + "images/UIComponents/Checkbox.png";
    inline static const std::string CHECKED_CHECKBOX_PATH = constants::gResPath + "images/UIComponents/CheckedCheckbox.png";
    inline static const std::string COLOR_GREEN_PATH = constants::gResPath + "images/UIComponents/colorGreen.png";
    inline static const std::string DROP_DOWN_MENU_PATH = constants::gResPath + "images/UIComponents/DropDownMenu.png";
    inline static const std::string FOCUSED_DROP_DOWN_MENU_PATH = constants::gResPath + "images/UIComponents/FocusedDropDownMenu.png";
    inline static const std::string FOCUSED_BUTTON_PATH = constants::gResPath + "images/UIComponents/FocusedButton.png";
    inline static const std::string FOCUSED_SLIDER_PATH = constants::gResPath + "images/UIComponents/FocusedSlider.png";
    inline static const std::string FOCUSED_TEXTBOX_PATH = constants::gResPath + "images/UIComponents/FocusedTextbox.png";
    inline static const std::string FOCUSED_Checkbox_PATH = constants::gResPath + "images/UIComponents/FocusedCheckbox.png";
    inline static const std::string FOCUSED_Checked_Checkbox_PATH = constants::gResPath + "images/UIComponents/FocusedCheckedCheckbox.png";
    inline static const std::string HEART_PATH = constants::gResPath + "images/UIComponents/Heart.png";
    inline static const std::string ITEM_PATH = constants::gResPath + "images/UIComponents/Item.png";
    inline static const std::string PROGRESS_BAR_PATH = constants::gResPath + "images/UIComponents/ProgressBar.png";
    inline static const std::string SLIDER_PATH = constants::gResPath + "images/UIComponents/Slider.png";
    inline static const std::string TEXTBOX_PATH = constants::gResPath + "images/UIComponents/Textbox.png";
    inline static const std::string FOCUSED_RETURN_BTN_PATH = constants::gResPath + "images/UIComponents/FocusedReturnBtn.png";
    inline static const std::string RETURN_BTN_PATH = constants::gResPath + "images/UIComponents/ReturnBtn.png";

    inline static const std::string FB_PATH0 = constants::gResPath + "images/Attacks/0.png";
    inline static const std::string FB_PATH1 = constants::gResPath + "images/Attacks/1.png";
    inline static const std::string FB_PATH2 = constants::gResPath + "images/Attacks/2.png";
    inline static const std::string FB_PATH3 = constants::gResPath + "images/Attacks/3.png";

    inline static const std::string ROBOT_PATH0 = constants::gResPath + "images/RobotAnimations/0.png";
    inline static const std::string ROBOT_PATH1 = constants::gResPath + "images/RobotAnimations/1.png";
    inline static const std::string ROBOT_PATH2 = constants::gResPath + "images/RobotAnimations/2.png";
    inline static const std::string ROBOT_PATH3 = constants::gResPath + "images/RobotAnimations/3.png";

    inline static std::map<int, Uint32> SINGLE_FRAME_TIME = {{0, 1000}}; // It doesnt matter what the value is

    inline static std::map<int, Uint32> KENNY_IDLE_TIME = {{0, 200}, {1, 200}, {2, 200}, {3, 200}, {4, 200}};
    inline static std::map<int, Uint32> KENNY_WALK_TIME = {{0, 200}, {1, 200}, {2, 200}, {3, 200}, {4, 200}, {5, 200}, {6, 200}, {7, 200}};

    inline static std::map<int, Uint32> KENNY_NEUTRAL_HEAVY_TIME = {{0, 100}, {1, 200}, {2, 100}, {3, 100}, {4, 200}};
    inline static std::map<int, Uint32> KENNY_SIDE_HEAVY_TIME = {{0, 100}, {1, 200}, {2, 100}, {3, 200}, {4, 100}, {5, 100}, {6, 100}};
    inline static std::map<int, Uint32> KENNY_SIDE_LIGHT_TIME = {{0, 300}, {1, 300}};
    inline static std::map<int, Uint32> KENNY_DOWN_LIGHT_TIME = {{0, 100}, {1, 100}, {2, 100}, {3, 200}};

    inline static std::map<int, Uint32> SWORD_SLASH_TIME = {{0, 150}, {1, 150}, {2, 150}};

    inline static const std::string KENNY_FALLING_LEFT = constants::gResPath + "images/kenny/falling/left";
    inline static const std::string KENNY_FALLING_RIGHT = constants::gResPath + "images/kenny/falling/right";
    inline static const std::string KENNY_JUMPING_LEFT = constants::gResPath + "images/kenny/jumping/left";
    inline static const std::string KENNY_JUMPING_RIGHT = constants::gResPath + "images/kenny/jumping/right";
    inline static const std::string KENNY_STUNNED_LEFT = constants::gResPath + "images/kenny/stunned/left";
    inline static const std::string KENNY_STUNNED_RIGHT = constants::gResPath + "images/kenny/stunned/right";

    inline static const std::string KENNY_IDLE_LEFT = constants::gResPath + "images/kenny/idle/left";
    inline static const std::string KENNY_IDLE_RIGHT = constants::gResPath + "images/kenny/idle/right";
    inline static const std::string KENNY_WALK_LEFT = constants::gResPath + "images/kenny/walk/left";
    inline static const std::string KENNY_WALK_RIGHT = constants::gResPath + "images/kenny/walk/right";

    inline static const std::string KENNY_BLOCK_LEFT = constants::gResPath + "images/kenny/block/left";
    inline static const std::string KENNY_BLOCK_RIGHT = constants::gResPath + "images/kenny/block/right";

    inline static const std::string KENNY_NEUTRAL_HEAVY_LEFT = constants::gResPath + "images/kenny/neutralHeavy/left";
    inline static const std::string KENNY_NEUTRAL_HEAVY_RIGHT = constants::gResPath + "images/kenny/neutralHeavy/right";
    inline static const std::string KENNY_SIDE_HEAVY_LEFT = constants::gResPath + "images/kenny/sideHeavy/left";
    inline static const std::string KENNY_SIDE_HEAVY_RIGHT = constants::gResPath + "images/kenny/sideHeavy/right";
    inline static const std::string KENNY_SIDE_LIGHT_LEFT = constants::gResPath + "images/kenny/sideLight/left";
    inline static const std::string KENNY_SIDE_LIGHT_RIGHT = constants::gResPath + "images/kenny/sideLight/right";
    inline static const std::string KENNY_DOWN_LIGHT_LEFT = constants::gResPath + "images/kenny/downLight/left";
    inline static const std::string KENNY_DOWN_LIGHT_RIGHT = constants::gResPath + "images/kenny/downLight/right";

    inline static const std::string SWORD_SLASH_LEFT = constants::gResPath + "images/kenny/swordSlash/left";
    inline static const std::string SWORD_SLASH_RIGHT = constants::gResPath + "images/kenny/swordSlash/right";

    inline static const std::string DARK_BLUE_SCREEN_PATH = constants::gResPath + "images/BackGrounds/DarkBlueScreen.png";
    inline static const std::string MAIN_MENU_PATH = constants::gResPath + "images/BackGrounds/MainMenu.png";
    inline static const std::string CHARACTER_SELECTION_PATH = constants::gResPath + "images/BackGrounds/CharcterSelection.png";
    inline static const std::string TRAINING_SELECTION_PATH = constants::gResPath + "images/BackGrounds/CharcterSelectionTraining.png";
    inline static const std::string DOJO_PATH = constants::gResPath + "images/BackGrounds/Dojo.png";
    inline static const std::string CP_PATH = constants::gResPath + "images/BackGrounds/Cyberpunk.png";

    inline static const std::string MENU_MUSIC_PATH = constants::gResPath + "music/MenuSoundtrack.wav";
    inline static const std::string FIGHT_MUSIC_PATH = constants::gResPath + "music/FightMusic.wav";
    static std::unique_ptr<Mix_Music, MixMusicDeleter> menuMusic;
    static std::unique_ptr<Mix_Music, MixMusicDeleter> fightMusic;

    // Character names
    inline static const std::string KENNY = "KENNY";

    inline static const graphics::Sprite::Layer UI_LAYER = graphics::Sprite::Layer::UICOMPONENT;
    inline static const graphics::Sprite::Layer BACKGROUND_LAYER = ichi::graphics::Sprite::Layer::BACKGROUND;
    inline static const graphics::Sprite::Layer FOREGROUND_LAYER = ichi::graphics::Sprite::Layer::FOREGROUND;

    inline static const graphics::AnimatedSprite::Layer UI_LAYER_AS = graphics::AnimatedSprite::Layer::UICOMPONENT;
    inline static const graphics::AnimatedSprite::Layer BACKGROUND_LAYER_AS = ichi::graphics::AnimatedSprite::Layer::BACKGROUND;
    inline static const graphics::AnimatedSprite::Layer FOREGROUND_LAYER_AS = ichi::graphics::AnimatedSprite::Layer::FOREGROUND;

    static datatypes::Hitbox window;
    static datatypes::Hitbox hbName;

    static datatypes::Hitbox returnHB;
    static datatypes::Hitbox blueProfileDropdownHB;
    static datatypes::Hitbox blueCharacterDropdownHB;
    static datatypes::Hitbox redProfileDropdownHB;
    static datatypes::Hitbox redCharacterDropdownHB;

    inline static const SDL_Color black{0, 0, 0, 255};
    inline static const SDL_Color white{255, 255, 255, 255};
    inline static const SDL_Color yellow{255, 255, 0, 255};

    static TTF_Font *font;

    static void changeSceneToMain();
    static void changeSceneToLocalPlayCharacterSelection();
    static void changeSceneToTrainingCharacterSelection();
    static void changeSceneToProfileEditor();
    static void changeSceneToSettings();
    static void changeSceneToDojo();
    static void changeSceneToCyberPunk();

    static void quitGame();
    static void resetTextboxes();
    static void importProfile();
    static void removeProfile();
    static void saveProfile();

    static std::shared_ptr<ichi::uicomponents::Button> createButton(ichi::datatypes::Hitbox &, const std::string &, const std::string &, const std::string &, const std::function<void()> &);
    static std::shared_ptr<uicomponents::DropDownMenu> createMenu(datatypes::Hitbox &, const std::vector<std::string> &, const std::string &, const std::string &, const std::string &);
    static std::shared_ptr<uicomponents::Textbox> createTextbox(datatypes::Hitbox &, const std::string &, const std::string &, int);
    static std::shared_ptr<uicomponents::Checkbox> createCheckbox(datatypes::Hitbox &);
    static std::shared_ptr<uicomponents::SlideBar> createSlideBar(datatypes::Hitbox &, const std::string &, int, int, const std::string &, const std::string &, std::function<void(float)>);
    static std::shared_ptr<Character> createKenny(const Profile *p, int controllerID, bool facingRight);

    static void createPopUpMenu();
    static void createMainMenu();
    static void createLocalPlayMenu();
    static void createTrainingMenu();
    static void createProfileEditorMenu();
    static void createSettingMenu();
    static void createDojo();
    static void createCyberPunk();

    static std::unique_ptr<Mix_Music, MixMusicDeleter> loadMusic(const std::string &path)
    {
        Mix_Music *music = Mix_LoadMUS(path.c_str());
        if (!music)
        {
            ICHI_ERROR("Could not load music effect: {}", SDL_GetError());
            return nullptr;
        }
        return std::unique_ptr<Mix_Music, MixMusicDeleter>(music);
    }

    SceneLoader() = delete;
    ~SceneLoader() = delete;
};

#endif // SCENE_LOADER_H
