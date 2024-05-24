#ifndef COLLISIONSYSTEM_HPP__
#define COLLISIONSYSTEM_HPP__

#include "../System.hpp"

class GameEngine;

class CollisionSystem : public System
{
public:
	CollisionSystem(GameEngine& l_game);
	~CollisionSystem() override final;

	void update(double l_dt) override final;
};

#endif