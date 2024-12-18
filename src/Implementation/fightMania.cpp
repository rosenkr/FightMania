#include "Ichi/Core/engine.h"
#include "Implementation/sceneLoader.h"

using namespace ichi;

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

	return 0;
}
