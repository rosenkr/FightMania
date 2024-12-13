#include "Ichi/Core/engine.h"

#include "Ichi/Scene/sceneManager.h"
#include "Ichi/Scene/popUpMenu.h"

#include "Ichi/UIComponents/textbox.h"
#include "Ichi/UIComponents/slidebar.h"
#include "Ichi/UIComponents/dropDownMenu.h"
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
const std::string FOCUSED_DROP_DOWN_MENU_PATH = TEMP + "resources/images/UIComponents/FocusedDropDownMenu.png";
const std::string FOCUSED_BUTTON_PATH = TEMP + "resources/images/UIComponents/FocusedButton.png";
const std::string FOCUSED_SLIDER_PATH = TEMP + "resources/images/UIComponents/FocusedSlider.png";
const std::string FOCUSED_TEXTBOX_PATH = TEMP + "resources/images/UIComponents/FocusedTextbox.png";
const std::string ITEM_PATH = TEMP + "resources/images/UIComponents/Item.png";
const std::string PROGRESS_BAR_PATH = TEMP + "resources/images/UIComponents/ProgressBar.png";
const std::string SLIDER_PATH = TEMP + "resources/images/UIComponents/Slider.png";
const std::string TEXTBOX_PATH = TEMP + "resources/images/UIComponents/Textbox.png";
const std::string FOCUSED_RETURN_BTN_PATH = TEMP + "resources/images/UIComponents/FocusedReturnBtn.png";
const std::string RETURN_BTN_PATH = TEMP + "resources/images/UIComponents/ReturnBtn.png";

const std::string DARK_BLUE_SCREEN_PATH = TEMP + "resources/images/BackGrounds/DarkBlueScreen.png";
const std::string CHARACTER_SELECTION_PATH = TEMP + "resources/images/BackGrounds/CharcterSelection.png";
const std::string TRAINING_SELECTION_PATH = TEMP + "resources/images/BackGrounds/TrainingSelection.png";

datatypes::Hitbox window(datatypes::Point(0, 0), 384, 224, false);

const graphics::Sprite::Layer UI_LAYER = graphics::Sprite::Layer::UICOMPONENT;
const graphics::Sprite::Layer BACKGROUND_LAYER = graphics::Sprite::Layer::BACKGROUND;

const SDL_Color black{0, 0, 0, 255};
const SDL_Color white{255, 255, 255, 255};

TTF_Font *font;

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

std::shared_ptr<uicomponents::Button> createButton(datatypes::Hitbox &hitbox, const std::string &label, const std::string &spritePath, const std::string &focusedSpritePath, const std::function<void()> &onClick)
{
	graphics::Sprite defaultSprite(hitbox, UI_LAYER, spritePath);
	graphics::Sprite focusedSprite(hitbox, UI_LAYER, focusedSpritePath);

	return std::make_shared<uicomponents::Button>(hitbox, label, font, black, defaultSprite, focusedSprite, onClick);
}

std::shared_ptr<uicomponents::DropDownMenu> createMenu(datatypes::Hitbox &hitbox, const std::vector<std::string> &items, const std::string &spritePath, const std::string &focusedSpritePath, const std::string &itemPath)
{
	graphics::Sprite defaultSprite(hitbox, UI_LAYER, spritePath);
	graphics::Sprite focusedSprite(hitbox, UI_LAYER, focusedSpritePath);
	graphics::Sprite itemSprite(hitbox, UI_LAYER, itemPath);

	return std::make_shared<uicomponents::DropDownMenu>(hitbox, items, font, black, defaultSprite, focusedSprite, itemSprite);
}

int main(int argc, char *argv[])
{
	auto instance = core::Engine::getInstance();

	if (!instance->init())
	{
		instance->shutdown();
		return -1;
	}

	font = TTF_OpenFont(FONT_PATH.c_str(), 8);

	//
	//		MAIN MENU
	//

	datatypes::Hitbox hbLocalPlay(datatypes::Point(50, 60), 75, 20, false);
	datatypes::Hitbox hbTraining(datatypes::Point(50, 90), 75, 20, false);
	datatypes::Hitbox hbProfileEditor(datatypes::Point(50, 120), 75, 20, false);
	datatypes::Hitbox hbSettings(datatypes::Point(50, 150), 75, 20, false);
	datatypes::Hitbox hbExit(datatypes::Point(50, 180), 75, 20, false);

	graphics::Sprite *darkBlueBackgroundMain = new graphics::Sprite(window, BACKGROUND_LAYER, DARK_BLUE_SCREEN_PATH);

	auto localPlay = createButton(hbLocalPlay, "Local Play", BUTTON_PATH, FOCUSED_BUTTON_PATH, changeSceneToLocalPlayCharacterSelection);
	auto training = createButton(hbTraining, "Training", BUTTON_PATH, FOCUSED_BUTTON_PATH, changeSceneToTrainingCharacterSelection);
	auto profileEditor = createButton(hbProfileEditor, "Profile Editor", BUTTON_PATH, FOCUSED_BUTTON_PATH, changeSceneToProfileEditor);
	auto settings = createButton(hbSettings, "Settings", BUTTON_PATH, FOCUSED_BUTTON_PATH, changeSceneToSettings);
	auto exit = createButton(hbExit, "Exit game", BUTTON_PATH, FOCUSED_BUTTON_PATH, quit);

	auto mainPane = new uicomponents::Pane(window, {localPlay, training, profileEditor, settings, exit});

	std::shared_ptr<scene::Scene> mainScene = std::make_shared<scene::Scene>(darkBlueBackgroundMain, std::vector<core::Component *>{mainPane}, false);

	scene::sceneManager::addScene(static_cast<int>(SceneName::MAIN), mainScene);

	//
	//		MAIN MENU END
	//

	//
	//		LOCAL PLAY SELECTION
	//

	datatypes::Hitbox hbReturnLP(datatypes::Point(0, 0), 30, 30, false);
	datatypes::Hitbox hbRedPlayerMenu(datatypes::Point(30, 180), 50, 15, false);
	datatypes::Hitbox hbBluePlayerMenu(datatypes::Point(220, 180), 50, 15, false);

	auto returnBtnLP = createButton(hbReturnLP, "", RETURN_BTN_PATH, FOCUSED_RETURN_BTN_PATH, changeSceneToMain);
	auto redMenu = createMenu(hbRedPlayerMenu, {"TestRed"}, DROP_DOWN_MENU_PATH, FOCUSED_DROP_DOWN_MENU_PATH, ITEM_PATH);
	auto blueMenu = createMenu(hbBluePlayerMenu, {"TestBlue"}, DROP_DOWN_MENU_PATH, FOCUSED_DROP_DOWN_MENU_PATH, ITEM_PATH);

	graphics::Sprite *characterSelectionBackground = new graphics::Sprite(window, BACKGROUND_LAYER, CHARACTER_SELECTION_PATH);

	auto characterPane = new uicomponents::Pane(window, {returnBtnLP, redMenu, blueMenu});

	std::shared_ptr<scene::Scene> characterSelectionScene = std::make_shared<scene::Scene>(characterSelectionBackground, std::vector<core::Component *>{characterPane}, false);

	scene::sceneManager::addScene(static_cast<int>(SceneName::LOCAL_PLAY_CHARACTER_SELECTION), characterSelectionScene);

	//
	//		LOCAL PLAY SELECTION END
	//

	//
	//		TRAINING SELECTION
	//

	datatypes::Hitbox hbReturnT(datatypes::Point(0, 0), 30, 30, false);

	graphics::Sprite returnSpriteT(hbReturnT, UI_LAYER, RETURN_BTN_PATH);
	graphics::Sprite focusedReturnSpriteT(hbReturnT, UI_LAYER, FOCUSED_RETURN_BTN_PATH);

	std::shared_ptr<uicomponents::Button> returnBtnT = std::make_shared<uicomponents::Button>(hbReturnT, "", font, black, returnSpriteT, focusedReturnSpriteT, changeSceneToMain);

	auto trainingPane = new uicomponents::Pane(window, {returnBtnT});

	graphics::Sprite *trainingSelcetion = new graphics::Sprite(window, BACKGROUND_LAYER, TRAINING_SELECTION_PATH);

	std::shared_ptr<scene::Scene> trainingSelectionScene = std::make_shared<scene::Scene>(trainingSelcetion, std::vector<core::Component *>{trainingPane}, false);

	scene::sceneManager::addScene(static_cast<int>(SceneName::TRAINING_CHARACTER_SELECTION), trainingSelectionScene);

	//
	//		TRAINING SELECTION END
	//

	//
	//		PROFILE EDITOR
	//

	datatypes::Hitbox hbReturnPE(datatypes::Point(0, 0), 30, 30, false);

	graphics::Sprite returnSpritePE(hbReturnPE, UI_LAYER, RETURN_BTN_PATH);
	graphics::Sprite focusedReturnSpritePE(hbReturnPE, UI_LAYER, FOCUSED_RETURN_BTN_PATH);

	std::shared_ptr<uicomponents::Button> returnBtnPE = std::make_shared<uicomponents::Button>(hbReturnPE, "", font, black, returnSpritePE, focusedReturnSpritePE, changeSceneToMain);

	auto profileEditorPane = new uicomponents::Pane(window, {returnBtnPE});

	graphics::Sprite *darkBlueBackgroundPE = new graphics::Sprite(window, BACKGROUND_LAYER, DARK_BLUE_SCREEN_PATH);

	std::shared_ptr<scene::Scene> profileEditorScene = std::make_shared<scene::Scene>(darkBlueBackgroundPE, std::vector<core::Component *>{profileEditorPane}, false);

	scene::sceneManager::addScene(static_cast<int>(SceneName::PROFILE_EDITOR), profileEditorScene);

	//
	//		PROFILE EDITOR END
	//

	//
	//		SETTINGS
	//

	datatypes::Hitbox hbReturnS(datatypes::Point(0, 0), 30, 30, false);

	graphics::Sprite returnSpriteS(hbReturnS, UI_LAYER, RETURN_BTN_PATH);
	graphics::Sprite focusedReturnSpriteS(hbReturnS, UI_LAYER, FOCUSED_RETURN_BTN_PATH);

	std::shared_ptr<uicomponents::Button> returnBtnS = std::make_shared<uicomponents::Button>(hbReturnS, "", font, black, returnSpriteS, focusedReturnSpriteS, changeSceneToMain);

	auto pane = new uicomponents::Pane(window, {returnBtnS});

	graphics::Sprite *darkBlueBackgroundS = new graphics::Sprite(window, BACKGROUND_LAYER, DARK_BLUE_SCREEN_PATH);

	std::shared_ptr<scene::Scene> settingScene = std::make_shared<scene::Scene>(darkBlueBackgroundS, std::vector<core::Component *>{pane}, false);

	scene::sceneManager::addScene(static_cast<int>(SceneName::SETTINGS), settingScene);

	//
	//		SETTINGS END
	//

	scene::sceneManager::setActiveScene(static_cast<int>(SceneName::MAIN));

	instance->run();

	TTF_CloseFont(font);

	return 0;
}
