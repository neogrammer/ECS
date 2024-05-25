#ifndef COMPONENTS_HPP__
#define COMPONENTS_HPP__
#include "../Component.hpp"
#include <memory>
#include "../../Animation.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "../core/Config.hpp"
#include <SFML/Graphics/Color.hpp>


struct CTransform : Component
{
	Vec2 pos{ 0.f, 0.f };
	Vec2 prevPos{ 0.f, 0.f };
	Vec2 velocity{ 0.f, 0.f };

	CTransform() : Component{} {}
	CTransform(const Vec2& p, const Vec2& v) : Component{}, pos{ p }, prevPos{ p }, velocity { v } {}
	~CTransform() override final = default;
};

struct CAnimation : Component
{
	Animation animation;
	CAnimation() : Component{}, animation{} {}
	CAnimation(sf::Vector2i l_frameSize, const std::string& l_name, int l_numFrames = 1, int l_cols = 1, int l_rows = 1, sf::Vector2i l_startPos = {0,0}, float l_frameDelay = 0.1f, bool l_looping = true, bool l_isFlippedH = false, bool l_isFlippedV = false) : Component{}, animation(l_frameSize, l_name, l_numFrames, l_cols, l_rows, l_startPos, l_frameDelay, l_looping, l_isFlippedH, l_isFlippedV) {}
	CAnimation(const Animation& l_animation) : Component{}, animation(l_animation) {}
	CAnimation(const CAnimation&) = default;
	CAnimation& operator=(const CAnimation&) = default;

	CAnimation(Animation l_animation) : Component{}, animation(l_animation) {}
	~CAnimation() override final = default;
};

struct CGravity : Component
{
	Vec2 direction;
	float magnitude;

	CGravity() : Component{}, direction{ Vec2(0,0) }, magnitude{} {}
	CGravity(Vec2 l_direction, float l_magnitude) : Component{}, direction{ l_direction }, magnitude{ l_magnitude } {}
	~CGravity() override final {}
};

struct CShape : Component
{
	sf::Sprite sprite;
	sf::Texture* tex{ nullptr };
	sf::Vector2f origin{ 0.f,0.f };
	sf::Vector2i size{ 1, 1 };

	CShape() : Component{}, sprite{}, tex{}, origin{}, size{} {}
	CShape(sf::Texture* l_tex, const Vec2& l_size, const Vec2& l_origin = {0.f, 0.f})
		: Component{}
		, sprite{}
		, tex{l_tex}
		, origin{l_origin.x, l_origin.y}
		, size{(int)l_size.x, (int)l_size.y}
	{
		sprite.setTexture(*tex);
		sprite.setPosition({ 0.f,0.f });
		sprite.setOrigin({ origin.x, origin.y });
		sprite.setTextureRect({ {0,0}, {size} });
	}
	~CShape() override final = default;
};

struct CBBox : Component
{
	
	float x;
	float y;
	Vec2 size;
	Vec2 halfSize;

	CBBox() : Component{}, x{}, y{}, size{ Vec2(0,0) }, halfSize{ Vec2(0,0) } {}
	CBBox(float l_x, float l_y, const Vec2& l_size) : Component{}, x{ l_x }, y{ l_y }, size{ l_size }, halfSize{ l_size.x / 2.f, l_size.y / 2.f } {}
	~CBBox() override final = default;
};

struct CLifespan : Component
{
	int initialFrameSpan{ 100 };
	int frameSpanLeft{ 100 };
	CLifespan() : Component{} {}
	CLifespan(int frameSpan) : Component{}, initialFrameSpan{ frameSpan }
	{
		frameSpanLeft = initialFrameSpan;
	}
	~CLifespan() override final = default;
};

#endif