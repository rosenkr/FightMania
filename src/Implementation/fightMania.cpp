#include "Ichi/Core/engine.h"
#include "Ichi/Scene/sceneManager.h"
#include "Ichi/UIComponents/button.h"
#include "Ichi/UIComponents/textbox.h"
#include "Ichi/UIComponents/dropDownMenu.h"
#include "Ichi/UIComponents/checkbox.h"
#include "Ichi/DataTypes/hitbox.h"
#include "Ichi/log.h"

#include "SDL2/SDL_ttf.h"

using namespace ichi;

void clicked()
{
	ICHI_TRACE("Clicked");
}

int main(int argc, char *argv[])
{
	auto instance = core::Engine::getInstance();

	if (!instance->init())
	{
		instance->shutdown();
		return -1;
	}

	TTF_Font *font = TTF_OpenFont("resources/fonts/PRSTART.TTF", 20);

	datatypes::Hitbox hb1(datatypes::Hitbox(datatypes::Point(0, 0), 90, 30, false));
	graphics::Sprite s(hb1, graphics::Sprite::Layer::UICOMPONENT, "resources/images/UIComponents/Button.png");
	graphics::Sprite fs(hb1, graphics::Sprite::Layer::UICOMPONENT, "resources/images/UIComponents/FocusedButton.png");
	core::Component *c = new uicomponents::Button(hb1, "Click Me", font, SDL_Color{255, 255, 255, 255}, s, fs, clicked);

	datatypes::Hitbox hb2(datatypes::Hitbox(datatypes::Point(100, 0), 90, 30, false));
	graphics::Sprite s1(hb2, graphics::Sprite::Layer::UICOMPONENT, "resources/images/UIComponents/Button.png");
	graphics::Sprite fs1(hb2, graphics::Sprite::Layer::UICOMPONENT, "resources/images/UIComponents/FocusedButton.png");
	core::Component *c1 = new uicomponents::Button(hb2, "Click Me", font, SDL_Color{255, 255, 255, 255}, s1, fs1, clicked);

	datatypes::Hitbox hb3(datatypes::Hitbox(datatypes::Point(100, 100), 90, 30, false));
	graphics::Sprite s2(hb3, graphics::Sprite::Layer::UICOMPONENT, "resources/images/UIComponents/Textbox.png");
	graphics::Sprite fs2(hb3, graphics::Sprite::Layer::UICOMPONENT, "resources/images/UIComponents/FocusedTextbox.png");
	core::Component *c2 = new uicomponents::Textbox(hb3, font, SDL_Color{0, 0, 0, 255}, s2, fs2);

	datatypes::Hitbox hb4(datatypes::Hitbox(datatypes::Point(200, 200), 120, 30, false));
	datatypes::Hitbox hb5(datatypes::Hitbox(datatypes::Point(200, 200), 109, 25, false));
	graphics::Sprite item(hb5, graphics::Sprite::Layer::UICOMPONENT, "resources/images/UIComponents/Item.png");
	graphics::Sprite menu(hb4, graphics::Sprite::Layer::UICOMPONENT, "resources/images/UIComponents/DropDownMenu.png");
	core::Component *c3 = new uicomponents::DropDownMenu(hb4, {"item1", "item2", "item3"}, font, SDL_Color{0, 0, 0, 255}, menu, item);

	datatypes::Hitbox hb6(datatypes::Hitbox(datatypes::Point(100, 300), 50, 50, false));
	graphics::Sprite s3(hb6, graphics::Sprite::Layer::UICOMPONENT, "resources/images/UIComponents/Checkbox.png");
	graphics::Sprite sChecked(hb6, graphics::Sprite::Layer::UICOMPONENT, "resources/images/UIComponents/CheckedCheckbox.png");
	core::Component *c4 = new uicomponents::Checkbox(hb6, s3, sChecked);

	std::vector<core::Component *> components = {c, c1, c2, c3, c4};

	std::shared_ptr<scene::Scene> scene = std::make_shared<scene::Scene>(components);

	scene::sceneManager::addScene(0, std::move(scene));

	scene::sceneManager::setActiveScene(0);

	instance->run();

	TTF_CloseFont(font);

	return 0;
}
