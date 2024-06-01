#include "include/core/Game.hpp"
#include "include/core/Config.hpp"

int main()
{
	Config::initialize();
	
	Game demo;

	demo.mainLoop();

	return 0;
}
