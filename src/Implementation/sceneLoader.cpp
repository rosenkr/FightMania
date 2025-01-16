#include "Implementation/sceneLoader.h"
#include "Implementation/profileHandler.h"
#include "Implementation/match.h"
#include "Implementation/projectileAttack.h"
#include "Implementation/meleeAttack.h"

#include "Ichi/Audio/audioPlayer.h"

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
    createCyberPunk();

    scene::sceneManager::setActiveScene(static_cast<int>(SceneName::MAIN));

    return font;
}

void SceneLoader::changeSceneToMain()
{
    if (ichi::scene::sceneManager::getActiveScene()->isPausable())
    {
        ichi::scene::sceneManager::getActiveScene()->setPaused(false);
        for (auto c : scene::sceneManager::getActiveScene()->getComponents())
            if (auto ptr = std::dynamic_pointer_cast<Match>(c))
                scene::sceneManager::getActiveScene()->removeComponent(ptr.get());
    }

    ichi::scene::sceneManager::setActiveScene(static_cast<int>(SceneName::MAIN));
}

void SceneLoader::changeSceneToLocalPlayCharacterSelection()
{
    scene::sceneManager::setActiveScene(static_cast<int>(SceneName::LOCAL_PLAY_CHARACTER_SELECTION));
    if (auto ptr = dynamic_cast<uicomponents::DropDownMenu *>(scene::sceneManager::getActiveScene()->getComponent(blueProfileDropdownHB.getPos())))
        ptr->updateItems(ProfileHandler::getNames());
    if (auto ptr = dynamic_cast<uicomponents::DropDownMenu *>(scene::sceneManager::getActiveScene()->getComponent(redProfileDropdownHB.getPos())))
        ptr->updateItems(ProfileHandler::getNames());
}

void SceneLoader::changeSceneToTrainingCharacterSelection()
{
    scene::sceneManager::setActiveScene(static_cast<int>(SceneName::TRAINING_CHARACTER_SELECTION));
    if (auto ptr = dynamic_cast<uicomponents::DropDownMenu *>(scene::sceneManager::getActiveScene()->getComponent(blueProfileDropdownHB.getPos())))
        ptr->updateItems(ProfileHandler::getNames());
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
    std::string blueProfile;
    if (auto ptr = dynamic_cast<const uicomponents::DropDownMenu *>(scene::sceneManager::getActiveScene()->getComponent(blueProfileDropdownHB.getPos())))
        blueProfile = ptr->getSelected();

    if (ProfileHandler::getProfile(blueProfile) == nullptr)
    {
        ICHI_ERROR("Could not find profile: {}", blueProfile)
        return;
    }
    std::shared_ptr<Character> blueCharacter;
    std::shared_ptr<Character> dummy;

    int controllerID = -1;
    if (ProfileHandler::getProfile(blueProfile)->isController())
    {
        if (input::ControllerHandler::getActiveControllerIDs().size() == 0)
        {
            ICHI_ERROR("Could not find any controllers to use");
            return;
        }
        else
            controllerID = input::ControllerHandler::getActiveControllerIDs().at(0);
    }

    if (auto ptr = dynamic_cast<uicomponents::DropDownMenu *>(scene::sceneManager::getActiveScene()->getComponent(blueCharacterDropdownHB.getPos())))
    {
        if (ptr->getSelected() == KENNY)
            blueCharacter = createKenny(ProfileHandler::getProfile(blueProfile), controllerID, true);
    }

    // placeholder for the dummy
    dummy = createKenny(ProfileHandler::getProfile(blueProfile), controllerID, false);

    if (blueCharacter == nullptr || dummy == nullptr)
    {
        ICHI_ERROR("You have not selected a correct character")
        return;
    }

    auto m = std::make_shared<Match>(blueCharacter, dummy, font);

    scene::sceneManager::setActiveScene(static_cast<int>(SceneName::DOJO));
    scene::sceneManager::getActiveScene()->addComponent(m);
}

void SceneLoader::changeSceneToCyberPunk()
{
    std::string blueProfile;
    if (auto ptr = dynamic_cast<const uicomponents::DropDownMenu *>(scene::sceneManager::getActiveScene()->getComponent(blueProfileDropdownHB.getPos())))
        blueProfile = ptr->getSelected();
    std::string redProfile;
    if (auto ptr = dynamic_cast<const uicomponents::DropDownMenu *>(scene::sceneManager::getActiveScene()->getComponent(redProfileDropdownHB.getPos())))
        redProfile = ptr->getSelected();

    if (ProfileHandler::getProfile(blueProfile) == nullptr)
    {
        ICHI_ERROR("Could not find profile: {}", blueProfile)
        return;
    }
    if (ProfileHandler::getProfile(redProfile) == nullptr)
    {
        ICHI_ERROR("Could not find profile: {}", redProfile)
        return;
    }

    std::shared_ptr<Character> blueCharacter;
    std::shared_ptr<Character> redCharacter;

    int blueID = -1;
    int redID = -1;
    size_t controllerAmount = ProfileHandler::getProfile(blueProfile)->isController() + ProfileHandler::getProfile(redProfile)->isController();
    if (input::ControllerHandler::getActiveControllerIDs().size() < controllerAmount)
    {
        ICHI_ERROR("Not enough controllers available. Required: {}, Active: {}", controllerAmount, input::ControllerHandler::getActiveControllerIDs().size());
        return;
    }
    int i = 0;
    if (ProfileHandler::getProfile(blueProfile)->isController())
        blueID = input::ControllerHandler::getActiveControllerIDs().at(i++);

    if (ProfileHandler::getProfile(redProfile)->isController())
        redID = input::ControllerHandler::getActiveControllerIDs().at(i);

    if (auto ptr = dynamic_cast<uicomponents::DropDownMenu *>(scene::sceneManager::getActiveScene()->getComponent(blueCharacterDropdownHB.getPos())))
    {
        if (ptr->getSelected() == KENNY)
            blueCharacter = createKenny(ProfileHandler::getProfile(blueProfile), blueID, true);
    }

    if (auto ptr = dynamic_cast<uicomponents::DropDownMenu *>(scene::sceneManager::getActiveScene()->getComponent(redCharacterDropdownHB.getPos())))
    {
        if (ptr->getSelected() == KENNY)
            redCharacter = createKenny(ProfileHandler::getProfile(redProfile), redID, false);
    }

    if (blueCharacter == nullptr || redCharacter == nullptr)
    {
        ICHI_ERROR("You have not selected a correct character")
        return;
    }

    auto m = std::make_shared<Match>(blueCharacter, redCharacter, font);

    scene::sceneManager::setActiveScene(static_cast<int>(SceneName::CYBER_PUNK));
    scene::sceneManager::getActiveScene()->addComponent(m);
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

std::shared_ptr<uicomponents::Checkbox> SceneLoader::createCheckbox(datatypes::Hitbox &hb)
{
    graphics::Sprite defaultSprite(hb, UI_LAYER, CHECKBOX_PATH);
    graphics::Sprite focusedSprite(hb, UI_LAYER, FOCUSED_Checkbox_PATH);

    graphics::Sprite defaultCheckedSprite(hb, UI_LAYER, CHECKED_CHECKBOX_PATH);
    graphics::Sprite focusedCheckedSprite(hb, UI_LAYER, FOCUSED_Checked_Checkbox_PATH);

    return std::make_shared<uicomponents::Checkbox>(hb, focusedSprite, focusedCheckedSprite, defaultSprite, defaultCheckedSprite);
}

std::shared_ptr<uicomponents::SlideBar> SceneLoader::createSlideBar(datatypes::Hitbox &hb, const std::string &bar, int sliderWidth, int sliderHeight, const std::string &slider, const std::string &focusedSlider, std::function<void(float)> ptr)
{
    graphics::Sprite sprite(hb, UI_LAYER, bar);

    return std::make_shared<uicomponents::SlideBar>(hb, sprite, sliderWidth, sliderHeight, slider, focusedSlider, ptr);
}

std::shared_ptr<Character> SceneLoader::createKenny(const Profile *p, int controllerID, bool facingRight)
{
    datatypes::Hitbox slash(datatypes::Point(0, 0), 35, 70, false);
    datatypes::Hitbox hb(datatypes::Point(50, 50), 180, 120, false);

    std::map<int, ichi::datatypes::Hitbox> sideLigthHitboxes = {
        {0, ichi::datatypes::Hitbox(ichi::datatypes::Point(23, 38), 60, 25, false)},
        {1, ichi::datatypes::Hitbox(ichi::datatypes::Point(14, 40), 60, 25, false)},
    };

    std::map<int, ichi::datatypes::Hitbox> downLightHitboxes = {
        {0, ichi::datatypes::Hitbox(ichi::datatypes::Point(0, 0), 0, 0, false)},
        {1, ichi::datatypes::Hitbox(ichi::datatypes::Point(0, 0), 0, 0, false)},
        {2, ichi::datatypes::Hitbox(ichi::datatypes::Point(19, 54), 65, 45, false)},
        {3, ichi::datatypes::Hitbox(ichi::datatypes::Point(15, 18), 65, 50, false)},
    };

    std::map<int, ichi::datatypes::Hitbox> sideHeavyHitboxes = {
        {0, ichi::datatypes::Hitbox(ichi::datatypes::Point(0, 0), 0, 0, false)},
        {1, ichi::datatypes::Hitbox(ichi::datatypes::Point(0, 0), 0, 0, false)},
        {2, ichi::datatypes::Hitbox(ichi::datatypes::Point(45, 0), 90, 50, false)},
        {3, ichi::datatypes::Hitbox(ichi::datatypes::Point(26, 27), 64, 45, false)},
        {4, ichi::datatypes::Hitbox(ichi::datatypes::Point(26, 59), 58, 15, false)},
        {5, ichi::datatypes::Hitbox(ichi::datatypes::Point(0, 0), 0, 0, false)},
        {6, ichi::datatypes::Hitbox(ichi::datatypes::Point(0, 0), 0, 0, false)},
    };

    if (!facingRight)
        hb.setX(250);

    auto stunnedLeftAnimation = std::make_shared<ichi::graphics::AnimatedSprite>(hb, FOREGROUND_LAYER, KENNY_STUNNED_LEFT, SINGLE_FRAME_TIME.size(), SINGLE_FRAME_TIME);
    auto stunnedRightAnimation = std::make_shared<ichi::graphics::AnimatedSprite>(hb, FOREGROUND_LAYER, KENNY_STUNNED_RIGHT, SINGLE_FRAME_TIME.size(), SINGLE_FRAME_TIME);

    auto blockLeftAnimation = std::make_shared<ichi::graphics::AnimatedSprite>(hb, FOREGROUND_LAYER, KENNY_BLOCK_LEFT, SINGLE_FRAME_TIME.size(), SINGLE_FRAME_TIME);
    auto blockRightAnimation = std::make_shared<ichi::graphics::AnimatedSprite>(hb, FOREGROUND_LAYER, KENNY_BLOCK_RIGHT, SINGLE_FRAME_TIME.size(), SINGLE_FRAME_TIME);

    auto walkLeftAnimation = std::make_shared<ichi::graphics::AnimatedSprite>(hb, FOREGROUND_LAYER, KENNY_WALK_LEFT, KENNY_WALK_TIME.size(), KENNY_WALK_TIME);
    auto walkRightAnimation = std::make_shared<ichi::graphics::AnimatedSprite>(hb, FOREGROUND_LAYER, KENNY_WALK_RIGHT, KENNY_WALK_TIME.size(), KENNY_WALK_TIME);

    auto idleLeftAnimation = std::make_shared<ichi::graphics::AnimatedSprite>(hb, FOREGROUND_LAYER, KENNY_IDLE_LEFT, KENNY_IDLE_TIME.size(), KENNY_IDLE_TIME);
    auto idleRightAnimation = std::make_shared<ichi::graphics::AnimatedSprite>(hb, FOREGROUND_LAYER, KENNY_IDLE_RIGHT, KENNY_IDLE_TIME.size(), KENNY_IDLE_TIME);

    auto fallingLeftAnimation = std::make_shared<ichi::graphics::AnimatedSprite>(hb, FOREGROUND_LAYER, KENNY_FALLING_LEFT, SINGLE_FRAME_TIME.size(), SINGLE_FRAME_TIME);
    auto fallingRightAnimation = std::make_shared<ichi::graphics::AnimatedSprite>(hb, FOREGROUND_LAYER, KENNY_FALLING_RIGHT, SINGLE_FRAME_TIME.size(), SINGLE_FRAME_TIME);

    auto jumpingLeftAnimation = std::make_shared<ichi::graphics::AnimatedSprite>(hb, FOREGROUND_LAYER, KENNY_JUMPING_LEFT, SINGLE_FRAME_TIME.size(), SINGLE_FRAME_TIME);
    auto jumpingRightAnimation = std::make_shared<ichi::graphics::AnimatedSprite>(hb, FOREGROUND_LAYER, KENNY_JUMPING_RIGHT, SINGLE_FRAME_TIME.size(), SINGLE_FRAME_TIME);

    std::map<Character::AnimationState, std::shared_ptr<graphics::AnimatedSprite>> animations = {
        {Character::AnimationState::LEFT_STUNNED, stunnedLeftAnimation},
        {Character::AnimationState::LEFT_BLOCKING, blockLeftAnimation},
        {Character::AnimationState::LEFT_WALKING, walkLeftAnimation},
        {Character::AnimationState::LEFT_IDLE, idleLeftAnimation},
        {Character::AnimationState::LEFT_FALLING, fallingLeftAnimation},
        {Character::AnimationState::LEFT_JUMPING, jumpingLeftAnimation},

        {Character::AnimationState::RIGHT_STUNNED, stunnedRightAnimation},
        {Character::AnimationState::RIGHT_BLOCKING, blockRightAnimation},
        {Character::AnimationState::RIGHT_WALKING, walkRightAnimation},
        {Character::AnimationState::RIGHT_IDLE, idleRightAnimation},
        {Character::AnimationState::RIGHT_FALLING, fallingRightAnimation},
        {Character::AnimationState::RIGHT_JUMPING, jumpingRightAnimation},
    };

    auto leftSideLightAnimation = std::make_shared<ichi::graphics::AnimatedSprite>(hb, FOREGROUND_LAYER, KENNY_SIDE_LIGHT_LEFT, KENNY_SIDE_LIGHT_TIME.size(), KENNY_SIDE_LIGHT_TIME);
    auto leftDownLightAnimation = std::make_shared<ichi::graphics::AnimatedSprite>(hb, FOREGROUND_LAYER, KENNY_DOWN_LIGHT_LEFT, KENNY_DOWN_LIGHT_TIME.size(), KENNY_DOWN_LIGHT_TIME);
    auto leftNeutralLightAnimation = std::make_shared<ichi::graphics::AnimatedSprite>(hb, FOREGROUND_LAYER, KENNY_SIDE_LIGHT_LEFT, KENNY_SIDE_LIGHT_TIME.size(), KENNY_SIDE_LIGHT_TIME);

    auto leftSideHeavyAnimation = std::make_shared<ichi::graphics::AnimatedSprite>(hb, FOREGROUND_LAYER, KENNY_SIDE_HEAVY_LEFT, KENNY_SIDE_HEAVY_TIME.size(), KENNY_SIDE_HEAVY_TIME);
    auto leftDownHeavyAnimation = std::make_shared<ichi::graphics::AnimatedSprite>(hb, FOREGROUND_LAYER, KENNY_SIDE_HEAVY_LEFT, KENNY_SIDE_HEAVY_TIME.size(), KENNY_SIDE_HEAVY_TIME);
    auto leftNeutralHeavyAnimation = std::make_shared<ichi::graphics::AnimatedSprite>(hb, FOREGROUND_LAYER, KENNY_NEUTRAL_HEAVY_LEFT, KENNY_NEUTRAL_HEAVY_TIME.size(), KENNY_NEUTRAL_HEAVY_TIME);

    auto rightSideLightAnimation = std::make_shared<ichi::graphics::AnimatedSprite>(hb, FOREGROUND_LAYER, KENNY_SIDE_LIGHT_RIGHT, KENNY_SIDE_LIGHT_TIME.size(), KENNY_SIDE_LIGHT_TIME);
    auto rightDownLightAnimation = std::make_shared<ichi::graphics::AnimatedSprite>(hb, FOREGROUND_LAYER, KENNY_DOWN_LIGHT_RIGHT, KENNY_DOWN_LIGHT_TIME.size(), KENNY_DOWN_LIGHT_TIME);
    auto rightNeutralLightAnimation = std::make_shared<ichi::graphics::AnimatedSprite>(hb, FOREGROUND_LAYER, KENNY_SIDE_LIGHT_RIGHT, KENNY_SIDE_LIGHT_TIME.size(), KENNY_SIDE_LIGHT_TIME);

    auto rightSideHeavyAnimation = std::make_shared<ichi::graphics::AnimatedSprite>(hb, FOREGROUND_LAYER, KENNY_SIDE_HEAVY_RIGHT, KENNY_SIDE_HEAVY_TIME.size(), KENNY_SIDE_HEAVY_TIME);
    auto rightDownHeavyAnimation = std::make_shared<ichi::graphics::AnimatedSprite>(hb, FOREGROUND_LAYER, KENNY_SIDE_HEAVY_RIGHT, KENNY_SIDE_HEAVY_TIME.size(), KENNY_SIDE_HEAVY_TIME);
    auto rightNeutralHeavyAnimation = std::make_shared<ichi::graphics::AnimatedSprite>(hb, FOREGROUND_LAYER, KENNY_NEUTRAL_HEAVY_RIGHT, KENNY_NEUTRAL_HEAVY_TIME.size(), KENNY_NEUTRAL_HEAVY_TIME);

    auto leftSwordSlash = std::make_shared<ichi::graphics::AnimatedSprite>(slash, FOREGROUND_LAYER, SWORD_SLASH_LEFT, SWORD_SLASH_TIME.size(), SWORD_SLASH_TIME);
    auto rightSwordSlash = std::make_shared<ichi::graphics::AnimatedSprite>(slash, FOREGROUND_LAYER, SWORD_SLASH_RIGHT, SWORD_SLASH_TIME.size(), SWORD_SLASH_TIME);

    auto sideLight = std::make_shared<MeleeAttack>(10, ichi::datatypes::Vector2D(2, 0), 1000, leftSideLightAnimation, rightSideLightAnimation, sideLigthHitboxes);
    auto downLight = std::make_shared<MeleeAttack>(10, ichi::datatypes::Vector2D(0, -8), 1000, leftDownLightAnimation, rightDownLightAnimation, downLightHitboxes);
    auto neutralLight = std::make_shared<MeleeAttack>(10, ichi::datatypes::Vector2D(1, 0), 1000, leftNeutralLightAnimation, rightNeutralLightAnimation, sideLigthHitboxes);

    auto sideHeavy = std::make_shared<MeleeAttack>(30, ichi::datatypes::Vector2D(3, -1), 1500, leftSideHeavyAnimation, rightSideHeavyAnimation, sideHeavyHitboxes);
    auto downHeavy = std::make_shared<ProjectileAttack>(leftSwordSlash, rightSwordSlash, leftNeutralHeavyAnimation, rightNeutralHeavyAnimation, 2, 20, ichi::datatypes::Vector2D(0, 0), 2000, 500);
    auto neutralHeavy = std::make_shared<ProjectileAttack>(leftSwordSlash, rightSwordSlash, leftNeutralHeavyAnimation, rightNeutralHeavyAnimation, 2, 10, ichi::datatypes::Vector2D(3, -2), 2000, 500);

    std::map<Character::AttackType, std::shared_ptr<Attack>> attacks = {
        {Character::AttackType::SIDE_LIGHT, sideLight},
        {Character::AttackType::SIDE_HEAVY, sideHeavy},

        {Character::AttackType::DOWN_LIGHT, downLight},
        {Character::AttackType::DOWN_HEAVY, downHeavy},

        {Character::AttackType::NEUTRAL_LIGHT, neutralLight},
        {Character::AttackType::NEUTRAL_HEAVY, neutralHeavy},
    };

    ichi::datatypes::Hitbox physicalHitbox = ichi::datatypes::Hitbox(hb.getPos() + ichi::datatypes::Point(32, 10), 50, 110, true);

    if (!facingRight)
    {
        physicalHitbox.setX(physicalHitbox.getX() + 100);
        physicalHitbox.setY(physicalHitbox.getX() + 10);
    }

    return std::make_shared<Character>(physicalHitbox, animations, p, attacks, facingRight, controllerID);
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
            {
                if (auto ptr2 = dynamic_cast<uicomponents::Textbox *>(ui.second.get()))
                    strings.push_back(ptr2->getText());
                if (auto ptr2 = dynamic_cast<uicomponents::Checkbox *>(ui.second.get()))
                    isChecked = ptr2->isChecked();
            }
    }

    ProfileHandler::saveProfile(strings, isChecked);
}

void SceneLoader::createPopUpMenu()
{
    datatypes::Hitbox popUpWindowHB(datatypes::Point(122, 50), 110, 140, false);
    datatypes::Hitbox returnToMainMenuHB(datatypes::Point(142, 150), 70, 20, false);
    datatypes::Point sliderLblPt(142, 100);
    datatypes::Hitbox sliderHb(datatypes::Point(142, 120), 70, 15, false);

    graphics::Sprite popUpWindowSprite(popUpWindowHB, UI_LAYER, POP_UP_MENU_PATH);
    graphics::Sprite popUpBackground(window, UI_LAYER, TRANSPARENT_BLACK_PATH);

    auto returnToMainMenuBtn = createButton(returnToMainMenuHB, "Main Menu", BUTTON_PATH, FOCUSED_BUTTON_PATH, changeSceneToMain);

    auto volumeSlider = createSlideBar(sliderHb, BAR_PATH, 5, 20, SLIDER_PATH, FOCUSED_SLIDER_PATH, audio::AudioPlayer::setVolume);

    auto volume = std::make_shared<uicomponents::Label>(sliderLblPt, "volume: ", font, white);

    auto pane = std::make_shared<uicomponents::Pane>(popUpWindowHB, std::vector<std::shared_ptr<uicomponents::UIComponent>>{volume, volumeSlider, returnToMainMenuBtn});

    auto popUp = std::make_shared<scene::PopUpMenu>(std::vector<std::shared_ptr<uicomponents::UIComponent>>{pane}, popUpBackground, popUpWindowSprite);

    scene::sceneManager::setPopUpMenu(popUp);
}

void SceneLoader::createMainMenu()
{
    datatypes::Hitbox hbLocalPlay(datatypes::Point(50, 60), 75, 20, false);
    datatypes::Hitbox hbTraining(datatypes::Point(50, 90), 75, 20, false);
    datatypes::Hitbox hbProfileEditor(datatypes::Point(50, 120), 75, 20, false);
    datatypes::Hitbox hbSettings(datatypes::Point(50, 150), 75, 20, false);
    datatypes::Hitbox hbExit(datatypes::Point(50, 180), 75, 20, false);

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

datatypes::Hitbox SceneLoader::returnHB(datatypes::Point(0, 0), 30, 30, false);
datatypes::Hitbox SceneLoader::blueProfileDropdownHB(datatypes::Point(30, 60), 50, 15, false);
datatypes::Hitbox SceneLoader::blueCharacterDropdownHB(datatypes::Point(30, 90), 50, 15, false);
datatypes::Hitbox SceneLoader::redProfileDropdownHB(datatypes::Point(220, 60), 50, 15, false);
datatypes::Hitbox SceneLoader::redCharacterDropdownHB(datatypes::Point(220, 90), 50, 15, false);

void SceneLoader::createLocalPlayMenu()
{
    datatypes::Hitbox startMatchHb(datatypes::Point(160, 110), 70, 15, false);

    auto returnBtn = createButton(returnHB, "", RETURN_BTN_PATH, FOCUSED_RETURN_BTN_PATH, changeSceneToMain);
    auto startMatchBtn = createButton(startMatchHb, "Start Match", BUTTON_PATH, FOCUSED_BUTTON_PATH, changeSceneToCyberPunk);

    auto redProfileMenu = createMenu(redProfileDropdownHB, {"TestRed"}, DROP_DOWN_MENU_PATH, FOCUSED_DROP_DOWN_MENU_PATH, ITEM_PATH);
    auto redCharacterMenu = createMenu(redCharacterDropdownHB, {KENNY}, DROP_DOWN_MENU_PATH, FOCUSED_DROP_DOWN_MENU_PATH, ITEM_PATH);
    auto blueProfileMenu = createMenu(blueProfileDropdownHB, {"TestBlue"}, DROP_DOWN_MENU_PATH, FOCUSED_DROP_DOWN_MENU_PATH, ITEM_PATH);
    auto blueCharacterMenu = createMenu(blueCharacterDropdownHB, {KENNY}, DROP_DOWN_MENU_PATH, FOCUSED_DROP_DOWN_MENU_PATH, ITEM_PATH);

    auto characterSelectionBackground = std::make_shared<graphics::Sprite>(window, BACKGROUND_LAYER, CHARACTER_SELECTION_PATH);

    auto characterPane = std::make_shared<uicomponents::Pane>(window, std::vector<std::shared_ptr<uicomponents::UIComponent>>{
                                                                          returnBtn, redProfileMenu, redCharacterMenu, blueProfileMenu, blueCharacterMenu, startMatchBtn});

    std::shared_ptr<scene::Scene> characterSelectionScene = std::make_shared<scene::Scene>(
        characterSelectionBackground,
        std::vector<std::shared_ptr<core::Component>>{std::shared_ptr<core::Component>(characterPane)},
        false);

    scene::sceneManager::addScene(static_cast<int>(SceneName::LOCAL_PLAY_CHARACTER_SELECTION), characterSelectionScene);
}

void SceneLoader::createTrainingMenu()
{
    datatypes::Hitbox hbStartTraining(datatypes::Point(160, 110), 70, 15, false);

    auto returnBtnT = createButton(returnHB, "", RETURN_BTN_PATH, FOCUSED_RETURN_BTN_PATH, changeSceneToMain);
    auto startTrainingBtn = createButton(hbStartTraining, "Start", BUTTON_PATH, FOCUSED_BUTTON_PATH, changeSceneToDojo);
    auto profileMenu = createMenu(blueProfileDropdownHB, {"TestTraining"}, DROP_DOWN_MENU_PATH, FOCUSED_DROP_DOWN_MENU_PATH, ITEM_PATH);
    auto characterMenu = createMenu(blueCharacterDropdownHB, {KENNY}, DROP_DOWN_MENU_PATH, FOCUSED_DROP_DOWN_MENU_PATH, ITEM_PATH);

    auto trainingPane = std::make_shared<uicomponents::Pane>(window, std::vector<std::shared_ptr<uicomponents::UIComponent>>{returnBtnT, profileMenu, characterMenu, startTrainingBtn});

    auto trainingSelcetion = std::make_shared<graphics::Sprite>(window, BACKGROUND_LAYER, TRAINING_SELECTION_PATH);

    std::shared_ptr<scene::Scene> trainingSelectionScene = std::make_shared<scene::Scene>(
        trainingSelcetion,
        std::vector<std::shared_ptr<core::Component>>{std::shared_ptr<core::Component>(trainingPane)},
        false);

    scene::sceneManager::addScene(static_cast<int>(SceneName::TRAINING_CHARACTER_SELECTION), trainingSelectionScene);
}

datatypes::Point namePt(50, 15);
datatypes::Hitbox SceneLoader::hbName(datatypes::Point(150, namePt.Y), 70, 10, false);

void SceneLoader::createProfileEditorMenu()
{
    datatypes::Point upPt(50, 35);
    datatypes::Point downPt(50, 55);
    datatypes::Point leftPt(50, 75);
    datatypes::Point rightPt(50, 95);
    datatypes::Point lightPt(50, 115);
    datatypes::Point heavyPt(50, 135);
    datatypes::Point jumpPt(50, 155);
    datatypes::Point blockPt(50, 175);
    datatypes::Point isControllerPt(250, 125);

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
    auto isControllerLbl = std::make_shared<uicomponents::Label>(isControllerPt, "Is Controller: ", font, white);

    auto nameTbx = createTextbox(hbName, TEXTBOX_PATH, FOCUSED_TEXTBOX_PATH, 8);
    auto upTbx = createTextbox(hbUp, TEXTBOX_PATH, FOCUSED_TEXTBOX_PATH, 8);
    auto downTbx = createTextbox(hbDown, TEXTBOX_PATH, FOCUSED_TEXTBOX_PATH, 8);
    auto leftTbx = createTextbox(hbLeft, TEXTBOX_PATH, FOCUSED_TEXTBOX_PATH, 8);
    auto rightTbx = createTextbox(hbRight, TEXTBOX_PATH, FOCUSED_TEXTBOX_PATH, 8);
    auto lightTbx = createTextbox(hbLight, TEXTBOX_PATH, FOCUSED_TEXTBOX_PATH, 8);
    auto heavyTbx = createTextbox(hbHeavy, TEXTBOX_PATH, FOCUSED_TEXTBOX_PATH, 8);
    auto jumpTbx = createTextbox(hbJump, TEXTBOX_PATH, FOCUSED_TEXTBOX_PATH, 8);
    auto blockTbx = createTextbox(hbBlock, TEXTBOX_PATH, FOCUSED_TEXTBOX_PATH, 8);

    datatypes::Hitbox checkBoxHb(datatypes::Point(isControllerPt.X, 150), 30, 30, false);
    auto controllerCheckbox = createCheckbox(checkBoxHb);

    auto returnBtnPE = createButton(returnHB, "", RETURN_BTN_PATH, FOCUSED_RETURN_BTN_PATH, changeSceneToMain);
    auto resetBtn = createButton(hbReset, "Reset", BUTTON_PATH, FOCUSED_BUTTON_PATH, resetTextboxes);
    auto importBtn = createButton(hbImport, "Import", BUTTON_PATH, FOCUSED_BUTTON_PATH, importProfile);
    auto removeBtn = createButton(hbRemove, "Remove", BUTTON_PATH, FOCUSED_BUTTON_PATH, removeProfile);
    auto saveBtn = createButton(hbSave, "Save", BUTTON_PATH, FOCUSED_BUTTON_PATH, saveProfile);

    auto profileEditorPane = std::make_shared<uicomponents::Pane>(window,
                                                                  std::vector<std::shared_ptr<uicomponents::UIComponent>>{
                                                                      returnBtnPE,
                                                                      nameLbl, upLbl, downLbl, leftLbl, rightLbl, lightLbl, heavyLbl, jumpLbl, blockLbl, isControllerLbl,
                                                                      nameTbx, upTbx, downTbx, leftTbx, rightTbx, lightTbx, heavyTbx, jumpTbx, blockTbx,
                                                                      resetBtn, importBtn, removeBtn, saveBtn, controllerCheckbox});

    auto darkBlueBackgroundPE = std::make_shared<graphics::Sprite>(window, BACKGROUND_LAYER, DARK_BLUE_SCREEN_PATH);

    std::shared_ptr<scene::Scene> profileEditorScene = std::make_shared<scene::Scene>(
        darkBlueBackgroundPE,
        std::vector<std::shared_ptr<core::Component>>{std::shared_ptr<core::Component>(profileEditorPane)},
        false);

    scene::sceneManager::addScene(static_cast<int>(SceneName::PROFILE_EDITOR), profileEditorScene);
}

void SceneLoader::createSettingMenu()
{
    datatypes::Hitbox sliderHb(datatypes::Point(120, 50), 70, 15, false);

    auto returnBtnS = createButton(returnHB, "", RETURN_BTN_PATH, FOCUSED_RETURN_BTN_PATH, changeSceneToMain);
    auto volumeSlider = createSlideBar(sliderHb, BAR_PATH, 5, 20, SLIDER_PATH, FOCUSED_SLIDER_PATH, audio::AudioPlayer::setVolume);

    auto pane = std::make_shared<uicomponents::Pane>(window, std::vector<std::shared_ptr<uicomponents::UIComponent>>{returnBtnS, volumeSlider});

    auto darkBlueBackgroundS = std::make_shared<graphics::Sprite>(window, BACKGROUND_LAYER, DARK_BLUE_SCREEN_PATH);

    std::shared_ptr<scene::Scene> settingScene = std::make_shared<scene::Scene>(
        darkBlueBackgroundS,
        std::vector<std::shared_ptr<core::Component>>{std::shared_ptr<core::Component>(pane)},
        false);

    scene::sceneManager::addScene(static_cast<int>(SceneName::SETTINGS), settingScene);
}

void SceneLoader::createDojo()
{
    auto groundHitbox = std::make_shared<datatypes::Hitbox>(datatypes::Point(0, 200), WINDOW_WIDTH, WINDOW_HEIGHT, true); // coords and w/h should be approximately at bottom of screen

    auto dojoBackground = std::make_shared<graphics::Sprite>(window, BACKGROUND_LAYER, DOJO_PATH);

    std::shared_ptr<scene::Scene> dojoScene = std::make_shared<scene::Scene>(dojoBackground, std::vector<std::shared_ptr<core::Component>>{}, true);

    dojoScene->addCollisionHitbox(groundHitbox);

    scene::sceneManager::addScene(static_cast<int>(SceneName::DOJO), dojoScene);
}

void SceneLoader::createCyberPunk()
{
    auto groundHitbox = std::make_shared<datatypes::Hitbox>(datatypes::Point(0, 200), WINDOW_WIDTH, WINDOW_HEIGHT, true);              // coords and w/h should be approximately at bottom of screen
    auto rightHitbox = std::make_shared<datatypes::Hitbox>(datatypes::Point(WINDOW_WIDTH - 10, 0), WINDOW_WIDTH, WINDOW_HEIGHT, true); // coords and w/h should be approximately at bottom of screen
    auto leftHitbox = std::make_shared<datatypes::Hitbox>(datatypes::Point(10 - WINDOW_WIDTH, 0), WINDOW_WIDTH, WINDOW_HEIGHT, true);  // coords and w/h should be approximately at bottom of screen

    auto cyberBackground = std::make_shared<graphics::Sprite>(window, BACKGROUND_LAYER, CP_PATH);

    std::shared_ptr<scene::Scene> cyberPunkScene = std::make_shared<scene::Scene>(cyberBackground, std::vector<std::shared_ptr<core::Component>>{}, true);

    cyberPunkScene->addCollisionHitbox(groundHitbox);
    cyberPunkScene->addCollisionHitbox(rightHitbox);
    cyberPunkScene->addCollisionHitbox(leftHitbox);

    scene::sceneManager::addScene(static_cast<int>(SceneName::CYBER_PUNK), cyberPunkScene);
}