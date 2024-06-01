#ifndef IDLESTATE_HPP__
#define IDLESTATE_HPP__
#include "../../gameObj/actors/player/PlayerState.hpp"

class IdleState : public PlayerState
{
public:
	IdleState();
	~IdleState() override final;
	void handleInput(Player& player, Input input) override final;
	void update(Player& player, sf::Time l_dt) override final;

};

#endif