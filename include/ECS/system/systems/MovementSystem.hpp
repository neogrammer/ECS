#ifndef MOVEMENTSYSTEM_HPP__
#define MOVEMENTSYSTEM_HPP__

#include "../System.hpp"
class GameEngine;

class MovementSystem : public System
{
public:
	MovementSystem(GameEngine& l_game);
	~MovementSystem() override final;

	void update(double l_dt) override final;
};

#endif