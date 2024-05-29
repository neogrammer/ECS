#include "Entity.hpp"
#include "../core/GameEngine.hpp"
#include "../core/Config.hpp"
Entity::Entity(const std::string& l_tag, sf::IntRect l_texFrame, size_t l_id, std::string l_texName, Vec2 l_pos)
	: m_id{ l_id }, m_tag{ l_tag }, m_alive{true}
	, m_cTuple{}, cMgr{ *this, l_texFrame,  l_texName, l_pos }
{}



size_t Entity::id()
{
	return m_id;
}

bool Entity::isAlive()
{
	return false;
}

const std::string& Entity::tag()
{
	return m_tag;
}

void Entity::destroy()
{
	this->m_alive = false;
}


void Entity::update(sf::Time l_dt)
{
	if (this->m_alive == true)
	{
		cMgr.update(l_dt);
	}
	else
	{
		
	}
}

void Entity::processInput()
{
	cMgr.processInput();
}


void Entity::render(sf::RenderWindow& l_wnd)
{
	cMgr.render(l_wnd);
}

