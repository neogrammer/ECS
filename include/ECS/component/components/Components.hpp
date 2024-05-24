#ifndef COMPONENTS_HPP__
#define COMPONENTS_HPP__
#include "../Component.hpp"

struct CTransform : Component
{
	Vec2 pos{ 0.f, 0.f };
	Vec2 velocity{ 0.f, 0.f };

	CTransform() : Component{} {}
	CTransform(const Vec2& p, const Vec2& v) : Component{}, pos { p }, velocity{ v } {}
	~CTransform() override final = default;
};

struct CName : Component
{
	const std::string name;

	CName() : Component{} {}
	CName(const std::string& l_name) : Component{}, name{ l_name } {}
	~CName() override final = default;
}; 

struct CShape : Component
{
	Vec2 pos{ 0.f, 0.f };
	Vec2 velocity{ 0.f, 0.f };

	CShape() : Component{} {}
	CShape(const Vec2& p, const Vec2& v) : Component{}, pos{ p }, velocity{ v } {}
	~CShape() override final = default;
};

struct CBBox : Component
{
	Vec2 pos{ 0.f, 0.f };
	Vec2 velocity{ 0.f, 0.f };

	CBBox() : Component{} {}
	CBBox(const Vec2& p, const Vec2& v) : Component{}, pos{ p }, velocity{ v } {}
	~CBBox() override final = default;
};

#endif