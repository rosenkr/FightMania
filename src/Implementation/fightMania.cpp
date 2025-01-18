#include "Ichi/Core/engine.h"
#include "Implementation/sceneLoader.h"

int main(int argc, char *argv[])
{
	auto instance = core::Engine::getInstance();

	if (!instance->init())
	{
		instance->shutdown();
		return -1;
	}

	if (!SceneLoader::init())
	{
		instance->shutdown();
		return -1;
	}

	instance->run();
	SceneLoader::shutdown();
	instance->shutdown();
	ichi::core::Engine::cleanup();


	return 0;
}
