#include "EntityManager.hpp"

size_t EntityManager::m_totalEntities = 0;

EntityManager::EntityManager()
{
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
	auto e = std::make_shared<Entity>(tag, EntityManager::m_totalEntities++);
	m_toAdd.push_back(e);
	return e;
}

EntityVec& EntityManager::getEntities()
{
	return m_entities;
}

void EntityManager::update(double l_dt)
{
	for (auto e : m_toAdd)
	{
		m_entities.push_back(e);
		m_entityMap[e->m_tag].push_back(e);
	}
	for (std::reverse_iterator ritr = m_entities.rbegin(); ritr != m_entities.rend(); ritr++)
	{
		// if e is dead, remove it from m_entities
		if (!((*ritr)->m_alive))
		{
			m_entityMap.erase((ritr+1).base()->get()->m_tag);
			m_entities.erase(++ritr.base());
		}
		// if e is dead, remove if form m_entityMap[e->tag()];
	}
	m_toAdd.clear();
}

EntityVec& EntityManager::getEntities(const std::string& tag)
{
	
	return m_entityMap[tag];
}

