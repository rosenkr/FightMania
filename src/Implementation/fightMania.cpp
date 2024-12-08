#include "Ichi/Core/engine.h"
#include "Ichi/Scene/sceneManager.h"
#include "Ichi/Scene/popUpMenu.h"
#include "Ichi/UIComponents/button.h"
#include "Ichi/UIComponents/textbox.h"
#include "Ichi/UIComponents/slidebar.h"
#include "Ichi/DataTypes/hitbox.h"
#include "Ichi/log.h"

#include "SDL2/SDL_ttf.h"

using namespace ichi;

float f = 0.5f;
datatypes::Hitbox hb7(datatypes::Point(100, 500), 70, 10, false);
graphics::Sprite s4(hb7, graphics::Sprite::Layer::UICOMPONENT, "resources/images/UIComponents/ProgressBar.png");
auto *c5 = new uicomponents::ProgressBar(hb7, s4, "resources/images/UIComponents/colorGreen.png");

void plus()
{
	f += 0.1;
	c5->setProcentageFilled(f);
}

void minus()
{
	f -= 0.1;
	c5->setProcentageFilled(f);
}

void quit()
{
	core::Engine::getInstance()->quit();
}

int main(int argc, char *argv[])
{
	auto instance = core::Engine::getInstance();

	if (!instance->init())
	{
		instance->shutdown();
		return -1;
	}

	// Temp string for Alex
	std::string str = "/home/sasha/Documents/Uni/Course3/projects/fight_mania/";
	TTF_Font *font = TTF_OpenFont((str + "resources/fonts/PRSTART.TTF").c_str(), 20);

	datatypes::Hitbox quitBox(datatypes::Point(384 * 2, 224 * 2), 90, 30, false);
	graphics::Sprite quitSprite(quitBox, graphics::Sprite::Layer::UICOMPONENT, "resources/images/UIComponents/Button.png");
	graphics::Sprite fQuitSprite(quitBox, graphics::Sprite::Layer::UICOMPONENT, "resources/images/UIComponents/FocusedButton.png");
	uicomponents::UIComponent *quitBtn = new uicomponents::Button(quitBox, "Quit", font, SDL_Color{255, 255, 255, 255}, quitSprite, fQuitSprite, quit);

	datatypes::Hitbox screen(datatypes::Point(0, 0), 384 * 4, 224 * 4, false);
	datatypes::Hitbox windowBox(datatypes::Point(384 * 2 - 200, 224 * 2 - 200), 400, 400, false);
	graphics::Sprite background(screen, graphics::Sprite::Layer::UICOMPONENT, "resources/images/PopUpMenu/TransparantBlack.png");
	graphics::Sprite window(windowBox, graphics::Sprite::Layer::UICOMPONENT, "resources/images/PopUpMenu/PopUpMenu.png");

	std::vector<uicomponents::UIComponent *> uicomponents{quitBtn};

	auto popMenu = std::make_shared<scene::PopUpMenu>(uicomponents, background, window);
	scene::sceneManager::setPopUpMenu(popMenu);

	datatypes::Hitbox hb1(datatypes::Hitbox(datatypes::Point(0, 0), 90, 30, false));
	graphics::Sprite s(hb1, graphics::Sprite::Layer::UICOMPONENT, str + "resources/images/UIComponents/Button.png");
	graphics::Sprite fs(hb1, graphics::Sprite::Layer::UICOMPONENT, str + "resources/images/UIComponents/FocusedButton.png");
	core::Component *c = new uicomponents::Button(hb1, "Click Me", font, SDL_Color{255, 255, 255, 255}, s, fs, clicked);

	datatypes::Hitbox hb2(datatypes::Hitbox(datatypes::Point(100, 0), 90, 30, false));
	graphics::Sprite s1(hb2, graphics::Sprite::Layer::UICOMPONENT, str + "resources/images/UIComponents/Button.png");
	graphics::Sprite fs1(hb2, graphics::Sprite::Layer::UICOMPONENT, str + "resources/images/UIComponents/FocusedButton.png");
	core::Component *c1 = new uicomponents::Button(hb2, "Click Me", font, SDL_Color{255, 255, 255, 255}, s1, fs1, clicked);

	datatypes::Hitbox hb3(datatypes::Hitbox(datatypes::Point(100, 100), 90, 30, false));
	graphics::Sprite s2(hb3, graphics::Sprite::Layer::UICOMPONENT, str + "resources/images/UIComponents/Textbox.png");
	graphics::Sprite fs2(hb3, graphics::Sprite::Layer::UICOMPONENT, str + "resources/images/UIComponents/FocusedTextbox.png");
	core::Component *c2 = new uicomponents::Textbox(hb3, font, SDL_Color{0, 0, 0, 255}, s2, fs2);

	// Create <one> main hitbox for the bar
	// pass the sprite for the bar, and the paths for the slider/focusedsliders
	datatypes::Hitbox hb4(datatypes::Hitbox(datatypes::Point(150, 150), 200, 15, false));
	graphics::Sprite s3(hb4, graphics::Sprite::Layer::UICOMPONENT, str + "resources/images/UIComponents/Bar.png");
	core::Component *c3 = new uicomponents::SlideBar(hb4, s3, str + "resources/images/UIComponents/Slider.png", str + "resources/images/UIComponents/FocusedSlider.png");

	if (uicomponents::SlideBar *x = dynamic_cast<uicomponents::SlideBar *>(c3))
	{
		x->getSliderValue();
	}

	std::vector<core::Component *> components = {c, c1, c2, c3};

	std::shared_ptr<scene::Scene> scene = std::make_shared<scene::Scene>(components);

	scene::sceneManager::addScene(0, std::move(scene));

	scene::sceneManager::setActiveScene(0);

	instance->run();

	TTF_CloseFont(font);

	return 0;
}
