#ifndef JUMPINGSTATE_HPP__
#define JUMPINGSTATE_HPP__
#include "../../gameObj/actors/player/PlayerState.hpp"


class JumpingState : public PlayerState
{


public:
	JumpingState();
	~JumpingState();
	void handleInput(Player& player, Input input) override final;
	void update(Player& player, sf::Time l_dt) override final;

};

#endif