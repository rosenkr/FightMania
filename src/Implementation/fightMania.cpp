#include "Ichi/Core/engine.h"

#include "Ichi/Scene/sceneManager.h"
#include "Ichi/Scene/popUpMenu.h"

#include "Ichi/UIComponents/textbox.h"
#include "Ichi/UIComponents/slidebar.h"
#include "Ichi/UIComponents/pane.h"

#include "Ichi/DataTypes/hitbox.h"

#include "Ichi/log.h"

#include "SDL2/SDL_ttf.h"

using namespace ichi;

int main(int argc, char *argv[])
{
	auto instance = core::Engine::getInstance();

	if (!instance->init())
	{
		instance->shutdown();
		return -1;
	}

	// Temp string for Alex
	// std::string str = "/home/sasha/Documents/Uni/Course3/projects/fight_mania/";
	std::string str = "";
	TTF_Font *font = TTF_OpenFont((str + "resources/fonts/PRSTART.TTF").c_str(), 20);

	datatypes::Hitbox window(datatypes::Point(0, 0), 384 * 4, 224 * 4, false);

	datatypes::Hitbox hb(datatypes::Point(100, 300), 50, 50, false);
	datatypes::Hitbox hb1(datatypes::Point(200, 300), 50, 50, false);
	datatypes::Hitbox hb2(datatypes::Point(100, 400), 50, 50, false);
	datatypes::Hitbox hb3(datatypes::Point(200, 400), 50, 50, false);

	datatypes::Hitbox hb4(datatypes::Point(500, 500), 100, 20, false);

	graphics::Sprite bar(hb4, graphics::Sprite::Layer::UICOMPONENT, "resources/images/UIComponents/Bar.png");

	graphics::Sprite s(hb, graphics::Sprite::Layer::UICOMPONENT, "resources/images/UIComponents/TextBox.png");
	graphics::Sprite s1(hb1, graphics::Sprite::Layer::UICOMPONENT, "resources/images/UIComponents/TextBox.png");
	graphics::Sprite s2(hb2, graphics::Sprite::Layer::UICOMPONENT, "resources/images/UIComponents/TextBox.png");
	graphics::Sprite s3(hb3, graphics::Sprite::Layer::UICOMPONENT, "resources/images/UIComponents/TextBox.png");
	graphics::Sprite sChecked(hb, graphics::Sprite::Layer::UICOMPONENT, "resources/images/UIComponents/FocusedTextbox.png");
	graphics::Sprite sChecked1(hb1, graphics::Sprite::Layer::UICOMPONENT, "resources/images/UIComponents/FocusedTextbox.png");
	graphics::Sprite sChecked2(hb2, graphics::Sprite::Layer::UICOMPONENT, "resources/images/UIComponents/FocusedTextbox.png");
	graphics::Sprite sChecked3(hb3, graphics::Sprite::Layer::UICOMPONENT, "resources/images/UIComponents/FocusedTextbox.png");

	std::shared_ptr<uicomponents::UIComponent> c = std::make_shared<uicomponents::Textbox>(hb, font, SDL_Color{0, 255, 0, 255}, s, sChecked);
	std::shared_ptr<uicomponents::UIComponent> c1 = std::make_shared<uicomponents::Textbox>(hb1, font, SDL_Color{0, 255, 0, 255}, s1, sChecked1);
	std::shared_ptr<uicomponents::UIComponent> c2 = std::make_shared<uicomponents::Textbox>(hb2, font, SDL_Color{0, 255, 0, 255}, s2, sChecked2);
	std::shared_ptr<uicomponents::UIComponent> c3 = std::make_shared<uicomponents::Textbox>(hb3, font, SDL_Color{0, 255, 0, 255}, s3, sChecked3);

	// uicomponents::Pane *pane = new uicomponents::Pane(window, {c, c1, c2, c3});
	uicomponents::UIComponent *uic = new uicomponents::SlideBar(hb4, bar, 10, 30, "resources/images/UIComponents/Slider.png", "resources/images/UIComponents/FocusedSlider.png");

	std::shared_ptr<scene::Scene> scene = std::make_shared<scene::Scene>(std::vector<core::Component *>{uic}, false);

	scene::sceneManager::addScene(0, std::move(scene));

	scene::sceneManager::setActiveScene(0);

	instance->run();

	TTF_CloseFont(font);

	return 0;
}
