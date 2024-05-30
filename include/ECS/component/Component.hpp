#ifndef COMPONENT_HPP__
#define COMPONENT_HPP__

#include "../../util/Vec2.hpp"

struct Component
{
	bool has;
	Component() : has{ false } {};
	virtual ~Component() {};
};


#endif