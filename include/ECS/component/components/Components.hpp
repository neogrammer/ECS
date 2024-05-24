#ifndef COMPONENTS_HPP__
#define COMPONENTS_HPP__
#include "../Component.hpp"
#include <SFML/Graphics/CircleShape.hpp>
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
	
	sf::CircleShape shape;
	int numSides{ 6 };
	int outlineThickness{ 1 };
	sf::Color fillCol;
	sf::Color outlineCol;
	float radius{ 3.f };
	sf::Vector2f origin{ 0.f,0.f };

	CShape() : Component{}, shape{} {}
	CShape(const Vec2& l_origin, int l_numSides, int l_outlineThickness, int l_rFill, int l_gFill, int l_bFill, int l_rOut, int l_gOut, int l_bOut, int l_radius)
		: Component{} 
		, origin{l_origin.x, l_origin.y}
		, shape(sf::CircleShape((float)l_radius, (size_t)l_numSides))
		, numSides{l_numSides}
		, outlineThickness{l_outlineThickness}
		, fillCol{ sf::Color((sf::Uint8)l_rFill, (sf::Uint8)l_gFill, (sf::Uint8)l_bFill, 255) }
		, outlineCol{ sf::Color((sf::Uint8)l_rOut, (sf::Uint8)l_gOut, (sf::Uint8)l_bOut, 255) }
		, radius{(float)l_radius}
	{
		shape.setOutlineThickness((float)outlineThickness);
		shape.setFillColor(fillCol);
		shape.setOutlineColor(outlineCol);
		shape.setPosition({ 0.f,0.f });
		shape.setOrigin({ origin.x, origin.y });
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