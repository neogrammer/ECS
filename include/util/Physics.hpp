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
};

class Physics
{
	

public:
	Physics() = delete;

	static bool PointVsRect(const Vec2& p, const rect& r);
};



#endif