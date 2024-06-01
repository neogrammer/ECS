#include "TileObj.hpp"

TileObj::TileObj(sf::Texture& l_tex, const sf::IntRect& l_rect, const Vec2& l_pos)
	: GameObj(l_tex, "tile", l_rect, Vec2(0.f,0.f), l_pos)
{
}

TileObj::~TileObj()
{
}

void TileObj::processInput()
{
}

void TileObj::update(sf::Time l_dt)
{
}

void TileObj::render(sf::RenderWindow& l_wnd)
{
}
