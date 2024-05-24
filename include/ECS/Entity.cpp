#include "Entity.hpp"

Entity::Entity(const std::string& l_tag, size_t l_id)
	: m_id{ l_id }, m_tag{ l_tag }, m_alive{true}
	, cTransform{nullptr}
	, cName{nullptr}
	, cShape{nullptr}
	, cBBox{nullptr}
	, cLifespan{nullptr}
{}

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
