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
	
	l_wnd.draw(spr());

	if (m_hasCollided)
	{
		sf::RectangleShape shp(sf::Vector2f((float)getTexRect().width, (float)getTexRect().height));
		shp.setFillColor(sf::Color(255, 255, 0, 255));
		shp.setOutlineColor(sf::Color::Yellow);
		shp.setPosition(sf::Vector2f(getBBox().left, getBBox().top));
		l_wnd.draw(shp);
	}

	m_hasCollided = false;
}

void TileObj::setCollided(bool l_collided)
{
	m_hasCollided = l_collided;
}
