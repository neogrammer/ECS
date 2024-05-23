#ifndef ENTITYMANAGER_HPP__
#define ENTITYMANAGER_HPP__
#include "Entity.hpp"
#include <vector>
#include <map>
#include <string>
#include "component/components/Components.hpp"

typedef std::vector<std::shared_ptr<Entity> > EntityVec;
typedef std::map<std::string, EntityVec> EntityMap;

class EntityManager
{
	EntityVec m_entities;
	EntityVec m_toAdd;
	EntityMap m_entityMap;	
	static size_t m_totalEntities;
public:
	EntityManager();
	void update(double l_dt);
	std::shared_ptr<Entity> addEntity(const std::string& tag);
	EntityVec& getEntities();
	EntityVec& getEntities(const std::string& tag);
};

#endif