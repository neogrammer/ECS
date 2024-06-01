#include "Physics.hpp"

bool Physics::PointVsRect(const Vec2& p, const rect& r)
{
    return (p.x >= r.pos.x && p.y >= r.pos.y && p.x < r.pos.x + r.size.x && p.y < r.pos.y + r.size.y);
}
