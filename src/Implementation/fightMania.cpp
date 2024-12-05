#include "Ichi/Core/engine.h"
#include "Ichi/Scene/sceneManager.h"
#include "Ichi/UIComponents/button.h"
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
	datatypes::Hitbox hb(datatypes::Hitbox(datatypes::Point(0, 0), 100, 100, false));
	graphics::Sprite s(hb, graphics::Sprite::Layer::UICOMPONENT, "resources/images/Robot animations/RobotWalk0.png");
	graphics::Sprite fs(hb, graphics::Sprite::Layer::UICOMPONENT, "resources/images/Robot animations/RobotWalk2.png");

	core::Component *c = new uicomponents::Button(hb, "Click Me", font, SDL_Color{255, 255, 255, 255}, s, fs, clicked);

	std::vector<core::Component *> components = {c};

	std::shared_ptr<scene::Scene> scene = std::make_shared<scene::Scene>(components);

	scene::sceneManager::addScene(0, std::move(scene));

	scene::sceneManager::setActiveScene(0);

	instance->run();

	TTF_CloseFont(font);

	return 0;
}
