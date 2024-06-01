#ifndef JUMPINGSHOOTINGSTATE_HPP__
#define JUMPINGSHOOTINGSTATE_HPP__
#include "../../gameObj/actors/player/PlayerState.hpp"

class JumpingShootingState : public PlayerState
{


public:
	JumpingShootingState();
	~JumpingShootingState();
	void handleInput(Player& player, Input input) override final;
	void update(Player& player, sf::Time l_dt) override final;

};

#endif