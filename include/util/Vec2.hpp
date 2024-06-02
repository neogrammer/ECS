#ifndef VEC2_HPP__
#define VEC2_HPP__

#include <corecrt_math.h>
#include <SFML/System/Vector2.hpp>
class Vec2
{
public:
	float x{}, y{};
	Vec2();
	Vec2(int l_x, int l_y);
	Vec2(float l_x, float l_y);

	bool operator==(sf::Vector2f v);
	bool operator==(const sf::Vector2f& v) const;
	bool operator==(Vec2 v);
	bool operator==(const Vec2& v) const;

	// Scale the vector in place
	void scale(float scaleFactor); 

	// Return a scaled copy of the vector without modifying the original
	Vec2 scaled(float scaleFactor) const; 

	float dot(const Vec2& v1, const Vec2& v2);
	float dot(const Vec2& v1, float x, float y); 
	float dot(float x1, float y1, float x2, float y2);

	float magnitude() const;
	void normalize();
	Vec2 normalized() const;

	Vec2& sub(Vec2 v);
	Vec2& add(Vec2 v);
	Vec2& mult(Vec2 v);
	Vec2& divide(Vec2 v);
	Vec2& sub(const Vec2& v);
	Vec2& add(const Vec2& v);
	Vec2& mult(const Vec2& v);	
	Vec2& divide(const Vec2& v);

	Vec2& operator/(const Vec2& v);
	Vec2& operator*(const Vec2& v);
//	Vec2& operator-(const Vec2& v);
	Vec2& operator+(const Vec2& v);
    Vec2& operator+=(const Vec2& v);
    Vec2& operator-=(const Vec2& v);
    friend Vec2& operator*=(Vec2& v, float f)
    {
        v.x *= f;
        v.y *= f;
        return v;
    }


    // Overload operator+ for Vec2 + float
    friend Vec2 operator+(const Vec2& v, float f) {
        return Vec2(v.x + f, v.y + f);
    }

    // Overload operator+ for float + Vec2
    friend Vec2 operator+(float f, const Vec2& v) {
        return Vec2(f + v.x, f + v.y);
    }

    // Overload operator+ for float + Vec2
    friend Vec2 operator+(const Vec2& v, const Vec2& v2) {
        return Vec2(v.x + v2.x, v.y + v2.y);
    }

    // Overload operator- for Vec2 - float
    friend Vec2 operator-(const Vec2& v, float f) {
        return Vec2(v.x - f, v.y - f);
    }
    // Overload operator- for Vec2 - float
    friend Vec2 operator-(Vec2 v, Vec2 v2) {
        return Vec2(v.x - v2.x, v.y - v2.y);
    }

    //// Overload operator- for Vec2 - float
    //friend Vec2 operator-(Vec2& v, const Vec2& v2) {
    //    return Vec2(v.x - v2.x, v.y - v2.y);
    //}

    // Overload operator- for float - Vec2
    friend Vec2 operator-(float f, const Vec2& v) {
        return Vec2(f - v.x, f - v.y);
    }

    // Overload operator* for Vec2 * float
    friend Vec2 operator*(const Vec2& v, float f) {
        return Vec2(v.x * f, v.y * f);
    }

    // Overload operator* for float * Vec2
    friend Vec2 operator*(float f, const Vec2& v) {
        return Vec2(f * v.x, f * v.y);
    }

    // Overload operator/ for Vec2 / float
    friend Vec2 operator/(const Vec2& v, float f) {
        if (f == 0.f) {
            return v.collapse ? Vec2(0.f, 0.f) : v;
        }
        return Vec2(v.x / f, v.y / f);
    }

    // Overload operator/ for float / Vec2
    friend Vec2 operator/(float f, const Vec2& v) {
        if (v.x == 0.f || v.y == 0.f) {
            return v.collapse ? Vec2(0.f, 0.f) : v;
        }
        return Vec2(f / v.x, f / v.y);
    }

private:
    bool collapse; // Control whether to collapse the result to zero vector
};

#endif