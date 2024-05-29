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

struct cRigidBody : Component
{
	Vec2 size;
	Vec2 halfSize{};
	Vec2 center;
	Vec2 vel;
	Vec2 prevPos;

	bool isDynamic;

	cRigidBody() : Component{}, size{}, center{}, vel{}, prevPos{}, halfSize{}, isDynamic{} {}
	cRigidBody(bool l_dynamic, Vec2 l_size, Vec2 l_vel, Vec2 l_center) : Component{}, size{l_size}, center{ l_center }, vel{l_vel}, prevPos{l_center}, isDynamic{l_dynamic} {halfSize = Vec2(size / 2.f);}

	void update(sf::Time l_dt)
	{
		// copy its current position for next frame incase the prevPos is needed for any calculations
		prevPos = center;
		if (isDynamic)
		{
			// if has collided, it will already be adjusted to the right spot and velocity updated to 0 in the correct direction so this is always safe to call
			center += vel * l_dt.asSeconds();
		}
	}

	static Vec2 topLeft(Entity&);
	static Vec2 bottomRight(Entity&);
};


struct cAnimation : Component
{
	bool wasSetupRan{ false };

	std::shared_ptr<Animation> currAnimation;
	std::vector<std::string> animNames;
	std::map<std::string, std::string> animTextureMap;
	std::map<std::string, std::shared_ptr<Animation> > animations;
	cAnimation() : Component{}, wasSetupRan{false}, currAnimation{}, animNames{}, animTextureMap{}, animations{} {
		animNames.clear();
		animTextureMap.clear();
		animations.clear();
	}
	//cAnimation(sf::Vector2i l_frameSize, const std::string& l_name, int l_numFrames = 1, int l_cols = 1, int l_rows = 1, sf::Vector2i l_startPos = {0,0}, float l_frameDelay = 0.1f, bool l_looping = true, bool l_isFlippedH = false, bool l_isFlippedV = false) : Component{}, animation(l_frameSize, l_name, l_numFrames, l_cols, l_rows, l_startPos, l_frameDelay, l_looping, l_isFlippedH, l_isFlippedV) {}
	explicit cAnimation(std::shared_ptr<Animation> l_animation) : Component{}, wasSetupRan{false}, currAnimation {}, animTextureMap{}, animations{} {}
	cAnimation(const cAnimation&) = default;
	cAnimation& operator=(const cAnimation&) = default;
	~cAnimation() override final = default;
	void update(sf::Time l_dt)
	{
		currAnimation->update(l_dt);
	}

	static void setup(Entity& e, std::string l_filename);
	static void changeAnimation(Entity& e, std::string l_animName);
	static std::vector<std::string> getAnimNames(Entity& e);
	
};

struct cGravity : Component
{
	Vec2 direction;
	float magnitude;

	cGravity() : Component{}, direction{ Vec2(0,0) }, magnitude{} {}
	cGravity(Vec2 l_direction, float l_magnitude) : Component{}, direction{ l_direction }, magnitude{ l_magnitude } {}
	~cGravity() override final {}
};

struct cLifespan : Component
{
	int initialFrameSpan{ 100 };
	int frameSpanLeft{ 100 };
	cLifespan() : Component{} {}
	cLifespan(int frameSpan) : Component{}, initialFrameSpan{ frameSpan }
	{
		frameSpanLeft = initialFrameSpan;
	}
	~cLifespan() override final = default;
};

#endif