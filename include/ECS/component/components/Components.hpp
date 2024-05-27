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