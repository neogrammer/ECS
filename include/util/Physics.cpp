#include "Physics.hpp"
#include <iostream>
bool Physics::PointVsRect(const Vec2& p, const rect& r)
{
    return (p.x >= r.pos.x && p.y >= r.pos.y && p.x < r.pos.x + r.size.x && p.y < r.pos.y + r.size.y);
}
//
bool Physics::RectVsRect(const rect& r1, const rect& r2)
{
    return (r1.pos.x < r2.pos.x + r2.size.x && r1.pos.x + r1.size.x > r2.pos.x &&
        r1.pos.y < r2.pos.y + r2.size.y && r1.pos.y + r1.size.y > r2.pos.y);

}
//
//bool Physics::RayVsRect(const Vec2& ray_origin, const Vec2& ray_dir, const rect& target, float& t_hitDist, Vec2& cn, Vec2& cp)
//{
//    ray r(ray_origin, ray_dir);
//    Vec2 t_near = (target.pos - ray_origin) / ray_dir;
//    Vec2 t_far = (target.pos + target.size - ray_origin) / ray_dir;
//
//    if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
//    if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);
//
//    if (t_near.x > t_far.y || t_near.y > t_far.x) { return false; }
//
//
//    float t_hit_near = std::max(t_near.x, t_near.y);
//    float t_hit_far = std::min(t_far.x, t_far.y);
//
//    if (t_hit_far < 0) return false;
//
//    Vec2 normal(0.0f, 0.0f);
//
//    /*if (t_near.x > t_near.y)
//    {
//        if (ray_dir.x < 0)
//        {
//            normal = { 1, 0 };
//        }
//        else
//        {
//            normal = { -1,0 };
//        }
//    }
//    else if (t_near.x < t_near.y)
//    {
//        if (ray_dir.y < 0)
//        {
//            normal = { 0,1 };
//
//        }
//        else
//        {
//            normal = { 0, -1 };
//        }
//    }
//    cn = normal;*/
//
//     if ((r.D.x > 0.f && r.D.y > 0.f) && t_near.x > t_near.y)
//      {
//          normal.x = -1.f;
//      }
//      else if ((r.D.x > 0.f && r.D.y > 0.f) && t_near.y > t_near.x)
//      {
//          normal.y = -1.f;
//      }
//      else if ((r.D.x < 0.f && r.D.y > 0.f) && t_near.x > t_near.y)
//      {
//          normal.x = 1.f;
//      }
//      else if ((r.D.x < 0.f && r.D.y > 0.f) && t_near.y > t_near.x)
//      {
//          normal.y = -1.f;
//      }
//      else if ((r.D.x < 0.f && r.D.y < 0.f) && t_near.x > t_near.y)
//      {
//          normal.x = 1.f;
//      }
//      else if ((r.D.x < 0.f && r.D.y < 0.f) && t_near.y > t_near.x)
//      {
//          normal.y = 1.f;
//      }
//      else if ((r.D.x > 0.f && r.D.y < 0.f) && t_near.x > t_near.y)
//      {
//          normal.x = -1.f;
//      }
//      else if ((r.D.x > 0.f && r.D.y < 0.f) && t_near.y > t_near.x)
//      {
//          normal.y = 1.f;
//      }
//
//      cn = normal;
//    if (t_hit_near > 1.f || t_hit_near < 0.f)
//        return false;
//    cp = ray_origin + (t_hit_near * r.D.normalized());
//    t_hitDist = t_hit_near;
//
//    return true;
//}
//
//bool Physics::DynamicVsRect(rect& in, const rect& target, float elapsedTime, float& t_hitDist, Vec2& cn, Vec2& cp)
//{
//
//    if (in.vel.x == 0 && in.vel.y == 0)
//    {
//        return false;
//    }
//    rect expanded_rect = { { target.pos.x - in.size.x / 2.f,target.pos.y - in.size.y / 2.f}, {target.size + in.size} };
//    expanded_rect.pos = target.pos - in.size / 2.f;
//    expanded_rect.size = target.size + in.size;
//
//    if (RayVsRect(in.pos.x + in.size / 2.f, in.vel * elapsedTime, expanded_rect, t_hitDist, cn, cp))
//    {
//        if (t_hitDist <= 1.0f || t_hitDist >= 0.f)
//        {
//            
//            cp = in.pos + in.size / 2.f;
//            cp += t_hitDist * ((in.vel * elapsedTime));
//            return true;
//        }
//    }
//
//    return false;
//
//
//}

bool Physics::RayVsRect(const Vec2& ray_origin, const Vec2& ray_dir, const rect* target, Vec2& contact_point, Vec2& contact_normal, float& t_hit_near)
{
    contact_normal = { 0,0 };
    contact_point = { 0,0 };

    // Cache division
    Vec2 invdir = 1.0f / ray_dir;

    // Calculate intersections with rectangle bounding axes
    Vec2 t_near = (target->pos - ray_origin) * invdir;
    Vec2 t_far = (target->pos + target->size - ray_origin) * invdir;

    if (std::isnan(t_far.y) || std::isnan(t_far.x)) return false;
    if (std::isnan(t_near.y) || std::isnan(t_near.x)) return false;

    // Sort distances
    if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
    if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

    // Early rejection		
    if (t_near.x > t_far.y || t_near.y > t_far.x) return false;

    // Closest 'time' will be the first contact
    t_hit_near = std::max(t_near.x, t_near.y);

    // Furthest 'time' is contact on opposite side of target
    float t_hit_far = std::min(t_far.x, t_far.y);

    // Reject if ray direction is pointing away from object
    if (t_hit_far < 0)
        return false;

    // Contact point of collision from parametric line equation
    contact_point = ray_origin + t_hit_near * ray_dir;

    if (t_near.x > t_near.y)
        if (invdir.x < 0)
            contact_normal = { 1, 0 };
        else
            contact_normal = { -1, 0 };
    else if (t_near.x < t_near.y)
        if (invdir.y < 0)
            contact_normal = { 0, 1 };
        else
            contact_normal = { 0, -1 };

    // Note if t_near == t_far, collision is principly in a diagonal
    // so pointless to resolve. By returning a CN={0,0} even though its
    // considered a hit, the resolver wont change anything.
    return true;
}

bool Physics::DynamicRectVsRect(const rect* r_dynamic, const float fTimeStep, const rect& r_static,
    Vec2& contact_point, Vec2& contact_normal, float& contact_time)
{
    // Check if dynamic rectangle is actually moving - we assume rectangles are NOT in collision to start
    if (r_dynamic->vel.x == 0 && r_dynamic->vel.y == 0)
        return false;

    // Expand target rectangle by source dimensions
    rect expanded_target;
    expanded_target.pos = r_static.pos - r_dynamic->size / 2;
    expanded_target.size = r_static.size + r_dynamic->size;

    if (RayVsRect(r_dynamic->pos + r_dynamic->size / 2, r_dynamic->vel * fTimeStep, &expanded_target, contact_point, contact_normal, contact_time))
        return (contact_time >= 0.0f && contact_time < 1.0f);
    else
        return false;
}



bool Physics::ResolveDynamicRectVsRect(rect* r_dynamic, const float fTimeStep, rect* r_static)
{
    Vec2 contact_point, contact_normal;
    float contact_time = 0.0f;
    if (DynamicRectVsRect(r_dynamic, fTimeStep, *r_static, contact_point, contact_normal, contact_time))
    {
        if (contact_normal.y > 0) r_dynamic->contact[0] = r_static; else nullptr;
        if (contact_normal.x < 0) r_dynamic->contact[1] = r_static; else nullptr;
        if (contact_normal.y < 0) r_dynamic->contact[2] = r_static; else nullptr;
        if (contact_normal.x > 0) r_dynamic->contact[3] = r_static; else nullptr;

        r_dynamic->vel += contact_normal * Vec2(std::abs(r_dynamic->vel.x), std::abs(r_dynamic->vel.y)) * (1 - contact_time);
        return true;
    }

    return false;
}