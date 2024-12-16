#include "Ichi/Core/engine.h"

#include "Ichi/Scene/sceneManager.h"
#include "Ichi/Scene/popUpMenu.h"

#include "Ichi/UIComponents/label.h"
#include "Ichi/UIComponents/textbox.h"
#include "Ichi/UIComponents/slidebar.h"
#include "Ichi/UIComponents/dropDownMenu.h"
#include "Ichi/UIComponents/button.h"
#include "Ichi/UIComponents/checkbox.h"
#include "Ichi/UIComponents/pane.h"

#include "Ichi/DataTypes/hitbox.h"

#include "Ichi/log.h"

#include "Implementation/profileHandler.h"

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

void resetTextboxes()
{
	ICHI_TRACE("RESET")
	for (auto c : scene::sceneManager::getActiveScene()->getComponents())
	{
		if (auto ptr = dynamic_cast<uicomponents::Pane *>(c))
			for (auto ui : ptr->getUIComponents())
				if (auto ptr2 = dynamic_cast<uicomponents::Textbox *>(ui.second.get()))
					ptr2->clear();
		if (auto ptr = dynamic_cast<uicomponents::Textbox *>(c))
			ptr->clear();
	}
}

void importProfile()
{
	ICHI_TRACE("IMPORT")
	for (auto c : scene::sceneManager::getActiveScene()->getComponents())
		if (auto ptr = dynamic_cast<uicomponents::Pane *>(c))
		{
			const Profile *profile = nullptr;

			if (auto tbPtr = dynamic_cast<uicomponents::Textbox *>(ptr->getUIComponents().at(datatypes::Point(150, 15)).get()))
				profile = ProfileHandler::getProfile(tbPtr->getText());
			if (!profile)
			{
				ICHI_ERROR("Could not import settings")
				return;
			}

			int i = 0;
			for (auto ui : ptr->getUIComponents())
			{
				if (ui.first == datatypes::Point(150, 15))
					continue;
				if (auto ptr2 = dynamic_cast<uicomponents::Textbox *>(ui.second.get()))
					ptr2->setText(profile->getKeybinds().at(i++));
			}
		}
}

void removeProfile()
{
	ICHI_TRACE("REMOVE")
	for (auto c : scene::sceneManager::getActiveScene()->getComponents())
		if (auto ptr = dynamic_cast<uicomponents::Pane *>(c))
			for (auto ui : ptr->getUIComponents())
				if (auto ptr2 = dynamic_cast<uicomponents::Textbox *>(ui.second.get()))
				{
					if (ui.first != datatypes::Point(150, 15))
						continue;
					ProfileHandler::removeProfile(ptr2->getText());
					return;
				}
}

void saveProfile()
{
	ICHI_TRACE("SAVE")
	std::vector<std::string> strings;
	bool isChecked = false;
	for (auto c : scene::sceneManager::getActiveScene()->getComponents())
	{
		if (auto ptr = dynamic_cast<uicomponents::Pane *>(c))
			for (auto ui : ptr->getUIComponents())
				if (auto ptr2 = dynamic_cast<uicomponents::Textbox *>(ui.second.get()))
					strings.push_back(ptr2->getText());

		if (auto ptr = dynamic_cast<uicomponents::Textbox *>(c))
			strings.push_back(ptr->getText());

		if (auto ptr = dynamic_cast<uicomponents::Checkbox *>(c))
			isChecked = ptr->isChecked();
	}

	ProfileHandler::saveProfile(strings, isChecked);
}

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

std::shared_ptr<uicomponents::Textbox> createTextbox(datatypes::Hitbox &hb, std::string s, std::string fs, int cap)
{
	graphics::Sprite defaultSprite(hb, UI_LAYER, s);
	graphics::Sprite focusedSprite(hb, UI_LAYER, fs);

	return std::make_shared<uicomponents::Textbox>(hb, font, black, defaultSprite, focusedSprite, cap);
}

int main(int argc, char *argv[])
{
	auto instance = core::Engine::getInstance();

	if (!instance->init())
	{
		instance->shutdown();
		return -1;
	}

	if (!ProfileHandler::init())
	{
		ICHI_ERROR("Could not read from profile text file")
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

	auto returnBtnT = createButton(hbReturnT, "", RETURN_BTN_PATH, FOCUSED_RETURN_BTN_PATH, changeSceneToMain);

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

	datatypes::Point namePt(50, 15);
	datatypes::Point upPt(50, 35);
	datatypes::Point downPt(50, 55);
	datatypes::Point leftPt(50, 75);
	datatypes::Point rightPt(50, 95);
	datatypes::Point lightPt(50, 115);
	datatypes::Point heavyPt(50, 135);
	datatypes::Point jumpPt(50, 155);
	datatypes::Point blockPt(50, 175);

	datatypes::Hitbox hbName(datatypes::Point(150, namePt.Y), 70, 10, false); // This is directly mapped to import method
	datatypes::Hitbox hbUp(datatypes::Point(150, upPt.Y), 70, 10, false);
	datatypes::Hitbox hbDown(datatypes::Point(150, downPt.Y), 70, 10, false);
	datatypes::Hitbox hbLeft(datatypes::Point(150, leftPt.Y), 70, 10, false);
	datatypes::Hitbox hbRight(datatypes::Point(150, rightPt.Y), 70, 10, false);
	datatypes::Hitbox hbLight(datatypes::Point(150, lightPt.Y), 70, 10, false);
	datatypes::Hitbox hbHeavy(datatypes::Point(150, heavyPt.Y), 70, 10, false);
	datatypes::Hitbox hbJump(datatypes::Point(150, jumpPt.Y), 70, 10, false);
	datatypes::Hitbox hbBlock(datatypes::Point(150, blockPt.Y), 70, 10, false);

	datatypes::Hitbox hbReset(datatypes::Point(250, 30), 45, 15, false);
	datatypes::Hitbox hbImport(datatypes::Point(250, 60), 45, 15, false);
	datatypes::Hitbox hbRemove(datatypes::Point(250, 90), 45, 15, false);
	datatypes::Hitbox hbSave(datatypes::Point(165, 200), 45, 15, false);

	auto nameLbl = std::make_shared<uicomponents::Label>(namePt, "Name: ", font, white);
	auto upLbl = std::make_shared<uicomponents::Label>(upPt, "Up Key: ", font, white);
	auto downLbl = std::make_shared<uicomponents::Label>(downPt, "Down Key: ", font, white);
	auto leftLbl = std::make_shared<uicomponents::Label>(leftPt, "Left Key: ", font, white);
	auto rightLbl = std::make_shared<uicomponents::Label>(rightPt, "Right Key: ", font, white);
	auto lightLbl = std::make_shared<uicomponents::Label>(lightPt, "Light Attack: ", font, white);
	auto heavyLbl = std::make_shared<uicomponents::Label>(heavyPt, "Heavy Attack: ", font, white);
	auto jumpLbl = std::make_shared<uicomponents::Label>(jumpPt, "Jump Key: ", font, white);
	auto blockLbl = std::make_shared<uicomponents::Label>(blockPt, "Block Key: ", font, white);

	auto nameTbx = createTextbox(hbName, TEXTBOX_PATH, FOCUSED_TEXTBOX_PATH, 8);
	auto upTbx = createTextbox(hbUp, TEXTBOX_PATH, FOCUSED_TEXTBOX_PATH, 8);
	auto downTbx = createTextbox(hbDown, TEXTBOX_PATH, FOCUSED_TEXTBOX_PATH, 8);
	auto leftTbx = createTextbox(hbLeft, TEXTBOX_PATH, FOCUSED_TEXTBOX_PATH, 8);
	auto rightTbx = createTextbox(hbRight, TEXTBOX_PATH, FOCUSED_TEXTBOX_PATH, 8);
	auto lightTbx = createTextbox(hbLight, TEXTBOX_PATH, FOCUSED_TEXTBOX_PATH, 8);
	auto heavyTbx = createTextbox(hbHeavy, TEXTBOX_PATH, FOCUSED_TEXTBOX_PATH, 8);
	auto jumpTbx = createTextbox(hbJump, TEXTBOX_PATH, FOCUSED_TEXTBOX_PATH, 8);
	auto blockTbx = createTextbox(hbBlock, TEXTBOX_PATH, FOCUSED_TEXTBOX_PATH, 8);

	auto returnBtnPE = createButton(hbReturnPE, "", RETURN_BTN_PATH, FOCUSED_RETURN_BTN_PATH, changeSceneToMain);
	auto resetBtn = createButton(hbReset, "Reset", BUTTON_PATH, FOCUSED_BUTTON_PATH, resetTextboxes);
	auto importBtn = createButton(hbImport, "Import", BUTTON_PATH, FOCUSED_BUTTON_PATH, importProfile);
	auto removeBtn = createButton(hbRemove, "Remove", BUTTON_PATH, FOCUSED_BUTTON_PATH, removeProfile);
	auto saveBtn = createButton(hbSave, "Save", BUTTON_PATH, FOCUSED_BUTTON_PATH, saveProfile);

	auto profileEditorPane = new uicomponents::Pane(window, {returnBtnPE,
															 nameLbl, upLbl, downLbl, leftLbl, rightLbl, lightLbl, heavyLbl, jumpLbl, blockLbl,
															 nameTbx, upTbx, downTbx, leftTbx, rightTbx, lightTbx, heavyTbx, jumpTbx, blockTbx,
															 resetBtn, importBtn, removeBtn, saveBtn});

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

	auto returnBtnS = createButton(hbReturnS, "", RETURN_BTN_PATH, FOCUSED_RETURN_BTN_PATH, changeSceneToMain);

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
