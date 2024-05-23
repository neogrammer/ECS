#ifndef COLLISIONSYSTEM_HPP__
#define COLLISIONSYSTEM_HPP__

#include "../System.hpp"

class CollisionSystem : public System
{
public:
	CollisionSystem();
	~CollisionSystem() override final;

	void update(double l_dt) override final;
};

#endif