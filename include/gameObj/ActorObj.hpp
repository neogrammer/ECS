#ifndef ACTOROBJ_HPP__
#define ACTOROBJ_HPP__

#include "GameObj.hpp"

class ActorObj : public GameObj
{
public:
	ActorObj(sf::Texture& l_tex, const sf::IntRect& l_rect, const Vec2& l_bboxSize, const Vec2& l_pos = Vec2(0.f, 0.f));
	virtual ~ActorObj() override;

	virtual void processInput() override;

	virtual void update(sf::Time l_dt) override;

	virtual void render(sf::RenderWindow& l_wnd) override;
};
#endif