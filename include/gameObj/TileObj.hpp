#ifndef TILEOBJ_HPP__
#define TILEOBJ_HPP__

#include "GameObj.hpp"

class TileObj : public GameObj
{
	bool m_hasCollided{ false };
public:
	TileObj(sf::Texture& l_tex, const sf::IntRect& l_rect, const Vec2& l_pos = Vec2(0.f,0.f));
	virtual ~TileObj() override;

	virtual void processInput() override;

	virtual void update(sf::Time l_dt) override;

	virtual void render(sf::RenderWindow& l_wnd) override;

	void setCollided(bool l_collided);
};
#endif