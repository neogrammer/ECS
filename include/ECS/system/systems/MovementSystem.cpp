#include "MovementSystem.hpp"
#include "../../../core/GameEngine.hpp"
#include "../../../scene/scenes/Play.hpp"


MovementSystem::MovementSystem(GameEngine& l_game)
	: System{l_game}
{

}

MovementSystem::~MovementSystem()
{
}

void MovementSystem::update(double l_dt)
{
	if (dynamic_cast<Play*>(game.currentScene().get()))
	{
	
	}
}