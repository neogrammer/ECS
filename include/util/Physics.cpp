#include "Physics.hpp"
#include "../ECS/Entity.hpp"
#include "../ECS/component/components/Components.hpp"


bool Physics::isColliding(cRigidBody& l_collider, cRigidBody& l_obstacle, Vec2& l_overlap)
{
	auto cx1 = l_collider.center.x;
	auto cy1 = l_collider.center.y;
	auto cx2 = l_obstacle.center.x;
	auto cy2 = l_obstacle.center.y;

	// length between the two center points
	float d = sqrt((cx2 - cx1) * (cx2 - cx1) + (cy2 - cy1) * (cy2 - cy1));
	float combinedx = l_collider.halfSize.x + l_obstacle.halfSize.x;
	float combinedy = l_collider.halfSize.y + l_obstacle.halfSize.y;
	// length of combined halfsizes
	float dComb = sqrt((combinedx) * (combinedx) + (combinedy) * (combinedy));

	if (d < dComb)
	{
		//collided!  store the overlap and return true
		l_overlap.x = combinedx - (cx2 - cx1);
		l_overlap.y = combinedy - (cy2 - cy1);
		if (l_overlap.x > 0.f && l_overlap.y > 0.f)
			return true;
		else
			return false;
	}
	else
	{
		return false;
	}

};


Vec2 Physics::getPreviousOverlap(cRigidBody& l_collider, cRigidBody& l_obstacle)
{
	auto cx1 = l_collider.center.x;
	auto cy1 = l_collider.center.y;
	auto cx2 = l_obstacle.center.x;
	auto cy2 = l_obstacle.center.y;

	// length between the two center points
	float d = sqrt((cx2 - cx1) * (cx2 - cx1) + (cy2 - cy1) * (cy2 - cy1));
	float combinedx = l_collider.halfSize.x + l_obstacle.halfSize.x;
	float combinedy = l_collider.halfSize.y + l_obstacle.halfSize.y;
	// length of combined halfsizes
	float dComb = sqrt((combinedx) * (combinedx)+(combinedy) * (combinedy));

	//get overlap then return it
	Vec2 olap(0.f,0.0f);
	olap.x = combinedx - (cx2 - cx1);
    olap.y = combinedy - (cy2 - cy1);
	return olap;
};

