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
	if (!l_dynamic->cBBox || !l_dynamic->cTransform) return;

	rect r1{ l_dynamic->cBBox->x + l_dynamic->cTransform->pos.x, l_dynamic->cBBox->x + l_dynamic->cTransform->pos.y, l_dynamic->cBBox->halfSize.x, l_dynamic->cBBox->halfSize.y };
	for (auto e : l_unaffected)
	{
		if (!e->cBBox || !e->cTransform) continue;

		Vec2 prevOlap(-1, -1);

		rect r2{ e->cBBox->x + e->cTransform->pos.x, e->cBBox->x + e->cTransform->pos.y, e->cBBox->halfSize.x, e->cBBox->halfSize.y };
		Vec2 currOlap = rectvRect(r1, r2);


		if (currOlap.x >= 0.f && currOlap.y >= 0)
		{
			rect r1Prev{ l_dynamic->cBBox->x + l_dynamic->cTransform->prevPos.x, l_dynamic->cBBox->x + l_dynamic->cTransform->prevPos.y, l_dynamic->cBBox->halfSize.x, l_dynamic->cBBox->halfSize.y };
			rect r2Prev{ e->cBBox->x + e->cTransform->prevPos.x, e->cBBox->x + e->cTransform->prevPos.y, e->cBBox->halfSize.x, e->cBBox->halfSize.y };
			Vec2 prevOlap = rectvRect(r1Prev, r2Prev);
			//collision occurred
			Vec2 normal = prevRectvRect(r1, r2, currOlap, prevOlap);
			if (normal.x != 0.f)
				l_dynamic->cTransform->velocity.x = currOlap.x * normal.x;
			if (normal.y != 0.f)
				l_dynamic->cTransform->velocity.y = currOlap.y * normal.y;

			// now ur good to update the sprite, may need to get rid of the return and resolve against another entity
			return;
		}

	}
}

void Physics::checkAndResolveCollision(rect& l_r1, rect& l_r2)
{
}
