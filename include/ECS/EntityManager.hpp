#ifndef ENTITYMANAGER_HPP__
#define ENTITYMANAGER_HPP__
#include "Entity.hpp"
#include <vector>
#include <map>
#include <memory>
#include <utility>
#include <string>
#include "component/components/Components.hpp"
#include "../core/Config.hpp"
#include "../util/Vec2.hpp"
#include <SFML/Graphics/Rect.hpp>

class EntityManager
{
	EntityVec m_entities{};
	EntityVec m_toAdd{};
	EntityMap m_entityMap{};
	size_t m_totalEntities;

public:
	bool calledMakeStart{ false };

	EntityManager();
	void update(double l_dt);
	std::shared_ptr<Entity> addEntity(const std::string& tag, sf::IntRect l_frameRect, std::string l_texName, Vec2 l_pos = Vec2(0.0f,0.0f));
	EntityVec& getEntities();
	EntityVec& getEntities(const std::string& tag);
	std::shared_ptr<Entity> getEntity(size_t l_id);
	size_t totalEntities() const;
	// returns the player entity, and does not add it to the managed buckets
	std::shared_ptr<Entity> makeStartingEntities(std::string l_scene);
};

#endif