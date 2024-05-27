#include "include/core/GameEngine.hpp"
#include "include/core/Config.hpp"

int main()
{
	Config::initialize();
	
	GameEngine game;

	game.mainLoop();

	return 0;
}
