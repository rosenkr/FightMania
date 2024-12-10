#include "Ichi/Core/engine.h"

#include "Ichi/Scene/sceneManager.h"
#include "Ichi/Scene/popUpMenu.h"

#include "Ichi/UIComponents/textbox.h"
#include "Ichi/UIComponents/slidebar.h"
#include "Ichi/UIComponents/button.h"
#include "Ichi/UIComponents/pane.h"

#include "Ichi/DataTypes/hitbox.h"

#include "Ichi/log.h"

#include "SDL2/SDL_ttf.h"

using namespace ichi;

// const std::string TEMP = "/home/sasha/Documents/Uni/Course3/projects/fight_mania/";
const std::string TEMP = "";

const std::string FONT_PATH = TEMP + "resources/fonts/PRSTART.TTF";
const std::string POP_UP_MENU_PATH = TEMP + "resources/images/PopUpMenu/PopUpMenu.png";
const std::string TRANSPARENT_BLACK_PATH = TEMP + "resources/images/PopUpMenu/TransparantBlack.png";
const std::string BAR_PATH = TEMP + "resources/images/UIComponents/Bar.png";
const std::string BUTTON_PATH = TEMP + "resources/images/UIComponents/Button.png";
const std::string CHECKBOX_PATH = TEMP + "resources/images/UIComponents/Checkbox.png";
const std::string CHECKED_CHECKBOX_PATH = TEMP + "resources/images/UIComponents/CheckedCheckbox.png";
const std::string COLOR_GREEN_PATH = TEMP + "resources/images/UIComponents/colorGreen.png";
const std::string DROP_DOWN_MENU_PATH = TEMP + "resources/images/UIComponents/DropDownMenu.png";
const std::string FOCUSED_BUTTON_PATH = TEMP + "resources/images/UIComponents/FocusedButton.png";
const std::string FOCUSED_SLIDER_PATH = TEMP + "resources/images/UIComponents/FocusedSlider.png";
const std::string FOCUSED_TEXTBOX_PATH = TEMP + "resources/images/UIComponents/FocusedTextbox.png";
const std::string ITEM_PATH = TEMP + "resources/images/UIComponents/Item.png";
const std::string PROGRESS_BAR_PATH = TEMP + "resources/images/UIComponents/ProgressBar.png";
const std::string SLIDER_PATH = TEMP + "resources/images/UIComponents/Slider.png";
const std::string TEXTBOX_PATH = TEMP + "resources/images/UIComponents/Textbox.png";

const datatypes::Hitbox window(datatypes::Point(0, 0), 384, 224, false);

const graphics::Sprite::Layer UI_LAYER = graphics::Sprite::Layer::UICOMPONENT;

const SDL_Color black{0, 0, 0, 255};
const SDL_Color white{255, 255, 255, 255};

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

void quit() { core::Engine::getInstance()->quit(); }
void changeSceneToMain() { scene::sceneManager::setActiveScene(static_cast<int>(SceneName::MAIN)); }
void changeSceneToLocalPlayCharacterSelection() { scene::sceneManager::setActiveScene(static_cast<int>(SceneName::LOCAL_PLAY_CHARACTER_SELECTION)); }
void changeSceneToTrainingCharacterSelection() { scene::sceneManager::setActiveScene(static_cast<int>(SceneName::TRAINING_CHARACTER_SELECTION)); }
void changeSceneToProfileEditor() { scene::sceneManager::setActiveScene(static_cast<int>(SceneName::PROFILE_EDITOR)); }
void changeSceneToSettings() { scene::sceneManager::setActiveScene(static_cast<int>(SceneName::SETTINGS)); }

int main(int argc, char *argv[])
{
	auto instance = core::Engine::getInstance();

	if (!instance->init())
	{
		instance->shutdown();
		return -1;
	}

	TTF_Font *font = TTF_OpenFont(FONT_PATH.c_str(), 12);

	//
	// 		MAIN SCENE
	//

	datatypes::Hitbox hbLocalPlay(datatypes::Point(50, 60), 75, 20, false);
	datatypes::Hitbox hbTraining(datatypes::Point(50, 90), 75, 20, false);
	datatypes::Hitbox hbProfileEditor(datatypes::Point(50, 120), 75, 20, false);
	datatypes::Hitbox hbSettings(datatypes::Point(50, 150), 75, 20, false);
	datatypes::Hitbox hbExit(datatypes::Point(50, 180), 75, 20, false);

	graphics::Sprite localPlaySprite(hbLocalPlay, UI_LAYER, BUTTON_PATH);
	graphics::Sprite trainingSprite(hbTraining, UI_LAYER, BUTTON_PATH);
	graphics::Sprite profileEditorSprite(hbProfileEditor, UI_LAYER, BUTTON_PATH);
	graphics::Sprite settingsSprite(hbSettings, UI_LAYER, BUTTON_PATH);
	graphics::Sprite exitSprite(hbExit, UI_LAYER, BUTTON_PATH);

	graphics::Sprite localPlayFocusedSprite(hbLocalPlay, UI_LAYER, FOCUSED_BUTTON_PATH);
	graphics::Sprite trainingFocusedSprite(hbTraining, UI_LAYER, FOCUSED_BUTTON_PATH);
	graphics::Sprite profileEditorFocusedSprite(hbProfileEditor, UI_LAYER, FOCUSED_BUTTON_PATH);
	graphics::Sprite settingsFocusedSprite(hbSettings, UI_LAYER, FOCUSED_BUTTON_PATH);
	graphics::Sprite exitFocusedSprite(hbExit, UI_LAYER, FOCUSED_BUTTON_PATH);

	std::shared_ptr<uicomponents::Button> localPlay = std::make_shared<uicomponents::Button>(hbLocalPlay, "Local Play", font, black, localPlaySprite, localPlayFocusedSprite, changeSceneToProfileEditor);
	std::shared_ptr<uicomponents::Button> training = std::make_shared<uicomponents::Button>(hbTraining, "Training", font, black, trainingSprite, trainingFocusedSprite, changeSceneToTrainingCharacterSelection);
	std::shared_ptr<uicomponents::Button> profileEditor = std::make_shared<uicomponents::Button>(hbProfileEditor, "Profile Editor", font, black, profileEditorSprite, profileEditorFocusedSprite, changeSceneToProfileEditor);
	std::shared_ptr<uicomponents::Button> settings = std::make_shared<uicomponents::Button>(hbSettings, "Settings", font, black, settingsSprite, settingsFocusedSprite, changeSceneToProfileEditor);
	std::shared_ptr<uicomponents::Button> exit = std::make_shared<uicomponents::Button>(hbExit, "Exit", font, black, exitSprite, exitFocusedSprite, quit);

	auto pane = new uicomponents::Pane(window, {localPlay, training, profileEditor, settings, exit});

	std::shared_ptr<scene::Scene> mainScene = std::make_shared<scene::Scene>(std::vector<core::Component *>{pane}, false);

	scene::sceneManager::addScene(static_cast<int>(SceneName::MAIN), mainScene);

	//
	// 		END OF MAIN SCENE
	//

	scene::sceneManager::setActiveScene(static_cast<int>(SceneName::MAIN));

	instance->run();

	TTF_CloseFont(font);

	return 0;
}
