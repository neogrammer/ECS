#include <corecrt_math.h>
#ifndef VEC2_HPP__
#define VEC2_HPP__

class Vec2
{
public:
	float x, y;
	Vec2() : Vec2{ 0, 0 } {}
	Vec2(int l_x, int l_y) : Vec2{ (float)l_x,(float)l_y } {}
	Vec2(float l_x, float l_y) : x{ l_x }, y{ l_y } {}

	Vec2& scale(float s)
	{
		this->x *= s;
		this->y *= s;

		return *this;
	}

	float distance(Vec2 v)
	{
		float dx = v.x - x;
		float dy = v.y - y;
		return dy / dx;
	}

	float length()
	{
		return sqrtf(x * x + y * y);
	}

	Vec2& normalize()
	{
		this->x = this->x / length();
		this->y = this->y / length();

		return *this;
	}

	Vec2& add(Vec2 v)
	{
		this->x += v.x;
		this->y += v.y;

		return *this;
	}

	Vec2 operator+(Vec2 v)
	{
		Vec2 a = *this;
		a.x += v.x;
		a.y += v.y;

		return a;
	}
	
	Vec2& sub(Vec2 v)
	{
		this->x -= v.x;
		this->y -= v.y;

		return *this;

	}

	Vec2 operator-(Vec2 v)
	{
		Vec2 a = *this;

		a.x -= v.x;
		a.y -= v.y;

		return a;
	}
	
	Vec2& mult(Vec2 v)
	{

		this->x *= v.x;
		this->y *= v.y;

		return *this;

	}

	Vec2 operator*(Vec2 v)
	{
		Vec2 a = *this;

		a.x *= v.x;
		a.y *= v.y;

		return a;
	}
	
	Vec2& divide(Vec2 v)
	{
		this->x /= v.x;
		this->y /= v.y;

		return *this;

	}

	Vec2 operator/(Vec2 v)
	{
		Vec2 a = *this;

		a.x /= v.x;
		a.y /= v.y;

		return a;
	}

};

#endif