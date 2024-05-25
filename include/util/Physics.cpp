#include "Physics.hpp"
#include "../ECS/Entity.hpp"

Vec2 Physics::pointInRect(Vec2& l_pt, rect& l_r)
{
	Vec2 range(0,0);

	if (l_pt.x >= l_r.cx - l_r.halfSizeX
		&& l_pt.x <= l_r.cx + l_r.halfSizeX
		&& l_pt.y >= l_r.cy - l_r.halfSizeY
		&& l_pt.y <= l_r.cy + l_r.halfSizeY)
	{
		range.x = l_pt.x - l_r.cx - l_r.halfSizeX;
		range.y = l_pt.x - l_r.cx - l_r.halfSizeX;

	}

	return range;
}

Vec2 Physics::rectvRect(rect& l_r1, rect& l_r2)
{
	// diff
	float dx = abs(l_r2.cx - l_r1.cx);
	float dy = abs(l_r2.cy - l_r1.cy);

	float olapX = (l_r2.halfSizeX + l_r1.halfSizeX - dx);
	float olapY = (l_r2.halfSizeY + l_r1.halfSizeY - dy);

	return Vec2(olapX,olapY);
}

Vec2 Physics::prevRectvRect(rect& l_r1, rect& l_r2, Vec2 l_olap, Vec2 l_prevOlap)
{
	// only enters here if either of the prev olap dims are negative
	if (l_prevOlap.x < 0.f && l_prevOlap.y < 0.f)
	{
		if (l_olap.x < l_olap.y)
		{
			// resolve on x
			if (l_r1.cx - l_r1.halfSizeX < l_r2.cx - l_r2.halfSizeX)
			{
				// coming from the left, push back left
				return Vec2(-1, 0);
			}
			else
			{
				return Vec2(1, 0);
			}
		}
		else
		{
			// resolve on y
			if (l_r1.cy - l_r1.halfSizeY < l_r2.cy - l_r2.halfSizeY)
			{
				// coming from the top, push back up
				return Vec2(0, -1);
			}
			else
			{
				return Vec2(0, 1);
			}
		}
	}
	else if (l_prevOlap.x < 0.f)
	{
		// resolve on x
		if (l_r1.cx - l_r1.halfSizeX < l_r2.cx - l_r2.halfSizeX)
		{
			// coming from the left, push back left
			return Vec2(-1, 0);
		}
		else
		{
			return Vec2(1, 0);
		}
	}
	else
	{
		// (l_prevOlap.y < 0.f)
		// resolve on y
		if (l_r1.cy - l_r1.halfSizeY < l_r2.cy - l_r2.halfSizeY)
		{
			// coming from the top, push back up
			return Vec2(0, -1);
		}
		else
		{
			return Vec2(0, 1);
		}
	}

	return Vec2(0,0);
}

void Physics::resolveCollisions(std::shared_ptr<Entity> l_dynamic, EntityVec& l_unaffected)
{
	


	if (!l_dynamic->hasComponent<CBBox>() || !l_dynamic->hasComponent<CTransform>()) return;
	auto& bd = l_dynamic->getComponent<CBBox>();
	auto& td = l_dynamic->getComponent<CTransform>();
	rect r1{ bd.x + td.pos.x, bd.y + td.pos.y, bd.halfSize.x, bd.halfSize.y };
	for (auto& e : l_unaffected)
	{

		if (!e->hasComponent<CBBox>() || !e->hasComponent<CTransform>()) continue;
		auto& bu = e->getComponent<CBBox>();
		auto& tu = e->getComponent<CTransform>();

		Vec2 prevOlap(-1, -1);

		rect r2{ bu.x + tu.pos.x, bu.y + tu.pos.y, bu.halfSize.x, bu.halfSize.y };
		Vec2 currOlap = rectvRect(r1, r2);


		if (currOlap.x >= 0.f && currOlap.y >= 0)
		{
			rect r1Prev{ bd.x + td.prevPos.x, bd.y + td.prevPos.y, bd.halfSize.x, bd.halfSize.y };
			rect r2Prev{ bu.x + tu.prevPos.x, bu.y + tu.prevPos.y, bu.halfSize.x, bu.halfSize.y };
			Vec2 prevOlap = rectvRect(r1Prev, r2Prev);
			//collision occurred
			Vec2 normal = prevRectvRect(r1, r2, currOlap, prevOlap);
			if (normal.x != 0.f)
				td.velocity.x = currOlap.x * normal.x;
			if (normal.y != 0.f)
				td.velocity.y = currOlap.y * normal.y;

			// now ur good to update the sprite, may need to get rid of the return and resolve against another entity
			return;
		}

	}
}

void Physics::checkAndResolveCollision(rect& l_r1, rect& l_r2)
{
}
