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
}
Vec2 Physics::RectVsRect(Entity& a, Entity& b)
{
	Vec2 overlap(-1.f, -1.f);

	if (a.cMgr.x1() < b.cMgr.x2()
		&& b.cMgr.x1() < a.cMgr.x2()
		&& a.cMgr.y1() < b.cMgr.y2()
		&& b.cMgr.y1() < a.cMgr.y2())
	{
		//collision, return the overlap
		float dx = abs(b.cMgr.center().x - a.cMgr.center().x);
		float dy = abs(b.cMgr.center().y - a.cMgr.center().y);

		overlap.x = a.cMgr.bbox().halfSize.x + b.cMgr.bbox().halfSize.x - dx;
		overlap.y = a.cMgr.bbox().halfSize.y + b.cMgr.bbox().halfSize.y - dy;
	}

	return overlap;
}

Vec2 Physics::PrevOverlap(Entity& a, Entity& b)
{
	Vec2 a_offset = Vec2(a.cMgr.prevPos().x * a.cMgr.dt() - a.cMgr.getPosition().x * a.cMgr.dt(), a.cMgr.prevPos().y * a.cMgr.dt() - a.cMgr.getPosition().y * a.cMgr.dt());
	Vec2 b_offset = Vec2(b.cMgr.prevPos().x * b.cMgr.dt() - b.cMgr.getPosition().x * b.cMgr.dt(), b.cMgr.prevPos().y * b.cMgr.dt() - b.cMgr.getPosition().y * b.cMgr.dt());

	//collision, return the overlap
	float dx = abs((b.cMgr.center().x + b_offset.x) - (a.cMgr.center().x + a_offset.x));
	float dy = abs((b.cMgr.center().y + b_offset.y) - (a.cMgr.center().y + a_offset.y));

	return Vec2(a.cMgr.bbox().halfSize.x + b.cMgr.bbox().halfSize.x - dx, a.cMgr.bbox().halfSize.y + b.cMgr.bbox().halfSize.y - dy);

}
void Physics::ResolveCollisions(Entity& a, EntityVec& eVec)
{
	// Entity A should have already accepted input this frame and updated the velocity, AND updated the sprites position

	for (auto& e : eVec)
	{
		Vec2 overlap = RectVsRect(a, *e);


		Vec2 norm = a.cMgr.prevPos() - a.cMgr.getPosition();
		norm = norm / Vec2(abs(norm.x), abs(norm.y));

		if (overlap.x > 0 && overlap.y > 0) // if not, check next entity for collision
		{
			// collision, get over lap from last frame
			Vec2 previousOlap = PrevOverlap(a, *e);

			if (previousOlap.x <= 0.f && previousOlap.y <= 0.f)
			{
				// no overlap last frame, resolve on the greatest dimension of the current overlap
				if (overlap.x > overlap.y)
				{
					// resolve on x
					a.cMgr.move(Vec2(norm.x * overlap.x, 0.0f));
					a.cMgr.velocity().x = 0.f;
				}
				else
				{
					//resolve on y
					a.cMgr.move(Vec2(0.f, norm.y * overlap.y));
					a.cMgr.velocity().y = 0.f;
				}
			}
			else if (previousOlap.x <= 0.f && previousOlap.y > 0.f)
			{
				// resolve on x
				a.cMgr.move(Vec2(norm.x * overlap.x, 0.0f));
				a.cMgr.velocity().x = 0.f;
			}
			else if (previousOlap.y <= 0.f && previousOlap.x > 0.f)
			{
				//resolve on y
				a.cMgr.move(Vec2(0.f, norm.y * overlap.y));
				a.cMgr.velocity().y = 0.f;
			}
			else
			{
				// change nothing ? maybe
			}
		}
	
	}
	// done checking for Entity A, the player most likely, should work against tiles and other obstacles
	// sprite has been moved accordingly and velocity updated to stop moving in the collided direction, now animate then render, then update the previous position

};



