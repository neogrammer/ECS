#ifndef PHYSICS_HPP__
#define PHYSICS_HPP__
#include "Vec2.hpp"
#include "../core/Config.hpp"
#include <vector>
#include <memory>
#include <utility>
#include "../core/Config.hpp"
class Entity;
struct cRigidBody;
class Physics
{
public:
	Physics() = delete;
	
	static bool isColliding(cRigidBody& l_collider, cRigidBody& l_obstacle, Vec2& l_overlap);
	static Vec2 getPreviousOverlap(cRigidBody& l_collider, cRigidBody& l_obstacle);
};

#endif