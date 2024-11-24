#include "Ichi/Managers/logManager.cpp"

#include "Ichi/log.h"

Ichi::Managers::logManager manager;

int main(int argc, char *argv[])
{

	manager.init();

	std::string s = "SVEJSAN";
	ICHI_INFO("HEJSAN {}", s);

	manager.shutdown();
	return 0;
}