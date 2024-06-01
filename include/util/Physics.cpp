#include "Physics.hpp"

bool Physics::PointVsRect(const Vec2& p, const rect& r)
{
    return (p.x >= r.pos.x && p.y >= r.pos.y && p.x < r.pos.x + r.size.x && p.y < r.pos.y + r.size.y);
}

bool Physics::RectVsRect(const rect& r1, const rect& r2)
{
    return (r1.pos.x < r2.pos.x + r2.size.x && r1.pos.x + r1.size.x > r2.pos.x &&
        r1.pos.y < r2.pos.y + r2.size.y && r1.pos.y + r1.size.y > r2.pos.y);

}

bool Physics::RayVsRect(const Vec2& ray_origin, const Vec2& ray_dir, const rect& target, float& t_hitDist, Vec2& cn, Vec2& cp)
{
    ray r(ray_origin, ray_dir);
    Vec2 t_near = (target.pos - ray_origin) / ray_dir;
    Vec2 t_far = (target.pos + target.size - ray_origin) / ray_dir;

    if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
    if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

    if (t_near.x > t_far.y || t_near.y > t_far.x) { return false; }


    float t_hit_near = std::max(t_near.x, t_near.y);
    float t_hit_far = std::min(t_far.x, t_far.y);

    if (t_hit_far < 0) return false;

    Vec2 normal(0.0f, 0.0f);

    /*if (t_near.x > t_near.y)
    {
        if (ray_dir.x < 0)
        {
            normal = { 1, 0 };
        }
        else
        {
            normal = { -1,0 };
        }
    }
    else if (t_near.x < t_near.y)
    {
        if (ray_dir.y < 0)
        {
            normal = { 0,1 };

        }
        else
        {
            normal = { 0, -1 };
        }
    }
    cn = normal;*/

     if ((r.D.x > 0.f && r.D.y > 0.f) && t_near.x > t_near.y)
      {
          normal.x = -1.f;
      }
      else if ((r.D.x > 0.f && r.D.y > 0.f) && t_near.y > t_near.x)
      {
          normal.y = -1.f;
      }
      else if ((r.D.x < 0.f && r.D.y > 0.f) && t_near.x > t_near.y)
      {
          normal.x = 1.f;
      }
      else if ((r.D.x < 0.f && r.D.y > 0.f) && t_near.y > t_near.x)
      {
          normal.y = -1.f;
      }
      else if ((r.D.x < 0.f && r.D.y < 0.f) && t_near.x > t_near.y)
      {
          normal.x = 1.f;
      }
      else if ((r.D.x < 0.f && r.D.y < 0.f) && t_near.y > t_near.x)
      {
          normal.y = 1.f;
      }
      else if ((r.D.x > 0.f && r.D.y < 0.f) && t_near.x > t_near.y)
      {
          normal.x = -1.f;
      }
      else if ((r.D.x > 0.f && r.D.y < 0.f) && t_near.y > t_near.x)
      {
          normal.y = 1.f;
      }

      cn = normal;
    if (t_hit_near > 1.f || t_hit_near < 0.f)
        return false;
    cp = ray_origin + (t_hit_near * r.D.normalized());
    t_hitDist = t_hit_near;

    return true;
}

bool Physics::DynamicVsRect(rect& in, const rect& target, float elapsedTime, float& t_hitDist, Vec2& cn, Vec2& cp)
{

    if (in.vel.x == 0 && in.vel.y == 0)
    {
        return false;
    }
    rect expanded_rect = { { target.pos.x - in.size.x / 2.f,target.pos.y - in.size.y / 2.f}, {target.size + in.size} };
    expanded_rect.pos = target.pos - in.size / 2.f;
    expanded_rect.size = target.size + in.size;

    if (RayVsRect(in.pos.x + in.size / 2.f, in.vel * elapsedTime, expanded_rect, t_hitDist, cn, cp))
    {
        if (t_hitDist <= 1.0f || t_hitDist >= 0.f)
        {
            
            cp = in.pos + in.size / 2.f;
            cp += t_hitDist * ((in.vel * elapsedTime));
            return true;
        }
    }

    return false;


}
