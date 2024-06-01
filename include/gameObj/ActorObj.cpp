#include "ActorObj.hpp"

ActorObj::ActorObj(sf::Texture& l_tex, const sf::IntRect& l_rect, const Vec2& l_bboxSize, const Vec2& l_pos)
	: GameObj(l_tex, "actor", l_rect, l_bboxSize, l_pos)
{
}

ActorObj::~ActorObj()
{
}

void ActorObj::processInput()
{
}

void ActorObj::update(sf::Time l_dt)
{
}

void ActorObj::render(sf::RenderWindow& l_wnd)
{
}
