#include "../core/GameEngine.hpp"
#include "../ECS/EntityManager.hpp"
#include "../core/Config.hpp"
Entity::Entity(Vec2 l_bboxSize, EntityManager& l_eMgr, const std::string& l_tag, sf::IntRect l_texFrame, size_t l_id, std::string l_texName, Vec2 l_pos)
	: eMgr{ l_eMgr }, m_id { l_id }
	, m_tag{ l_tag }, m_alive{ true }
	, m_cTuple{}, cMgr{l_bboxSize, *this, l_texFrame,  l_texName, l_pos }
{
	cMgr.has = true;
}



size_t Entity::id()
{
	return m_id;
}

bool Entity::isAlive()
{
	return m_alive;
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

		cMgr.update(l_dt);

}

void Entity::processInput()
{
	cMgr.processInput();
}


void Entity::render(sf::RenderWindow& l_wnd)
{
	cMgr.render(l_wnd);
}

