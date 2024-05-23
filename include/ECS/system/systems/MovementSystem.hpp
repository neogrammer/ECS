#ifndef MOVEMENTSYSTEM_HPP__
#define MOVEMENTSYSTEM_HPP__

#include "../System.hpp"

class MovementSystem : public System
{
public:
	MovementSystem();
	~MovementSystem() override final;

	void update(double l_dt) override final;
};

#endif