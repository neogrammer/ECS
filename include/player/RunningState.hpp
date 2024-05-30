#ifndef RUNNINGSTATE_HPP__
#define RUNNINGSTATE_HPP__
#include "PlayerState.hpp"

class RunningState : public PlayerState
{


public:
	RunningState();
	~RunningState();
	void handleInput(Player& player, Input input) override final;
	void update(Player& player, sf::Time l_dt) override final;

};

#endif