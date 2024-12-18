#include "Implementation/sceneLoader.h"

#include "Implementation/profileHandler.h"

#include "Ichi/Audio/audioPlayer.h"

#include "Implementation/character.h"
#include "Implementation/ground.h"

#include "Ichi/DataTypes/hitbox.h"
#include "Ichi/Core/engine.h"

#include "Ichi/log.h"

datatypes::Hitbox SceneLoader::window = datatypes::Hitbox(datatypes::Point(0, 0), 384, 224, false);
TTF_Font *SceneLoader::font = nullptr;

bool SceneLoader::init()
{
    font = TTF_OpenFont(FONT_PATH.c_str(), 8);

    if (!ProfileHandler::init())
    {
        ICHI_ERROR("Could not read from profile text file")
        return false;
    }

    createPopUpMenu();
    createMainMenu();
    createLocalPlayMenu();
    createTrainingMenu();
    createProfileEditorMenu();
    createSettingMenu();
    createDojo();

    scene::sceneManager::setActiveScene(static_cast<int>(SceneName::MAIN));

    return font;
}

void SceneLoader::changeSceneToMain() { ichi::scene::sceneManager::setActiveScene(static_cast<int>(SceneName::MAIN)); }

void SceneLoader::changeSceneToLocalPlayCharacterSelection()
{
    scene::sceneManager::setActiveScene(static_cast<int>(SceneName::LOCAL_PLAY_CHARACTER_SELECTION));
    for (auto c : scene::sceneManager::getActiveScene()->getComponents())
        if (auto ptr = std::dynamic_pointer_cast<uicomponents::Pane>(c))
            for (auto ui : ptr->getUIComponents())
                if (auto ptr2 = dynamic_cast<uicomponents::DropDownMenu *>(ui.second.get()))
                    ptr2->updateItems(ProfileHandler::getNames());
}

void SceneLoader::changeSceneToTrainingCharacterSelection()
{
    scene::sceneManager::setActiveScene(static_cast<int>(SceneName::TRAINING_CHARACTER_SELECTION));
    for (auto c : scene::sceneManager::getActiveScene()->getComponents())
        if (auto ptr = std::dynamic_pointer_cast<uicomponents::Pane>(c))
            for (auto ui : ptr->getUIComponents())
                if (auto ptr2 = dynamic_cast<uicomponents::DropDownMenu *>(ui.second.get()))
                    ptr2->updateItems(ProfileHandler::getNames());
}

void SceneLoader::changeSceneToProfileEditor()
{
    scene::sceneManager::setActiveScene(static_cast<int>(SceneName::PROFILE_EDITOR));
}

void SceneLoader::changeSceneToSettings()
{
    scene::sceneManager::setActiveScene(static_cast<int>(SceneName::SETTINGS));
}

void SceneLoader::changeSceneToDojo()
{
    std::string profile;
    for (auto c : scene::sceneManager::getActiveScene()->getComponents())
        if (auto ptr = std::dynamic_pointer_cast<uicomponents::Pane>(c))
            for (auto ui : ptr->getUIComponents())
                if (auto ptr2 = dynamic_cast<uicomponents::DropDownMenu *>(ui.second.get()))
                    profile = ptr2->getSelected();
    if (ProfileHandler::getProfile(profile) == nullptr)
    {
        ICHI_ERROR("Could not find profile: {}", profile)
        return;
    }
    // Create character with ProfileHandler::getProfile(profile)
    scene::sceneManager::setActiveScene(static_cast<int>(SceneName::DOJO));
}

std::shared_ptr<uicomponents::Button> SceneLoader::createButton(datatypes::Hitbox &hitbox, const std::string &label, const std::string &spritePath, const std::string &focusedSpritePath, const std::function<void()> &onClick)
{
    graphics::Sprite defaultSprite(hitbox, UI_LAYER, spritePath);
    graphics::Sprite focusedSprite(hitbox, UI_LAYER, focusedSpritePath);

    return std::make_shared<uicomponents::Button>(hitbox, label, font, black, defaultSprite, focusedSprite, onClick);
}

std::shared_ptr<uicomponents::DropDownMenu> SceneLoader::createMenu(datatypes::Hitbox &hitbox, const std::vector<std::string> &items, const std::string &spritePath, const std::string &focusedSpritePath, const std::string &itemPath)
{
    graphics::Sprite defaultSprite(hitbox, UI_LAYER, spritePath);
    graphics::Sprite focusedSprite(hitbox, UI_LAYER, focusedSpritePath);
    graphics::Sprite itemSprite(hitbox, UI_LAYER, itemPath);

    return std::make_shared<uicomponents::DropDownMenu>(hitbox, items, font, black, defaultSprite, focusedSprite, itemSprite);
}

std::shared_ptr<uicomponents::Textbox> SceneLoader::createTextbox(datatypes::Hitbox &hb, const std::string &s, const std::string &fs, int cap)
{
    graphics::Sprite defaultSprite(hb, UI_LAYER, s);
    graphics::Sprite focusedSprite(hb, UI_LAYER, fs);

    return std::make_shared<uicomponents::Textbox>(hb, font, black, defaultSprite, focusedSprite, cap);
}

std::shared_ptr<uicomponents::SlideBar> SceneLoader::createSlideBar(datatypes::Hitbox &hb, const std::string &bar, int sliderWidth, int sliderHeight, const std::string &slider, const std::string &focusedSlider, std::function<void(float)> ptr)
{
    graphics::Sprite sprite(hb, UI_LAYER, bar);

    return std::make_shared<uicomponents::SlideBar>(hb, sprite, sliderWidth, sliderHeight, slider, focusedSlider, ptr);
}

void SceneLoader::quitGame()
{
    core::Engine::getInstance()->quit();
}

void SceneLoader::resetTextboxes()
{
    ICHI_TRACE("RESET")
    for (auto c : scene::sceneManager::getActiveScene()->getComponents())
    {
        if (auto ptr = std::dynamic_pointer_cast<uicomponents::Pane>(c))
            for (auto ui : ptr->getUIComponents())
                if (auto ptr2 = dynamic_cast<uicomponents::Textbox *>(ui.second.get()))
                    ptr2->clear();
        if (auto ptr = std::dynamic_pointer_cast<uicomponents::Textbox>(c))
            ptr->clear();
    }
}

void SceneLoader::importProfile()
{
    ICHI_TRACE("IMPORT")
    for (auto c : scene::sceneManager::getActiveScene()->getComponents())
        if (auto ptr = std::dynamic_pointer_cast<uicomponents::Pane>(c))
        {
            const Profile *profile = nullptr;

            if (auto tbPtr = dynamic_cast<uicomponents::Textbox *>(ptr->getUIComponents().at(hbName.getPos()).get()))
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

void SceneLoader::removeProfile()
{
    ICHI_TRACE("REMOVE")
    for (auto c : scene::sceneManager::getActiveScene()->getComponents())
        if (auto ptr = std::dynamic_pointer_cast<uicomponents::Pane>(c))
            for (auto ui : ptr->getUIComponents())
                if (auto ptr2 = dynamic_cast<uicomponents::Textbox *>(ui.second.get()))
                {
                    if (ui.first != hbName.getPos())
                        continue;
                    ProfileHandler::removeProfile(ptr2->getText());
                    return;
                }
}

void SceneLoader::saveProfile()
{
    ICHI_TRACE("SAVE")
    std::vector<std::string> strings;
    bool isChecked = false;
    for (auto c : scene::sceneManager::getActiveScene()->getComponents())
    {
        if (auto ptr = std::dynamic_pointer_cast<uicomponents::Pane>(c))
            for (auto ui : ptr->getUIComponents())
                if (auto ptr2 = dynamic_cast<uicomponents::Textbox *>(ui.second.get()))
                    strings.push_back(ptr2->getText());

        if (auto ptr = std::dynamic_pointer_cast<uicomponents::Textbox>(c))
            strings.push_back(ptr->getText());

        if (auto ptr = std::dynamic_pointer_cast<uicomponents::Checkbox>(c))
            isChecked = ptr->isChecked();
    }

    ProfileHandler::saveProfile(strings, isChecked);
}

datatypes::Hitbox popUpWindowHB(datatypes::Point(122, 50), 110, 140, false);
datatypes::Hitbox returnToMainMenuHB(datatypes::Point(142, 150), 70, 20, false);

void SceneLoader::createPopUpMenu()
{

    graphics::Sprite popUpWindowSprite(popUpWindowHB, UI_LAYER, POP_UP_MENU_PATH);
    graphics::Sprite popUpBackground(window, UI_LAYER, TRANSPARENT_BLACK_PATH);

    auto returnToMainMenuBtn = createButton(returnToMainMenuHB, "Main Menu", BUTTON_PATH, FOCUSED_BUTTON_PATH, changeSceneToMain);

    auto popUp = std::make_shared<scene::PopUpMenu>(std::vector<std::shared_ptr<uicomponents::UIComponent>>{returnToMainMenuBtn}, popUpBackground, popUpWindowSprite);

    scene::sceneManager::setPopUpMenu(popUp);
}

datatypes::Hitbox hbLocalPlay(datatypes::Point(50, 60), 75, 20, false);
datatypes::Hitbox hbTraining(datatypes::Point(50, 90), 75, 20, false);
datatypes::Hitbox hbProfileEditor(datatypes::Point(50, 120), 75, 20, false);
datatypes::Hitbox hbSettings(datatypes::Point(50, 150), 75, 20, false);
datatypes::Hitbox hbExit(datatypes::Point(50, 180), 75, 20, false);

void SceneLoader::createMainMenu()
{

    auto darkBlueBackgroundMain = std::make_shared<graphics::Sprite>(window, BACKGROUND_LAYER, DARK_BLUE_SCREEN_PATH);

    auto localPlay = createButton(hbLocalPlay, "Local Play", BUTTON_PATH, FOCUSED_BUTTON_PATH, changeSceneToLocalPlayCharacterSelection);
    auto training = createButton(hbTraining, "Training", BUTTON_PATH, FOCUSED_BUTTON_PATH, changeSceneToTrainingCharacterSelection);
    auto profileEditor = createButton(hbProfileEditor, "Profile Editor", BUTTON_PATH, FOCUSED_BUTTON_PATH, changeSceneToProfileEditor);
    auto settings = createButton(hbSettings, "Settings", BUTTON_PATH, FOCUSED_BUTTON_PATH, changeSceneToSettings);
    auto exit = createButton(hbExit, "Exit game", BUTTON_PATH, FOCUSED_BUTTON_PATH, quitGame);

    auto mainPane = std::make_shared<uicomponents::Pane>(window, std::vector<std::shared_ptr<uicomponents::UIComponent>>{localPlay, training, profileEditor, settings, exit});

    std::shared_ptr<scene::Scene> mainScene = std::make_shared<scene::Scene>(
        darkBlueBackgroundMain,
        std::vector<std::shared_ptr<core::Component>>{std::shared_ptr<core::Component>(mainPane)},
        false);

    scene::sceneManager::addScene(static_cast<int>(SceneName::MAIN), mainScene);
}

datatypes::Hitbox hbReturnLP(datatypes::Point(0, 0), 30, 30, false);
datatypes::Hitbox hbBluePlayerMenu(datatypes::Point(30, 180), 50, 15, false);
datatypes::Hitbox hbRedPlayerMenu(datatypes::Point(220, 180), 50, 15, false);

void SceneLoader::createLocalPlayMenu()
{

    auto returnBtnLP = createButton(hbReturnLP, "", RETURN_BTN_PATH, FOCUSED_RETURN_BTN_PATH, changeSceneToMain);
    auto redMenu = createMenu(hbRedPlayerMenu, {"TestRed"}, DROP_DOWN_MENU_PATH, FOCUSED_DROP_DOWN_MENU_PATH, ITEM_PATH);
    auto blueMenu = createMenu(hbBluePlayerMenu, {"TestBlue"}, DROP_DOWN_MENU_PATH, FOCUSED_DROP_DOWN_MENU_PATH, ITEM_PATH);

    auto characterSelectionBackground = std::make_shared<graphics::Sprite>(window, BACKGROUND_LAYER, CHARACTER_SELECTION_PATH);

    auto characterPane = std::make_shared<uicomponents::Pane>(window, std::vector<std::shared_ptr<uicomponents::UIComponent>>{returnBtnLP, redMenu, blueMenu});

    std::shared_ptr<scene::Scene> characterSelectionScene = std::make_shared<scene::Scene>(
        characterSelectionBackground,
        std::vector<std::shared_ptr<core::Component>>{std::shared_ptr<core::Component>(characterPane)},
        false);

    scene::sceneManager::addScene(static_cast<int>(SceneName::LOCAL_PLAY_CHARACTER_SELECTION), characterSelectionScene);
}

datatypes::Hitbox hbStartTraining(datatypes::Point(160, 110), 70, 15, false);
datatypes::Hitbox hbReturnT(datatypes::Point(0, 0), 30, 30, false);

void SceneLoader::createTrainingMenu()
{

    auto returnBtnT = createButton(hbReturnT, "", RETURN_BTN_PATH, FOCUSED_RETURN_BTN_PATH, changeSceneToMain);
    auto startTrainingBtn = createButton(hbStartTraining, "Start", BUTTON_PATH, FOCUSED_BUTTON_PATH, changeSceneToDojo);
    auto playerMenu = createMenu(hbBluePlayerMenu, {"TestBlue"}, DROP_DOWN_MENU_PATH, FOCUSED_DROP_DOWN_MENU_PATH, ITEM_PATH);

    auto trainingPane = std::make_shared<uicomponents::Pane>(window, std::vector<std::shared_ptr<uicomponents::UIComponent>>{returnBtnT, playerMenu, startTrainingBtn});

    auto trainingSelcetion = std::make_shared<graphics::Sprite>(window, BACKGROUND_LAYER, TRAINING_SELECTION_PATH);

    std::shared_ptr<scene::Scene> trainingSelectionScene = std::make_shared<scene::Scene>(
        trainingSelcetion,
        std::vector<std::shared_ptr<core::Component>>{std::shared_ptr<core::Component>(trainingPane)},
        false);

    scene::sceneManager::addScene(static_cast<int>(SceneName::TRAINING_CHARACTER_SELECTION), trainingSelectionScene);
}

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

datatypes::Hitbox SceneLoader::hbName(datatypes::Point(150, namePt.Y), 70, 10, false);
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

void SceneLoader::createProfileEditorMenu()
{

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

    auto profileEditorPane = std::make_shared<uicomponents::Pane>(window,
                                                                  std::vector<std::shared_ptr<uicomponents::UIComponent>>{
                                                                      returnBtnPE,
                                                                      nameLbl, upLbl, downLbl, leftLbl, rightLbl, lightLbl, heavyLbl, jumpLbl, blockLbl,
                                                                      nameTbx, upTbx, downTbx, leftTbx, rightTbx, lightTbx, heavyTbx, jumpTbx, blockTbx,
                                                                      resetBtn, importBtn, removeBtn, saveBtn});

    auto darkBlueBackgroundPE = std::make_shared<graphics::Sprite>(window, BACKGROUND_LAYER, DARK_BLUE_SCREEN_PATH);

    std::shared_ptr<scene::Scene> profileEditorScene = std::make_shared<scene::Scene>(
        darkBlueBackgroundPE,
        std::vector<std::shared_ptr<core::Component>>{std::shared_ptr<core::Component>(profileEditorPane)},
        false);

    scene::sceneManager::addScene(static_cast<int>(SceneName::PROFILE_EDITOR), profileEditorScene);
}

datatypes::Hitbox hbReturnS(datatypes::Point(0, 0), 30, 30, false);
datatypes::Hitbox sliderHb(datatypes::Point(120, 50), 70, 15, false);

void SceneLoader::createSettingMenu()
{

    auto returnBtnS = createButton(hbReturnS, "", RETURN_BTN_PATH, FOCUSED_RETURN_BTN_PATH, changeSceneToMain);
    auto volumeSlider = createSlideBar(sliderHb, BAR_PATH, 5, 20, SLIDER_PATH, FOCUSED_SLIDER_PATH, audio::AudioPlayer::setVolume);

    auto pane = std::make_shared<uicomponents::Pane>(window, std::vector<std::shared_ptr<uicomponents::UIComponent>>{returnBtnS, volumeSlider});

    auto darkBlueBackgroundS = std::make_shared<graphics::Sprite>(window, BACKGROUND_LAYER, DARK_BLUE_SCREEN_PATH);

    std::shared_ptr<scene::Scene> settingScene = std::make_shared<scene::Scene>(
        darkBlueBackgroundS,
        std::vector<std::shared_ptr<core::Component>>{std::shared_ptr<core::Component>(pane)},
        false);

    scene::sceneManager::addScene(static_cast<int>(SceneName::SETTINGS), settingScene);
}

datatypes::Hitbox hbReturnD(datatypes::Point(0, 0), 30, 30, false);
ichi::datatypes::Hitbox robotHitbox(datatypes::Point(0, 0), 120, 120, true);
ichi::datatypes::Hitbox groundHitbox(datatypes::Point(0, 200), WINDOW_WIDTH, WINDOW_HEIGHT, true); // coords and w/h should be approximately at bottom of screen

void SceneLoader::createDojo()
{

    graphics::Sprite returnSpriteD(hbReturnD, UI_LAYER, RETURN_BTN_PATH);
    graphics::Sprite focusedReturnSpriteD(hbReturnD, UI_LAYER, FOCUSED_RETURN_BTN_PATH);

    std::shared_ptr<uicomponents::Button> returnBtnD = std::make_shared<uicomponents::Button>(hbReturnD, "", font, black, returnSpriteD, focusedReturnSpriteD, changeSceneToMain);

    auto dojoBackground = std::make_shared<graphics::Sprite>(window, BACKGROUND_LAYER, DOJO_PATH);

    std::shared_ptr<scene::Scene> dojoScene = std::make_shared<scene::Scene>(dojoBackground, std::vector<std::shared_ptr<core::Component>>{}, true);

    scene::sceneManager::addScene(static_cast<int>(SceneName::DOJO), dojoScene);

    // robot
    std::vector<std::string> paths = {ROBOT_PATH0, ROBOT_PATH1, ROBOT_PATH2, ROBOT_PATH3};

    std::shared_ptr<ichi::graphics::AnimatedSprite> animation = std::make_shared<ichi::graphics::AnimatedSprite>(
        robotHitbox, FOREGROUND_LAYER, paths, std::map<int, Uint32>{{0, 200}, {1, 200}, {2, 200}, {3, 200}});

    std::shared_ptr<Character> robot = std::make_shared<Character>(
        robotHitbox, 120, 2, 3, animation, false);

    dojoScene->addComponent(robot);

    // ground "hidden under dojo"
    std::string path = BAR_PATH; // just some random img
    std::shared_ptr<ichi::graphics::Sprite> sprite = std::make_shared<ichi::graphics::Sprite>(groundHitbox, UI_LAYER, path);
    std::shared_ptr<Ground> dojoGround = std::make_shared<Ground>(groundHitbox);
    dojoScene->addComponent(dojoGround);
}