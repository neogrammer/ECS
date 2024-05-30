#include "System.hpp"
#include "../../core/GameEngine.hpp"

System::System(GameEngine& l_game)
	: game{ l_game } {}

System::~System()
{
}

void System::update(double l_dt)
{
}
