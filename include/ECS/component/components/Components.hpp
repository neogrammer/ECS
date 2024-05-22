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

#endif