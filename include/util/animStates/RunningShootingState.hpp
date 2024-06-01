#ifndef RUNNINGSHOOTINGSTATE_HPP__
#define RUNNINGSHOOTINGSTATE_HPP__
#include "../../gameObj/actors/player/PlayerState.hpp"


class RunningShootingState : public PlayerState
{


public:
	RunningShootingState();
	~RunningShootingState();
	void handleInput(Player& player, Input input) override final;
	void update(Player& player, sf::Time l_dt) override final;

};

#endif