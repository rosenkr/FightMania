#include "Ichi/Core/engine.h"

int main(int argc, char *argv[])
{
	auto instance = ichi::core::Engine::getInstance();
	instance.run();
	return 0;
}