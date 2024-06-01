#include "Vec2.hpp"

Vec2::Vec2() : Vec2{ 0, 0 } {}
Vec2::Vec2(int l_x, int l_y) : Vec2{ (float)l_x,(float)l_y } {}
Vec2::Vec2(float l_x, float l_y) : x{ l_x }, y{ l_y }, collapse{ false } {}

bool Vec2::operator==(sf::Vector2f v)
{
	return false;
}


bool Vec2::operator==(const sf::Vector2f& v) const
{
	return false;
}

bool Vec2::operator==(Vec2 v)
{
	if (this->x == v.x && this->y == v.y) return true;
	else
		return false;

}

bool Vec2::operator==(const Vec2& v) const
{
	return false;
}
// Scale the vector in place
void Vec2::scale(float scaleFactor) {
	x *= scaleFactor;
	y *= scaleFactor;
}

// Return a scaled copy of the vector without modifying the original
Vec2 Vec2::scaled(float scaleFactor) const {
	return Vec2(x * scaleFactor, y * scaleFactor);
}
// Define a function to compute the dot product of two Vec2 vectors
float Vec2::dot(const Vec2& v1, const Vec2& v2) {
	return v1.x * v2.x + v1.y * v2.y;
}

// Overload the dot function to support different argument types
float Vec2::dot(const Vec2& v1, float x, float y) {
	return v1.x * x + v1.y * y;
}

float Vec2::dot(float x1, float y1, float x2, float y2) {
	return x1 * x2 + y1 * y2;
}


// Normalize the vector in-place
void Vec2::normalize() {
	float length = sqrtf(x * x + y * y);
	if (length != 0.0f) {
		x /= length;
		y /= length;
	}
}

// Return a normalized copy of the vector without modifying the original
Vec2 Vec2::normalized() const {
	Vec2 result = *this;
	result.normalize();
	return result;
}
// Compute the magnitude of the vector
float Vec2::magnitude() const {
	return sqrtf(x * x + y * y);
}


Vec2& Vec2::add(Vec2 v)
{
	this->x += v.x;
	this->y += v.y;

	return *this;
}

Vec2& Vec2::sub(Vec2 v)
{
	this->x -= v.x;
	this->y -= v.y;

	return *this;

}



Vec2& Vec2::mult(Vec2 v)
{

	this->x *= v.x;
	this->y *= v.y;

	return *this;

}


Vec2& Vec2::divide(Vec2 v)
{
	if(v.x == 0.f || v.y == 0.f)
	{
		return *this;
	}
	this->x /= v.x;
	this->y /= v.y;

	return *this;

}

Vec2& Vec2::sub(const Vec2& v)
{
	this->x -= v.x;
	this->y -= v.y;

	// TODO: insert return statement here
	return *this;
}

Vec2& Vec2::add(const Vec2& v)
{
	this->x += v.x;
	this->y += v.y;
	// TODO: insert return statement here
	return *this;
}

Vec2& Vec2::mult(const Vec2& v)
{
	this->x *= v.x;
	this->y *= v.y;
	// TODO: insert return statement here
	return *this;
}

Vec2& Vec2::divide(const Vec2& v)
{
	if (v.x == 0.f || v.y == 0.f)
	{
		return *this;
	}
	this->x /= v.x;
	this->y /= v.y;
	// TODO: insert return statement here
	return *this;
}



Vec2& Vec2::operator/(const Vec2& v)
{
	if (v.x == 0.f || v.y == 0.f)
	{
		return *this;
	}
	this->x /= v.x;
	this->y /= v.y;
	// TODO: insert return statement here
	return *this;
}

Vec2& Vec2::operator*(const Vec2& v)
{

	this->x *= v.x;
	this->y *= v.y;
	// TODO: insert return statement here
	return *this;
	// TODO: insert return statement here
}

//Vec2& Vec2::operator-(const Vec2& v)
//{
//	this->x -= v.x;
//	this->y -= v.y;
//	// TODO: insert return statement here
//	return *this;
//	// TODO: insert return statement here
//}

Vec2& Vec2::operator+(const Vec2& v)
{
	this->x += v.x;
	this->y += v.y;
	// TODO: insert return statement here
	return *this;
	// TODO: insert return statement here
}

Vec2& Vec2::operator+=(const Vec2& v)
{
	this->x = this->x + v.x;
	this->y = this->y + v.y;

	return *this;
}


Vec2& Vec2::operator-=(const Vec2& v)
{
	this->x = this->x - v.x;
	this->y = this->y - v.y;

	return *this;
}

Vec2 scale(Vec2 v, float s)
{
	return Vec2();
}

float dot(Vec2 v, const Vec2& v2)
{
	return 0.0f;
}
