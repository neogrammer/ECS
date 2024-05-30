#include "ShootingState.hpp"

ShootingState::ShootingState()
	: PlayerState{"SHOOTING"}
{
}

ShootingState::~ShootingState()
{
}

void ShootingState::handleInput(Player& player, Input input)
{
}

void ShootingState::update(Player& player, sf::Time l_dt)
{
}
