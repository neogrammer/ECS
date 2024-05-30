#ifndef PHYSICS_HPP__
#define PHYSICS_HPP__
#include "Vec2.hpp"
#include "../core/Config.hpp"
#include <vector>
#include <memory>
#include <utility>
class Entity;
struct cRigidBody;
class Physics
{
public:
	Physics() = delete;
	
	static bool isColliding(cRigidBody& l_collider, cRigidBody& l_obstacle, Vec2& l_overlap);
	static Vec2 getPreviousOverlap(cRigidBody& l_collider, cRigidBody& l_obstacle);

	static Vec2 RectVsRect(Entity& a, Entity& b);
	static Vec2 PrevOverlap(Entity& a, Entity& b);
	static void ResolveCollisions(Entity& a, EntityVec& eVec);
};



#endif