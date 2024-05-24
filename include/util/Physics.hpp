#ifndef PHYSICS_HPP__
#define PHYSICS_HPP__
#include "Vec2.hpp"
#include "../core/Config.hpp"
#include <vector>
#include <memory>
#include <utility>
#include "../core/Config.hpp"

class Entity;

class Physics
{
public:
	Physics() = delete;

	// checks a point in a rect and returns a point from -rectSize to rectSize in both the x and y axes if within the rect and outside this range if not in the rect
	static Vec2 pointInRect(Vec2& l_pt, rect& l_r);

	// returns the overlap of two rects, if either is negative then there is no overlap, however the return value can be stored for the next frame for if
	//  an overlap then actually occurs, this return state can be used to find the direction of resolution that should be applied,
	// and on the frame of the collision this return value should be used to offset the rect, l_r1 which is the one affected in this algorithm, l_r2 is unaffected by the collision
	static Vec2 rectvRect(rect& l_r1, rect& l_r2);

	// returns the normal used to multiply against the current overlap returned by RectvRect this frame so the offset only affects the correct dimension in the correct direction
	static Vec2 prevRectvRect(rect& l_r1, rect& l_r2, Vec2 l_olap, Vec2 l_prevOlap);

	// check a moving entity against a collection of other static entities that will affect the moving of the one being affected 
	static void resolveCollisions(std::shared_ptr<Entity> l_dynamic, EntityVec& l_unaffected);

	static void checkAndResolveCollision(rect& l_r1, rect& l_r2);
	
};

#endif