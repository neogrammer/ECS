#include "BusterStdProjectile.hpp"
#include <core/Config.hpp>

BusterStdProjectile::BusterStdProjectile()
 : BusterStdProjectile(0.f,0.f, 0)
{}

BusterStdProjectile::BusterStdProjectile(float inX, float inY, int dir)
	: ProjectileObj(Config::textures.get((int)Config::Textures::BulletBusterStd), sf::IntRect(0,0,14,14), Vec2(6.f, 6.f),Vec2(0.f,0.f))
{
	this->setPosition(Vec2(inX, inY));
	m_dir = ProjDir(dir);

}

BusterStdProjectile::~BusterStdProjectile()
{

}

void BusterStdProjectile::processInput()
{

}

void BusterStdProjectile::update(sf::Time l_dt)
{
	

	if (m_dir == ProjDir::East)
	{ 
		getVelocity().x = -160.f;
	}
	else if (m_dir == ProjDir::West)
	{
		getVelocity().x = 160.f;
	}

	move(getVelocity() * l_dt.asSeconds());

	// change animation


	if (spr().getPosition().x < -40.f || spr().getPosition().x > 1600.f)
	{
		alive() = false;
	}
}

void BusterStdProjectile::render(sf::RenderWindow& l_wnd)
{
	l_wnd.draw(this->spr());
}
