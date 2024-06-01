#ifndef PHYSICS_HPP__
#define PHYSICS_HPP__
#include "Vec2.hpp"
#include "../core/Config.hpp"
#include <vector>
#include <memory>
#include <utility>

struct rect
{
	Vec2 pos;
	Vec2 size;

	Vec2 vel;
};

struct ray
{
	bool isHorizontal{ false };
	bool isVertical{ false };
	Vec2 p;
	Vec2 q;
	Vec2 D;

	ray(Vec2 p, Vec2 q) : ray(p.x, p.y, q.x, q.y) {}
	ray(float px, float py, float qx, float qy)
		: p(px,py), q(qx,qy)
	{
		if (q.y == p.y)
		{
			// horizontal line
			isHorizontal = true;
		}
		if (q.x == p.x)
		{
			// vertical line
			isVertical = true;
		}
		D = q - p;
	}

	float position(const rect& r)
	{
		Vec2 rp = Vec2(r.pos.x, r.pos.y);
		Vec2 rs = r.size;

		//return the closest collision, near and far
		// what is the t in both points on both axes
		float near_tx = (rp.x - p.x) / D.x;
		float far_tx = (rp.x + rs.x - p.x) / D.x;

		float near_ty = (rp.y - p.y) / D.y;
		float far_ty = (rp.y + rs.y - p.y) / D.y;
		
		if (isHorizontal)
		{
			near_ty = -INFINITY;
			far_ty = INFINITY;
		}
		else if (isVertical)
		{
			near_tx = -INFINITY;
			far_tx = INFINITY;
		}

		if (far_tx < near_tx)
		{
			auto tmp = far_tx;
			far_tx = near_tx;
			near_tx = tmp;
		}
		
		if (far_ty < near_ty)
		{
			auto tmp = far_ty;
			far_ty = near_ty;
			near_ty = tmp;
		}

		if (near_tx < far_ty && near_ty < far_tx)
		{
			float t_near = std::max(near_tx, near_ty);
			float t_far = std::min(far_tx, far_ty);

			return t_near;
		}

		return -1.f;
	}
};



class Physics
{
	

public:
	Physics() = delete;

	static bool PointVsRect(const Vec2& p, const rect& r);
	static bool RectVsRect(const rect& r1, const rect& r2);
	static bool RayVsRect(const Vec2& ray_origin, const Vec2& ray_dir, const rect& target, float& t_hitDist, Vec2& cn, Vec2& cp);
	static bool DynamicVsRect(rect& collider, const rect& target, float elapsedTime, float& t_hitDist, Vec2& cn, Vec2& cp);
};



#endif