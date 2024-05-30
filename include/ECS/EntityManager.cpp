#include "EntityManager.hpp"
#include "Factories.hpp"

EntityManager::EntityManager()
	: m_totalEntities{ 0 }
	, m_entities{}
	, m_toAdd{}
	, m_entityMap{}
{}

std::shared_ptr<Entity> EntityManager::addEntity(Vec2 l_bboxSize, const std::string& tag, sf::IntRect l_frameRect, std::string l_texName, Vec2 l_pos)
{
	auto e = std::shared_ptr<Entity>(new Entity(l_bboxSize, *this, tag, l_frameRect, this->m_totalEntities++, l_texName, l_pos));

	m_toAdd.push_back(e);
	return e;
} 

EntityVec& EntityManager::getEntities()
{
	return m_entities;
}

void EntityManager::update(double l_dt)
{
	for (auto& e : m_toAdd)
	{
		m_entities.push_back(e);
		m_entityMap[e->tag()].push_back(e);
	}
	m_toAdd.clear();
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
}

EntityVec& EntityManager::getEntities(const std::string& tag)
{
	
	return m_entityMap[tag];
}

std::shared_ptr<Entity> EntityManager::getEntity(size_t l_id)
{
	for (auto& e : m_entities)
	{
		if (e->id() == l_id)
			return e;
	}
	return nullptr;
}

size_t EntityManager::totalEntities() const
{
	return m_totalEntities;
}

std::shared_ptr<Entity> EntityManager::makeStartingEntities(std::string l_scene)
{
	std::shared_ptr<Entity> ptr;

	
	if (l_scene == "play")
	{
		m_entities.clear();
		m_toAdd.clear();
		// dont add the player to the bucket, he is special, return it
		auto p = Make::Player(*this,  this->m_totalEntities++);
		auto n = m_entityMap.insert(std::pair( "player",std::vector<std::shared_ptr<Entity> >{}));
		n.first->second.clear();
		n.first->second.push_back(p);

		// make other entities then add them to the buckets for starting game state
		m_entities.push_back(p);	
		ptr = p;

		calledMakeStart = true;
	}
	else
	{

		return nullptr;
	}
	return ptr;
}

