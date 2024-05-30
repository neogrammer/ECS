#ifndef SHOOTINGSTATE_HPP__
#define SHOOTINGSTATE_HPP__
#include "PlayerState.hpp"

class ShootingState : public PlayerState
{


public:
	ShootingState();
	~ShootingState();
	void handleInput(Player& player, Input input) override final;
	void update(Player& player, sf::Time l_dt) override final;

};

#endif