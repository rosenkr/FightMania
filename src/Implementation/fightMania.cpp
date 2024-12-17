#include "Ichi/Core/engine.h"

#include "Ichi/Scene/sceneManager.h"
#include "Ichi/Scene/popUpMenu.h"

#include "Ichi/UIComponents/textbox.h"
#include "Ichi/UIComponents/slidebar.h"
#include "Ichi/UIComponents/button.h"
#include "Ichi/UIComponents/pane.h"

#include "Implementation/character.h"
#include "Implementation/ground.h"

#include "Ichi/DataTypes/hitbox.h"

#include "Ichi/log.h"

#include "SDL2/SDL_ttf.h"

using namespace ichi;

const std::string TEMP = "/home/sasha/Documents/Uni/Course3/projects/fight_mania/";
//const std::string TEMP = "";

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
const std::string HEART_PATH = TEMP + "resources/images/UIComponents/Heart.png";
const std::string ITEM_PATH = TEMP + "resources/images/UIComponents/Item.png";
const std::string PROGRESS_BAR_PATH = TEMP + "resources/images/UIComponents/ProgressBar.png";
const std::string SLIDER_PATH = TEMP + "resources/images/UIComponents/Slider.png";
const std::string TEXTBOX_PATH = TEMP + "resources/images/UIComponents/Textbox.png";
const std::string FOCUSED_RETURN_BTN_PATH = TEMP + "resources/images/UIComponents/FocusedReturnBtn.png";
const std::string RETURN_BTN_PATH = TEMP + "resources/images/UIComponents/ReturnBtn.png";
const std::string ROBOT_PATH0 = TEMP + "resources/images/RobotAnimations/0.png";
const std::string ROBOT_PATH1 = TEMP + "resources/images/RobotAnimations/1.png";
const std::string ROBOT_PATH2 = TEMP + "resources/images/RobotAnimations/2.png";
const std::string ROBOT_PATH3 = TEMP + "resources/images/RobotAnimations/3.png";

const std::string DARK_BLUE_SCREEN_PATH = TEMP + "resources/images/BackGrounds/DarkBlueScreen.png";
const std::string CHARACTER_SELECTION_PATH = TEMP + "resources/images/BackGrounds/CharcterSelection.png";
const std::string TRAINING_SELECTION_PATH = TEMP + "resources/images/BackGrounds/TrainingSelection.png";
const std::string DOJO_PATH = TEMP + "resources/images/BackGrounds/Dojo.png";


datatypes::Hitbox window(datatypes::Point(0, 0), 384, 224, false);

const graphics::Sprite::Layer UI_LAYER = graphics::Sprite::Layer::UICOMPONENT;
const graphics::Sprite::Layer BACKGROUND_LAYER = graphics::Sprite::Layer::BACKGROUND;
const graphics::Sprite::Layer FOREGROUND_LAYER = graphics::Sprite::Layer::FOREGROUND;

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

void changeSceneToDojo() { scene::sceneManager::setActiveScene(static_cast<int>(SceneName::DOJO)); }

std::shared_ptr<uicomponents::Button> createButton(datatypes::Hitbox &hitbox, const std::string &label, const std::string &spritePath, const std::string &focusedSpritePath, const std::function<void()> &onClick)
{
	graphics::Sprite defaultSprite(hitbox, UI_LAYER, spritePath);
	graphics::Sprite focusedSprite(hitbox, UI_LAYER, focusedSpritePath);

	uicomponents::Button btn(hitbox, "", font, black, defaultSprite, focusedSprite, onClick);
	return std::make_shared<uicomponents::Button>(hitbox, label, font, black, defaultSprite, focusedSprite, onClick);
}

void createToSettings()
{
}

int main(int argc, char *argv[])
{
	auto instance = core::Engine::getInstance();

	if (!instance->init())
	{
		instance->shutdown();
		return -1;
	}

	font = TTF_OpenFont(FONT_PATH.c_str(), 12);

	//
	//		MAIN MENU
	//

	datatypes::Hitbox hbLocalPlay(datatypes::Point(50, 60), 75, 20, false);
	datatypes::Hitbox hbTraining(datatypes::Point(50, 90), 75, 20, false);
	datatypes::Hitbox hbProfileEditor(datatypes::Point(50, 120), 75, 20, false);
	datatypes::Hitbox hbSettings(datatypes::Point(50, 150), 75, 20, false);
	datatypes::Hitbox hbExit(datatypes::Point(50, 180), 75, 20, false);
	
	datatypes::Hitbox hbDojo(datatypes::Point(150, 150), 75, 20, false);

	graphics::Sprite *darkBlueBackgroundMain = new graphics::Sprite(window, BACKGROUND_LAYER, DARK_BLUE_SCREEN_PATH);

	auto localPlay = createButton(hbLocalPlay, "Local Play", BUTTON_PATH, FOCUSED_BUTTON_PATH, changeSceneToLocalPlayCharacterSelection);
	auto training = createButton(hbTraining, "Training", BUTTON_PATH, FOCUSED_BUTTON_PATH, changeSceneToTrainingCharacterSelection);
	auto profileEditor = createButton(hbProfileEditor, "Profile Editor", BUTTON_PATH, FOCUSED_BUTTON_PATH, changeSceneToProfileEditor);
	auto settings = createButton(hbSettings, "Settings", BUTTON_PATH, FOCUSED_BUTTON_PATH, changeSceneToSettings);
	auto exit = createButton(hbExit, "Exit game", BUTTON_PATH, FOCUSED_BUTTON_PATH, quit);

	auto dojo = createButton(hbDojo, "Dojo", BUTTON_PATH, FOCUSED_BUTTON_PATH, changeSceneToDojo);

	auto mainPane = new uicomponents::Pane(window, {localPlay, training, profileEditor, settings, exit, dojo});

	std::shared_ptr<scene::Scene> mainScene = std::make_shared<scene::Scene>(darkBlueBackgroundMain, std::vector<core::Component *>{mainPane}, false);

	scene::sceneManager::addScene(static_cast<int>(SceneName::MAIN), mainScene);

	//
	//		MAIN MENU END
	//

	//
	//		LOCAL PLAY SELECTION
	//

	datatypes::Hitbox hbReturnLP(datatypes::Point(0, 0), 30, 30, false);

	graphics::Sprite returnSpriteLP(hbReturnLP, UI_LAYER, RETURN_BTN_PATH);
	graphics::Sprite focusedReturnSpriteLP(hbReturnLP, UI_LAYER, FOCUSED_RETURN_BTN_PATH);

	std::shared_ptr<uicomponents::Button> returnBtnLP = std::make_shared<uicomponents::Button>(hbReturnLP, "", font, black, returnSpriteLP, focusedReturnSpriteLP, changeSceneToMain);

	graphics::Sprite *characterSelectionBackground = new graphics::Sprite(window, BACKGROUND_LAYER, CHARACTER_SELECTION_PATH);

	auto characterPane = new uicomponents::Pane(window, {returnBtnLP});

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

	//
	//		DOJO
	//
	
	datatypes::Hitbox hbReturnD(datatypes::Point(0, 0), 30, 30, false);
	graphics::Sprite returnSpriteD(hbReturnD, UI_LAYER, RETURN_BTN_PATH);
	graphics::Sprite focusedReturnSpriteD(hbReturnD, UI_LAYER, FOCUSED_RETURN_BTN_PATH);


	std::shared_ptr<uicomponents::Button> returnBtnD = std::make_shared<uicomponents::Button>(hbReturnD, "", font, black, returnSpriteD, focusedReturnSpriteD, changeSceneToMain);


	graphics::Sprite *dojoBackground = new graphics::Sprite(window, BACKGROUND_LAYER, DOJO_PATH);

	auto dojoPane = new uicomponents::Pane(window, {returnBtnD});

	std::shared_ptr<scene::Scene> dojoScene = std::make_shared<scene::Scene>(dojoBackground, std::vector<core::Component *>{dojoPane}, false);

	scene::sceneManager::addScene(static_cast<int>(SceneName::DOJO), dojoScene);

	
	// robot
	ichi::datatypes::Hitbox robotHitbox(datatypes::Point(0,0), 120, 120, true);
	//ichi::datatypes::Hitbox animationHitbox(datatypes::Point(20, 20), 120, 120, false); 
	std::vector<std::string> paths = {ROBOT_PATH0,ROBOT_PATH1,ROBOT_PATH2,ROBOT_PATH3};

	std::shared_ptr<ichi::graphics::AnimatedSprite> animation = std::make_shared<ichi::graphics::AnimatedSprite>(
		robotHitbox, FOREGROUND_LAYER, paths, std::map<int, Uint32>{{0, 1}, {1, 1}, {2, 1}, {3, 1}}
	);

	std::shared_ptr<Character> robot = std::make_shared<Character>(
    robotHitbox, 120, 2, 3, *animation, false
	);

	dojoScene->addComponent(robot); 

	// ground "hidden under dojo"
	ichi::datatypes::Hitbox groundHitbox(datatypes::Point(0,200), WINDOW_WIDTH, WINDOW_HEIGHT, true); // coords and w/h should be approximately at bottom of screen
	std::string path = BAR_PATH; // just some random img
	std::shared_ptr<ichi::graphics::Sprite> sprite = std::make_shared<ichi::graphics::Sprite>(groundHitbox, UI_LAYER, path);
	std::shared_ptr<Ground> dojoGround = std::make_shared<Ground>(groundHitbox);
	dojoScene->addComponent(dojoGround); 

	

	//
	//		DOJO END
	//

	scene::sceneManager::setActiveScene(static_cast<int>(SceneName::MAIN));

	instance->run();

	TTF_CloseFont(font);

	return 0;
}
