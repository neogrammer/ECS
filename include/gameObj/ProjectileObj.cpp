#include "ProjectileObj.hpp"

ProjectileObj::ProjectileObj(sf::Texture& l_tex, const sf::IntRect& l_rect, const Vec2& l_bboxSize, const Vec2& l_pos)
	: GameObj(l_tex, "projectile", l_rect, l_bboxSize, l_pos)
{
}

ProjectileObj::~ProjectileObj()
{
}

void ProjectileObj::processInput()
{
}

void ProjectileObj::update(sf::Time l_dt)
{
}

void ProjectileObj::render(sf::RenderWindow& l_wnd)
{
}
