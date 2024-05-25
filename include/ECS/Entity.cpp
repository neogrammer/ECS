#include "Entity.hpp"
#include "../core/GameEngine.hpp"
#include "../core/Config.hpp"
Entity::Entity(const std::string& l_tag, size_t l_id)
	: m_id{ l_id }, m_tag{ l_tag }, m_alive{true}
	, m_cTuple()
{}


bool Entity::isAlive() const
{
	return m_alive;
}

size_t Entity::id() const
{
	return m_id;
}

const std::string& Entity::tag()
{
	return m_tag;
}

void Entity::destroy()
{
	this->m_alive = false;
}

void Entity::setAnim(GameEngine& l_game, std::string texName, std::string animName)
{
	if (!this->getComponent<CAnimation>().has)
		this->addComponent<CAnimation>();
	

	this->getComponent<CAnimation>().animation = *l_game.getAnimation(Config::texNamelookup[texName], animName);
	
	return; 

}
