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

	instance->run();

	TTF_CloseFont(font);

	return 0;
}
