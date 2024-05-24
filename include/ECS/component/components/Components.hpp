#ifndef COMPONENTS_HPP__
#define COMPONENTS_HPP__
#include "../Component.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

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

struct CName : Component
{
	const std::string name{"Default"};

	CName() : Component{} {}
	CName(const std::string& l_name = "Default") : Component{}, name{l_name} {}
	~CName() override final = default;
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
	// not used
	int side{};

	CBBox() : Component{} {}
	CBBox(int side) : Component{}, side{ side } {}
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